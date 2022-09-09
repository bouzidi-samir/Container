#include "binary_tree.hpp"
#include "map.hpp"
#include <iostream>
#include <vector>

#define T1 int
#define T2 std::string
// typedef ft::map<T1, T2>::value_type T3;

int main(void) {
	ft::map<int, std::string>	my_map;
	std::string					value = "bonsoir";
	srand(time(NULL));
	int	head;
	std::vector<int>	keys;
	for (int i = 0 ; i < 1 ; i++) {
		int	key = rand() % 25 + 1;
		if (i == 0) head = key;
		keys.push_back(key);
		my_map.insert(ft::pair<int, std::string>(key, value));
	}

	my_map.tree.btree_display(my_map.tree.Root, 0);

	std::cout << "size = " << my_map.size() << std::endl;

	my_map.tree.deleteNode(my_map.tree.Root, ft::pair<int, std::string>(head, ""));

	std::cout << "====================================================================================" << std::endl;
	my_map.tree.btree_display(my_map.tree.Root, 0);

	std::cout << "size = " << my_map.size() << std::endl;

	// ft::map<string, int> m;
	// m.insert(ft::pair<string, int>("a", 1));
	// m.insert(ft::pair<string, int>("b", 2));
	// m.insert(ft::pair<string, int>("c", 3));
	// ft::map<string, int>::const_iterator it = m.begin();
	// std::cout << it->first << std::endl;
	// //m.tree.print_tree(m.tree.Root);
	// while (it != m.end()) {
	// 	cout << it->first << " et " << it->second << endl;
	// 	it++;
	// }


	// it--;
	// while (it != m.begin()) {
	// 	cout << it->first << " " << it->second << endl;
	// 	it--;
	// }
}