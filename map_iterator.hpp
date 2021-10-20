/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:48:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/20 17:41:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
#include "iterator.hpp"

namespace ft
{

template < class T >
class map_iterator : public iterator<bidirectional_iterator_tag, T>
{
	public :

		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef bidirectional_iterator_tag			iterator_category;

		map_iterator(void) : _value(0) {}
		map_iterator(reference value) : _value(&value) {}
		map_iterator(pointer value) : _value(value) {}
		map_iterator(const map_iterator& rhs) : _value(rhs._value) {}
		virtual ~map_iterator(void) {}

		operator map_iterator<const T>()
		{
			return map_iterator<const T>(*_value);
		}

		map_iterator&		operator=(pointer rhs)
		{
			_value = rhs;
			return (*this);
		}
		map_iterator&		operator=(const map_iterator& rhs)
		{
			_value = rhs._value;
			return (*this);
		}

		bool						operator==(const map_iterator& rhs) const
		{ return (_value == rhs._value); }
		bool						operator!=(const map_iterator& rhs) const
		{ return (_value != rhs._value); }
		bool						operator<(const map_iterator& rhs) const
		{ return (_value < rhs._value); }
		bool						operator>(const map_iterator& rhs) const
		{ return (_value > rhs._value); }
		bool						operator<=(const map_iterator& rhs) const
		{ return (_value <= rhs._value); }
		bool						operator>=(const map_iterator& rhs) const
		{ return (_value >= rhs._value); }

		reference					operator*(void) const
		{ return *_value; }
		pointer					operator->(void) const
		{ return _value; }
		reference					operator[](difference_type rhs) const
		{ return _value[rhs]; }

		map_iterator&		operator+=(difference_type rhs)
		{
			_value += rhs;
			return (*this);
		}
		map_iterator&		operator-=(difference_type rhs)
		{
			_value -= rhs;
			return (*this);
		}

		map_iterator		operator+(difference_type rhs) const
		{ return (map_iterator(_value + rhs)); }

		difference_type				operator-(const map_iterator& rhs) const
		{ return (_value - rhs._value); }
		map_iterator		operator-(difference_type rhs) const
		{ return (map_iterator(_value - rhs)); }

		map_iterator&		operator++(void)
		{
			++_value;
			return (*this);
		}
		map_iterator		operator++(int rhs)
		{
			(void)rhs;
			++_value;
			return (*this);
		}
		map_iterator&		operator--(void)
		{
			--_value;
			return (*this);
		}
		map_iterator		operator--(int rhs)
		{
			(void)rhs;
			--_value;
			return (*this);
		}

	private :

		pointer _value;
};

}

#endif