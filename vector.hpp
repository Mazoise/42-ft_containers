/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:01:06 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/09 20:33:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "randomAccessIterator.hpp"
#include "enableIf.hpp"

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
		typedef std::reverse_iterator<iterator>						reverse_iterator;
		typedef std::reverse_iterator<const_iterator>				const_reverse_iterator;

		explicit vector (const allocator_type& alloc = allocator_type())
		: _value(0), _size(0), _capacity(0)
		{ (void)alloc; } //??

		explicit vector (size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type())
		: _value(0), _size(0), _capacity(0)
		{ assign(n, val); 		(void)alloc; } //??

		template <class InputIterator>
		vector (InputIterator first, typename ft::enable_if<InputIterator::input_iter, InputIterator>::type last,
		const allocator_type& alloc = allocator_type())
		: _value(0), _size(0), _capacity(0)
		{ assign(first, last); 		(void)alloc; } //??

		vector (const vector& x) // alloc here?
		{ *this = x; }

		virtual ~vector (void)
		{ delete[] _value; }

		vector& operator= (const vector& x)
		{
			if (_capacity)
				delete[] _value;
			_size = x.size();
			_capacity = x.size();
			_value = new value_type[_size]; //not same capacity !
			for (size_t i = 0; i < _size; i++)
				_value[i] = x[i];
			return (*this);
		}
		iterator begin (void)
		{ return &_value[0]; }
		const_iterator begin (void) const
		{ return &_value[0]; }
		iterator end (void)
		{ return &_value[_size - 1]; }
		const_iterator end (void) const
		{ return &_value[_size - 1]; }
		reverse_iterator rbegin (void)
		{ return &_value[_size - 1]; }
		const_reverse_iterator rbegin (void) const
		{ return &_value[_size - 1]; }
		reverse_iterator rend (void)
		{ return &_value[0]; }
		const_reverse_iterator rend (void) const
		{ return &_value[0]; }

		size_type size (void) const
		{ return _size; }
		// size_type max_size (void) const
		// { return Alloc.max_size(); }
		void resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
				_size = n;
			else if (n > _size)
			{
				if (n > _capacity)
					reserve(_size * 2 > n ? _size * 2 : n);
				for (size_t i = _size; i < n; i++)
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
			if (n > _capacity)
			{
				value_type*		tmp = new value_type[n];

				if (_capacity)
				{
					for (size_t i = 0; i < _size; i++)
						tmp[i] = _value[i];
					delete[] _value;
				}
				_value = tmp;
				_capacity = n;
			}
		}

		reference operator[] (size_type n)
		{ return _value[n]; }
		const_reference operator[] (size_type n) const
		{ return _value[n]; }
		reference at (size_type n)
		{ return _value[n]; }
		const_reference at (size_type n) const
		{ return _value[n]; }
		reference front (void)
		{ return _value[0]; }
		const_reference front (void) const
		{ return _value[0]; }
		reference back (void)
		{ return _value[_size - 1]; }
		const_reference	 back (void) const
		{ return _value[_size - 1]; }

		template <class InputIterator>
		void assign (InputIterator first, typename ft::enable_if<InputIterator::input_iter, InputIterator>::type last)
		{
			size_t	len = last - first;
			if (_capacity && _capacity < len)
			{
				delete[] _value;
				_value = new value_type[len];
			}
			size_t	i = 0;
			for (InputIterator it = first; it != last; it++)
			{
				_value[i] = it;
				i++;
			}
			_size = i;
		}
		void assign (size_type n, const value_type& val)
		{
			if (_capacity < n)
			{
				if (_capacity)
					delete[] _value;
				_value = new value_type[n];
				_capacity = n;
			}
			for (size_t i = 0; i < n; i++)
			{
				_value[i] = val;
			}
			_size = n;
		}
		void push_back (const value_type& val)
		{
			if (_capacity <= _size)
				reserve(_size == 0 ? 1 : _size * 2);
			_value[_size] = val;
			_size++;
		}
		void pop_back (void)
		{ erase(end() - 1); }
		iterator insert (iterator position, const value_type& val)
		{
			if (_capacity <= _size)
				reserve(_size == 0 ? 1 : _size * 2);
			for (iterator it = end(); it != position; it--)
				*it = *(it - 1);
			*position = val;
			_size++;
			return (position);
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
			if (_capacity < _size + n)
				reserve(_size + n);
			for (iterator it = end() + n - 1; it != position + n - 1; it--)
				*it = *(it - n);
			for (iterator it = position; it != position + n; it++)
				*it = val;
			(void)val;
			_size += n;
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, typename ft::enable_if<InputIterator::input_iter, InputIterator>::type last)
		{
			size_t	len = last - first;
			
			if (_capacity < _size + len)
				reserve(_size + len);
			for (iterator it = end(); it != position + len - 1; it--)
				*it = *(it - len);
			for (iterator it = position; it != position + len; it++)
			{
				*it = first;
				first++;
			}
			_size += len;
		}
		iterator erase (iterator position)
		{
			for (size_t i = position; i < _size - 1; i++)
				_value[i] = _value[i + 1];
			_size--;
			return (position);
		}
		iterator erase (iterator first, iterator last)
		{
			size_t	len = last - first;

			for (iterator it = first; it != last; it++)
				*it = *(it + len);
			_size -= len;
			return (first);
		}
		void swap (vector& x) //swap with other vector !
		{
			value_type*		tmp_value;
			size_t			tmp;

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

		void clear (void) //destroy?
		{
			_size = 0;
		}

		// template <class T, class Alloc>
		// bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		// {}
		// template <class T, class Alloc>
		// bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		// {}
		// template <class T, class Alloc>
		// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		// {}
		// template <class T, class Alloc>
		// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		// {}
		// template <class T, class Alloc>
		// bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		// {}
		// template <class T, class Alloc>
		// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		// {}

		// template <class T, class Alloc>
		// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		// {}

	private :

		value_type*													_value;
		size_t												_size;
		size_t												_capacity;
};

// template <class Alloc>
// class vector<bool,Alloc>
// {
// 	class reference
// 	{
// 		friend class vector;
// 			reference (void);                                          // no public constructor
// 		public:
// 			~reference (void);
// 			operator bool (void) const;                               // convert to bool
// 			reference& operator= (const bool x);                  // assign from bool
// 			reference& operator= (const reference& x);            // assign from bit
// 			void flip (void);                                          // flip bit value.
// 	};
// 	void			flip (void);
// 	void			swap (vector& x);
// 	static void		swap (reference ref1, reference ref2);
// 	template <class T> struct hash;
// 	template <class Alloc> struct hash <vector<bool,Alloc>>;
// }

}

#endif
