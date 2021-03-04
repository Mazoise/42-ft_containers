/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:21:16 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/04 11:09:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector<int> test;

	std::cout << "Empty ? " << test.empty() << " / Capacity : " << test.capacity() << " / Size : " << test.size() << std::endl;
	for (size_t i = 0; i < 51; i++)
	{
		test.push_back(1);
		std::cout << "s: " << test.size() << ",c: " << test.capacity() << " / ";
		if (!(i % 10))
			std::cout << std::endl;
	}
	test.resize(72);
	std::cout << "s: " << test.size() << ",c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "s: " << test.size() << ",c: " << test.capacity() << std::endl;
	test.resize(170);
	std::cout << "s: " << test.size() << ",c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "s: " << test.size() << ",c: " << test.capacity() << std::endl;
	std::cout << test[72] << std::endl;
	std::cout << test[170] << std::endl;
	test.resize(62);
	std::cout << "s: " << test.size() << ",c: " << test.capacity() << std::endl;
	std::vector<int> test2(1, 1);
	std::cout << "s: " << test2.size() << ",c: " << test2.capacity() << std::endl;
	std::vector<int> test3(12, 12);
	std::cout << "s: " << test3.size() << ",c: " << test3.capacity() << std::endl;
	std::vector<int> test4(65, 65);
	std::cout << "s: " << test4.size() << ",c: " << test4.capacity() << std::endl;
}
