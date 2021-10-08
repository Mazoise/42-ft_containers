/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:25:50 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/08 16:01:00 by mchardin         ###   ########.fr       */
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
	 ft::vector<Awesome> test(21, 12);
	ft::stack<Awesome,  ft::vector<Awesome> > test2(test);
	print_stack<Awesome,  ft::vector<Awesome> >(test2);
}
