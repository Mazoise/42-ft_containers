/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:48:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/20 19:25:54 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

# include <iostream>

namespace ft
{

template < class T>
class randomAccessIterator // : public std::iterator<std::random_access_iterator_tag, T>
{
	public :

		typedef T																				value_type;
		typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;

		randomAccessIterator(void) : _value(0) {}
		randomAccessIterator(value_type* value) : _value(value) {}
		randomAccessIterator(const randomAccessIterator& rhs) : _value(rhs._value) {}
		virtual ~randomAccessIterator(void) {}
		randomAccessIterator&		operator=(value_type* rhs)
		{
			_value = rhs;
			return (*this);
		}
		randomAccessIterator&		operator=(const randomAccessIterator& rhs)
		{
			_value = rhs._value;
			return (*this);
		}

		bool						operator==(const randomAccessIterator& rhs) const
		{ return (_value == rhs._value); }
		bool						operator!=(const randomAccessIterator& rhs) const
		{ return (_value != rhs._value); }
		bool						operator<(const randomAccessIterator& rhs) const
		{ return (_value < rhs._value); }
		bool						operator>(const randomAccessIterator& rhs) const
		{ return (_value > rhs._value); }
		bool						operator<=(const randomAccessIterator& rhs) const
		{ return (_value <= rhs._value); }
		bool						operator>=(const randomAccessIterator& rhs) const
		{ return (_value >= rhs._value); }

		value_type&					operator*(void) const
		{ return *_value; }
		value_type*					operator->(void) const
		{ return _value; }
		value_type&					operator[](difference_type rhs) const
		{ return _value[rhs]; }

		randomAccessIterator&		operator+=(difference_type rhs)
		{
			_value += rhs;
			return (*this);
		}
		randomAccessIterator&		operator-=(difference_type rhs)
		{
			_value -= rhs;
			return (*this);
		}
		randomAccessIterator		operator+(const randomAccessIterator& rhs)
		{ return (_value + rhs._value); }
		randomAccessIterator		operator+(difference_type rhs) const
		{ return (randomAccessIterator(_value + rhs)); }

		difference_type				operator-(const randomAccessIterator& rhs) const
		{ return (_value - rhs._value); }
		randomAccessIterator		operator-(difference_type rhs) const
		{ return (randomAccessIterator(_value - rhs)); }

		randomAccessIterator&		operator++(void)
		{
			++_value;
			return (*this);
		}
		randomAccessIterator		operator++(int rhs)
		{
			(void)rhs;
			++_value;
			return (*this);
		}
		randomAccessIterator&		operator--(void)
		{
			--_value;
			return (*this);
		}
		randomAccessIterator		operator--(int rhs)
		{
			(void)rhs;
			--_value;
			return (*this);
		}

	private :

		value_type* _value;
};

}

#endif