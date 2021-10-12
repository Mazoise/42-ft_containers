/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:00:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/12 16:31:54 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "vector_iterator.hpp"
#include "enableIf.hpp"
#include <limits>
#define BLACK 0
#define RED 1
#define LEFT 0
#define RIGHT 1

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
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		// typedef map_iterator<value_type>			iterator;
		// typedef map_iterator<const value_type>		const_iterator;
		// typedef rev_map_iterator<iterator>			reverse_iterator;
		// typedef rev_map_iterator<const_iterator>	const_reverse_iterator;

	private :

		class	element
		{
			friend class map;
			public :
				pointer			_value;
				element *		_child[2];
				element *		_parent;
				bool			_color;
			
				element() : _value(0), _parent(0), _color(RED)
				{
					_child[LEFT] = 0;
					_child[RIGHT] = 0;
				}
				element(value_type * value) : _value(value), _parent(0), _color(RED)
				{
					_child[LEFT] = 0;
					_child[RIGHT] = 0;
				}
				element(const element &	rhs)
				{
					*this = rhs;
				}
				element & operator=(const element & rhs)
				{
					_value = rhs._value;
					_child[LEFT] = rhs._child[LEFT];
					_child[RIGHT] = rhs._child[RIGHT];
					_parent = rhs._parent;
					_color = rhs._color;
					return(*this);
				}
		};

		element *			_root;
		size_type			_size;
		key_compare			_comp;
		allocator_type		_alloc;

	public :

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
			public :
				typedef bool							result_type;
				typedef value_type						first_argument_type;
				typedef value_type						second_argument_type;

				bool operator()(const value_type& lhs, const value_type& rhs) const
				{
					return _comp(lhs.first, rhs.first);
				}
			protected :

				value_compare(Compare c) : _comp(c) {}
				Compare _comp;
		};

		map() : _root(0), _size(0), _comp(key_compare()),_alloc(allocator_type()) {}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _root(0), _size(0), _comp(comp),_alloc(alloc) {}
		// template<class InputIt>
		// map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())  : _root(0), _size(0), _comp(comp),_alloc(alloc)
		// {
		// 	insert(first, last);
		// }
		map(const map& rhs)
		{
			_root = rhs;
		}
		~map() {}
		map& operator=(const map& rhs)
		{
			if (&rhs != this)
			{
				_alloc = rhs._alloc;
				_comp = rhs._comp;
				clear();
				insert(rhs.begin(), rhs.end());
			}
			return *this;
		}
		allocator_type get_allocator() const
		{
			return _alloc;
		}
		T& at(const Key& key);
		const T& at(const Key& key ) const;
		T& operator[](const Key& key);
		// iterator begin();
		// const_iterator begin() const;
		// iterator end();
		// const_iterator end() const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

		bool empty() const
		{
			return(!_size);
		}
		size_type size() const
		{
			return _size;
		}
		size_type max_size() const
		{
			return _alloc.max_size();
		}
		void clear();
		void insert(const value_type& value) // WARNING : return std::pair<iterator, bool> not void
		{
			value_type *new_value = new value_type(value); // replace with allocator
			element *	new_elem = new element(new_value);
			_simple_insert(new_elem);
			_red_black(new_elem);
		} //rewrite pair
		// iterator insert(iterator hint, const value_type& value);
		// template<class InputIt>
		// void insert(InputIt first, InputIt last);
		// void erase(iterator pos);
		// void erase(iterator first, iterator last);
		size_type erase(const key_type& key);
		void swap(map& other);

		size_type count(const Key& key) const;
		// iterator find(const Key& key);
		// const_iterator find(const Key& key) const;
		// std::pair<iterator,iterator> equal_range(const Key& key);
		// std::pair<const_iterator,const_iterator> equal_range(const Key& key) const;
		// iterator lower_bound(const Key& key);
		// const_iterator lower_bound(const Key& key) const;
		// iterator upper_bound(const Key& key);
		// const_iterator upper_bound(const Key& key) const;

		key_compare key_comp() const
		{
			return _comp;
		}
		value_compare value_comp() const
		{
			return value_compare(_comp);
		}

	private :

		void	_rotate(element * rhs, bool dir)
		{
			element * tmp = rhs->_child[!dir];
			rhs->_child[!dir] = rhs->_child[!dir]->_child[dir];
			if (rhs->_child[!dir])
				rhs->_child[!dir]->_parent = rhs;
			tmp->_child[dir] = rhs;
			tmp->_parent = rhs->_parent;
			if (!tmp->_parent)
				_root = tmp;
			else if (rhs->_parent->_child[dir] == rhs)
				rhs->_parent->_child[dir] = tmp;
			else
				rhs->_parent->_child[!dir] = tmp;
			rhs->_parent = tmp;
		}
		void	_simple_insert(element * new_elem)
		{
			element	*	i = _root;
			bool		dir;

			if (!_root)
			{
				_root = new_elem;
				return ;
			}
			while (i)
			{
				dir = value_compare(_comp)(*(new_elem->_value), *(i->_value)); // check order
				if (i->_child[dir])
					i = i->_child[dir];
				else
				{
					i->_child[dir] = new_elem;
					new_elem->_parent = i;
					return ;
				}
			}
		}
		void	_red_black(element * elem)
		{
			bool			dir = LEFT;
			element *		uncle;
	
			if (_root == elem)
			{
				elem->_color = BLACK;
				return ;
			}
			while(elem->_parent->_color == RED)
			{
				if (elem->_parent->_parent->_child[RIGHT] == elem->_parent)
					dir = RIGHT;
				uncle = elem->_parent->_parent->_child[!dir];
				if (uncle && uncle->_color == RED)
				{
					elem->_parent->_color = BLACK;
					uncle->_color = BLACK;
					uncle->_parent->_color = RED;
					elem = uncle->_parent;
				}
				else if (elem == elem->_parent->_child[!dir])
				{
					elem = elem->_parent;
					_rotate(elem, dir);
				}
				else
				{
					elem->_parent->_color = BLACK;
					elem->_parent->_parent->_color = RED;
					elem = elem->_parent->_parent;
					_rotate(elem, !dir);
				}
				
			}
		}
};

// template<class Key, class T, class Compare, class Alloc>
// bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
// {
// 	return (0);
// }

// template<class Key, class T, class Compare, class Alloc>
// bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
// {
// 	return (0);
// }

// template<class Key, class T, class Compare, class Alloc>
// bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
// {
// 	return (0);
// }

// template<class Key, class T, class Compare, class Alloc>
// bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
// {
// 	return (0);
// }

// template<class Key, class T, class Compare, class Alloc>
// bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
// {
// 	return (0);
// }

// template< class Key, class T, class Compare, class Alloc >
// bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
// {
// 	return (0);
// }


// template<class Key, class T, class Compare, class Alloc>
// void swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs);

}

#endif