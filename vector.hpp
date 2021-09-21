/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:01:06 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/21 17:44:32 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "randomAccessIterator.hpp"
#include "reverseIterator.hpp"
#include "enableIf.hpp"
#include <limits>

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class vector
{
	public :

		typedef T													value_type;
		typedef Alloc												allocator_type;
		typedef std::size_t											size_type;
		typedef std::ptrdiff_t										difference_type;
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef value_type*											pointer;
		typedef const value_type*									const_pointer;
		typedef typename ft::randomAccessIterator<value_type>		iterator;
		typedef typename ft::randomAccessIterator<const value_type>	const_iterator;
		typedef ft::reverseIterator<iterator>						reverse_iterator;
		typedef ft::reverseIterator<const_iterator>					const_reverse_iterator;

		explicit vector (const allocator_type& alloc = allocator_type())
		: _value(0), _size(0), _capacity(0), _alloc(alloc)
		{}

		explicit vector (size_type n, const_reference val = value_type(),
		const allocator_type& alloc = allocator_type())
		: _value(0), _size(0), _capacity(0), _alloc(alloc)
		{ assign(n, val); }

		template <class InputIterator>
		vector (InputIterator first, typename ft::enable_if<!isIntegral<InputIterator>::value, InputIterator>::type last,
		const allocator_type& alloc = allocator_type())
		: _value(0), _size(0), _capacity(0), _alloc(alloc)
		{ assign(first, last); }

		vector (const vector& x)
		: _value(0), _size(0), _capacity(0)
		{ *this = x; }

		virtual ~vector (void)
		{
			if (_capacity)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_value[i]);
				_alloc.deallocate(_value, _capacity);
			}
		}

		vector& operator= (const vector& x)
		{
			_alloc = x._alloc;
			if (_capacity)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_value[i]);
				_alloc.deallocate(_value, _capacity);
				_capacity = 0;
			}
			reserve(x.size());
			_size = _capacity;
			for (size_type i = 0; i < _size; i++)
				_value[i] = x[i];
			return (*this);
		}
		iterator begin (void)
		{ return iterator(_value[0]); }
		const_iterator begin (void) const
		{ return const_iterator(_value[0]); }
		iterator end (void)
		{ return iterator(_value[_size]); }
		const_iterator end (void) const
		{ return const_iterator(_value[_size]); }
		reverse_iterator rbegin (void)
		{ return reverse_iterator(_value[_size - 1]); }
		const_reverse_iterator rbegin (void) const
		{ return const_reverse_iterator(_value[_size - 1]); }
		reverse_iterator rend (void)
		{ return reverse_iterator(_value[-1]); }
		const_reverse_iterator rend (void) const
		{ return const_reverse_iterator(_value[-1]); }

		size_type size (void) const
		{ return _size; }
		size_type max_size (void) const
		{ return _alloc.max_size(); }
		void resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
				_size = n;
			else if (n > _size)
			{
				if (n > _capacity)
					reserve(_size << 1 > n ? _size << 1 : n);
				for (size_type i = _size; i < n; i++)
					_value[i] = val;
			}
			_size = n;
		}
		size_type capacity (void) const
		{ return _capacity; }
		bool empty (void) const
		{ return (_size == 0);}
		void reserve (size_type n)
		{
			if (n > _alloc.max_size())
				throw (std::length_error("vector::reserve"));
			if (n > _capacity)
			{
				pointer		tmp = _alloc.allocate(n);

				if (_capacity)
				{
					for (size_type i = 0; i < _size; i++)
					{
						tmp[i] = _value[i];
					}
					_alloc.deallocate(_value, _capacity);
				}
				_value = tmp;
				_capacity = n;
			}
		}
		reference operator[] (size_type n)
		{ return at(n); }
		const_reference operator[] (size_type n) const
		{ return at(n); }
		reference at (size_type n)
		{
			if (n > _size)
				throw std::out_of_range("");
			else
				return _value[n];
		}
		const_reference at (size_type n) const
		{
			if (n > _size)
				throw std::out_of_range("");
			else
				return _value[n];
		}
		reference front (void)
		{ return _value[0]; }
		const_reference front (void) const
		{ return _value[0]; }
		reference back (void)
		{ return _value[_size - 1]; }
		const_reference	 back (void) const
		{ return _value[_size - 1]; }

		template <class InputIterator>
		void assign (InputIterator first, typename ft::enable_if<!isIntegral<InputIterator>::value, InputIterator>::type last)
		{
			size_type	len = last - first;
			if (_capacity < len)
			{
				if (_capacity)
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_value[i]);
					_alloc.deallocate(_value, _capacity);
					_capacity = 0;
				}
				reserve(len);
			}
			size_type	i = 0;
			for (InputIterator it = first; it != last; it++)
			{
				_value[i] = *it;
				i++;
			}
			_size = i;
		}
		void assign (size_type n, const_reference val)
		{
			if (_capacity < n)
			{
				if (_capacity)
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_value[i]);
					_alloc.deallocate(_value, _capacity);
					_capacity = 0;
				}
				reserve(n);
				// _value = reinterpret_cast<pointer>(operator new(sizeof(value_type) * n));
			}
			for (size_type i = 0; i < n; i++)
			{
				_value[i] = val;
			}
			_size = n;
		}
		void push_back (const_reference val)
		{
			if (_capacity <= _size)
				reserve(_size == 0 ? 1 : _size << 1);
			_value[_size] = val;
			_size++;
		}
		void pop_back (void)
		{ erase(end() - 1); }
		iterator insert (iterator position, const_reference val)
		{
			size_type		diff = position - begin();
	
			if (_capacity <= _size)
			{
				if (!_size)
					reserve(1);
				else
					reserve(_size << 1);
				position = begin() + diff;
			}
			for (iterator it = end(); it != position; it--)
				*it = *(it - 1);
			*position = val;
			_size++;
			return (position);
		}
		void insert (iterator position, size_type n, const_reference val)
		{
			size_type		diff = position - begin();

			if (_capacity < _size + n)
			{
				if (_size * 2 < _size + n)
					reserve(_size + n);
				else
					reserve(_size * 2);
				position = begin() + diff;
			}
			_size += n;
			for (iterator it = end() - 1; it != position + n - 1; it--)
				*it = *(it - n);
			for (iterator it = position; it != position + n; it++)
				*it = val;
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, typename ft::enable_if<!isIntegral<InputIterator>::value, InputIterator>::type last)
		{
			size_type	len = last - first;
			size_type	diff = position - begin();

			if (_capacity < _size + len)
			{
				if (_size * 2 < _size + len)
					reserve(_size + len);
				else
					reserve(_size * 2);
				position = begin() + diff;
			}
			_size += len;
			for (iterator it = end() - 1; it != position + len - 1; it--)
				*it = *(it - len);
			for (iterator it = position; it != position + len; it++)
			{
				*it = *first;
				first++;
			}
		}
		iterator erase (iterator position)
		{
			for (iterator it = position; it != end() - 1; it++)
				*it = *(it + 1);
			_size--;
			return (position);
		}
		iterator erase (iterator first, iterator last)
		{
			size_type	len = last - first;

			for (iterator it = first; it != end() - len; it++)
				*it = *(it + len);
			_size -= len;
			return (first);
		}
		void swap (vector& x) //swap with other vector !
		{
			pointer			tmp_value;
			size_type			tmp;

			tmp = _capacity;
			_capacity = x._capacity;
			x._capacity = tmp;
			tmp = _size;
			_size = x._size;
			x._size = tmp;
			tmp_value = _value;
			_value = x._value;
			x._value = tmp_value;
		}

		void clear (void) //_alloc.destroy?
		{
			_size = 0;
		}

	private :

		pointer											_value;
		size_type												_size;
		size_type												_capacity;
		allocator_type											_alloc;
};

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);
}

}

#endif
