/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:13:26 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/29 17:33:11 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>

namespace ft
{

struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };

template< class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
class iterator
{
	public :

		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

};

template < class Iter >
class iterator_traits
{
	public :
	
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;

};

template < class T >
class iterator_traits<T*>
{
	public :

		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef random_access_iterator_tag			iterator_category;
};

template < class Iterator>
class reverse_iterator
{
	public :
		typedef Iterator								iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

		reverse_iterator(void)
		{
			current = iterator_type();
		}
		explicit reverse_iterator(iterator_type x)
		{
			current = x;
		}
		template< class U >
		reverse_iterator(const reverse_iterator<U> & rhs)
		{
			*this = rhs;
		}
		virtual ~reverse_iterator(void) {}

		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& rhs)
		{
			current = rhs.current;
			return *this;
		}
		iterator_type base() const
		{
			return current;
		}
		reference operator*() const
		{
		  iterator_type tmp = current;
		  return(*(--tmp));
		}
		pointer operator->() const
		{
			iterator_type tmp = current;
			return (&(*(--tmp)));
		}
		reference operator[](difference_type n) const
		{
			return (current[-n - 1]);
		}
		reverse_iterator& operator++()
		{
			current--;
			return *this;
		}
		reverse_iterator& operator--()
		{
			current++;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}
		reverse_iterator operator+( difference_type n ) const
		{
			return reverse_iterator(current - n);
		}
		reverse_iterator operator-( difference_type n ) const
		{
			return reverse_iterator(current + n);
		}
		reverse_iterator& operator+=( difference_type n )
		{
			current -= n;
			return *this;
		}
		reverse_iterator& operator-=( difference_type n )
		{
			current += n;
			return *this;
		}

	protected :

		iterator_type	current;
};

template< class Iterator1, class Iterator2 >
bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() == rhs.base();
}
template< class Iterator1, class Iterator2 >
bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() != rhs.base();
}
template< class Iterator1, class Iterator2 >
bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() < rhs.base();
}
template< class Iterator1, class Iterator2 >
bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() <= rhs.base();
}
template< class Iterator1, class Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() > rhs.base();
}
template< class Iterator1, class Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() >= rhs.base();
}

template< class Iter >
reverse_iterator<Iter>	operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
{
	return(reverse_iterator<Iter>(it.base() - n));
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type	operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
{
	return (rhs.base() - lhs.base());
}

}

#endif