#ifndef BSTREE_H
#define BSTREE_H

/**
 * Classe generica che implementa un albero binario di ricerca.
 * 
 * @brief Albero binario di ricerca
 * 
 * @param T tipo del dato
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
        node *left; // figlio sinistro del nodo
        node *right; // figlio destro del nodo

        /**
         * Costruttore di default
        */
        node(): left(nullptr), right(nullptr) {}

        /**
         * Costruttore secondario che inizializza il nodo
         * @param v valore del dato
        */
        node(const T &v): value(v), left(nullptr), right(nullptr) {}

        /**
         * Costruttore secondario che inizializza il nodo
         * @param v valore del dato
         * @param n puntatore al figlio sinistro
        */
        node(const T &v, node *n): value(v), left(n), right(nullptr) {}
        
        /**
         * Costruttore secondario che inizializza il nodo
         * @param v valore del dato
         * @param n1 puntatore al figlio sinistro
         * @param n2 puntatore al figlio destro
        */
        node(const T &v, node *n1, node *n2): value(v), left(n1), right(n2) {}

        /**
         * Distruttore
        */
        ~node() {
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

public:
    
    /**
     * Costruttore di default 
    */
    binary_search_tree(): _root(nullptr), _size(0) {}

    /**
     * Distruttore
    */
    ~binary_search_tree(){}

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
        node *curr = _root;

        while(curr != nullptr){

            if(_eql(curr->value, value))
                return true;
            
            if(_conf(curr-> value, value)) 
                curr = curr->left;
            else
                curr = curr->right;

        }
        return false;
    }

    /**
     * Inserisce un elemento nell'albero nella posizione opportuna.
     * I confronti necessari sono eseguiti mediante il funtore di confronto.
     * 
     * @param value valore da inserire
     * 
     * @throw eccezione di allocazione di memoria
    */
    void add(const T& value){
        node *tmp = new node(value);

        if(_root == nullptr){
            _root = tmp;
            _size++;
            return;
        }

        node *parent = _root;
        node *curr = _root;
        
        while(curr != nullptr){

            if(_eql(curr->value, value))
                return;
            
            parent = curr;
            if(_conf(curr->value, value))
                curr = curr->left;
            else
                curr = curr->right;

        }
        
        if(_conf(parent->value, value))
            parent->left = tmp;
        else
            parent->right = tmp;
        
        _size++;

    }

};

#endif