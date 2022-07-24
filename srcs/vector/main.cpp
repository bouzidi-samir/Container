/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:48:11 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/17 16:37:37 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./vector.hpp"

int main() {

    std::cout << "           --- Constructors Test ---             \n";
    {

        ft::vector<int>  test1; 
 
        ft::vector<int>::iterator ite = &test1.back();
        ft::vector<int>::iterator it = &test1[2];
    
        //ft::vector<int>  test2(1, 2, 3); 
        //ft::vector<int>  test3; 

        std::cout << "The size of test1 is: " << *ite << std::endl;
        //std::cout << "The size of test2 is: " << test2.size() << std::endl;
        //std::cout << "The size of test3 is: " << test3.size() << std::endl;
       
    }

    return (0);
}