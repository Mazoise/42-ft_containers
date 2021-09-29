/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:01:04 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/29 19:35:57 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template < class T, class Container = ft::vector<T> >
class stack
{
	public :

		typedef Container								container_type;
		typedef typename Container::value_type			value_type;
		typedef typename Container::size_type			size_type;
		typedef typename Container::reference			reference;
		typedef typename Container::const_reference		const_reference;

		explicit stack(const Container& container = Container()) : _container(container)
		{}

		stack(const stack& other)
		{
			_container = other._container;
		}

		~stack()
		{}

		stack& operator=( const stack& rhs )
		{
			_container = rhs._container;
			return *this;
		}

		reference top()
		{
			return _container.back();
		}

		const_reference top() const
		{
			return _container.back();
		}

		bool empty() const
		{
			return _container.empty();
		}

		size_type size() const
		{
			return _container.size();
		}

		void push( const value_type& value )
		{
			_container.push_back(value);
		}

		void pop()
		{
			_container.pop_back();
		}

	protected:

		Container	_container;
};

template< class T, class Container >
bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return (lhs._container == rhs._container);
}

template< class T, class Container >
bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return (lhs._container != rhs._container);
}

template< class T, class Container >
bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return (lhs._container < rhs._container);
}

template< class T, class Container >
bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return (lhs._container <= rhs._container);
}

template< class T, class Container >
bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return (lhs._container > rhs._container);
}

template< class T, class Container >
bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return (lhs._container >= rhs._container);
}

}

#endif