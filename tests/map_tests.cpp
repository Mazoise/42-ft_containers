/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:56:14 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/12 16:01:13 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

// template <class T, class Container>
// void	print_map(ft::map<T, Container> &test)
// {
// 	ft::map<T, Container>	save = test;
// 	const T const_top = save.top();

// 	std::cout << "const top: " << const_top << std::endl;

// 	while (!save.empty())
// 	{
// 		std::cout << "top : " << save.top() << " - size : " << save.size() << std::endl;
// 		save.pop();
// 	}
// }

void	map_tests(void)
{
	std::cout << std::endl << "MAP TESTS" << std::endl;
	ft::map<std::string, int> test;
	std::pair<std::string, int> test_pair;
	test_pair = std::make_pair("Hello", 42);
	test.insert(test_pair);
	// print_map<std::string, int>(test);
}
