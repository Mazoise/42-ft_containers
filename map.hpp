/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:00:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/07 20:12:57 by mchardin         ###   ########.fr       */
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

		typedef Key									key_type;
		typedef T									mapped_type;
		typedef std::pair<const Key, T>				value_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef Allocator::pointer					pointer;
		typedef Allocator::const_pointer			const_pointer;
		typedef map_iterator<value_type>			iterator;
		typedef map_iterator<const value_type>		const_iterator;
		typedef rev_map_iterator<iterator>			reverse_iterator;
		typedef rev_map_iterator<const_iterator>	const_reverse_iterator;

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		public :
			typedef bool							result_type;
			typedef value_type						first_argument_type;
			typedef value_type						second_argument_type;

			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return (_comp(lhs.first, rhs.first));
			}
		protected :

			value_compare(Compare c) : _comp(c) {}
			Compare _comp;
	};

		map() : _map(0), _size(0), _comp(key_compare()),_alloc(allocator_type()) {}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _map(0), _size(0), _comp(comp),_alloc(alloc) {}
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

		size_type count(const Key& key) const;
		iterator find(const Key& key);
		const_iterator find(const Key& key) const;
		std::pair<iterator,iterator> equal_range(const Key& key);
		std::pair<const_iterator,const_iterator> equal_range(const Key& key) const;
		iterator lower_bound(const Key& key);
		const_iterator lower_bound(const Key& key) const;
		iterator upper_bound(const Key& key);
		const_iterator upper_bound(const Key& key) const;

		key_compare key_comp() const;
		value_compare value_comp() const;

	private :

		class element
		{
			protected :
				pointer			_value;
				element *		_left;
				element *		_right;
				element *		_parent;
			
				element() : _value(0), _left(0), _right(0), _parent(0) {}
				element(const element &	rhs)
				{
					*this = rhs;
				}
				element & operator=(const element & rhs)
				{
					_value = rhs._value;
					_left = rhs._left;
					_right = rhs._right;
					_parent = rhs._parent;
					return(*this);
				}
		}

		element *			_map;
		size_type			_size;
		key_compare			_comp;
		allocator_type		_alloc;

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