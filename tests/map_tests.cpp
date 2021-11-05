/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:56:14 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/05 17:01:23 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"
#include <stdlib.h>

template <class key, class value>
void	print_map( ft::map<key, value> &test)
{
	size_t i = 0;
	typename  ft::map<key, value>::const_iterator		beg = test.begin();
	typename  ft::map<key, value>::const_iterator		end = test.end();
	typename  ft::map<key, value>::const_reverse_iterator		rbeg = test.rbegin();
	typename  ft::map<key, value>::const_reverse_iterator		rend = test.rend();
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
	for (typename  ft::map<key, value>::const_reverse_iterator it = rbeg; it != rend; it++)
	{
		std::cout << "\"" << it->first << "\" : " << it->second;
		if (i % 5 == 4 || i == test.size() - 1)
			std::cout << std::endl;
		else
			std::cout << " - ";
		i++;
	}
}

template <class T>
void							at_count_tests(ft::map<T, std::string>	*test)
{
	test->at(21) = "Bijour21";
	(*test)[43] = "Bijour43";
	print_map<T, std::string>(*test);
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
	print_map<T, std::string>(*test);
	std::cout << test->count(21) << " ";
	std::cout << test->count(-7) << " ";
	std::cout << test->count(-12) << " ";
	std::cout << test->count(42) << std::endl;
}

template <class T>
void		erase_tests(ft::map<T, std::string>	*test)
{
	test->erase(21);
	print_map<T, std::string>(*test);
	typename ft::map<T, std::string>::iterator it = test->end();
	it--;
	typename ft::map<T, std::string>::iterator it2 = it;
	it--;
	it--;
	it--;
	std::cout << "\"" << it->first << "\" : " << it->second << std::endl;
	std::cout << "\"" << it2->first << "\" : " << it2->second << std::endl;
	test->erase(it, it2);
	std::cout << "coucou" << std::endl;
	print_map<T, std::string>(*test);
	test->erase(test->begin(), test->end());
	print_map<T, std::string>(*test);
}

template <class T>
ft::map<T, std::string> *		insert_tests()
{
	typename ft::map<std::string, T> test;
	test.insert(ft::make_pair<std::string, T>("Hello", 42));
	print_map<std::string, T>(test);
	typename ft::map<T, std::string> *test2 = new ft::map<T, std::string>();
	test2->insert(ft::make_pair<T, std::string>(42, "Hello"));
	print_map<T, std::string>(*test2);
	test2->insert(ft::make_pair<T, std::string>(21, "Hello2"));
	test2->insert(ft::make_pair<T, std::string>(12, "Hello3"));
	test2->insert(ft::make_pair<T, std::string>(15, "Hello4"));
	test2->insert(ft::make_pair<T, std::string>(6, "Hello5"));
	test2->insert(ft::make_pair<T, std::string>(42, "Hello6"));
	test2->insert(ft::make_pair<T, std::string>(43, "Hello7"));
	test2->insert(ft::make_pair<T, std::string>(43, "Hello8"));
	test2->insert(ft::make_pair<T, std::string>(1, "Hello9"));
	test2->insert(ft::make_pair<T, std::string>(-4, "Hello10"));
	test2->insert(ft::make_pair<T, std::string>(8, "Hello11"));
	test2->insert(ft::make_pair<T, std::string>(443, "Hello12"));
	test2->insert(ft::make_pair<T, std::string>(72, "Hello13"));
	test2->insert(ft::make_pair<T, std::string>(17, "Hello14"));
	print_map<T, std::string>(*test2);
	return (test2);
}

void							massive_tests()
{
	std::cout << std::endl << "MASSIVE TESTS" << std::endl;
	ft::map<int, std::string> *test2 = new ft::map<int, std::string>();
	std::string str;
	for (int i = 0; i < 50000; i++)
	{
		std::stringstream ss;
		ss << i;
		str = ss.str();
		test2->insert(ft::make_pair<int, std::string>(i, str));
	}
	print_map<int, std::string>(*test2);
	for (int i = 49999; i >= 0; i--)
		std::cout << (*test2)[i] << std::endl;
	for (int i = 0; i < 50000; i++)
		std::cout << (*test2)[i] << std::endl;
	delete test2;
}

template <class T>
void	relational_operator_tests()
{
	typename ft::map<char,T> test1;
	typename ft::map<char,T> test2;

	test1['a']=100;
	test1['b']=200;

	test2['a']=100;
	test2['b']=200;

	if (test1 == test2)
		std::cout << "test1 and test2 are equal" << std::endl;
	if (test1 != test2)
		std::cout << "test1 and test2 are not equal" << std::endl;
	if (test1 < test2)
		std::cout << "test1 is less than test2" << std::endl;
	if (test1 > test2)
		std::cout << "test1 is greater than test2" << std::endl;
	if (test1 <= test2)
		std::cout << "test1 is less than or equal to test2" << std::endl;
	if (test1 >= test2)
		std::cout << "test1 is greater than or equal to test2" << std::endl;

	test1['a']=400;

	if (test1 == test2)
		std::cout << "test1 and test2 are equal" << std::endl;
	if (test1 != test2)
		std::cout << "test1 and test2 are not equal" << std::endl;
	if (test1 < test2)
		std::cout << "test1 is less than test2" << std::endl;
	if (test1 > test2)
		std::cout << "test1 is greater than test2" << std::endl;
	if (test1 <= test2)
		std::cout << "test1 is less than or equal to test2" << std::endl;
	if (test1 >= test2)
		std::cout << "test1 is greater than or equal to test2" << std::endl;

	test1['a']=100;
	test1['c']=20;

	if (test1 == test2)
		std::cout << "test1 and test2 are equal" << std::endl;
	if (test1 != test2)
		std::cout << "test1 and test2 are not equal" << std::endl;
	if (test1 < test2)
		std::cout << "test1 is less than test2" << std::endl;
	if (test1 > test2)
		std::cout << "test1 is greater than test2" << std::endl;
	if (test1 <= test2)
		std::cout << "test1 is less than or equal to test2" << std::endl;
	if (test1 >= test2)
		std::cout << "test1 is greater than or equal to test2" << std::endl;
}

template <class T>
void	bound_tests(ft::map<T, std::string>	*test)
{
	ft::pair<typename ft::map<T, std::string>::iterator, typename ft::map<T, std::string>::iterator> ret;
	ret = test->equal_range(42);

	std::cout << "Lower bound";
	std::cout << "\"" << ret.first->first << "\" : " << ret.first->second << std::endl;

	std::cout << "Upper bound";
	std::cout << "\"" << ret.second->first << "\" : " << ret.second->second << std::endl;
}

template <class T>
void	copy_swap_tests(ft::map<T, std::string>	*test)
{
	typename ft::map<T, std::string>	test2(*test);
	print_map<T, std::string>(test2);
	test->erase(42);
	test->erase(72);
	test->erase(6);
	swap(*test, test2);
	print_map<T, std::string>(test2);
	print_map<T, std::string>(*test);
}

void	map_tests()
{
	ft::map<int, std::string> * test = insert_tests<int>();
	at_count_tests<int>(test);
	relational_operator_tests<int>();
	bound_tests<int>(test);
	copy_swap_tests<int>(test);
	erase_tests<int>(test);
	ft::map<Awesome, std::string> * test2 = insert_tests<Awesome>();
	at_count_tests<Awesome>(test2);
	relational_operator_tests<Awesome>();
	bound_tests<Awesome>(test2);
	copy_swap_tests<Awesome>(test2);
	erase_tests<Awesome>(test2);
	massive_tests();
	delete test;
}
