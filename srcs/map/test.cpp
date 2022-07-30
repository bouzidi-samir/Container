#include "binary_tree.hpp"
#include "map.hpp"
#include <iostream>

using namespace std;

int main(void) {
	binary_tree<int, std::less<int> > T;


	T.insert(5);
	T.insert(8);
	T.insert(4);
	T.insert(2);
	T.insert(6);
	
	T.deleteNode(T.Root, 5);

	T.print_tree(T.Root);

	ft::map<string, int> m;
	//m.insert(ft::pair<string, int>("a", 1));
}