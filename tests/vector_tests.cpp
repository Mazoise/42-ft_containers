/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:03:59 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/05 15:58:26 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

template <class T>
void	print_vector( ft::vector<T> &test)
{
	typename  ft::vector<T>::const_iterator		beg = test.begin();
	typename  ft::vector<T>::const_iterator		end = test.end();
	// typename  ft::vector<T>::const_reverse_iterator		rbeg = test.rbegin();
	// typename  ft::vector<T>::const_reverse_iterator		rend = test.rend();
	std::cout << "size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	for (typename  ft::vector<T>::const_iterator it = beg; it != end; it++)
	{
		std::cout << *it << " ";
		if (((it - beg) % 10 == 9) && it > beg)
			std::cout << std::endl;
	}
	// for (typename  ft::vector<T>::const_reverse_iterator it = rbeg; it != rend; it++)
	// {
	// 	std::cout << *it << " ";
	// 	if (((it - rbeg) % 10 == 9) && it > rbeg)
	// 		std::cout << std::endl;
	// }
	std::cout << std::endl;
}

template <class T>
void	push_pop_back_tests(void)
{
	std::cout << std::endl << "PUSH BACK & POP BACK TESTS" << std::endl;
	 ft::vector<T> test;

	std::cout << "Empty ? " << test.empty() << " / Capacity : " << test.capacity() << " / Size : " << test.size() << std::endl;
	for (size_t i = 0; i < 51; i++)
	{
		test.push_back(i);
		std::cout << test.size() << ": " << test.capacity() << " - ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
	print_vector<T>(test);
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	print_vector<T>(test);
}

template <class T>
void	resize_tests(void)
{
	std::cout << std::endl << "RESIZE TESTS" << std::endl;
	 ft::vector<T> test(12, 12);

	test.resize(72);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(4170);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(62);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
}

template <class T>
void	insert_tests()
{
	std::cout << std::endl << "INSERT TESTS" << std::endl;
	 ft::vector<T> test(1, 1);
	 ft::vector<T> test2(5, 5);

	test.reserve(10);
	test.insert(test.begin(), 70);
	print_vector<T>(test);
	test.insert(test.begin(), 200, 12);
	print_vector<T>(test);
	test.insert(test.begin() + 12, 200, 30);
	print_vector<T>(test);
	test.insert(test.end(), 12, 50);
	print_vector<T>(test);
	test.insert(test.end() - 1, 0, 60);
	print_vector<T>(test);
	test.insert(test.end() - 1, 70);
	print_vector<T>(test);
	test.insert(test.begin(), 70);
	print_vector<T>(test);
	test.insert(test.begin() + 2, 70);
	print_vector<T>(test);
	test.insert(test.begin() + 412, test2.begin(), test2.end());
	print_vector<T>(test);
	test.insert(test.begin() + 6, test2.begin(), test2.end());
	print_vector<T>(test);
	test.insert(test.end(), test2.begin(), test2.end());
	print_vector<T>(test);
	T myarray [] = { 501,502,503 };
  	test.insert (test.begin(), myarray, myarray+3);
	print_vector<T>(test);
}

template <class T>
void	reserve_tests(void)
{
	std::cout << std::endl << "RESERVE TESTS" << std::endl;
	 ft::vector<T> test(65, 7);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(66);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(128);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(1023);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(10252);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	try
	{
		test.reserve(test.max_size() + 1);
	}
	catch(std::length_error &le)
	{
		std::cout << "length error" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
	print_vector<T>(test);
}
 
template <class T>
void	copy_swap_tests(void)
{
	std::cout << std::endl << "COPY && SWAP TESTS" << std::endl;
	 ft::vector<T> test;
	for (size_t i = 0; i < 50; i++) { test.push_back(i); }
	 ft::vector<T> test_copy(test);
	for (size_t i = 0; i < test_copy.size(); i++) { test_copy[i] += 100; }
	print_vector<T>(test_copy);
	 ft::vector<T> test_range(test.begin() + 20, test.begin() + 30);
	print_vector<T>(test_range);
	test_copy.swap(test);
	print_vector<T>(test);
	print_vector<T>(test_copy);
	test_copy.swap(test_range);
	print_vector<T>(test_range);
	print_vector<T>(test_copy);
	test.swap(test_copy);
	print_vector<T>(test);
	print_vector<T>(test_copy);
}

template <class T>
void	reverse_it_tests(void)
{
	std::cout << std::endl << "REVERSE IT TESTS" << std::endl;
	 ft::vector<T> test;
	for (size_t i = 0; i < 12; i++) { test.push_back(i); }
	typename  ft::vector<T>::reverse_iterator		revbeg = test.rbegin();
	for (typename  ft::vector<T>::reverse_iterator it = revbeg; it != test.rend(); it++)
	{
		std::cout << *it << " ";
		if (!((revbeg - it) % 10) && it != revbeg)
			std::cout << std::endl;
	}
	std::cout << *(test.rbegin() + 2) << std::endl;
	std::cout << *(test.rend() - 8) << std::endl;
	std::cout << (test.rbegin() == revbeg) << std::endl;
	revbeg++;
	std::cout << *revbeg << std::endl;
	std::cout << (test.rbegin() == test.rend()) << std::endl;
	std::cout << (test.rbegin() <= test.rbegin()) << std::endl;
	std::cout << (test.rbegin() < test.rend()) << std::endl;
	std::cout << (test.rbegin() >= test.rend()) << std::endl;
	revbeg += 3;
	std::cout << *revbeg << std::endl;
	std::cout << std::endl;
}

template <class T>
void	erase_clear_tests(void)
{
	std::cout << std::endl << "ERASE && CLEAR TESTS" << std::endl;
	 ft::vector<T> test(31, 12);
	test.erase(test.begin(), test.begin() + 5);
	print_vector<T>(test);
	test.erase(test.begin() + 12, test.begin() + 16);
	print_vector<T>(test);
	test.clear();
	print_vector<T>(test);
}

void	max_size_tests(void)
{
	std::cout << std::endl << "MAX SIZE TESTS" << std::endl;
	 ft::vector<int> test(31, 12);
	 ft::vector<std::string> test2;
	 ft::vector<long long int> test3;
	 ft::vector<Awesome> test4;
	 ft::vector<unsigned int> test5(12, 340);
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
	std::cout << test3.max_size() << std::endl;
	std::cout << test4.max_size() << std::endl;
	std::cout << test5.max_size() << std::endl;
}

void	awesome_tests(void)
{
	std::cout << std::endl << "AWESOME TESTS" << std::endl;
	 ft::vector<Awesome> test(21, 12);
	print_vector<Awesome>(test);
	 ft::vector<Awesome> test2;
	print_vector<Awesome>(test2);
	// test2.push_back(12);
	// test2.push_back(8);
	// test2.push_back(16);
	print_vector<Awesome>(test2);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.assign(test2.begin(), test2.end());
	print_vector<Awesome>(test);
	test = test2;
	print_vector<Awesome>(test);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.insert(test.end(), test2.begin(), test2.end());
	print_vector<Awesome>(test);
	test.insert(test.begin(), test2.begin(), test2.end());
	test2 = test;
	print_vector<Awesome>(test);
	std::cout << "end awesome test" << std::endl;
}

void			vector_massive_tests()
{
	std::cout << std::endl << "MASSIVE TESTS" << std::endl;
	ft::vector<std::string> *test2 = new ft::vector<std::string>();
	std::string str;
	for (int i = 0; i < 50000; i++)
	{
		std::stringstream ss;
		ss << i;
		str = ss.str();
		test2->push_back(str);
	}
	print_vector<std::string>(*test2);
	for (int i = 49999; i >= 0; i--)
		std::cout << (*test2)[i] << std::endl;
	for (int i = 0; i < 50000; i++)
		std::cout << (*test2)[i] << std::endl;
}

template <class T>
void	stl_tests()
{
	ft::vector<T> test;

	for (size_t i = 0; i < 51; i++)
		test.push_back(i);
	std::cout << *(std::find<typename ft::vector<T>::iterator, T>(test.begin(), test.end(), 12)) << std::endl;
}

void	vector_tests()
{
	std::cout << std::endl << "VECTOR TESTS : INT" << std::endl;
	push_pop_back_tests<int>();
	resize_tests<int>();
	insert_tests<int>();
	reserve_tests<int>();
	copy_swap_tests<int>();
	reverse_it_tests<int>();
	erase_clear_tests<int>();
	max_size_tests();
	std::cout << std::endl << "VECTOR TESTS : AWESOME" << std::endl;
	push_pop_back_tests<Awesome>();
	resize_tests<Awesome>();
	insert_tests<Awesome>();
	reserve_tests<Awesome>();
	copy_swap_tests<Awesome>();
	reverse_it_tests<Awesome>();
	erase_clear_tests<Awesome>();
	awesome_tests();
	// vector_massive_tests();
	stl_tests<int>();
}
