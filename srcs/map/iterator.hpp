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
			*this = i;
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

		value_type*	operator->(void) const { return this->ptr; } 
		value_type& operator*(void) const { return *this->ptr; }

		private:

		iterator_value	ptr;
		iterator_value	last;

};

};

#endif