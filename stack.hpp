/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:01:04 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/28 19:12:29 by mchardin         ###   ########.fr       */
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

		typedef container_type			Container;
		typedef value_type				Container::value_type;
		typedef size_type				Container::size_type;
		typedef reference				Container::reference;
		typedef const_reference			Container::const_reference;

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
			this._container = rhs._container;
			return *this;
		}

		reference top()
		{
			return _container.top();
		}

		const_reference top() const
		{
			return _container.top();
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
			_container.push(value);
		}

		void pop()
		{
			_container.pop();
		}

	private:

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