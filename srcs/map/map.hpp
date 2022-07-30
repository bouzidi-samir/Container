#ifndef MAP_HPP
#define MAP_HPP

#include "iterator.hpp"
#include "binary_tree.hpp"
#include "pair.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

	public:
	
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef typename ft::iterator<value_type>			iterator;
		typedef typename ft::iterator<const value_type>		const_iterator;

		binary_tree<value_type, key_compare>	tree;


	private:
		key_compare								comp;
		allocator_type							alloc;


	public:

		explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type())
		{
			this->comp = comp;
			this->alloc = alloc;
			this->tree.compare = comp;
			this->tree.allocator = alloc;
		}

		~map(void) {}






		iterator begin(void)
		{
			return iterator(this->tree.getFirstNode(), this->tree.getLastNode());
		}

		iterator end(void)
		{
			return iterator(this->tree.null_leaf, this->tree.getLastNode());
		}

		void insert(value_type const& val)
		{
			this->tree.insert(val);
		}

};

};

#endif