/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:25:50 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/05 16:02:22 by mchardin         ###   ########.fr       */
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
	ft::stack<int,  ft::vector<int> > test_int2(test_int);
	print_stack<int,  ft::vector<int> >(test_int2);
	ft::vector<Awesome> test(21, 12);
	ft::stack<Awesome,  ft::vector<Awesome> > test2(test);
	print_stack<Awesome,  ft::vector<Awesome> >(test2);
}
