/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:04:27 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/24 15:47:43 by sbouzidi         ###   ########.fr       */
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
            
            typedef typename ft::iterator<const T>					const_iterator;
            typedef typename ft::iterator<T>						iterator;
	     
	        typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
            typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
            
            typedef typename std::size_t                                size_type;
            
            typedef typename std::ptrdiff_t                             difference_type;
            
            typedef typename Allocator::const_reference                 const_reference;
            typedef typename Allocator::reference                       reference;
            typedef typename Allocator::const_pointer                   const_pointer;
            typedef typename Allocator::pointer                         pointer;
		
            //            CONSTRUCTORS/DESTRUCTOR          //
            
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type &mem = allocator_type(), 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr)
            {
                (void)enable;
                _alloc = mem;
                size_type s = 0;
                InputIterator begin = first;
                for (;first != last; first++)
				    s++;
                _tab = _alloc.allocate(s);
                first = begin;
                s = 0;
                for (;first != last; first++)
                {
				    _alloc.construct(_tab + s, *first);
				    s++;
			    }
                _size = s;
			    _size_capacity = s;
            }

            explicit vector(const allocator_type &mem = allocator_type()) 
            {
                _size = 0;
                _alloc = mem;
                _size_capacity = 0;
            } 

            explicit vector (size_type n, const value_type &value = value_type(),
                const allocator_type &mem = allocator_type()) 
            {
                _alloc = mem;
                _size = n;
                _size_capacity = n;
                _tab = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++) {
				    _alloc.construct(_tab + i, value);
			    }
            }

            vector(vector const & x) 
            {
                this->_size = x._size;
                this->_size_capacity = x._size_capacity;
                this->_tab = _alloc.allocate(x._size_capacity);
			    for (size_type i = 0; i < x.size(); i++)
				    _tab[i] = x._tab[i];
            } 
            
		    ~vector(void) {}
		
		        ///////////// ITERATORS ///////////
		
        iterator 				begin() { return iterator(_tab); }

		const_iterator			begin() const { return const_iterator(_tab); }

		iterator				end() { return iterator(_tab + _size); }

		const_iterator			end() const { return const_iterator(_tab + _size); }

		reverse_iterator		rbegin() { return reverse_iterator(_tab + (_size)); }

		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_tab + (_size)); }
			
		reverse_iterator		rend() { return reverse_iterator(_tab); }

		const_reverse_iterator	rend() const { return const_reverse_iterator(_tab); }


		        ///////////// METHODES ///////////
        
        size_type	size() const { return this->_size; }

		size_type	max_size() const { return _alloc.max_size(); }

		void		resize(size_type n, value_type val = value_type()) {
			if (n < this->_size) {
				for (size_type i = n; i <= this->_size;i++) {
					_alloc.destroy(_tab + i);
				}
			}
			else if (n > this->_size) {
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++) {
					_alloc.construct(tmp + i, _tab[i]);
					_alloc.destroy(_tab + i);
				}
				if (_size > 0)
					_alloc.deallocate(_tab, this->_size_capacity);
				_tab = tmp;
				while (this->_size < n) {
					_tab[this->_size] = val;
					this->_size++;
				}
			}
			else
				return ;
			this->_size = n;
			this->_size_capacity = n;
		}

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
             
        	////////////     ELEMENT ACCESS     //////////
		
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

            ////////////     ELEMENT ACCESS     //////////

        void	push_back(const T& element)
	    {   
		    if (_size < _size_capacity)
			{
				_tab[_size] = element;
				_size++; 
			}
			else if (this->_size == 0) 
            {
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

        template<class InputIterator>
		void    assign (InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr ) 
            {
                (void)enable;
			    size_type s = 0;
		        if (!empty()) 
                {
			        for (size_type  i = 0; i < this->_size; ++i)
                    {
				        _alloc.destroy(this->_tab + i);
			        }
		            _alloc.deallocate(_tab, _size);
		        } 
		        InputIterator iter = first;
		        for(; first != last; first++) 
			        s++;
		   	    _tab = _alloc.allocate(s);
		  	    first = iter;
		        s = 0;
		  	    for(;first != last; first++) 
                {
				    _alloc.construct(_tab + s, *first);
			    	s++;
		        }
		        _size = s;
		        _size_capacity = s;
		    }

        void    assign(size_type n, const value_type& val) 
        {
		   if (!empty()) 
           {
			   for (size_type  i = 0; i < this->_size; i++)
				   _alloc.destroy(this->_tab + i);
			   _alloc.deallocate(_tab, _size);
		   } 
		   this->_size = n;
		   this->_size_capacity = n;
		   this->_tab = _alloc.allocate(this->_size);
		   for(size_type i = 0; i < this->_size; i++) 
				_alloc.construct(_tab + i , val);
		}

		iterator		insert(iterator position, const value_type &val) {

			difference_type  i = position - _tab;

            if (_size == 0)
            {
                this->_tab = _alloc.allocate(_size + 1);
                 _alloc.construct(_tab + i, val);
                this->_size_capacity++;
            }
			else if ((_size + 1) > _size_capacity) {
				_size_capacity *= 2;
				pointer tmp;
				tmp = _alloc.allocate(_size_capacity);
				for (size_type j = 0; j < _size; j++) {
					_alloc.construct(tmp + j, _tab[j]);
					_alloc.destroy(_tab + j);
				}
				_alloc.deallocate(_tab, _size_capacity / 2);
				_tab = tmp;
				int j = _size - 1;
                while (j >= i)
                {
                    _tab[j + 1] = _tab[j];
                    j--;
                }
			}
			else {
                int j = _size - 1;
                while (j >= i)
                {
                    _tab[j + 1] = _tab[j];
                    j--;
                }
			}
            this->_size++;
			_tab[i] = val;
			return iterator(_tab + i);
		}

		void			insert (iterator position, size_type n, const value_type& val) {

			iterator it = position;
			for (size_type i = 0; i < n; i++)
				it = insert(it, val);
		}

		template <class InputIterator>
		void			insert(iterator position, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr) {
            (void)enable;

			iterator it = position;
            for (;first != last; first++) {
				it = insert(it, *first);
				it++;
			}
		}

        iterator erase(iterator pos)
        {                
            difference_type d = pos - _tab;

			_alloc.destroy(_tab + d);
			while (d < static_cast<int>(_size))
			{
				_tab[d] = _tab[d + 1];
				d++;
			}
			this->_size--;
			return iterator(pos);
        }

        iterator		erase(iterator first, iterator last) 
        {
			iterator it = first;
			difference_type d = last - first;

            while (first != last) 
            {
                erase(it);
                first++;
            }
			return first - d;
		}

        void			swap(vector &x) 
        {
		   std::swap(this->_tab,x._tab);
		   std::swap(this->_size,x._size);
		   std::swap(this->_size_capacity,x._size_capacity);
		}

        //////////// OPERATOR = //////////

        vector& operator=(const vector &x) 
        {
			if (this->_size > 0) 
            {
				for(size_type i = 0; i < this->_size; i++)
					_alloc.destroy(this->_tab + i);
				_alloc.deallocate(this->_tab, this->_size_capacity);
			}
			_tab = _alloc.allocate(x._size_capacity);
			_size = x._size;
			_size_capacity = x._size_capacity;
			for(size_t i = 0; i < this->_size; i++)
				_tab[i] = x._tab[i];
			return *this;
		}
        



    private:
    
		pointer			_tab;
		allocator_type	_alloc;
		size_type		_size;
		size_type		_size_capacity;
  

    };

        ////////// RELATIONAL OPERATORS ///////////

    template<class T, class Alloc>
	    bool operator==(const vector<T,Alloc>& left, const vector<T,Alloc>& right) 
        {
	        ft::vector<int>::const_iterator it = left.begin();
	        ft::vector<int>::const_iterator ite = left.end();
	        ft::vector<int>::const_iterator it2 = right.begin();
	        if (left.size() == right.size()) 
            {
		        while (it != ite)
                {
			        if(!(*it == *it2))
				        return false;
			        ++it;
			        ++it2;
		        }
		        return true;
	        }
	        else
		        return false;
        }

    template <class T, class Alloc>
	    bool operator!=(const vector<T,Alloc>& left, const vector<T,Alloc>& right) 
    {
	    return (!(left == right));
    }

    template <class T, class Alloc>
	    bool operator<(const vector<T,Alloc>& left, const vector<T,Alloc>& right) 
    {
	    ft::vector<int>::const_iterator first1 = left.begin();
	    ft::vector<int>::const_iterator first2 = right.begin();
	    ft::vector<int>::const_iterator last1 = left.end();
	    ft::vector<int>::const_iterator last2 = right.end();

	    while (first1!=last1)
  	    {
  		    if (first2==last2 || *first2<*first1) 
            {
			    return false;
		    }
  		    else if (*first1<*first2) 
            {
			    return true;
		    }
  		    ++first1; ++first2;
  	    }
  	    return (first2!=last2);  
    }

    template <class T, class Alloc>
	    bool operator<=(const vector<T,Alloc>& left, const vector<T,Alloc>& right) 
    {
	  return (!(left > right));
  	}

    template <class T, class Alloc>
	    bool operator>(const vector<T,Alloc>& left, const vector<T,Alloc>& right) 
    {
	  return (right < left);
  	}

    template <class T, class Alloc>
	    bool operator>=(const vector<T,Alloc>& left, const vector<T,Alloc>& right) 
    {
	  return (!(left < right));
  	}

    template< class T, class Alloc>
	    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) 
    {
		x.swap(y);
	}
}

#endif