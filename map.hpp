/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:00:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/04 18:31:19 by mchardin         ###   ########.fr       */
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
		typedef ft::map_iterator< value_type >			iterator;
		typedef ft::map_iterator< const value_type >	const_iterator;
		typedef ft::reverse_iterator< iterator >		reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;

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
			_root = new element<value_type>();
		}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _size(0), _comp(comp), _alloc(alloc)
		{
			_root = new element<value_type>();
		}
		template<class InputIt>
		map(InputIt first, typename ft::enable_if<!isIntegral<InputIt>::value, InputIt>::type last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())  : _size(0), _comp(comp),_alloc(alloc)
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
			clear();
			delete _root;
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
			return iterator(_begin());
		}
		const_iterator begin() const
		{
			return const_iterator(begin());
		}
		iterator end()
		{
			return iterator(_end());
		}
		const_iterator end() const
		{
			return const_iterator(end());
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(_end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(rbegin());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(_begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(rend());
		}
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
			if (tmp)
				return (ft::make_pair(iterator(tmp), 0));
			pointer new_value = _alloc.allocate(1);
			_alloc.construct(new_value, value_type(value));
			element<value_type> *	new_elem = new element<value_type>(new_value);
			_simple_insert(new_elem);
			_red_black(new_elem);
			_size++;
			return (ft::make_pair(iterator(new_elem), 1));
		}
		iterator insert(iterator hint, const value_type& value)
		{
			(void)hint;
			pair<iterator, bool> res;
			res = insert(value);
			return res.first;
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
		void erase(iterator pos)
		{
			std::cerr << "DEB erase pos" << std::endl;
			if (_size > 1)
				_delete(pos, _find(pos->first));
			else
			{
				_alloc.destroy(_root->get_value());
				_alloc.deallocate(_root->get_value(), 1);
				delete _root;
				_root = new element<value_type>();
			}
			std::cerr << "END erase pos" << std::endl;
			_size--;
		}
		void erase(iterator first, iterator last)
		{
			if (first != last)
				std::cerr << "erase range : now = " << first->first << " : " << first->second << std::endl;
			iterator next = first;
			iterator now;
			std::cerr << "DEB erase range" << std::endl;
			while (next != last)
			{
				now = first;
				++first;
				next = first;
				erase(now);
			}
			std::cerr << "END erase range" << std::endl;
		}
		size_type erase(const key_type& key)
		{
			element<value_type> *	del_elem = _find(key);

			std::cerr << "DEB erase key" << std::endl;
			if (!del_elem)
				return 0;
			if (_size > 1)
				_delete(iterator(del_elem), del_elem);
			else
			{
				_alloc.destroy(_root->get_value());
				_alloc.deallocate(_root->get_value(), 1);
				delete _root;
				_root = new element<value_type>();
			}
			_size--;
			std::cerr << "FIN erase key" << std::endl;
			return 1;
		}
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
				if (tmp->get_child(dir) && tmp->get_child(dir)->get_value())
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
				if (tmp->get_child(dir) && tmp->get_child(dir)->get_value())
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
				if (tmp->get_child(dir) && tmp->get_child(dir)->get_value())
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
				if (tmp->get_child(dir) && tmp->get_child(dir)->get_value())
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
			while(tmp->get_child(LEFT) && tmp->get_child(LEFT)->get_value())
				tmp = tmp->get_child(LEFT);
			return tmp;
		}
		element<value_type> *	_rend() const
		{
			element<value_type> * tmp = _root;
			while(tmp->get_child(RIGHT) && tmp->get_child(RIGHT)->get_value())
				tmp = tmp->get_child(RIGHT);
			return tmp;
		}
		element<value_type> *	_rbegin() const
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
			std::cerr << "BIJOUR" << std::endl;
			return 0;
		}
		
		void	_rotate(element<value_type> * rhs, bool dir)
		{
			
			std::cerr << "beg rotate" << std::endl;
			if (!rhs)
			{
				std::cerr << "SNH" << std::endl;
				return ;
			}
			element<value_type> * tmp = rhs->get_child(!dir);
			rhs->set_child(tmp->get_child(dir), !dir);
			tmp->get_child(dir)->set_parent(rhs);
			tmp->set_child(rhs, dir);
			tmp->set_parent(rhs->get_parent());
			if (!tmp->get_parent())
				_root = tmp;
			else
				rhs->get_parent()->set_child(tmp, rhs->get_side());
			tmp->set_child(rhs, dir);
			rhs->set_parent(tmp);
			std::cerr << "end rotate" << std::endl;
		}
		void	_simple_insert(element<value_type> * new_elem)
		{
			element<value_type>	*	i = _root;
			bool		dir;

			if (!_root->get_value())
			{
				delete _root;
				_root = new_elem;
				return ;
			}
			while (i->get_value())
			{
				dir = value_compare(_comp)(*(i->get_value()), *(new_elem->get_value())); // check order
				if (i->get_child(dir) && i->get_child(dir)->get_value())
					i = i->get_child(dir);
				else
				{
					delete i->get_child(dir);
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

		bool		_pre_correct(bool del_color, element<value_type> * rep, element<value_type> * x)
		{
			if (del_color == RED && (rep->get_color() == RED || !rep->get_value()))
				return 0;
			else if (del_color == RED && rep->get_color() == BLACK)
			{
				rep->set_color(RED);
				return 1;
			}
			else if (del_color == BLACK && rep->get_color() == RED)
			{
				rep->set_color(BLACK);
				return 0;
			}
			else if (x == _root)
				return 0;
			else
				return 1;
			
		}

		void	_correct(bool del_color, element<value_type> * rep, element<value_type> * x)
		{
			// std::cerr << "Correct Fonction" << std::endl;
			if (_pre_correct(del_color, rep, x))
			{
				element<value_type> * w;
				std::cerr << "pre_correct passed" << std::endl;
				while (x != _root && x->get_color() == BLACK)
				{
					w = x->get_brother();
					if (w->get_color() == RED)
					{
						std::cerr << "W is red" << std::endl;
						w->set_color(BLACK);
						x->get_parent()->set_color(RED);
						_rotate(x->get_parent(), x->get_side());
						std::cerr << "Bijour" << std::endl;
					}
					else if (w->get_value() && w->get_child(x->get_side())->get_color() == BLACK && w->get_child(w->get_side())->get_color() == BLACK)
					{
						std::cerr << "W children black - black" << std::endl;
						w->set_color(RED);
						x = x->get_parent();
					}
					else
					{
						if (w->get_value() && w->get_child(w->get_side())->get_color() == BLACK)
						{
							std::cerr << "W children red - black" << std::endl;
							w->get_child(x->get_side())->set_color(BLACK);
							w->set_color(RED);
							_rotate(w, w->get_side());
						}
						std::cerr << "W children black - red or red - red" << std::endl;
						w->set_color(x->get_parent()->get_color());
						x->get_parent()->set_color(BLACK);
						if (w->get_value())
							w->get_child(w->get_side())->set_color(BLACK);
						_rotate(x->get_parent(), x->get_side());
						x = _root;
					}
					w = x->get_brother();
				}
				x->set_color(BLACK);
			}
			// std::cerr << "end correct" << std::endl;
		}

		void	_delete(iterator del_it, element<value_type> * del_node) //returns replacement node
		{
			element<value_type> *	x;
			bool					dir;
			
			if (!del_node->get_child(RIGHT)->get_value() || !del_node->get_child(LEFT)->get_value())
			{
				std::cerr << "Not 2 children" << std::endl;
				if (!del_node->get_child(RIGHT)->get_value())
					dir = LEFT;
				else
					dir = RIGHT;
				std::cerr << "TEST1" << std::endl;
				x = del_node->get_child(dir);
				if (del_node->get_parent())
				{
					del_node->get_parent()->set_child(x, del_node->get_side());
					del_node->set_child(0, dir);
				}
				else
					_root = x;
				std::cerr << "TEST2" << std::endl;
				x->set_parent(del_node->get_parent());
				_correct(del_node->get_color(), x, x);
				std::cerr << "TEST3" << std::endl;
			}
			else
			{
				std::cerr << "2 children" << std::endl;
				del_it++;
				element<value_type> *	repl_node = _find(del_it->first);
				x = repl_node->get_child(RIGHT);
				repl_node->get_parent()->set_child(repl_node->get_child(RIGHT), repl_node->get_side());
				repl_node->set_parent(del_node->get_parent());
				if (del_node->get_parent())
					del_node->get_parent()->set_child(repl_node, del_node->get_side());
				repl_node->set_child(del_node->get_child(LEFT), LEFT);
				repl_node->get_child(LEFT)->set_parent(repl_node);
				repl_node->set_child(del_node->get_child(RIGHT), RIGHT);
				repl_node->get_child(RIGHT)->set_parent(repl_node);
				_correct(del_node->get_color(), repl_node, x);
			}
			if (_root)
			{
				std::cerr << "ROOT" << std::endl;
				_print_node(_root);
				std::cerr << "parent" << std::endl;
				_print_node(_root->get_parent());
				std::cerr << "left child" << std::endl;
				_print_node(_root->get_child(LEFT));
				std::cerr << "right child" << std::endl;
				_print_node(_root->get_child(RIGHT));
				std::cerr << std::endl;
			}
			_alloc.destroy(del_node->get_value());
			_alloc.deallocate(del_node->get_value(), 1);
			delete del_node;
		}

		void	_print_node(element<value_type> *	_elem)
		{
			if (!_elem)
				return ;
			if (_elem->get_value())
			std::cerr << "ME :" << _elem->get_value()->first << std::endl;
			if (_elem->get_parent())
				std::cerr << "PARENT :" << _elem->get_parent()->get_value()->first << std::endl;
			if (_elem->get_child(LEFT) && _elem->get_child(LEFT)->get_value())
				std::cerr << "LEFT_CHILD :" << _elem->get_child(LEFT)->get_value()->first << std::endl;
			if (_elem->get_child(RIGHT) && _elem->get_child(RIGHT)->get_value())
				std::cerr << "RIGHT_CHILD :" << _elem->get_child(RIGHT)->get_value()->first << std::endl;
			if (_elem->get_brother() && _elem->get_brother()->get_value())
				std::cerr << "BROTHER :" << _elem->get_brother()->get_value()->first << std::endl;
			if (_elem->get_uncle() && _elem->get_uncle()->get_value())
				std::cerr << "UNCLE :" << _elem->get_uncle()->get_value()->first << std::endl;
			std::cerr << "SIDE :" << _elem->get_side() << std::endl;
			std::cerr << std::endl;
		}
};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
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