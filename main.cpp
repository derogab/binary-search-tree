#include <iostream>
#include "bstree.h"

/**
 * Struct point che implementa un punto 2D.
 * 
 * @brief Struct point che implementa un punto 2D.
*/
struct point {
    int x; ///< coordinata x del punto
    int y; ///< coordinata y del punto

    point(int xx, int yy) : x(xx), y(yy) {}
};

/**
 * Funtore per l'uguaglianza tra interi.
 * 
 * @brief Funtore per l'uguaglianza tra interi.
*/
struct equal_int {
	bool operator()(const int a, const int b) const {
		return (a==b);
	} 
};

/**
 * Funtore per il confronto tra interi.
 * 
 * @brief Funtore per il confronto tra interi.
*/
struct compare_int {
	bool operator()(const int a, const int b) const {
		return (a < b);
	} 
};

/**
 * Funtore per l'uguaglianza tra stringhe.
 * 
 * @brief Funtore per l'uguaglianza tra stringhe.
*/
struct equal_string {
	bool operator()(const std::string &a, const std::string &b) const {
		return (a==b);
	} 
};

/**
 * Funtore per il confronto tra stringhe.
 * La valutazione è fatta sulla lunghezza.
 * Ritorna true se la prima stringa è più corta della seconda.
 * 
 * @brief Funtore per il confronto tra stringhe.
*/
struct compare_string {
	bool operator()(const std::string &a, const std::string &b) const {
		return (a.size()<b.size());
	} 
};

/**
 * Funtore per il confronto di uguaglianza tra due punti.
 * Ritorna true se p1.x != p2.x.
 * 
 * @brief Funtore per il confronto di due punti.
*/
struct equal_point {
    bool operator()(const point &p1, const point &p2) const {
        return (p1.x==p2.x) && (p1.y==p2.y);
    } 
};

/**
 * Funtore per il confronto di due punti. 
 * Ritorna true se p1.x < p2.x.
 * 
 * @brief Funtore per il confronto di due punti.
*/
struct compare_point {
    bool operator()(const point &p1, const point &p2) const {
        return (p1.x<p2.x);
    } 
};

/**
 * Ridefinizione dell'operatore di stream << per un point.
 * Necessario per l'operatore di stream della classe binary_search_tree.
*/
std::ostream &operator<<(std::ostream &os, const point &p) {
	std::cout << "(" << p.x << "," << p.y << ")";
	return os;
}

/**
 * Predicato di cofronto del valore con 3.
 * La valutazione è fatta sul numero intero.
 * Ritorna true se il valore è maggiore di 3.
 * 
 * @brief Predicato per il confronto dei valori.
*/
struct is_plus_than_3 {
    bool operator()(int value) const {
        return value > 3;
    }
};

/**
 * Predicato di cofronto parità del valore.
 * La valutazione è fatta sul numero intero.
 * Ritorna true se il valore è pari, false altrimenti.
 * 
 * @brief Predicato per il confronto parità del valore
*/
struct is_even {
    bool operator()(int value) const {
        return value % 2 == 0;
    }
};

void test_metodi_fondamentali() {
    std::cout << "******** Test sui metodi fondamentali ********" << std::endl;

	binary_search_tree<int, compare_int, equal_int> bstree;

	bstree.add(1);
	bstree.add(2);
	bstree.add(0);

	std::cout << "stampa di bstree dopo inserimenti" << std::endl << bstree << std::endl;

	binary_search_tree<int, compare_int, equal_int> bstree2(bstree);

	std::cout << "stampa di bstree2" << std::endl << bstree2 << std::endl;

	binary_search_tree<int, compare_int, equal_int> bstree3;

	bstree3 = bstree;	

	std::cout << "stampa di bstree3" << std::endl << bstree3 << std::endl;

	bstree.clear();
	bstree2.clear();
	bstree3.clear();

}


void test_uso() {
    std::cout << "******** Test sull'uso ********" << std::endl;

	binary_search_tree<int, compare_int, equal_int> int_bstree;
	binary_search_tree<std::string, compare_string, equal_string> string_bstree;
	binary_search_tree<point, compare_point, equal_point> point_bstree;

	// Funzione di inserimento

	int_bstree.add(1);
	int_bstree.add(2);
	int_bstree.add(0);
	int_bstree.add(1);
	int_bstree.add(3);
	int_bstree.add(78);
	int_bstree.add(4);
	int_bstree.add(104);
	int_bstree.add(45);

	string_bstree.add("aaa");
	string_bstree.add("bbbb");
	string_bstree.add("c");
	string_bstree.add("dd");

	point_bstree.add(point(1,1));
	point_bstree.add(point(1,2));
	point_bstree.add(point(2,7));
	point_bstree.add(point(0,0));
	point_bstree.add(point(5,4));
	
	std::cout << "stampa di int_bstree dopo inserimenti" << std::endl << int_bstree << std::endl;
	std::cout << "stampa di string_bstree dopo inserimenti" << std::endl << string_bstree << std::endl;
	std::cout << "stampa di point_bstree dopo inserimenti" << std::endl << point_bstree << std::endl;

	// Iteratore
	typename binary_search_tree<int, compare_int, equal_int>::const_iterator i1,ie1;

	i1 = int_bstree.begin();
	ie1 = int_bstree.end();

	std::cout << "ristampa di int_bstree con iteratore" << std::endl;
	while(i1!=ie1) {
		std::cout << *i1 << " ";
		++i1;
	}
	std::cout << std::endl;

	typename binary_search_tree<std::string, compare_string, equal_string>::const_iterator i2,ie2;

	i2 = string_bstree.begin();
	ie2 = string_bstree.end();

	std::cout << "ristampa di string_bstree con iteratore" << std::endl;
	while(i2!=ie2) {
		std::cout << *i2 << " ";
		++i2;
	}
	std::cout << std::endl;

	typename binary_search_tree<point, compare_point, equal_point>::const_iterator i3,ie3;

	i3 = point_bstree.begin();
	ie3 = point_bstree.end();

	std::cout << "ristampa di point_bstree con iteratore" << std::endl;
	while(i3!=ie3) {
		std::cout << *i3 << " ";
		++i3;
	}
	std::cout << std::endl;
	
	// Funzione di sottoalbero
	binary_search_tree<int, compare_int, equal_int> int_subbstree = int_bstree.subtree(78);
	std::cout << "stampa di int_subbstree = bstree.subtree(78)" << std::endl << int_subbstree << std::endl;

	binary_search_tree<std::string, compare_string, equal_string> string_subbstree = string_bstree.subtree("dd");
	std::cout << "stampa di string_subbstree = bstree.subtree(78)" << std::endl << string_subbstree << std::endl;

	binary_search_tree<point, compare_point, equal_point> point_subbstree = point_bstree.subtree(point(1,2));
	std::cout << "stampa di point_subbstree = bstree.subtree(78)" << std::endl << point_subbstree << std::endl;

	// Funzione globale printIF
	std::cout << "ristampa di int_bstree completo" << std::endl << int_bstree << std::endl;

	is_plus_than_3 ipt3;
	
	std::cout << "stampa elenco di valori in int_bstree che rispettano predicato is_plus_than_3" << std::endl;
	printIF<int, compare_int, equal_int, is_plus_than_3>(int_bstree, ipt3);

	is_even even;
	
	std::cout << "stampa elenco di valori in int_bstree che rispettano predicato is_even" << std::endl;
	printIF<int, compare_int, equal_int, is_even>(int_bstree, even);


	// Pulizia
	int_bstree.clear();
	string_bstree.clear();
	point_bstree.clear();	
	int_subbstree.clear();
	string_subbstree.clear();
	point_subbstree.clear();

}

/**
 * Test sull'albero di interi
*/
void test_tree_int(binary_search_tree<int, compare_int, equal_int> &other) {
    std::cout << "******** Test sull'albero di interi ********" << std::endl;

    std::cout << "Insertimento dei valori 6, 2, 7, 1, 4, 9, 3, 5, 8" << std::endl;
    other.add(6);
    other.add(2);
    other.add(7);
    other.add(1);
    other.add(4);
    other.add(9);
    other.add(3);
    other.add(5);
    other.add(8);

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << other << std::endl;

    std::cout<< "Dimensione dell'albero: " << other.size() << std::endl;

    std::cout << "Stampa con iteratori: " << std::endl;

    binary_search_tree<int, compare_int, equal_int>::const_iterator i,ie;

    for(i=other.begin(),ie=other.end(); i!=ie; ++i)
        std::cout << *i << std::endl;

    other.clear();
    std::cout << "Dimensione dell'albero dopo clear(): " << other.size() << std::endl;
}

void test_const_tree_int(const binary_search_tree<int, compare_int, equal_int> &other) {
    std::cout << "******** Test sull'albero costante di interi ********" << std::endl;

    // add non è chiamabile su un oggetto const

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << other << std::endl;

    std::cout << "Dimensione dell'albero: " << other.size() << std::endl;

    std::cout << "Stampa con iteratori" << std::endl;

    binary_search_tree<int, compare_int, equal_int>::const_iterator i,ie;

    for(i=other.begin(),ie=other.end(); i!=ie; ++i)
        std::cout<<*i<<std::endl;

    // clear non è chiamabile su un oggetto const
}

void test_funtore_stringhe(void) {
	std::cout << "******** Test sull'albero di stringhe ********" << std::endl;

	binary_search_tree<std::string, compare_string,equal_string> str_tree;

	std::cout << "Insertimento dei valori 'pippo', 'pluto', 'paperino', 'cip'" << std::endl;
	str_tree.add("pippo");
	str_tree.add("pluto");	
	str_tree.add("paperino");
	str_tree.add("cip");

	std::cout << "Stampa con operator<<" << std::endl;
	std::cout << str_tree << std::endl;

	std::cout << "Dimensione dell'albero: " << str_tree.size() << std::endl;

	std::cout << "Ricerca di 'cip': " << str_tree.find("cip") << std::endl;
	std::cout << "Ricerca di 'cipp': " << str_tree.find("cipp") << std::endl;

	str_tree.clear();
}

void test_tree_point(void) {

	binary_search_tree<point, compare_point, equal_point> point_tree;

	std::cout << "******** Test sull'albero di point ********" << std::endl;

	std::cout << "Insertimento dei valori (1,1), (1,2), (2,7), (0,0), (5,4)" << std::endl;
	point_tree.add(point(1,1));
	point_tree.add(point(1,2));
	point_tree.add(point(2,7));
	point_tree.add(point(0,0));
	point_tree.add(point(5,4));

	std::cout << "Stampa con operator<<" << std::endl;
	std::cout << point_tree << std::endl;

	std::cout << "Dimensione dell'albero: " << point_tree.size() << std::endl;

	std::cout << "Stampa con iteratori" << std::endl;

	binary_search_tree<point,compare_point,equal_point>::const_iterator i,ie;

	for(i=point_tree.begin(),ie=point_tree.end(); i!=ie; ++i)
		std::cout<<*i<<std::endl;

	std::cout << "Ricerca di '(1,1)': " << point_tree.find(point(1,1)) << std::endl;
	std::cout << "Ricerca di '(2,2)': " << point_tree.find(point(2,2)) << std::endl;

	point_tree.clear();
}

/**
 * Funzione MAIN con i vari test.
*/
int main(int argc, char const *argv[]) {

    // variabili 
    binary_search_tree<int, compare_int, equal_int> int_test_tree;

    // tests 
    test_metodi_fondamentali();
    test_tree_int(int_test_tree);
    test_const_tree_int(int_test_tree);
    test_funtore_stringhe();
    test_tree_point();
	test_uso();

	// pulizia
	int_test_tree.clear();

    return 0;

}
