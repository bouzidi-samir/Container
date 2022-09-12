/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscalisi <gscalisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:29:15 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/09/12 16:09:08 by gscalisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{

    template<bool, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { 
        typedef T type; 
    };

    template <bool is_integral, typename T>
        struct is_integral_struct {
            typedef T type;
            static const bool value = is_integral;
        };
    
    //Je set cahque type avec ma structure:

    template <typename>
        struct is_integral_type : public is_integral_struct<false, bool> {};

    template <>
        struct is_integral_type<bool> : public is_integral_struct<true, bool> {};

    template <>
        struct is_integral_type<char> : public is_integral_struct<true, char> {};
    
    template <>
        struct is_integral_type<signed char> : public is_integral_struct<true, signed char> {};
    
    template <>
        struct is_integral_type<short int> : public is_integral_struct<true, short int> {};
        
    template <>
        struct is_integral_type<int> : public is_integral_struct<true, int> {};

    template <>
        struct is_integral_type<long int> : public is_integral_struct<true, long int> {};

    template <>
        struct is_integral_type<long long int> : public is_integral_struct<true, long long int> {};

    template <>
        struct is_integral_type<unsigned char> : public is_integral_struct<true, unsigned char> {};

    template <>
        struct is_integral_type<unsigned short int> : public is_integral_struct<true, unsigned short int> {};

    template <>
        struct is_integral_type<unsigned int> : public is_integral_struct<true, unsigned int> {};

    template <>
        struct is_integral_type<unsigned long int> : public is_integral_struct<true, unsigned long int> {};
    
    template <>
        struct is_integral_type<unsigned long long int> : public is_integral_struct<true, unsigned long long int> {};

    template <typename T>
        struct is_integral : public is_integral_type<T> { };    

		
	template <class InputIterator1, class InputIterator2>
  		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			while (first1!=last1) {
				if (!(*first1 == *first2))
				return false;
				++first1; ++first2;
			}
		return true;
		}

	template <class InputIterator1, class InputIterator2>
  		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
		{
			while (first1!=last1)
			{
				if (first2==last2 || *first2<*first1) return false;
				else if (*first1<*first2) return true;
				++first1; ++first2;
			}
			return (first2!=last2);
		}
			  
		
    
}
#endif