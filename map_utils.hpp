/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:31:05 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/27 15:54:43 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_HPP
# define MAP_UTILS_HPP

# include <iostream>
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
				element(pointer value) : _value(value), _parent(0), _color(RED)
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
				element *get_child(bool dir) const { return _child[dir]; }
				element *get_parent() const { return _parent; }
				element *get_grand_parent() const
				{
					if (_parent)
						return (_parent->get_parent());
					return (0);
				}
				element *get_brother() const
				{
					if (!_parent)
						return (0);
					return (_parent->get_child(!get_side()));
				}
				element *get_uncle() const
				{
					element * tmp = get_parent();
					if (!tmp)
						return (0);
					return (tmp->get_brother());
				}
				pointer get_value() const { return _value; }
				bool	get_color() const { return _color; }
				bool	get_side() const
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

	template< class T1, class T2> struct pair
	{
		public :
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

		pair() : first(first(), second(second())) {}
		pair( const T1& x, const T2& y ) : first(x), second(y) {}
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}
		pair( const pair& p ) : first(p.first), second(p.second) {}

		pair& operator=( const pair& rhs)
		{
			first = rhs.first;
			second = rhs.second;
		}
	};

	template< class T1, class T2 >
	pair<T1,T2> make_pair(T1 t, T2 u)
	{
		return(pair<T1, T2>(t, u));
	}

template< class T1, class T2 >
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class T1, class T2 >
bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (!(lhs == rhs));
}

template< class T1, class T2 >
bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	if (lhs.first > rhs.first)
		return false;
	if (lhs.first < rhs.first)
		return true;
	if (lhs.second > rhs.second)
		return false;
	if (lhs.second < rhs.second)
		return true;
	return false;
}

template< class T1, class T2 >
bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (!(lhs > rhs));
}

template< class T1, class T2 >
bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (!(lhs == rhs || lhs < rhs));
}

template< class T1, class T2 >
bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (!(lhs < rhs));
}

}

#endif