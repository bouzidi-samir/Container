#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <string>

template <class T>
class Node {

	public:
	 	T data; 
	Node *parent;
	Node *left;
	Node *right;

	private:
};

template <class T, class Compar, class Alloc = std::allocator<T>>
class binary_tree {

	public:

		typedef Compar key_compare;
		typedef T value_type;
		typedef Node<T> Node;
		typedef typename Alloc::template rebind<Node>::other    allocator_type;
		Node *Root;
		key_compare compare;
		allocator_type allocator;

		binary_tree(void);
		binary_tree(key_compare const &compare, allocator_type const &allocator){
			this->compare = compare;
			this->allocator = allocator;
			Root = null;
		}

		Node *initializeNode(value_type const& key) {
			Node *ret = this->allocator.allocat(1);
			ret->left = NULL;
			ret->right = NULL;
			ret->parent = NULL;
			ret->data =  data;

			return ret;
		}
		
		void insert(value_type const& key){
			Node *add = this->initializeNode(key);
			Node *current = this->Root;

			if (current == NULL)
				this->Root= add;
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
			if(node == NULL)
				return false;
			else if (node->data == key)
				return true;
			else if (compare(node->data, key))
				return search(node->left, key);
			else
				return search(node->right, key);
		}


	private:

};

#endif

//créer node
//reprendre les fonctions et le code du site