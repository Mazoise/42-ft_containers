/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:03:59 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/15 19:29:50 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Hello default !" << std::endl; }
		Awesome( int n ) : _n( 42 ) { std::cout << "Hello number !" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs; std::cout << "Hello copy !" << std::endl; }
		virtual ~Awesome(void) { std::cout << "Goodbye !" << std::endl; }

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

int main()
{
	ft::vector<int> test;

	std::cout << "Empty ? " << test.empty() << " / Capacity : " << test.capacity() << " / Size : " << test.size() << std::endl;
	for (size_t i = 0; i < 51; i++)
	{
		test.push_back(1);
		std::cout << "s: " << test.size() << ", c: " << test.capacity() << " / ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
	test.resize(72);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(4170);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	std::cout << test[72] << std::endl;
	std::cout << test[170] << std::endl;
	test.resize(62);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.insert(test.begin(), 200, 12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	ft::vector<int> test2(1, 1);
	std::cout << "s: " << test2.size() << ", c: " << test2.capacity() << std::endl;
	ft::vector<int> test3(12, 12);
	std::cout << "s: " << test3.size() << ", c: " << test3.capacity() << std::endl;
	ft::vector<int> test4(65, 65);
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	test4.reserve(12);
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	test4.reserve(66);
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	test4.reserve(128);
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	test4.reserve(1023);
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	test4.reserve(10252);
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	ft::vector<int> test5(test);
	std::cout << "s: " << test5.size() << ", c: " << test5.capacity() << std::endl;
	test4.swap(test3);
	for (size_t i = 0; i < test4.size(); i++)
	{
		std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << " / ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
	for (size_t i = 0; i < test3.size(); i++)
	{
		std::cout << "s: " << test3.size() << ", c: " << test3.capacity() << " / ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	test4.erase(test4.begin(), test4.begin() + 5);
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	test4.clear();
	std::cout << "s: " << test4.size() << ", c: " << test4.capacity() << std::endl;
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
	std::cout << test3.max_size() << std::endl;
	std::cout << test4.max_size() << std::endl;
	std::cout << test5.max_size() << std::endl;
	ft::vector<Awesome> test6(21, 12);
	for (size_t i = 0; i < test6.size(); i++)
	{
		std::cout << "s: " << test6.size() << ", c: " << test6.capacity() << " / ";
		std::cout << "value: " << test6[i] << " / ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
}
