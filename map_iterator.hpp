/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:48:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/21 10:18:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# define BLACK 0
# define RED 1
# define LEFT 0
# define RIGHT 1

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
		
				pointer		_value;
				element *	_child[2];
				element *	_parent;
				bool		_color;
		};

template < class T >
class map_iterator : public iterator<bidirectional_iterator_tag, T>
{
	public :

		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef bidirectional_iterator_tag			iterator_category;

		map_iterator(void) : _elem(0) {}
		map_iterator(element<value_type> & elem) : _elem(&elem) {}
		map_iterator(element<value_type> * elem) : _elem(elem) {}
		map_iterator(const map_iterator& rhs) : _elem(rhs._elem) {}
		virtual ~map_iterator(void) {}

		operator map_iterator<const T>()
		{
			return map_iterator<const T>(*_elem);
		}

		map_iterator&		operator=(element<value_type> * rhs)
		{
			_elem = rhs;
			return *this;
		}
		map_iterator&		operator=(const map_iterator& rhs)
		{
			_elem = rhs._elem;
			return *this;
		}

		bool						operator==(const map_iterator& rhs) const
		{ return (_elem == rhs._elem); }
		bool						operator!=(const map_iterator& rhs) const
		{ return (_elem != rhs._elem); }

		reference					operator*(void) const
		{ return _elem->get_value(); }
		pointer					operator->(void) const
		{ return _elem->get_value(); }

		map_iterator&		operator++(void)
		{
			_elem = _neighbor(RIGHT);
			return *this;
		}
		map_iterator		operator++(int rhs)
		{
			(void)rhs;
			_elem = _neighbor(RIGHT);
			return *this;
		}
		map_iterator&		operator--(void)
		{
			_elem = _neighbor(LEFT);
			return *this;
		}
		map_iterator		operator--(int rhs)
		{
			(void)rhs;
			_elem = _neighbor(LEFT);
			return *this;
		}

	private :

		element<value_type> * _elem;

		element<value_type> *	_neighbor(bool dir)
		{
			element<value_type> * tmp = _elem;
			if (tmp->get_child(dir))
			{
				tmp = tmp->get_child(dir);
				while (tmp->get_child(!dir))
					tmp = tmp->get_child(!dir);
				return tmp;
			}
			else if (tmp->get_parent())
			{
				if (tmp->get_side() != dir)
					return (tmp->get_parent());
				else
				{
					while (tmp->get_parent() && tmp->get_side() == dir)
						tmp = tmp->get_parent();
					if (!tmp->get_parent())
						return(tmp->get_child(dir));
					return(tmp->get_parent());
				}
			}
			else
				return 0;
		}
};

}

#endif