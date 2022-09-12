#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

#include "../map/map.hpp"
#include "iterator_traits.hpp"


namespace ft
{
    template <class T>
	class reverse_iterator
    {
        public:
            
            typedef T													iterator_type;
            typedef typename ft::iterator_traits<T>::value_type			value_type;
            typedef typename ft::iterator_traits<T>::difference_type	difference_type;
            typedef typename ft::iterator_traits<T>::pointer			pointer;
            typedef typename ft::iterator_traits<T>::reference			reference;
            typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;


        template <class I>
        reverse_iterator (const reverse_iterator<I> &rev_it) : _element(rev_it.base()) {}

        reverse_iterator() : _element() {}

        explicit reverse_iterator (iterator_type it) : _element(it) {}

        ~reverse_iterator(void) {}

		operator reverse_iterator<const T> () const { return this->current; }
        
        iterator_type base() const { return (_element); }
 
            
 

        reference operator*() const {
			iterator_type	cpy = _element;
			return (*(--cpy));
		}

        reverse_iterator &operator=(reverse_iterator const & src) {this->_element = src._element; return *this;}
        
        reverse_iterator operator+(difference_type d) const {return (reverse_iterator(_element - d));}
        
        reverse_iterator operator-(difference_type d) const {return (reverse_iterator(_element.base() + d));}
        
        reverse_iterator& operator++() {--_element; return (*this);}

        reverse_iterator& operator--() {++_element; return (*this);}

        reverse_iterator operator++(int)
        {
            reverse_iterator temp = *this;
            ++(*this);
            return (temp);
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator temp = *this;
            --(*this);
            return (temp);
        }

        reverse_iterator operator+=(difference_type d) {_element -= d;return *this;}

        reverse_iterator operator-=(difference_type d) {_element += d;return *this;}

        reference operator[](int n) {return *(_element - n);}

        pointer operator->() {return &(operator*());}

        pointer operator->() const {return &(operator*());}

        private:
            iterator_type _element;
    };

    template <class L, class R>
    bool operator==(const reverse_iterator<L> &left, const reverse_iterator<R> &right) 
    { 
        return (left.base() == right.base());
    }

    template <class L, class R>
    bool operator!=(const reverse_iterator<L> &left, const reverse_iterator<R> &right) 
    { 
        return (left.base() != right.base());
    }

    template< class L, class R >
	bool operator<(const reverse_iterator<L> &left, const reverse_iterator<R> &right) 
    { 
        return left.base() > right.base(); 
    }

    template< class L, class R >
	bool operator>(const reverse_iterator<L> &left, const reverse_iterator<R> &right) 
    { 
        return left.base() < right.base(); 
    }

    template< class L, class R >
	bool operator<=(const reverse_iterator<L> &left, const reverse_iterator<R> &right) 
    { 
        return left.base() >= right.base(); 
    }

    template< class L, class R >
	bool operator>=(const reverse_iterator<L> &left, const reverse_iterator<R> &right) 
    { 
        return left.base() <= right.base(); 
    }

    template <typename T>
	reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type d, const reverse_iterator<T> left)
    {
	    return reverse_iterator<T>(left.base() - d);
	}

    template <typename T>
	reverse_iterator<T> operator-(typename reverse_iterator<T>::difference_type d, const reverse_iterator<T> left)
    {
		printf("here1");
	    return reverse_iterator<T>(left.base() + d);
	}

    template <class L, class R>
	typename reverse_iterator<L>::difference_type operator+(const reverse_iterator<L>& left, const reverse_iterator<R>& right)
	{ 
        return right.base() + left.base(); 
    }

    template <class L, class R>
	typename reverse_iterator<L>::difference_type operator-(const reverse_iterator<L>& left, const reverse_iterator<R>& right)
	{ 		
		printf("here2");
        return right.base() - left.base(); 
    }
}
#endif