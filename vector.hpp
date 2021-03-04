/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:01:06 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/04 16:56:48 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

template < class T, class Alloc = allocator<T> >
class vector
{
	public :

		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef std::size_t									size_type;
		typedef srd::ptrdiff_t								difference_type;
		typedef Alloc::reference							reference;
		typedef Alloc::const_reference						const_reference;
		typedef Alloc::pointer								pointer;
		typedef Alloc::const_pointer						const_pointer;
		typedef random_access_iterator<value_type>			iterator;
		typedef random_access_iterator<const value_type>	const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		explicit vector (const allocator_type& alloc = allocator_type())
		: _value(0), _size(0), _capacity(0)
		{}

		explicit vector (size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type())
		{ assign(n, val); }

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator_type())
		{ assign(first, last); }

		vector (const vector& x) // alloc here?
		{ *this = x; }

		virtual ~vector (void)
		{ delete[] _value; }

		vector& operator= (const vector& x)
		{
			if (_capacity)
				delete[] _value;
			_size = x.size();
			_capacity = x.capacity();
			new T[_capacity];
			for (size_t i = 0; i < _size; i++)
				_value[i] = x[i];
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
		size_type max_size (void) const
		{ return allocator.max_size(); }
		void resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
				erase(&_value[n], end());
			else if (n > _size)
			{
				if (n > _capacity)
					reserve(n);
				for (size_t i = _size; i < n; i++)
					_value[i] = val;
			}
			_size = n;
		}
		size_type capacity (void) const
		{ return _capacity; }
		bool empty (void) const
		{ return (_size != 0)}
		void reserve (size_type n)
		{
			if (n > _capacity)
			{
				T*		tmp = new T[n];

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
		void assign (InputIterator first, InputIterator last)
		{
			size_t	len = last - first;
			
			if (_capacity && _capacity < len)
			{
				delete[] _value;
				_value = new T[len];
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
			if (_capacity && _capacity < n)
			{
				delete[] _value;
				_value = new T[n];
			}
			for (size_t i = 0; i < n; i++)
			{
				_value[i] = val;
				first++;
			}
			_size = n;
		}
		void push_back (const value_type& val)
		{ insert(end(), val); }
		void pop_back (void)
		{ erase(end()); }
		iterator insert (iterator position, const value_type& val)
		{
			if (_capacity <= _size)
				reserve(_size >> 2);
			for (iterator it = end(); it != position; it--)
				*it = *(it - 1);
			*position = val;
			_size++;
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
			if (_capacity < _size + n)
				reserve(_size + n);
			for (iterator it = end(); it != position + n - 1; it--)
				*it = *(it - n);
			for (iterator it = position; it != position + n; it++)
				*it = val;
			_size += n;
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
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
		}
		iterator erase (iterator first, iterator last)
		{
			size_t	len = last - first;

			for (iterator it = first; it < last; it++)
				*it = *(it + len);
			_size -= len;
		}
		void swap (vector& x)
		{
			iterator	it2 = end();
			T			tmp;
	
			for (iterator it = begin(); it <= begin() + (_size / 2); it++)
			{
				tmp = *it;
				*it = *it2;
				*it2 = tmp;
				it2--;
			}
		}
		void clear (void)
		{
			_size = 0;
		}

		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}

		template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{}

	private :

		T*													_value;
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

#endif
