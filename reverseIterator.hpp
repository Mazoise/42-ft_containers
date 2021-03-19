/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:00:17 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/19 18:11:42 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

# include <iostream>

namespace ft
{

template < class Iterator>
class reverseIterator
{
	public :

		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;

		reverseIterator(void) : _value(0) {}
		reverseIterator(value_type* value) : _value(value) {}
		reverseIterator(const reverseIterator& rhs) : _value(rhs._value) {}
		virtual ~reverseIterator(void) {}
		reverseIterator&		operator=(value_type* rhs)
		{
			_value = rhs;
			return (*this);
		}
		reverseIterator&		operator=(const reverseIterator& rhs)
		{
			_value = rhs._value;
			return (*this);
		}

		bool						operator==(const reverseIterator& rhs) const
		{ return (_value == rhs._value); }
		bool						operator!=(const reverseIterator& rhs) const
		{ return (_value != rhs._value); }
		bool						operator<(const reverseIterator& rhs) const
		{ return (_value < rhs._value); }
		bool						operator>(const reverseIterator& rhs) const
		{ return (_value > rhs._value); }
		bool						operator<=(const reverseIterator& rhs) const
		{ return (_value <= rhs._value); }
		bool						operator>=(const reverseIterator& rhs) const
		{ return (_value >= rhs._value); }

		value_type&					operator*(void) const
		{ return *_value; }
		value_type*					operator->(void) const
		{ return _value; }
		value_type&					operator[](difference_type rhs) const
		{ return _value[rhs]; }

		reverseIterator&		operator+=(difference_type rhs)
		{
			_value -= rhs;
			return (*this);
		}
		reverseIterator&		operator-=(difference_type rhs)
		{
			_value += rhs;
			return (*this);
		}
		reverseIterator		operator+(const reverseIterator& rhs)
		{ return (_value - rhs._value); }
		reverseIterator		operator+(difference_type rhs) const
		{ return (reverseIterator(_value - rhs)); }

		difference_type				operator-(const reverseIterator& rhs) const
		{ return (_value + rhs._value); }
		reverseIterator		operator-(difference_type rhs) const
		{ return (reverseIterator(_value + rhs)); }

		reverseIterator&		operator++(void)
		{
			--_value;
			return (*this);
		}
		reverseIterator		operator++(int rhs)
		{
			(void)rhs;
			--_value;
			return (*this);
		}
		reverseIterator&		operator--(void)
		{
			++_value;
			return (*this);
		}
		reverseIterator		operator--(int rhs)
		{
			(void)rhs;
			++_value;
			return (*this);
		}

	private :

		value_type* _value;
};

}

#endif