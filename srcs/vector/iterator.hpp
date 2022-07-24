/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:52 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/24 15:34:34 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "./vector.hpp"
#include "./iterator_traits.hpp"

namespace ft 
{
template <class T, class Pointer = T*, class Reference = T&>
	class iterator {

		public :


        typedef std::random_access_iterator_tag iterator_category;
        typedef T         						value_type;
        typedef typename std::ptrdiff_t         difference_type;
        typedef Pointer   						pointer;
        typedef Reference 						reference;

        //            CONSTRUCTORS/DESTRUCTORS          //
        
		iterator () { return ; }
		
        iterator (pointer p) { _ptr = p; }
		
        iterator (iterator const &src ) { this->_ptr = src._ptr; }
		
        ~iterator(void) { };
		
        ///////////////// OPERATORS ///////////

        iterator &operator=(iterator const &src) { _ptr = src._ptr; return *this; }
		
        iterator operator+(difference_type n) const {return iterator(this->_ptr + n);}
        
		iterator operator-(difference_type n) const {return iterator(this->_ptr - n);}
    
		difference_type operator+(const iterator &right) const {return this->_ptr - right._ptr;}
		
        difference_type operator-(const iterator & right) const {return this->_ptr - right._ptr;}
		
		iterator operator+=(difference_type n) { return this->_ptr += n; }

		iterator operator-=(difference_type n) { return this->_ptr -= n; }
        
        bool operator==(const iterator &right) const { return this->_ptr == right._ptr; }
        
        ///////////// ACCESSS /////////////
        
        value_type &operator[](int n) {return this->_ptr[n];}
		
		reference operator*() {return *_ptr;}
	
		pointer operator->(){return _ptr;}
		
        pointer operator->() const {return _ptr;} 
		
        
        //Incrementers
        
        iterator & operator++() {_ptr++; return *this;} 

		iterator operator++(int) {iterator iter = *this; ++(*this) ; return iter;} 
		
        iterator & operator--() {_ptr--; return *this;} 
		
        iterator operator--(int) {iterator iter = *this; --(*this) ; return iter;} 

        
        operator iterator<const T>() const 
        {
                iterator<const T> temp(this->_ptr);
                return (temp);
   		}
		
        pointer base() const {return this->_ptr; }

		private :
			pointer _ptr;
	};

	template <typename T>
	iterator<T> operator+(typename iterator<T>::difference_type n, const iterator<T> left){
	    return (n + left.base());
	}

	template <typename T>
	iterator<T> operator-(typename iterator<T>::difference_type n, const iterator<T> left){
	    return (n - left.base());
	}

	template <class Iterator1, class Iterator2>
	  typename iterator<Iterator1>::difference_type operator-(
	    const iterator<Iterator1>& left,
	    const iterator<Iterator2>& right)
	 	{ return left.base() - right.base(); }

	template <class Iterator1, class Iterator2>
	  typename iterator<Iterator1>::difference_type operator+(
	    const iterator<Iterator1>& left,
	    const iterator<Iterator2>& right)
	 	{ return left.base() + right.base(); }

	template< class T, class T2 >
	bool operator==( const iterator<T>& left, const iterator<T2>& right ) { return left.base() == right.base(); }

	template< class T, class T2 >
	bool operator!=( const iterator<T>& left, const iterator<T2>& right ) { return left.base() != right.base(); }

	template< class T, class T2 >
	bool operator<( const iterator<T>& left, const iterator<T2>& right ) { return left.base() < right.base(); }

	template< class T, class T2 >
	bool operator<=( const iterator<T>& left, const iterator<T2>& right ) { return left.base() <= right.base(); }

	template< class T, class T2 >
	bool operator>( const iterator<T>& left, const iterator<T2>& right ) { return left.base() > right.base(); }

	template< class T, class T2 >
	bool operator>=( const iterator<T>& left, const iterator<T2>& right ) { return left.base() >= right.base(); }

		//--------------------[Reverse Iterators]--------------------//
template <class T>
	class reverse_iterator{

		public :

        typedef T													iterator_type;
        typedef typename ft::iterator_traits<T>::value_type			value_type;
        typedef typename ft::iterator_traits<T>::difference_type	difference_type;
        typedef typename ft::iterator_traits<T>::pointer			pointer;
        typedef typename ft::iterator_traits<T>::reference			reference;
        typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;

		template<class G>
		reverse_iterator (const reverse_iterator<G> &r) : _ptr(r.base() - 1) {} 
		reverse_iterator (void) : _ptr(0){}
		reverse_iterator (const iterator_type &it) : _ptr(it - 1) {}
		~reverse_iterator(void) { }
		reverse_iterator &operator=(reverse_iterator const &src) { _ptr = src._ptr; return *this; }
		iterator_type base() const {return this->_ptr + 1; }
		reference operator*() {return *(_ptr);}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(this->base() - n); }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(this->base() + n); }
		reverse_iterator operator++() { _ptr--; return *this; } 
		reverse_iterator operator++( int ) { 
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
			} 
		reverse_iterator operator--() { _ptr++; return *this; } 
		reverse_iterator operator--( int ) { 
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
			} 
		reverse_iterator operator+=(difference_type n) { this->_ptr -= n;return *this;}
		reverse_iterator operator-=(difference_type n) { this->_ptr += n;return *this;}
		pointer operator->(){ return _ptr.operator->(); }
		pointer operator->() const { return _ptr.operator->(); }
		reference operator[](int n) { return *(this->_ptr - n); }

		private :
			iterator_type _ptr;
	};

	template <typename T>
	reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> left){
	    return reverse_iterator<T>(left.base() - n);
	}

	template <typename T>
	reverse_iterator<T> operator-(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> left){
	    return reverse_iterator<T>(left.base() + n);
	}

	template <class Iterator1, class Iterator2>
	  typename reverse_iterator<Iterator1>::difference_type operator-(
	    const reverse_iterator<Iterator1>& left,
	    const reverse_iterator<Iterator2>& right)
	 	{ return right.base() - left.base(); }

	template <class Iterator1, class Iterator2>
	  typename reverse_iterator<Iterator1>::difference_type operator+(
	    const reverse_iterator<Iterator1>& left,
	    const reverse_iterator<Iterator2>& right)
	 	{ return right.base() + left.base(); }

	template< class T, class T2 >
	bool operator==( const reverse_iterator<T>& left, const reverse_iterator<T2>& right ) { return left.base() == right.base(); }

	template< class T, class T2 >
	bool operator!=( const reverse_iterator<T>& left, const reverse_iterator<T2>& right ) { return left.base() != right.base(); }

	template< class T, class T2 >
	bool operator<( const reverse_iterator<T>& left, const reverse_iterator<T2>& right ) { return left.base() > right.base(); }

	template< class T, class T2 >
	bool operator<=( const reverse_iterator<T>& left, const reverse_iterator<T2>& right ) { return left.base() >= right.base(); }

	template< class T, class T2 >
	bool operator>( const reverse_iterator<T>& left, const reverse_iterator<T2>& right ) { return left.base() < right.base(); }

	template< class T, class T2 >
	bool operator>=( const reverse_iterator<T>& left, const reverse_iterator<T2>& right ) { return left.base() <= right.base(); }
}

#endif