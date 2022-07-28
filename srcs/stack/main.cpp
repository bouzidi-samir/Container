/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouzidi <sbouzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:17:41 by sbouzidi          #+#    #+#             */
/*   Updated: 2022/07/28 10:57:36 by sbouzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./stack.hpp"
#include <stack>

std::stack<int> std_stack;
ft::stack<int> my_stack;

void fill_stack() {

    std_stack.push(12);
    my_stack.push(12);
    std_stack.push(2);
    my_stack.push(2);
    std_stack.push(7);
    my_stack.push(7);
    std_stack.push(15);
    my_stack.push(15);
}

void size_checking() {

    std::cout << "SIZE OF THE STD STACK:\n";
    std::cout << std_stack.size() << std::endl;
    std::cout << "SIZE OF THE MY STACK:\n";
    std::cout << my_stack.size() <<std::endl;
}

int main() {

    std::cout << "STACK TESTER:\n";
    fill_stack();
    size_checking();
    std::cout << "STACK POP()\n";
    std_stack.pop();
    my_stack.pop();
    size_checking();
    return(0);
}