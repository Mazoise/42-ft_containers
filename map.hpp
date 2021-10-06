/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:00:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/06 21:17:46 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "vector_iterator.hpp"
#include "enableIf.hpp"
#include <limits>

namespace ft
{

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
	public :

		typedef key_type				Key;
		typedef mapped_type				T;
		typedef value_type				std::pair<const Key, T>;
		typedef size_type				std::size_t;
		typedef difference_type			std::ptrdiff_t;
		typedef key_compare				Compare;
		typedef allocator_type			Allocator;
		typedef reference				value_type&;
		typedef const_reference			const value_type&;
		typedef pointer					Allocator::pointer;
		typedef const_pointer			Allocator::const_pointer;
		typedef iterator				map_iterator<value_type>;
		typedef const_iterator			map_iterator<const value_type>;
		typedef reverse_iterator		std::reverse_iterator<iterator>;
		typedef const_reverse_iterator	std::reverse_iterator<const_iterator>;

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		public :
			typedef bool					result_type;
			typedef value_type				first_argument_type;
			typedef value_type				second_argument_type;

			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return (comp(lhs.first, rhs.first));
			}
		protected :

			value_compare(Compare c) : comp(c) {}
			Compare comp;
	};

		map();
		explicit map(const Compare& comp, const Allocator& alloc = Allocator());
		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
		map(const map& other);
		~map();
		map& operator=(const map& other);
		allocator_type get_allocator() const;

		T& at(const Key& key);
		const T& at(const Key& key ) const;
		T& operator[](const Key& key);
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

bool empty() const;
size_type size() const;
size_type max_size() const;
void clear();
std::pair<iterator, bool> insert(const value_type& value);
iterator insert(iterator hint, const value_type& value);
template<class InputIt>
void insert(InputIt first, InputIt last);
void erase(iterator pos);
void erase(iterator first, iterator last);
size_type erase(const key_type& key);
void swap(map& other);

size_type count( const Key& key ) const;
iterator find( const Key& key );
const_iterator find( const Key& key ) const;
std::pair<iterator,iterator> equal_range( const Key& key );
std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
iterator lower_bound( const Key& key );
const_iterator lower_bound( const Key& key ) const;
iterator upper_bound( const Key& key );
const_iterator upper_bound( const Key& key ) const;

key_compare key_comp() const;
value_compare value_comp() const;

	private :

};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (0);
}
template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (0);
}
template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (0);
}
template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (0);
}
template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (0);
}
template< class Key, class T, class Compare, class Alloc >
bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return (0);
}

template<class Key, class T, class Compare, class Alloc>
void swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs);

}

#endif