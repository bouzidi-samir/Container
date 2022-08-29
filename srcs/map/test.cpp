#include "binary_tree.hpp"
#include "map.hpp"
#include <iostream>

using namespace std;

int main(void) {
	// binary_tree<int, less<int> > T;


	// T.insert(5);
	// T.insert(8);
	// T.insert(4);
	// T.insert(2);
	// T.insert(6);
	
	// T.deleteNode(T.Root, 5);

	// T.print_tree(T.Root);

	ft::map<string, int> m;
	m.insert(ft::pair<string, int>("a", 1));
	m.insert(ft::pair<string, int>("b", 2));
	m.insert(ft::pair<string, int>("c", 3));
	ft::map<string, int>::const_iterator it = m.begin();
	std::cout << it->first << std::endl;
	//m.tree.print_tree(m.tree.Root);
	while (it != m.end()) {
		cout << it->first << " et " << it->second << endl;
		it++;
	}


	it--;
	while (it != m.begin()) {
		cout << it->first << " " << it->second << endl;
		it--;
	}
}