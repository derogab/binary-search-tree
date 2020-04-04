#include <iostream>
#include "bstree.h"


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
 * Funzione MAIN con i vari test.
*/
int main(int argc, char const *argv[]) {

    binary_search_tree<int, compare_int, equal_int> int_tree;
    binary_search_tree<std::string, compare_string, equal_string> string_tree;

    // inserimenti interi
    int_tree.add(6);
    int_tree.add(2);
    int_tree.add(7);
    int_tree.add(1);
    int_tree.add(4);
    int_tree.add(9);
    int_tree.add(3);
    int_tree.add(5);
    int_tree.add(8);

    // inserimenti stringhe
    string_tree.add("a");
    string_tree.add("ab");
    string_tree.add("abc");
    string_tree.add("abcd");
    string_tree.add("abcde");

    // cerca interi
    std::cout << "int_tree.find(5): " << int_tree.find(5) << std::endl;
    std::cout << "int_tree.find(6): " << int_tree.find(6) << std::endl;

    // cerca stringhe
    std::cout << "string_tree.find(\"abcde\"): " << string_tree.find("abcde") << std::endl;
    std::cout << "string_tree.find(\"abcdef\"): " << string_tree.find("abcdef") << std::endl;

    // get size
    std::cout << "int_tree.size(): " << int_tree.size() << std::endl;
    std::cout << "string_tree.size(): " << string_tree.size() << std::endl;

    // test iterator
    typename binary_search_tree<int, compare_int, equal_int>::const_iterator i,ie;

	i = int_tree.begin();
	ie = int_tree.end();

    std::cout << "values: " << int_tree << std::endl;
    
    return 0;

}
