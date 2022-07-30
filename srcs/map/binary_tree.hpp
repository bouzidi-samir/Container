#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <string>
#include <memory>

template <class T>
class Node {

	public:
	 	T data; 
	Node *parent;
	Node *left;
	Node *right;
	Node *null_leaf;

	Node* next() {

		if (this->right != null_leaf)
		{
			Node *tmp = this->right;
			while (tmp->left != null_leaf)
				tmp = tmp->left;
			return tmp;
		}
		else
		{
			Node *tmp = this;
			while (tmp->parent != null_leaf && tmp == tmp->parent->right)
				tmp = tmp->parent;
			return tmp->parent;
		}
	}

	Node* prev() {

		if (this->left != null_leaf)
		{
			Node *tmp = this->left;
			while (tmp->right != null_leaf)
				tmp = tmp->right;
			return tmp;
		}
		else
		{
			Node *tmp = this;
			while (tmp->parent != null_leaf && tmp == tmp->parent->left)
				tmp = tmp->parent;
			return tmp->parent;
		}
	}

	private:
};

template <class T, class Compar, class Alloc = std::allocator<T> >
class binary_tree {

	public:

		typedef Compar key_compare;
		typedef T value_type;
		typedef Node<T> Node;
		typedef typename Alloc::template rebind<Node>::other    allocator_type;
		Node *Root;
		Node *null_leaf;
		key_compare compare;
		allocator_type allocator;

		binary_tree(void)
		{
			this->null_leaf = this->allocator.allocate(1);

			this->null_leaf->left = NULL;
			this->null_leaf->right = NULL;
			this->null_leaf->parent = NULL;
			this->null_leaf->null_leaf = NULL;
			Root = this->null_leaf;
			Root->parent = this->null_leaf;

		}
		// binary_tree(key_compare const &compare, allocator_type const &allocator){
		// 	this->compare = compare;
		// 	this->allocator = allocator;
		// 	Root = NULL;
		// }

		Node *initializeNode(value_type const& key) {
			Node *ret = this->allocator.allocate(1);
			ret->left = NULL;
			ret->right = NULL;
			ret->parent = NULL;
			ret->null_leaf = null_leaf;
			ret->data = key;

			return ret;
		}
		
		void insert(value_type const& key){
			Node *add = this->initializeNode(key);
			Node *current = this->Root;

			if (current == null_leaf) {
				this->Root= add;
			}
			else
			{
				while(1)
				{
					if(compare(add->data, current->data))
					{
						if(current->left)
							current = current->left;
						else
						{
							current->left = add;
							add->parent = current;
							return;
						}
					}
					else
					{
						if(current->right)
							current = current->right;
						else
						{
							current->right = add;
							add->parent = current;
							return;
						}
					}
				}
			}
		}

		bool search(Node *node, value_type const& key){
			if(node == null_leaf)
				return false;
			else if (node->data == key)
				return true;
			else if (compare(key, node->data))
				return search(node->left, key);
			else
				return search(node->right, key);
		}


		Node* deleteNode(Node *node, value_type const& key) {
			if (node == NULL)
				return node;

			if (compare(key, node->data))
			{
				node->left = deleteNode(node->left, key);
				if (node->left)
					node->left->parent = node;
			}

			else if (compare(node->data, key))
			{
				node->right = deleteNode(node->right, key);
				if (node->right)
					node->right->parent = node;
			}

			else {
				if (node->left == NULL && node->right == NULL)
					return NULL;
				
				else if (node->left == NULL)
				{
					Node *tmp = node->right;
					this->allocator.deallocate(node, 1);
					return tmp;
				}

				else if (node->right == NULL)
				{
					Node *tmp = node->left;
					this->allocator.deallocate(node, 1);
					return tmp;
				}

				Node* tmp = getFirstNode(node->right);
				node->data = tmp->data;
				node->right = deleteNode(node->right, tmp->data);
				if (node->right)
					node->right->parent = node;
			}
			return node;
		}

		Node *getFirstNode(Node *node) {
			Node *current = node;

			while (current && current->left)
			{
				current = current->left;
			}

			return current;
		}

		Node *getLastNode(Node *node) {
			Node *current = node;

			while (current && current->right)
			{
				current = current->right;
			}
			return current;
		}



	void print_tree(Node *nod) {
		printHelper(nod, "", true);
	}

	void printHelper(Node* root, std::string indent, bool last) {
		if (root != NULL) {
			std::cout << indent;
			if (last) {
				std::cout << "R---- ";
				indent += "   ";
			} else {
				std::cout << "L---- ";
				indent += "|  ";
			}

			std::cout << root->data << std::endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}


	private:

};

#endif

//créer node
//reprendre les fonctions et le code du site