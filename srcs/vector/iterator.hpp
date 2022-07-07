/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:52 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/07 15:55:37 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "./vector.hpp"

namespace ft
{
template <class T, class Pointer = T*, class Reference = T&>
    class Iterator
    {
        public:

            typedef std::random_access_iterator_tag iterator_category;
            typedef T         value_type;
            typedef typename std::ptrdiff_t difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;

            Iterator () { return ; }
            Iterator(pointer ptr) { this->_ptr = ptr; };
            Iterator(Iterator const &ref) { *this = ref;};

            ~Iterator() {};

            Iterator &operator=(Iterator const &src) {this->_ptr = src._ptr; return (*this);};
            Iterator operator+(Iterator src) {return (Iterator(this->_ptr + src._ptr));};

            bool operator==(Iterator const &src) const {return (this->_ptr == src._ptr);};
            bool operator!=(Iterator const &src) const {return (this->_ptr != src._ptr);};
            bool operator>(Iterator const &src) const {return (this->_ptr > src._ptr);};
            bool operator<(Iterator const &src) const {return (this->_ptr < src._ptr);};
            bool operator>=(Iterator const &src) const {return (this->_ptr >= src._ptr);};
            bool operator<=(Iterator const &src) const {return (this->_ptr <= src._ptr);};

            value_type &operator[](int i) {return this->_ptr[i];}
            reference operator*() {return (*(this->_ptr));};
            Iterator &operator++() {_ptr++; return (*this);};
            Iterator operator++(int) {Iterator iter = *this; ++(*this) ; return iter;};
            Iterator &operator--() {_ptr--; return (*this);};
            Iterator operator--(int) {Iterator iter = *this; --(*this) ; return iter;};

            operator Iterator<const T> () const
                { return (Iterator<const T>(this->_ptr)); }


        private:
            pointer _ptr;
    };

        template <typename T>
        Iterator<T> operator+(typename Iterator<T>::difference_type l, const Iterator<T> r)
        {return (l + r.base());}
        
        template <typename T>
        Iterator<T> operator-(typename Iterator<T>::difference_type l, const Iterator<T> r)
        {return (l - r.base());}
        
        template <class T, class T1>
        bool operator==(
            const Iterator<T> &left, const Iterator<T1> &right)
        {return left.base() == right.base();}

        template <class T, class T1>
        bool operator!=(
            const Iterator<T> &left, const Iterator<T1> &right)
        {return left.base() != right.base();}
    
        template <class T, class T1>
        bool operator<(
            const Iterator<T> &left, const Iterator<T1> &right)
        {return left.base() < right.base();}

        template <class T, class T1>
        bool operator>(
            const Iterator<T> &left, const Iterator<T1> &right)
        {return left.base() > right.base();}

        template <class T, class T1>
        bool operator<=(
            const Iterator<T> &left, const Iterator<T1> &right)
        {return left.base() <= right.base();}
        
        template <class T, class T1>
        bool operator>=(
            const Iterator<T> &left, const Iterator<T1> &right)
        {return left.base() >= right.base();}

        template <class I, class I1>
        typename Iterator<I>::difference_type operator+(
            const Iterator<I> &left, const Iterator<I1> &right)
        {return left.base() + right.base();}

        template <class I, class I1>
        typename Iterator<I>::difference_type operator-(
            const Iterator<I> &left, const Iterator<I1> &right)
        {return left.base() - right.base();}
}







#endif