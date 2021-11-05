/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:25:50 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/05 16:24:43 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

template <class T, class Container>
void	print_stack(ft::stack<T, Container> &test)
{
	ft::stack<T, Container>	save = test;
	const T const_top = save.top();

	std::cout << "const top: " << const_top << std::endl;

	while (!save.empty())
	{
		std::cout << "top : " << save.top() << " - size : " << save.size() << std::endl;
		save.pop();
	}
}

void	stack_tests(void)
{
	std::cout << std::endl << "STACK TESTS" << std::endl;
	ft::vector<int> test_int(21, 12);
	ft::stack<int, ft::vector<int> > test_int2(test_int);
	print_stack<int, ft::vector<int> >(test_int2);
	ft::vector<Awesome> test(21, 12);
	ft::stack<Awesome,  ft::vector<Awesome> > test2(test);
	print_stack<Awesome,  ft::vector<Awesome> >(test2);
	ft::stack<int, ft::vector<int> > test3;
	ft::stack<int, ft::vector<int> > test4;
	test3.push(10);
	test3.push(20);
	test3.push(30);

	test4.push(10);
	test4.push(20);
	test4.push(30);

	if (test3==test4)
		std::cout << "test3 and test4 are equal\n";
	if (test3!=test4)
		std::cout << "test3 and test4 are not equal\n";
	if (test3<test4)
		std::cout << "test3 is less than test4\n";
	if (test3>test4)
		std::cout << "test3 is greater than test4\n";
	if (test3<=test4)
		std::cout << "test3 is less than or equal to test4\n";
	if (test3>=test4)
		std::cout << "test3 is greater than or equal to test4\n";

	if (test_int2==test4)
		std::cout << "test_int2 and test4 are equal\n";
	if (test_int2!=test4)
		std::cout << "test_int2 and test4 are not equal\n";
	if (test_int2<test4)
		std::cout << "test_int2 is less than test4\n";
	if (test_int2>test4)
		std::cout << "test_int2 is greater than test4\n";
	if (test_int2<=test4)
		std::cout << "test_int2 is less than or equal to test4\n";
	if (test_int2>=test4)
		std::cout << "test_int2 is greater than or equal to test4\n";

	if (test3==test_int2)
		std::cout << "test3 and test_int2 are equal\n";
	if (test3!=test_int2)
		std::cout << "test3 and test_int2 are not equal\n";
	if (test3<test_int2)
		std::cout << "test3 is less than test_int2\n";
	if (test3>test_int2)
		std::cout << "test3 is greater than test_int2\n";
	if (test3<=test_int2)
		std::cout << "test3 is less than or equal to test_int2\n";
	if (test3>=test_int2)
		std::cout << "test3 is greater than or equal to test_int2\n";

}
