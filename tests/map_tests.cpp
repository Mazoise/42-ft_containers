/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:56:14 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/04 18:35:59 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

template <class key, class value>
void	print_map( ft::map<key, value> &test)
{
	size_t i = 0;
	typename  ft::map<key, value>::const_iterator		beg = test.begin();
	typename  ft::map<key, value>::const_iterator		end = test.end();
	std::cout << "size : " << test.size() << std::endl;
	for (typename  ft::map<key, value>::const_iterator it = beg; it != end; it++)
	{
		std::cout << "\"" << it->first << "\" : " << it->second;
		if (i % 5 == 4 || i == test.size() - 1)
			std::cout << std::endl;
		else
			std::cout << " - ";
		i++;
	}
	std::cout << std::endl;
}

void							at_count_tests(ft::map<int, std::string>	*test)
{
	test->at(21) = "Bijour21";
	(*test)[43] = "Bijour43";
	print_map<int, std::string>(*test);
	try
	{
		(*test)[-7];
		(*test)[-23] = "bada";
		test->at(54) = "coucou";
	}
	catch(const std::out_of_range & e)
	{
		std::cout << "out of range" << '\n';
	}
	catch(const std::exception& e)
	{
		std::cout << "other error" << '\n';
	}
	print_map<int, std::string>(*test);
	std::cout << test->count(21) << " ";
	std::cout << test->count(-7) << " ";
	std::cout << test->count(-12) << " ";
	std::cout << test->count(42) << std::endl;
}

void		erase_tests(ft::map<int, std::string>	*test)
{
	test->erase(21);
	print_map<int, std::string>(*test);
	ft::map<int, std::string>::iterator it = test->end();
	it--;
	ft::map<int, std::string>::iterator it2 = it;
	it--;
	it--;
	it--;
	std::cout << "\"" << it->first << "\" : " << it->second << std::endl;
	std::cout << "\"" << it2->first << "\" : " << it2->second << std::endl;
	test->erase(it, it2);
	std::cout << "coucou" << std::endl;
	print_map<int, std::string>(*test);
	// test->erase(test->begin(), test->end());
	// print_map<int, std::string>(*test);
}

ft::map<int, std::string> *		insert_tests()
{
	std::cout << std::endl << "MAP TESTS" << std::endl;
	ft::map<std::string, int> test;
	test.insert(ft::make_pair<std::string, int>("Hello", 42));
	std::cout << std::endl << "MAP TESTS" << std::endl;
	print_map<std::string, int>(test);
	ft::map<int, std::string> *test2 = new ft::map<int, std::string>();
	test2->insert(ft::make_pair<int, std::string>(42, "Hello"));
	print_map<int, std::string>(*test2);
	test2->insert(ft::make_pair<int, std::string>(21, "Hello2"));
	test2->insert(ft::make_pair<int, std::string>(12, "Hello3"));
	test2->insert(ft::make_pair<int, std::string>(15, "Hello4"));
	test2->insert(ft::make_pair<int, std::string>(6, "Hello5"));
	test2->insert(ft::make_pair<int, std::string>(42, "Hello6"));
	test2->insert(ft::make_pair<int, std::string>(43, "Hello7"));
	test2->insert(ft::make_pair<int, std::string>(43, "Hello8"));
	test2->insert(ft::make_pair<int, std::string>(1, "Hello9"));
	test2->insert(ft::make_pair<int, std::string>(-4, "Hello10"));
	test2->insert(ft::make_pair<int, std::string>(8, "Hello11"));
	test2->insert(ft::make_pair<int, std::string>(443, "Hello12"));
	test2->insert(ft::make_pair<int, std::string>(72, "Hello13"));
	test2->insert(ft::make_pair<int, std::string>(17, "Hello14"));
	print_map<int, std::string>(*test2);
	return (test2);
}

void	map_tests()
{
	ft::map<int, std::string> * test = insert_tests();
	at_count_tests(test);
	erase_tests(test);
	// std::cout << test.max_size() << std::endl;
	// std::cout << test2.max_size() << std::endl;
}
