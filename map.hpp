/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:00:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/21 09:48:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "map_iterator.hpp"
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
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef map_iterator<value_type>			iterator;
		typedef map_iterator<const value_type>		const_iterator;
		// typedef rev_map_iterator<iterator>			reverse_iterator;
		// typedef rev_map_iterator<const_iterator>	const_reverse_iterator;

	private :

		element<value_type> *	_root;
		size_type				_size;
		key_compare				_comp;
		allocator_type			_alloc;

	public :

		class value_compare : public std::binary_function<value_type, value_type, bool> // recode binary function?
		{
			friend class map; // allowed?
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

		map() : _size(0), _comp(key_compare()),_alloc(allocator_type())
		{
			_root = new element<value_type>(); // alloc
		}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _size(0), _comp(comp), _alloc(alloc)
		{
			_root = new element<value_type>(); // alloc
		}
		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())  : _size(0), _comp(comp),_alloc(alloc)
		{
			insert(first, last);
		}
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
		T& at(const Key& key)
		{
			element<value_type> * tmp = _root;
			bool					dir;

			while (tmp && tmp->get_value())
			{
				if (tmp->get_value()->first == key)
					return (tmp->get_value()->second);
				dir = key_compare()(tmp->get_value()->first, key);
				tmp = tmp->get_child(dir);
			}
			throw std::out_of_range("");
		}
		const T& at(const Key& key ) const
		{
			element<value_type> * tmp = _root;
			bool					dir;

			while (tmp && tmp->get_value())
			{
				if (tmp->get_value()->first == key)
					return (tmp->get_value()->second);
				dir = key_compare()(tmp->get_value()->first, key);
				tmp = tmp->get_child(dir);
			}
			throw std::out_of_range("");
		}
		T& operator[](const Key& key)
		{
			try
			{
				return at(key);
			}
			catch (std::out_of_range &e)
			{
				insert(std::make_pair<key_type, mapped_type>(key, mapped_type()));
				return (at(key));
			}
		}
		iterator begin()
		{
			return(iterator(_begin()));
		}
		const_iterator begin() const
		{
			return(const_iterator(_begin()));
		}
		iterator end()
		{
			return(iterator(_end()));
		}
		const_iterator end() const
		{
			return(const_iterator(_end()));
		}
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
			element<value_type> *	end_elem = _end();
			std::cerr << "BEFORE" << std::endl;
			if (_end() != _root)
				_end()->get_parent()->set_child(0, RIGHT);
			std::cerr << "AFTER" << std::endl;
			// check if key exists here, do not replace value
			value_type *new_value = new value_type(value); // replace with allocator
			element<value_type> *	new_elem = new element<value_type>(new_value);
			_simple_insert(new_elem);
			_red_black(new_elem);
			_size++;
			end_elem->set_parent(_end());
			_end()->set_child(end_elem, RIGHT);
			std::cerr << "ROOT : " << _root->get_value()->first << " - color : " << _root->get_color() << std::endl;
		} //rewrite pair
		// iterator insert(iterator hint, const value_type& value);
		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while(first != last)
			{
				insert(*first);
				first++;
			}
		}
		// void erase(iterator pos);
		// void erase(iterator first, iterator last);
		size_type erase(const key_type& key);
		void swap(map& other);

		size_type count(const Key& key) const
		{
			try
			{
				at(key);
				return (1);
			}
			catch (std::out_of_range &e)
			{
				return (0);
			}
		}
		// iterator find(const Key& key);
		// const_iterator find(const Key& key) const;
		// std::pair<iterator, iterator> equal_range(const Key& key);
		// std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
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

		element<value_type> *	_end()
		{
			element<value_type> * tmp = _root;
			while(tmp->get_child(RIGHT))
				tmp = tmp->get_child(RIGHT);
			return tmp;
		}
		element<value_type> *	_begin()
		{
			element<value_type> * tmp = _root;
			while(tmp->get_child(LEFT))
				tmp = tmp->get_child(LEFT);
			return tmp;
		}
		void	_rotate(element<value_type> * rhs, bool dir)
		{
			element<value_type> * tmp = rhs->get_child(!dir);
			rhs->set_child(rhs->get_child(!dir)->get_child(dir), !dir);
			if (rhs->get_child(!dir))
				rhs->get_child(!dir)->set_parent(rhs);
			tmp->set_child(rhs, dir);
			tmp->set_parent(rhs->get_parent());
			if (!tmp->get_parent())
				_root = tmp;
			else if (rhs->get_parent()->get_child(dir) == rhs)
				rhs->get_parent()->set_child(tmp, dir);
			else
				rhs->get_parent()->set_child(tmp, !dir);
			rhs->set_parent(tmp);
		}
		void	_simple_insert(element<value_type> * new_elem)
		{
			element<value_type>	*	i = _root;
			bool		dir;

			if (!_root->get_value())
			{
				_root = new_elem;
				return ;
			}
			while (i)
			{
				dir = value_compare(_comp)(*(i->get_value()), *(new_elem->get_value())); // check order
				if (i->get_child(dir))
					i = i->get_child(dir);
				else
				{
					i->set_child(new_elem, dir);
					new_elem->set_parent(i);
					return ;
				}
			}
		}
		void	_red_black(element<value_type> * elem)
		{
			bool			dir = LEFT;
			element<value_type> *		uncle;
	
			if (_root == elem)
			{
				elem->set_color(BLACK);
				return ;
			}
			while(elem != _root && elem->get_parent()->get_color() == RED)
			{
				uncle = elem->get_uncle();
				dir = elem->get_parent()->get_side();
				if (uncle && uncle->get_color() == RED)
				{
					elem->get_parent()->set_color(BLACK);
					uncle->set_color(BLACK);
					uncle->get_parent()->set_color(RED);
					elem = elem->get_grand_parent();
				}
				else if (elem->get_side() == !dir)
				{
					elem = elem->get_parent();
					_rotate(elem, dir);
				}
				else
				{
					elem->get_parent()->set_color(BLACK);
					elem->get_grand_parent()->set_color(RED);
					elem = elem->get_grand_parent();
					_rotate(elem, !dir);
				}
				_root->set_color(BLACK);
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