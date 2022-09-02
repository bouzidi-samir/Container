/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:48:11 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/28 14:51:34 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./vector.hpp"
#include <vector>

std::vector<int> std_vector;
ft::vector<int> my_vector;

void fill_vector() {

    std_vector.push_back(12);
    my_vector.push_back(12);
    std_vector.push_back(2);
    my_vector.push_back(2);
    std_vector.push_back(7);
    my_vector.push_back(7);
    std_vector.push_back(15);
    my_vector.push_back(15);
}

void size_checking() {

    std::cout << "SIZE OF THE STD STACK:\n";
    std::cout << std_vector.size() << std::endl;
    std::cout << "SIZE OF THE MY STACK:\n";
    std::cout << my_vector.size() <<std::endl;
}

int main() {

    std::cout << "VECTOR TESTER:\n";
    fill_vector();
    size_checking();
    std::cout << "VECTOR POP_BACK().....\n";
    std_vector.pop_back();
    my_vector.pop_back();
    size_checking();
   
    return (0);
}