/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:00:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/22 12:07:08 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "map_iterator.hpp"
#include "utils.hpp"
#include <limits>

namespace ft
{

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
class map
{
	public :

		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const Key, T>				value_type;
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
			clear();
			insert(first, last);
		}
		map(const map& rhs)
		{
			*this = rhs;
		}
		~map()
		{
			// clear();
		}
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
			element<value_type> * tmp = _find(key);

			if (tmp)
				return (tmp->get_value()->second);
			else
				throw std::out_of_range("");
		}
		const T& at(const Key& key ) const
		{
			element<value_type> * tmp = _find(key);

			if (tmp)
				return (tmp->get_value()->second);
			else
			throw std::out_of_range("");
		}
		T& operator[](const Key& key)
		{
			element<value_type> * tmp = _find(key);

			if (tmp)
				return (tmp->get_value()->second);
			else
			{
				insert(ft::make_pair<key_type, mapped_type>(key, mapped_type()));
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
		void clear()
		{
			erase(begin(), end());
		}
		pair<iterator, bool> insert(const value_type& value)
		{
			element<value_type> * tmp = _find(value.first);
			if (_find(value.first))
				return (ft::make_pair(iterator(tmp), 0));
			element<value_type> *	end_elem = _end();
			if (_end() != _root)
				_end()->get_parent()->set_child(0, RIGHT);
			value_type *new_value = new value_type(value); // replace with allocator
			element<value_type> *	new_elem = new element<value_type>(new_value);
			_simple_insert(new_elem);
			_red_black(new_elem);
			_size++;
			end_elem->set_parent(_end());
			_end()->set_child(end_elem, RIGHT);
			return (ft::make_pair(iterator(new_elem), 1));
		} //rewrite pair
		iterator insert(iterator hint, const value_type& value)
		{
			(void)hint;
			insert(value);
		}
		template<class InputIt>
		void insert(InputIt first, typename ft::enable_if<!isIntegral<InputIt>::value, InputIt>::type last) // add enable if 
		{
			while(first != last)
			{
				insert(*first);
				first++;
			}
		}
		// void erase(iterator pos)
		// {
		// 	element<value_type> *	end_elem = _end();
		// 	if (_end() != _root)
		// 		_end()->get_parent()->set_child(0, RIGHT);
			
		// 	_size--;
		// }
		void erase(iterator first, iterator last);
		size_type erase(const key_type& key);
		void swap(map& rhs)
		{
			element<value_type> *	tmp_root;
			size_type				tmp_size;
			key_compare				tmp_comp;
			allocator_type			tmp_alloc;

			tmp_comp = _comp;
			_comp = rhs._comp;
			rhs._comp = tmp_comp;
			tmp_root = _root;
			_root = rhs._root;
			rhs._root = tmp_root;
			tmp_size = _size;
			_size = rhs._size;
			rhs._size = tmp_size;
			tmp_alloc = _alloc;
			_alloc = rhs._alloc;
			rhs._alloc = tmp_alloc;
		}

		size_type count(const Key& key) const
		{
			if (_find(key))
				return 1;
			return 0;
		}
		iterator find(const Key& key)
		{
			element<value_type> * tmp = _find(key);
			if (tmp)
				return(iterator(tmp));
			else
				return(end());
		}
		const_iterator find(const Key& key) const
		{
			element<value_type> * tmp = _find(key);
			if (tmp)
				return(const_iterator(tmp));
			else
				return(end());			
		}
		pair<iterator, iterator> equal_range(const Key& key)
		{
			return(ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}
		pair<const_iterator, const_iterator> equal_range(const Key& key) const
		{
			return(ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
		}
		iterator lower_bound(const Key& key)
		{
			element<value_type> * tmp = _root;
			bool					dir;

			while (tmp && tmp->get_value())
			{
				if (tmp->get_value()->first == key)
					return (iterator(tmp));
				dir = key_compare()(tmp->get_value()->first, key);
				if (tmp->get_child(dir))
					tmp = tmp->get_child(dir);
				else if (dir == RIGHT)
					return(iterator(tmp));
				else
					return(++iterator(tmp));
			}
			return(end());
		}
		const_iterator lower_bound(const Key& key) const
		{
			element<value_type> * tmp = _root;
			bool					dir;

			while (tmp && tmp->get_value())
			{
				if (tmp->get_value()->first == key)
					return (const_iterator(tmp));
				dir = key_compare()(tmp->get_value()->first, key);
				if (tmp->get_child(dir))
					tmp = tmp->get_child(dir);
				else if (dir == RIGHT)
					return(const_iterator(tmp));
				else
					return(++const_iterator(tmp));
			}
			return(end());
		}
		iterator upper_bound(const Key& key)
		{
			element<value_type> * tmp = _root;
			bool					dir;

			while (tmp && tmp->get_value())
			{
				if (tmp->get_value()->first == key)
					return (++iterator(tmp));
				dir = key_compare()(tmp->get_value()->first, key);
				if (tmp->get_child(dir))
					tmp = tmp->get_child(dir);
				else if (dir == RIGHT)
					return(iterator(tmp));
				else
					return(++iterator(tmp));
			}
			return(end());
		}
		const_iterator upper_bound(const Key& key) const
		{
			element<value_type> * tmp = _root;
			bool					dir;

			while (tmp && tmp->get_value())
			{
				if (tmp->get_value()->first == key)
					return (++const_iterator(tmp));
				dir = key_compare()(tmp->get_value()->first, key);
				if (tmp->get_child(dir))
					tmp = tmp->get_child(dir);
				else if (dir == RIGHT)
					return(const_iterator(tmp));
				else
					return(++const_iterator(tmp));
			}
			return(end());
		}

		key_compare key_comp() const
		{
			return _comp;
		}
		value_compare value_comp() const
		{
			return value_compare(_comp);
		}

	private :

		element<value_type> *	_end() const
		{
			element<value_type> * tmp = _root;
			while(tmp->get_child(RIGHT))
				tmp = tmp->get_child(RIGHT);
			return tmp;
		}
		element<value_type> *	_begin() const
		{
			element<value_type> * tmp = _root;
			while(tmp->get_child(LEFT))
				tmp = tmp->get_child(LEFT);
			return tmp;
		}
		element<value_type> *	_find(key_type key) const
		{
			element<value_type> * tmp = _root;
			bool					dir;

			while (tmp && tmp->get_value())
			{
				if (tmp->get_value()->first == key)
					return (tmp);
				dir = key_compare()(tmp->get_value()->first, key);
				tmp = tmp->get_child(dir);
			}
			return 0;
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

		// iterator	_delete(iterator pos) //returns replacement node
		// {
		// 	if (!pos->get_child(RIGHT))
		// 	{
		// 		pos->get_parent->set_child(pos->get_child(LEFT), pos->get_side())
		// 		if (pos->get_child(LEFT))
		// 			pos->get_child(LEFT)->set_parent(pos->get_parent())
		// 	}
		// 	else if (!pos->get_child(RIGHT))
		// 	{
		// 		pos->get_parent->set_child(pos->get_child(RIGHT), pos->get_side())
		// 		if (pos->get_child(RIGHT))
		// 			pos->get_child(RIGHT)->set_parent(pos->get_parent())
		// 	}
		// 	else
		// 	{
		// 		iterator tmp = pos;
				
		// 		pos++;
		// 		pos->get_parent->set_child(0, pos->get_side());
		// 		pos->set_parent(tmp->get_parent());
		// 		tmp->get_parent->set_child(pos, tmp->get_side());
		// 		pos->set_child(tmp->get_child(LEFT), LEFT);

		// 	}
			
		// }
};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs > rhs));
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs == rhs || lhs < rhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return (!(lhs < rhs));
}

// template<class Key, class T, class Compare, class Alloc>
// void swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs);

}

#endif