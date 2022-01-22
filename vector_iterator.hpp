/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:48:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/29 16:34:01 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp" 

namespace ft
{

template < class T>
class vector_iterator : public ft::iterator<std::random_access_iterator_tag, T>
{
	public :

		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category			iterator_category;

		vector_iterator(void) : _value(0) {}
		vector_iterator(reference value) : _value(&value) {}
		vector_iterator(pointer value) : _value(value) {}
		vector_iterator(const vector_iterator& rhs) : _value(rhs._value) {}
		virtual ~vector_iterator(void) {}

		operator vector_iterator<const T>()
		{
			return vector_iterator<const T>(*_value);
		}

		vector_iterator&		operator=(pointer rhs)
		{
			_value = rhs;
			return *this;
		}
		vector_iterator&		operator=(const vector_iterator& rhs)
		{
			_value = rhs._value;
			return *this;
		}

		bool						operator==(const vector_iterator& rhs) const
		{ return (_value == rhs._value); }
		bool						operator!=(const vector_iterator& rhs) const
		{ return (_value != rhs._value); }
		bool						operator<(const vector_iterator& rhs) const
		{ return (_value < rhs._value); }
		bool						operator>(const vector_iterator& rhs) const
		{ return (_value > rhs._value); }
		bool						operator<=(const vector_iterator& rhs) const
		{ return (_value <= rhs._value); }
		bool						operator>=(const vector_iterator& rhs) const
		{ return (_value >= rhs._value); }

		reference					operator*(void) const
		{ return *_value; }
		pointer					operator->(void) const
		{ return _value; }
		reference					operator[](difference_type rhs) const
		{ return _value[rhs]; }

		vector_iterator&		operator+=(difference_type rhs)
		{
			_value += rhs;
			return *this;
		}
		vector_iterator&		operator-=(difference_type rhs)
		{
			_value -= rhs;
			return *this;
		}

		vector_iterator		operator+(difference_type rhs) const
		{ return (vector_iterator(_value + rhs)); }

		difference_type				operator-(const vector_iterator& rhs) const
		{ return (_value - rhs._value); }
		vector_iterator		operator-(difference_type rhs) const
		{ return (vector_iterator(_value - rhs)); }

		vector_iterator&		operator++(void)
		{
			++_value;
			return *this;
		}
		vector_iterator		operator++(int)
		{
			vector_iterator tmp = *this;
			++(*this);
			return (tmp);
		}
		vector_iterator&		operator--(void)
		{
			--_value;
			return *this;
		}
		vector_iterator		operator--(int)
		{
			vector_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	private :

		pointer _value;
};

}

#endif