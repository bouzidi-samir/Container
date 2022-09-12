#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <string>
#include <memory>
#include "pair.hpp"

template <class T>
class Node {

	public:
	 	T data; 
	Node *parent;
	Node *left;
	Node *right;
	Node *null_leaf;

	Node* next() {

		if (this != this->null_leaf && this->right != this->null_leaf)
		{
			Node *tmp = this->right;
			while (tmp->left != this->null_leaf && tmp->left != nullptr)
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
			this->Root = this->null_leaf;
			// this->Root->parent = this->null_leaf;
		}

		int size(Node *node) const
		{
			if (node == null_leaf)
				return  0;
			return 1 + size(node->left) + size(node->right);
		}

		// binary_tree(key_compare const &compare, allocator_type const &allocator){
		// 	this->compare = compare;
		// 	this->allocator = allocator;
		// 	Root = NULL;
		// }

		Node *initializeNode(value_type const& key) {
			Node *ret = this->allocator.allocate(1);
			ret->left = null_leaf;
			ret->right = null_leaf;
			ret->parent = null_leaf;
			ret->null_leaf = null_leaf;
			ret->data = key;

			return ret;
		}
		
		void insert(value_type const& key){
			Node *add = this->initializeNode(key);
			Node *nodeent = this->Root;

			if (nodeent == null_leaf) {
				this->Root = add;
			}
			else
			{
				while(1)
				{
					if (compare(add->data.first, nodeent->data.first))
					{
						if(nodeent->left != null_leaf)
							nodeent = nodeent->left;
						else
						{
							nodeent->left = add;
							add->parent = nodeent;
							return;
						}
					}
					else
					{
						if(nodeent->right != null_leaf)
							nodeent = nodeent->right;
						else
						{
							nodeent->right = add;
							add->parent = nodeent;
							return;
						}
					}
				}
			}
		}

		Node *search(Node *node, value_type const& key){
			if(node == null_leaf)
				return null_leaf;
			else if (node->data.first == key.first)
				return node;
			else if (compare(key.first, node->data.first))
				return search(node->left, key);
			else
				return search(node->right, key);
		}

		Node* deleteNode(Node *node, value_type const& key) {
			Node *tmp = null_leaf;

			if (node == null_leaf)
				return node;
			if (compare(key.first, node->data.first))
			{
				node->left = deleteNode(node->left, key);
				if (node->left)
					node->left->parent = node;
			}
			else if (compare(node->data.first, key.first))
			{
				node->right = deleteNode(node->right, key);
				if (node->right)
					node->right->parent = node;
			}
			else
			{
				if (node->left == null_leaf && node->right == null_leaf)
				{
					if (node == this->Root) {
						// this->Root->parent = null_leaf;
						this->Root = null_leaf;
					}
					this->allocator.destroy(node);
					this->allocator.deallocate(node, 1);
					return null_leaf;
				}
				
				else if (node->left == null_leaf)
				{
					tmp = node->right;
					if (node == this->Root) {
						this->Root = tmp;
						this->Root->parent = null_leaf;
					}
					this->allocator.destroy(node);
					this->allocator.deallocate(node, 1);
					return tmp;
				}

				else if (node->right == null_leaf)
				{
					tmp = node->left;
					if (node == this->Root) {
						this->Root = tmp;
						this->Root->parent = null_leaf;
					}
					this->allocator.destroy(node);
					this->allocator.deallocate(node, 1);
					return tmp;
				}

				tmp = getFirstNode(node->right);
				node->data = tmp->data;
				node->right = deleteNode(node->right, tmp->data);
				if (node->right)
					node->right->parent = node;
			}
			return node;
		}
		
		Node *getFirstNode() const {
			Node	*temp = Root;
			if (Root != null_leaf)
			{
				while (temp->left != temp->null_leaf)
					temp = temp->left;
			}
			return temp;
		}

		Node *getFirstNode(Node *node) const {
			Node *nodeent = node;

			while (nodeent->left != null_leaf)
			{
				nodeent = nodeent->left;
			}

			return nodeent;
		}

		Node *getLastNode() const {
			Node *	temp = Root;
			if (temp != temp->null_leaf) {
				while (temp->right != temp->null_leaf)
					temp = temp->right;
			}
			return (temp);
			// if (this->Root == null_leaf)
			// 	return null_leaf;
			// return getLastNode(this->Root);
		}

		Node *getLastNode(Node *node) const {
			Node *nodeent = node;

			while (nodeent != null_leaf && nodeent->right != null_leaf)
			{
				nodeent = nodeent->right;
			}
			return nodeent;
		}

	void print_tree(Node *nod) {
		printHelper(nod, "", true);
	}

	void printHelper(Node* root, std::string indent, bool last) {
		if (root != null_leaf) {
			std::cout << indent;
			if (last) {
				std::cout << "R---- ";
				indent += "   ";
			} else {
				std::cout << "L---- ";
				indent += "|  ";
			}

			std::cout << root->data.first << std::endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

	void	btree_display(Node *root, int space)
	{
		int	i = 5;

		if (root == null_leaf)
			return ;
		space += 5;
		btree_display(root->right, space);
		while (i++ < space)
			printf(" ");
		if (root->parent == root->null_leaf)
			std::cout << "[" << root->data.first << "-" << root->data.second << "] -> parent=null_leaf" << std::endl;
		else
			std::cout << "[" << root->data.first << "-" << root->data.second << "] -> parent=" << root->parent->data.first << std::endl;
		
		btree_display(root->left, space);
	}
};

#endif
