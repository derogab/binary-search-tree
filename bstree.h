#ifndef BSTREE_H
#define BSTREE_H

/**
 * Classe generica che implementa un albero binario di ricerca.
 * 
 * @brief Albero binario di ricerca
 * 
 * @param T tipo del dato
*/
template <typename T>
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

};

#endif