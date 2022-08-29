#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "binary_tree.hpp"

namespace ft {

template <class T>
	class iterator {


		public:

		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef typename std::ptrdiff_t			difference_type;
		typedef T*								pointer;
		typedef T&								reference;

		private:
		typedef Node<value_type>*	iterator_value;

		public:

		iterator() {
			ptr = NULL;
			last = NULL;
		}

		iterator(iterator_value ptr, iterator_value last) {
			this->ptr = ptr;
			this->last = last;
		}

		template <class it>
		iterator(iterator<it> const& i) {
			//*this = i;
			this->ptr = i.ptr;
			this->last = i.last;
		}

		~iterator() {}

		iterator& operator=(iterator const& i) {
			this->ptr = i.ptr;
			this->last = i.last;
			return *this;
		}

		iterator& operator++(void) {
			if (this->ptr->null_leaf == NULL)
				this->ptr = this->last;
			else
				this->ptr = this->ptr->next();
			return *this;
		}

		iterator operator++(int) {
			iterator tmp(*this);
			++*this;
			return tmp;
		}

		iterator& operator--(void) {
			if (this->ptr->null_leaf == NULL)
				this->ptr = this->last;
			else
				this->ptr = this->ptr->prev();
			return *this;
		}

		iterator operator--(int) {
			iterator tmp(*this);
			--*this;
			return tmp;
		}

		iterator_value base(void) const { return this->ptr; }
		pointer	operator->(void) const { return &this->ptr->data; } 
		reference operator*(void) const { return this->ptr->data; }

		private:

		iterator_value	ptr;
		iterator_value	last;

};

template<class iterator, class iterator2>
bool operator==(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return !(it != ite); }
template<class iterator, class iterator2>
bool operator!=(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) {
	if (it.base()->null_leaf == NULL && it.base()->null_leaf == NULL)
		return false;
	if (it.base()->null_leaf == NULL && it.base()->null_leaf)
		return true;
	if (it.base()->null_leaf && ite.base()->null_leaf == NULL)
		return true;
	return it->first != ite->first || it->second != ite->second;
}

template <class T>
class const_iterator {


	public:

	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef const T							value_type;
	typedef typename std::ptrdiff_t			difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;




}

};

#endif