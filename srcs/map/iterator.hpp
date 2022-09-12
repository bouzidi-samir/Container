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
			if (ptr == this->last)
				ptr = ptr->null_leaf;
			else if (ptr != ptr->null_leaf && ptr->right != ptr->null_leaf)
			{
				ptr = ptr->right;
				while (ptr->left != ptr->null_leaf && ptr->left != nullptr)
					ptr = ptr->left;
			}
			else
			{
				while (ptr != ptr->null_leaf && ptr->parent != ptr->null_leaf && ptr == ptr->parent->right)
					ptr = ptr->parent;
				ptr = ptr->parent;
			}
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
			--(*this);
			return tmp;
		}

		iterator_value base(void) const { return this->ptr; }
		pointer	operator->(void) const { return &this->ptr->data; } 
		reference operator*(void) const { return this->ptr->data; }

		public:

		iterator_value	ptr;
		iterator_value	last;

};

template<class iterator, class iterator2>
bool operator==(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return !(it != ite); }
template<class iterator, class iterator2>
bool operator!=(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) 
{
	return it.base() != ite.base();
}

template <class T>
class const_iterator {


	public:

	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef typename std::ptrdiff_t			difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;

	private:
	typedef Node<value_type>*	iterator_value;
	iterator_value	ptr;
	iterator_value	last;

	public:

	const_iterator(void)  {
		ptr = NULL;
		last = NULL;
	}

	const_iterator(iterator_value ptr, iterator_value last) {
		this->ptr = ptr;
		this->last = last;
	}

	template <class it>
	const_iterator(iterator<it> const& i) {
		this->ptr = i.ptr;
		this->last = i.last;
	}

	~const_iterator() {}

	const_iterator& operator=(const_iterator const& i) {
			this->ptr = i.ptr;
			this->last = i.last;
			return *this;
		}

	const_iterator& operator++(void) {
		if (this->ptr->null_leaf == NULL)
			this->ptr = this->last;
		else
			this->ptr = this->ptr->next();
		return *this;
	}

	const_iterator operator++(int) {
		const_iterator tmp(*this);
		++*this;
		return tmp;
	}

	const_iterator& operator--(void) {
		if (this->ptr->null_leaf == NULL)
			this->ptr = this->last;
		else
			this->ptr = this->ptr->prev();
		return *this;
	}

	const_iterator operator--(int) {
		const_iterator tmp(*this);
		--*this;
		return tmp;
	}

	iterator_value base(void) const { return this->ptr; }
	pointer	operator->(void) const { return &this->ptr->data; } 
	reference operator*(void) const { return this->ptr->data; }

};

template<class const_iterator, class const_iterator2>
bool operator==(ft::const_iterator<const_iterator> const& it, ft::const_iterator<const_iterator2> const& ite) { return !(it != ite); }
template<class const_iterator, class const_iterator2>
bool operator!=(ft::const_iterator<const_iterator> const& it, ft::const_iterator<const_iterator2> const& ite) 
{
	return it.base() != ite.base();
}

template <class Iterator1, class Iterator2>
bool operator== (const ft::const_iterator<Iterator1>& lhs, const ft::iterator<Iterator2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator!= (const ft::const_iterator<Iterator1>& lhs, const ft::iterator<Iterator2>& rhs)
{
	return (lhs.base() != rhs.base());
}

};


#endif