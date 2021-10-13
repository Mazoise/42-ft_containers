/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:56:14 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/13 14:35:20 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

template <class key, class value>
void	print_map( ft::map<key, value> &test)
{
	size_t i = 0;
	typename  ft::map<key, value>::iterator		beg = test.begin();
	typename  ft::map<key, value>::iterator		end = test.end();
	std::cout << "size : " << test.size() << std::endl;
	for (typename  ft::map<key, value>::iterator it = beg; it != end; it++)
	{
		std::cout << "\"" << it->first << "\" : " << it->second;
		if (i % 5 == 4)
			std::cout << std::endl;
		else if (!i || i < test.size() - 1)
			std::cout << " - ";
		i++;
	}
	std::cout << std::endl;
}

void	map_tests(void)
{
	std::cout << std::endl << "MAP TESTS" << std::endl;
	ft::map<std::string, int> test;
	test.insert(std::make_pair<std::string, int>("Hello", 42));
	// print_map<std::string, int>(test);
	ft::map<int, std::string> test2;
	test2.insert(std::make_pair<int, std::string>(42, "Hello"));
	// print_map<int, std::string>(test2);
	test2.insert(std::make_pair<int, std::string>(21, "Hello2"));
	test2.insert(std::make_pair<int, std::string>(12, "Hello3"));
	test2.insert(std::make_pair<int, std::string>(15, "Hello4"));
	test2.insert(std::make_pair<int, std::string>(6, "Hello5"));
	// test2.insert(std::make_pair<int, std::string>(42, "Hello6"));
	test2.insert(std::make_pair<int, std::string>(43, "Hello7"));
	// test2.insert(std::make_pair<int, std::string>(43, "Hello8"));
	test2.insert(std::make_pair<int, std::string>(1, "Hello9"));
	test2.insert(std::make_pair<int, std::string>(-4, "Hello10"));
	test2.insert(std::make_pair<int, std::string>(8, "Hello11"));
	test2.insert(std::make_pair<int, std::string>(443, "Hello12"));
	test2.insert(std::make_pair<int, std::string>(72, "Hello13"));
	test2.insert(std::make_pair<int, std::string>(17, "Hello14"));
	// print_map<int, std::string>(test2);
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
}
