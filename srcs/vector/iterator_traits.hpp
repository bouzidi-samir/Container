/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:40:24 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/20 19:05:20 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


namespace ft {

    template <class Iterator>
        class iterator_traits{
            public:
                typedef typename Iterator::difference_type      difference_type;
                typedef typename Iterator::value_type           value_type;
                typedef typename Iterator::pointer              pointer;
                typedef typename Iterator::reference            reference;
                typedef typename Iterator::iterator_category    iterator_category;
        };
        
    template <class T>
        class iterator_traits<T*> {
            public:
                typedef ptrdiff_t                       difference_type;
                typedef T                               value_type;
                typedef T*                              pointer;
                typedef T&                              reference;
                typedef std::random_access_iterator_tag iterator_category;
        };

    template <class T>
        class iterator_traits<const T*> {
            public:
                typedef ptrdiff_t                       difference_type;
                typedef T                               value_type;
                typedef const T*                        pointer;
                typedef const T&                        reference;
                typedef std::random_access_iterator_tag iterator_category;
        };

}