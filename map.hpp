/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:00:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/20 20:50:35 by mchardin         ###   ########.fr       */
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
template<class T>
class	element
		{
			public :

				typedef T		value_type;
				typedef T*		pointer;

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
					return *this;
				}
				element *get_child(bool dir) { return _child[dir]; }
				element *get_parent() { return _parent; }
				element *get_grand_parent()
				{
					if (_parent)
						return (_parent->get_parent());
					return (0);
				}
				element *get_brother()
				{
					if (!_parent)
						return (0);
					return (_parent->get_child(!get_side()));
				}
				element *get_uncle()
				{
					element * tmp = get_parent();
					if (!tmp)
						return (0);
					return (tmp->get_brother());
				}
				pointer get_value() { return _value; }
				bool	get_color() { return _color; }
				bool	get_side()
				{
					if (!_parent)
						return (0);
					if (_parent->get_child(RIGHT) == this)
						return(RIGHT);
					return (LEFT);
				}
				void	set_child(element *rhs, bool dir) { _child[dir] = rhs; }
				void	set_brother(element *rhs) { get_brother() = rhs; }
				void	set_parent(element *rhs) { _parent = rhs; }
				void	set_grand_parent(element *rhs) { get_grand_parent() = rhs; }
				void	set_uncle(element *rhs) { get_uncle() = rhs; }
				void	set_color(bool rhs) { _color = rhs; }
				void	set_value(pointer rhs) { _value = rhs; }

			private:
		
				pointer			_value;
				element *	_child[2];
				element *	_parent;
				bool			_color;
		};

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

		element<value_type> *	_root;
		size_type				_size;
		key_compare				_comp;
		allocator_type			_alloc;
		size_t					_osef;
		size_t					_osef2;
		size_t					_osef3;

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

		map() : _root(0), _size(0), _comp(key_compare()),_alloc(allocator_type()), _osef(0), _osef2(0), _osef3(0) {}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _root(0), _size(0), _comp(comp),_alloc(alloc), _osef(0), _osef2(0), _osef3(0) {}
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
			// check if key exists here, do not replace value
			value_type *new_value = new value_type(value); // replace with allocator
			element<value_type> *	new_elem = new element<value_type>(new_value);
			_simple_insert(new_elem);
			_red_black(new_elem);
			_size++;
			std::cerr << "ROOT : " << _root->get_value()->first << " - color : " << _root->get_color() << std::endl;
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

			if (!_root)
			{
				_root = new_elem;
				return ;
			}
			while (i)
			{
				dir = value_compare(_comp)(*(new_elem->get_value()), *(i->get_value())); // check order
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