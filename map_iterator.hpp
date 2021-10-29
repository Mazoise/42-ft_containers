/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:48:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/29 17:43:16 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "map_utils.hpp"
# define BLACK 0
# define RED 1
# define LEFT 0
# define RIGHT 1

namespace ft
{

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
		// map_iterator(element<value_type> & elem) : _elem(&elem) {}
		map_iterator(element<value_type> * elem) : _elem(elem) {}
		map_iterator(const map_iterator& rhs) : _elem(rhs._elem) {}
		virtual ~map_iterator(void) {}

		operator map_iterator<const T>() const
		{
			return map_iterator<const T>(reinterpret_cast<element<const value_type> *>(_elem));
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

		reference					operator*(void)
		{ return *(_elem->get_value()); }
		pointer					operator->(void)
		{ return _elem->get_value(); }

		map_iterator&		operator++(void)
		{
			_elem = _neighbor(RIGHT);
			return *this;
		}
		map_iterator		operator++(int)
		{
			map_iterator tmp = *this;
			++(*this);
			return (tmp);
		}
		map_iterator&		operator--(void)
		{
			_elem = _neighbor(LEFT);
			return *this;
		}
		map_iterator		operator--(int)
		{
			map_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	private :

		element<value_type> * _elem;

		element<value_type> *	_neighbor(bool dir) const
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