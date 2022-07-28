/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:16:06 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/28 10:58:12 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "../vector/vector.hpp"
#include <iostream>

namespace ft
{
    template < class T, class Container = ft::vector<T> >
    class stack
    {
        public:

            typedef T	value_type;

            typedef Container container_type;

            typedef size_t  size_type;

        explicit stack (const container_type &cont = container_type())
        {
            this->_cont = cont;
        }

        size_type size() const {
            return this->_cont.size();
        }

        bool empty() const {
            return this->_cont.empty();
        }
        
        value_type &top() {
            return _cont.back();
        }

        const value_type &top() const {
            return _cont.back();
        }

        void push(value_type const &value) {
            _cont.push_back(value);
        }

        void pop() {
            _cont.pop_back();
        }

        Container getContainer() const {
            return this->_cont;
        }

        private:
            container_type _cont;
    };

    template <class T, class Container>
        bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { 
            return (lhs.getContainer() == rhs.getContainer());
        }

    template <class T, class Container>
        bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { 
            return (lhs.getContainer() != rhs.getContainer());
        }

    template <class T, class Container>
        bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { 
            return (lhs.getContainer() < rhs.getContainer());
        }

    template <class T, class Container>
        bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { 
            return (lhs.getContainer() > rhs.getContainer());
        }

    template <class T, class Container>
        bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { 
            return (lhs.getContainer() <= rhs.getContainer());
        }

    template <class T, class Container>
        bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { 
            return (lhs.getContainer() >= rhs.getContainer());
        }
}

#endif
