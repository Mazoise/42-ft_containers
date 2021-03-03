/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:01:06 by mchardin          #+#    #+#             */
/*   Updated: 2021/03/03 20:17:33 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

template < class T, class Alloc = allocator<T> >
class vector
{
	public :
		explicit								vector(const allocator_type& alloc = allocator_type()); //DEFAULT
		explicit								vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()); //FILL
		template <class InputIterator>			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); //RANGE
												vector(const vector& x); //COPY
		virtual									~vector(void);
		vector&									operator=(const vector& x);

		iterator								begin();
		const_iterator							begin() const;
		iterator								end();
		const_iterator							end() const;
		reverse_iterator						rbegin();
		const_reverse_iterator					rbegin() const;
		reverse_iterator						rend();
		const_reverse_iterator					rend() const;
		size_type								size() const;
		size_type								max_size() const;
		void									resize(size_type n, value_type val = value_type());
		size_type								capacity() const;
		bool									empty() const;
		void									reserve(size_type n);
		reference								operator[](size_type n);
		const_reference							operator[](size_type n) const;
		reference								at(size_type n) { return _value[n]; }
		const_reference							at(size_type n) const { return _value[n]; }
		reference								front();
		const_reference							front() const;
		reference								back();
		const_reference							back() const;
		template <class InputIterator> void		assign(InputIterator first, InputIterator last); //RANGE
		void									assign(size_type n, const value_type& val); //FILL
		void									push_back(const value_type& val);
		void									pop_back();
		iterator								insert(iterator position, const value_type& val); //SINGLE
		void									insert(iterator position, size_type n, const value_type& val); //FILL
		template <class InputIterator> void		insert(iterator position, InputIterator first, InputIterator last); //RANGE
		iterator								erase(iterator position);
		iterator								erase(iterator first, iterator last);
		void									swap(vector& x);
		void									clear();
		template <class T, class Alloc> bool	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc> bool	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc> bool	operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc> bool	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc> bool	operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc> bool	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc> void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y);

	private :

		T										*_value;
};

template <class Alloc>
class vector<bool,Alloc>
{
	class reference
	{
		friend class vector;
			reference();                                          // no public constructor
		public:
			~reference();
			operator bool () const;                               // convert to bool
			reference& operator= (const bool x);                  // assign from bool
			reference& operator= (const reference& x);            // assign from bit
			void flip();                                          // flip bit value.
	};
	void			flip();
	void			swap(vector& x);
	static void		swap (reference ref1, reference ref2);
	template <class T> struct hash;
	template <class Alloc> struct hash <vector<bool,Alloc>>;
}

#endif
