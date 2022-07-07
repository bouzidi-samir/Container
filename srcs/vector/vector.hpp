/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:04:27 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/07 15:55:33 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <limits>
# include <memory>
# include <vector>
# include <cstddef>
# include <sstream>
# include <cctype>
# include <cstdint>
# include <cmath>
# include <stdexcept>
# include <algorithm>
# include "./iterator.hpp"
# include "../Utils.hpp"

namespace ft
{

    template< typename T, class Allocator = std::allocator<T> >
    class	vector
    {
        public:
            typedef T value_type;
	        
            typedef Allocator allocator_type;
            typedef typename ft::Iterator<const T>					const_iterator;
            typedef typename ft::Iterator<T>						iterator;
            typedef typename std::size_t                                size_type;
            typedef typename std::ptrdiff_t                             difference_type;
            typedef typename Allocator::const_reference                 const_reference;
            typedef typename Allocator::reference                       reference;
            typedef typename Allocator::const_pointer                   const_pointer;
            typedef typename Allocator::pointer                         pointer;
	        

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type &mem = allocator_type(), 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr)
            {
                _alloc = mem;
                InputIterator begin = first;
                size_type s = 0;
                for (;first != last; first++)
				    s++;
                _tab = _alloc.allocate(s);
                s = 0;
                first = begin;
                for (;first != last; first++)
                {
				    _alloc.construct(_tab + s, *first);
				    s++;
			    }
                _size = s;
			    _size_capacity = s;
            }

            explicit vector(const allocator_type &mem = Allocator()) {
                _alloc = mem;
                _size = 0;
                _size_capacity = 0;
            } 

            explicit vector (size_type n, const value_type &value = value_type(),
                const allocator_type &mem = Allocator()) {
                _alloc = mem;
                _size = n;
                _size_capacity = n;
                _tab = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++) {
				    _alloc.construct(_tab + i, value);
			    }
            }
            
            vector(const vector &other) {
                _tab = other._tab;
                _size = other._size;
                _size_capacity = other._size_capacity;
			    for (size_type i = 0; i < other.size(); i++)
				    _tab[i] = other._tab[i];
            } 
            
            ~vector(void) {}

            size_type   size() const {return this->_size;}

            size_type   max_size() const {return allocator_type().max_size();}

            size_type	capacity() const {return _size_capacity;}

            bool    empty() const {return (_size == 0 ? true : false);}
            
            void		reserve(size_type s) {
		        
                if (s > this->max_size())
				    throw std::length_error("vector");
			    if (s > _size_capacity) 
                {
			        pointer temp = _alloc.allocate(s);
			        if (_size > 0)
                    {
				        for (size_type i = 0; i < _size; i++)
                        {
					        _alloc.construct(temp + i, _tab[i]);
					        _alloc.destroy(_tab + i);
				        }
			  	        _alloc.deallocate(_tab, _size_capacity);
				    }  
			        _tab = temp;
			        _size_capacity = s;
		        }
		    }

            reference   operator[] (size_type i) {return _tab[i];}

            const_reference operator[] (size_type i) const {return _tab[i];}

            reference   at (size_type i) {
			    if (i < 0 || i >= _size)
				    throw std::out_of_range("vector");
			    return _tab[i];   
		    }

            const_reference at (size_type i) const {
			    if (i < 0 || i >= _size)
				    throw std::out_of_range("vector");
			    return _tab[i];   
		    }

            reference   front() {return _tab[0];}

            const_reference   front() const {return _tab[0];}
            
            reference   back() {return _tab[_size - 1];}

            const_reference   back() const {return _tab[_size - 1];}
           
            void	push_back(const T& element)
	        {   
		        if (_size < _size_capacity)
			    {
				    _tab[_size] = element;
				    _size++; 
			    }
			    else if (this->_size == 0) {
				    _size_capacity++;
				    _tab = _alloc.allocate(_size_capacity);
				    _alloc.construct(this->_tab + _size, element);
				    _size++;
			    }
			    else
			    {
				    _size_capacity *= 2;
				    pointer tmp = _alloc.allocate(_size_capacity);
				    for (size_type i = 0; i < _size; i++)
				    {
					    _alloc.construct(tmp + i, _tab[i]);
					    _alloc.destroy(_tab + i);
				    }
				    if (_size_capacity > 0)
				        _alloc.deallocate(_tab, _size_capacity / 2);
				    _tab = tmp;
				    _tab[_size] = element;
				    _size++;
			    } 
	        };

            void			pop_back(void)
            {
			    if (this->_size > 0)
                { 
				    _alloc.destroy(&this->back());
                    _size--;
                }
            }

            iterator    insert(iterator pos, const value_type &value)
            {
                difference_type  dist = pos - _tab;
                if (_size == 0)
                {
                    _tab = _alloc.allocate(_size + 1);
                    _alloc.construct(_tab + dist, value);
                    _size_capacity++;
                }   
                else if ((_size + 1) > _size_capacity)
                {
                    _size_capacity *= 2;
                    pointer temp = _alloc.allocate(_size_capacity);
                    for (size_type j = 0; j < _size; j++) 
                    {
					    _alloc.construct(temp + j, _tab[j]);
					    _alloc.destroy(_tab + j);
				    }
                    _alloc.deallocate(_tab, _size_capacity / 2);
                    _tab = temp;
                    int k = _size - 1;
                    while (k >= dist)
                    {
                        _tab[k + 1] = _tab[k];
                        k--;
                    }
                }
                else
                {
                    int k = _size - 1;
                    while (k >= dist)
                    {
                        _tab[k + 1] = _tab[k];
                        k--;
                    }
                }
                _size++;
                _tab[dist] = value;
                return iterator(_tab + dist);
            }

            void insert(iterator pos, size_type n, const value_type &value)
            {
                iterator it = pos;
                size_type i = 0;
                while (i < n)
                {
                    it = insert(it, value);
                    i++;
                }
            }

            template <class InputIterator>
            void			insert(iterator pos, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr)
            {
                (void)enable;
                iterator it = pos;
                while (first != last)
                {
                    it = insert(it, *first);
                    first++;
                }
            }

            iterator erase (iterator pos)
            {
                



            }

        private:
            
            pointer			_tab;
            allocator_type  _alloc;
            size_type		_size;
		    size_type		_size_capacity;

    };

}

#endif