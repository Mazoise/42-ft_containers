/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:01:06 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/04 11:36:28 by mchardin         ###   ########.fr       */
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

		explicit											vector (const allocator_type& alloc = allocator_type ())
		: _value(0), _size(0), _capacity(0)
		{} //DEFAULT
		explicit											vector (size_type n, const value_type& val = value_type (), const allocator_type& alloc = allocator_type ())
		: _value(new T(n)), _size(n), _capacity(n) //use alloc?
		{
			insert(begin(), n, val);
		} //FILL
		template <class InputIterator>
															vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type ())
		: _value(new T(last - first)), _size(last - first), _capacity(last - first)
		{
			insert(begin(), first, last);
		} //RANGE
															vector (const vector& x) // alloc here?
		{ *this = x; } //COPY
		virtual												~vector (void)
		{ delete[] _value; }
		vector&												operator= (const vector& x)
		{
			_size = x.size();
			_capacity = x.capacity();
			// alloc?
			for (size_t i = 0; i < _size; i++)
				_value[i] = x[i];
		}

		iterator											begin ()
		{ return &_value[0]; }
		const_iterator										begin () const
		{ return &_value[0]; }
		iterator											end ()
		{ return &_value[_size - 1]; }
		const_iterator										end () const
		{ return &_value[_size - 1]; }
		reverse_iterator									rbegin ()
		{ return &_value[_size - 1]; }
		const_reverse_iterator								rbegin () const
		{ return &_value[_size - 1]; }
		reverse_iterator									rend ()
		{ return &_value[0]; }
		const_reverse_iterator								rend () const
		{ return &_value[0]; }
		size_type											size () const
		{ return _size; }
		size_type											max_size () const
		{ return allocator.max_size(); }
		void												resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
				erase(&_value[n], end());
			else if (n > _size)
			{
				if (n > _capacity)
					; //realloc_size = n
				for (size_t i = _size; i < n; i++)
					_value[i] = val;
			}
			_size = n;
		}
		size_type											capacity () const
		{ return _capacity; }
		bool												empty () const
		{ return (_size != 0)}
		void												reserve (size_type n)
		{}
		reference											operator[] (size_type n)
		{ return _value[n]; }
		const_reference										operator[] (size_type n) const
		{ return _value[n]; }
		reference											at (size_type n)
		{ return _value[n]; }
		const_reference										at (size_type n) const
		{ return _value[n]; }
		reference											front ()
		{ return _value[0]; }
		const_reference										front () const
		{ return _value[0]; }
		reference											back ()
		{ return _value[_size - 1]; }
		const_reference										back () const
		{ return _value[_size - 1]; }
		template <class InputIterator>
		void												assign (InputIterator first, InputIterator last)
		{} //RANGE
		void												assign (size_type n, const value_type& val)
		{} //FILL
		void												push_back (const value_type& val)
		{}
		void												pop_back ()
		{}
		iterator											insert (iterator position, const value_type& val)
		{} //SINGLE
		void												insert (iterator position, size_type n, const value_type& val)
		{} //FILL
		template <class InputIterator>
		void												insert (iterator position, InputIterator first, InputIterator last)
		{} //RANGE
		iterator											erase (iterator position)
		{}
		iterator											erase (iterator first, iterator last)
		{}
		void												swap (vector& x)
		{}
		void												clear ()
		{}
		template <class T, class Alloc>
		bool												operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool												operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool												operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool												operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool												operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		bool												operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{}
		template <class T, class Alloc>
		void												swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
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
// 			reference ();                                          // no public constructor
// 		public:
// 			~reference ();
// 			operator bool () const;                               // convert to bool
// 			reference& operator= (const bool x);                  // assign from bool
// 			reference& operator= (const reference& x);            // assign from bit
// 			void flip ();                                          // flip bit value.
// 	};
// 	void			flip ();
// 	void			swap (vector& x);
// 	static void		swap (reference ref1, reference ref2);
// 	template <class T> struct hash;
// 	template <class Alloc> struct hash <vector<bool,Alloc>>;
// }

#endif
