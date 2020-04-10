#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include <iostream>

/**
 * @brief Tentativo di copia dell'albero fallita.
 * 
 * @return Eccezione
 */
class NoTreeCopiedException: public std::exception {
  virtual const char* what() const throw() {
    return "errore nella copia dell'albero";
  }
};

/**
 * @brief Tentativo di creazione del nodo fallito
 * 
 * @return Eccezione
 */
class NoNodeCreatedException: public std::exception {
  virtual const char* what() const throw() {
    return "errore nella creazione del nodo";
  }
};

/**
 * Classe generica che implementa un albero binario di ricerca.
 * 
 * @brief Albero binario di ricerca
 * 
 * @param T tipo del dato
 * @param C funtore di comparazione
 * @param E funtore di uguaglianza
*/
template <typename T, typename C, typename E>
class binary_search_tree {

private:
    
    /**
     * Struttura di supporto interna che implementa un nodo dell'albero
     * 
     * @brief Nodo dell'albero
    */
    struct node {
        
        T value; // valore del dato inserito
        node *parent; // padre del nodo
        node *left; // figlio sinistro del nodo
        node *right; // figlio destro del nodo

        /**
         * Costruttore di default
        */
        node(): parent(nullptr), left(nullptr), right(nullptr) {}

        /**
         * Costruttore secondario che inizializza il nodo
         * 
         * @param v valore del dato
        */
        node(const T &v): value(v), parent(nullptr), left(nullptr), right(nullptr) {}
        
        /**
         * Costruttore secondario che inizializza il nodo
         * 
         * @param v valore del dato
         * @param p puntatore al padre
         * @param n1 puntatore al figlio sinistro
         * @param n2 puntatore al figlio destro
        */
        node(const T &v, node *p, node *n1, node *n2): value(v), parent(n1), left(n1), right(n2) {}

        /**
         * Distruttore
        */
        ~node() {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
        }

    };

    node *_root; // puntatore alla radice dell'albero
    unsigned int _size; // numero di nodi nell'albero 

    C _conf; // oggetto funtore per il confronto
    E _eql; // oggetto funtore per l'uguaglianza

    /**
     * Funzione helper per la rimozione ricorsiva dei nodi
     * 
     * @param n nodo da rimuovere
    */
    void clear_helper(node *n){
        if(n != nullptr){
            clear_helper(n->left);
            clear_helper(n->right);
            delete n;
            _size--;
            n = nullptr;
        }
    }

    /**
     * Funzione helper per la copia ricorsiva dei nodi
     * 
     * @param to_copy nodo da copiare
     * @param parent padre del nodo copia 
     * 
     * @throw eccezione sulla creazione del nodo
    */
    node * copy_helper(const node *to_copy, node *parent = nullptr) const{

        if(to_copy == nullptr){
            return nullptr;
        }
        
        node *copy;
        try{
            copy = new node(to_copy->value);
        }
        catch(...){
            throw NoNodeCreatedException();
        }
              
        copy->parent = parent;
        copy->left  = copy_helper(to_copy->left, copy);
        copy->right = copy_helper(to_copy->right, copy);

        return copy;        
    }

    /**
     * Funzione helper per la conta ricorsiva dei nodi
     * 
     * @param to_count nodo da usare come radice nella conta
    */
    int count_helper(const node *to_count) const{

        if(to_count == nullptr){
            return 0;
        }
        
        int l = count_helper(to_count->left);
        int r = count_helper(to_count->right);

        return l + r + 1;

    }

public:
    
    /**
     * Costruttore di default 
    */
    binary_search_tree(): _root(nullptr), _size(0) {}

    /**
     * Costruttore di copia
     * 
     * @param other albero da copiare
     * 
     * @throw eccezione di copiatura dell'albero
    */
    binary_search_tree(const binary_search_tree &other) : _root(nullptr), _size(0) {

        try {
            _root = copy_helper(other._root);
            _size = other._size;
        }
        catch(...) {
            clear();
            throw NoTreeCopiedException();
        }

    }

    /**
     * Operatore di assegnamento
     * 
     * @param other albero da copiare
     * 
     * @return reference a this
     * 
     * @throw eccezione di allocazione di memoria
    */
    binary_search_tree &operator=(const binary_search_tree &other) {
        if(this != &other) {
            binary_search_tree tmp(other);
            std::swap(_root,tmp._root);
            std::swap(_size,tmp._size);
        }
        return *this;
	}

    /**
     * Distruttore
    */
    ~binary_search_tree(){
        clear();
    }

    /**
     * Cancella il contenuto dell'albero
    */
    void clear(){
        clear_helper(_root);
        _root = nullptr;
    }

    /**
     * Ritorna il numero di elementi nell'albero
     * 
     * @return numero di elementi presenti nell'albero
    */
    unsigned int size() const {
        return _size;
    }

    /**
     * Determina se esiste un determinato elemento nell'albero.
     * L'uguaglianza e il confronto sono definiti mediante i relativi funtori.
     * 
     * @param value valore da cercare
     * 
     * @return true se esiste l'elemento, false altrimenti
    */
    bool find(const T &value) const {
        const node *curr = _root;

        while(curr != nullptr){

            if(_eql(curr->value, value))
                return true;
            
            if(_conf(value, curr->value)) 
                curr = curr->left;
            else
                curr = curr->right;

        }
        return false;
    }

    /**
     * Restituisce un determinato sottoalbero dell'albero principale.
     * L'uguaglianza e il confronto sono definiti mediante i relativi funtori.
     * 
     * @param value valore che sarà radice del sottoalbero
     * 
     * @return il sottoalbero ricercato
     * 
     * @throw eccezione di copiatura dell'albero
    */
    binary_search_tree subtree(const T &value) const {
        node *curr = _root;
        binary_search_tree<T,C,E> tmp;

        while(curr != nullptr){

            if(_eql(curr->value, value)){

                try{
                    tmp._root = copy_helper(curr);
                    tmp._size = count_helper(curr);
                }
                catch(...){
                    tmp.clear();
                    throw NoTreeCopiedException();
                }

                return tmp;

            }
            
            if(_conf(value, curr->value)) 
                curr = curr->left;
            else
                curr = curr->right;

        }

        return tmp;
    }

    /**
     * Inserisce un elemento nell'albero nella posizione opportuna.
     * I confronti necessari sono eseguiti mediante il funtore di confronto.
     * 
     * @param value valore da inserire
     * 
     * @throw eccezione sulla creazione del nodo
    */
    void add(const T& value){
        
        node *tmp;
        try{
            tmp = new node(value);
        }
        catch(...){
            throw NoNodeCreatedException();
        }

        if(_root == nullptr){
            _root = tmp;
            _size++;
            return;
        }

        node *prec = _root;
        node *curr = _root;
        
        while(curr != nullptr){

            if(_eql(curr->value, value)){
                delete tmp;
                return;
            }
            
            prec = curr;
            if(_conf(value, curr->value))
                curr = curr->left;
            else
                curr = curr->right;

        }
        
        tmp->parent = prec;

        if(_conf(value, prec->value))
            prec->left = tmp;
        else
            prec->right = tmp;

        _size++;

    }

    /**
     * Iteratore costante dell'albero
     * 
     * @brief Iteratore costante dell'albero 
    */
    class const_iterator{

    private:
        const node *_n;

        friend class binary_search_tree; 
 
        /**
         * Costruttore privato di inizializzazione 
         * 
         * Usato dalla classe container tipicamente nei metodi begin e end
        */
        const_iterator(const node *n) : _n(n) { }

        /**
         * Restituisce il successivo nodo tramite l'ordinamento scelto
        */
        const node* get_next(const node *n){

			// se posso andare a destra ci vado. e poi tutto a sinistra.
            if(n->right != nullptr){
                n = n->right;
                while(n->left != nullptr){
                    n = n->left;
                }

                return n;
            }

            // altrimenti 
            while(true){
                if(n->parent == nullptr){
                    n = nullptr;
                    return n;
                }
                if(n->parent->left == n){
                    n = n->parent;
                    return n;
                }
                n = n->parent;
            }

            return n;
        }

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const T*                  pointer;
        typedef const T&                  reference;

        const_iterator() : _n(nullptr) {}

        const_iterator(const const_iterator &other) : _n(other._n) {}

        const_iterator& operator=(const const_iterator &other) {
			_n = other._n;
			return *this;
		}

        ~const_iterator() {}

        /**
         * Ritorna il dato riferito dall'iteratore (dereferenziamento)
        */ 
        reference operator*() const {
            return _n->value;
        }

        /**
         * Ritorna il puntatore al dato riferito dall'iteratore
        */
        pointer operator->() const {
            return &(_n->value);
        }

        /**
         * Operatore di iterazione post-incremento
        */
        const_iterator operator++(int) {
			const_iterator tmp(*this);
			
            _n = get_next(_n);

            return tmp;

        }

        /**
         * Operatore di iterazione pre-incremento
        */
        const_iterator& operator++() {
            
            _n = get_next(_n);

			return *this;

        }

        /**
         * Uguaglianza
        */
        bool operator==(const const_iterator &other) const {
            return (_n == other._n);
        }

        /**
         * Diversità
        */
        bool operator!=(const const_iterator &other) const {
            return (_n != other._n);
        }

    };
    
    /**
     * Ritorna l'iteratore all'inizio della sequenza dati
     * 
     * @return iteratore all'inizio della sequenza
    */
    const_iterator begin() const {
        const node *curr;
        
        curr = _root;
        if(curr == nullptr){
            return const_iterator(curr);
        }

        while(curr->left != nullptr){
            curr = curr->left;
        }

        return const_iterator(curr);
    }

    /**
     * Ritorna l'iteratore alla fine della sequenza dati
     * 
     * @return iteratore alla fine della sequenza
    */
    const_iterator end() const {
        return const_iterator(nullptr);

        const node *curr;
        
        curr = _root;
        if(curr == nullptr){
            return const_iterator(curr);
        }

        while(curr->right != nullptr){
            curr = curr->right;
        }

        return const_iterator(curr);
    }
    

};

/**
 * Overload dell'operatore di stream << per un binary_search_tree
 * 
 * @brief Operatore <<
 * 
 * @param T tipo del dato
 * @param C funtore di comparazione
 * @param E funtore di uguaglianza
 * 
 * @return puntatore allo stream
*/
template <typename T, typename C, typename E>
std::ostream &operator<<(std::ostream &os, const binary_search_tree<T,C,E> &bstree) {

    typename binary_search_tree<T,C,E>::const_iterator i,ie;

    i = bstree.begin();
    ie = bstree.end();

    while(i!=ie) {
        os << *i << " ";
        i++;
    }

    return os;
}

/**
 * Funzione globale printIF.
 * Stampa a schermo l'elenco dei valori dell'albero che soddisfano un predicato.
 * 
 * @brief Stampa i valori dell'albero che soddisfano un predicato.
 * 
 * @param T tipo del dato
 * @param C funtore di comparazione
 * @param E funtore di uguaglianza
 * @param P funtore del predicato 
 * @param bstree albero di tipo T
 * @param pred predicato
*/
template <typename T, typename C, typename E, typename P>
void printIF(const binary_search_tree<T,C,E> &bstree, P pred) {

    typename binary_search_tree<T,C,E>::const_iterator i,ie;

	i = bstree.begin();
	ie = bstree.end();
	
	while(i!=ie) {
		if(pred(*i)) {
			std::cout << *i << std::endl;
		}
		++i;
	}

}

#endif