/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:48:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/20 17:38:23 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp" 

namespace ft
{

template < class T>
class vector_iterator : public iterator<random_access_iterator_tag, T>
{
	public :

		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef random_access_iterator_tag			iterator_category;

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
			return (*this);
		}
		vector_iterator&		operator=(const vector_iterator& rhs)
		{
			_value = rhs._value;
			return (*this);
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
			return (*this);
		}
		vector_iterator&		operator-=(difference_type rhs)
		{
			_value -= rhs;
			return (*this);
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
			return (*this);
		}
		vector_iterator		operator++(int rhs)
		{
			(void)rhs;
			++_value;
			return (*this);
		}
		vector_iterator&		operator--(void)
		{
			--_value;
			return (*this);
		}
		vector_iterator		operator--(int rhs)
		{
			(void)rhs;
			--_value;
			return (*this);
		}

	private :

		pointer _value;
};

template < class Iterator>
class rev_vector_iterator
{
	public :

		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

		rev_vector_iterator(void) : _value(0) {}
		rev_vector_iterator(pointer value) : _value(value) {}
		rev_vector_iterator(reference value) : _value(&value) {}
		rev_vector_iterator(const rev_vector_iterator& rhs) : _value(rhs._value) {}
		virtual ~rev_vector_iterator(void) {}

		operator rev_vector_iterator<const Iterator>()
		{
			return rev_vector_iterator<const Iterator>(*_value);
		}

		rev_vector_iterator&		operator=(pointer rhs)
		{
			_value = rhs;
			return (*this);
		}
		rev_vector_iterator&		operator=(const rev_vector_iterator& rhs)
		{
			_value = rhs._value;
			return (*this);
		}

		bool						operator==(const rev_vector_iterator& rhs) const
		{ return (_value == rhs._value); }
		bool						operator!=(const rev_vector_iterator& rhs) const
		{ return (_value != rhs._value); }
		bool						operator<(const rev_vector_iterator& rhs) const
		{ return (_value > rhs._value); }
		bool						operator>(const rev_vector_iterator& rhs) const
		{ return (_value < rhs._value); }
		bool						operator<=(const rev_vector_iterator& rhs) const
		{ return (_value >= rhs._value); }
		bool						operator>=(const rev_vector_iterator& rhs) const
		{ return (_value <= rhs._value); }

		reference					operator*(void) const
		{ return *_value; }
		pointer					operator->(void) const
		{ return _value; }
		reference					operator[](difference_type rhs) const
		{ return _value[rhs]; }

		rev_vector_iterator&		operator+=(difference_type rhs)
		{
			_value -= rhs;
			return (*this);
		}
		rev_vector_iterator&		operator-=(difference_type rhs)
		{
			_value += rhs;
			return (*this);
		}
		rev_vector_iterator		operator+(difference_type rhs) const
		{ return (rev_vector_iterator(_value - rhs)); }

		difference_type		operator-(const rev_vector_iterator& rhs) const
		{ return (rhs._value - _value); }
		rev_vector_iterator		operator-(difference_type rhs) const
		{ return (rev_vector_iterator(_value + rhs)); }

		rev_vector_iterator&		operator++(void)
		{
			--_value;
			return (*this);
		}
		rev_vector_iterator		operator++(int rhs)
		{
			(void)rhs;
			--_value;
			return (*this);
		}
		rev_vector_iterator&		operator--(void)
		{
			++_value;
			return (*this);
		}
		rev_vector_iterator		operator--(int rhs)
		{
			(void)rhs;
			++_value;
			return (*this);
		}

	private :

		pointer _value;
};

}

#endif