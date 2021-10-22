/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:28:30 by mchardin          #+#    #+#             */
/*   Updated: 2021/10/22 12:07:26 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{

template <class T, T val>
struct integralConstant { static const T value = val; };

typedef integralConstant<bool, true> trueType;
typedef integralConstant<bool, false> falseType;

template <class T> struct isIntegral : public falseType {};
template <class T> struct isIntegral<const T> : public isIntegral<T> {};
template <class T> struct isIntegral<volatile const T> : public isIntegral<T> {};
template <class T> struct isIntegral<volatile T> : public isIntegral<T> {};

template <> struct isIntegral <unsigned char> : public trueType {};
template <> struct isIntegral <unsigned short> : public trueType {};
template <> struct isIntegral <unsigned int> : public trueType {};
template <> struct isIntegral <unsigned long> : public trueType {};

template <> struct isIntegral <signed char> : public trueType {};
template <> struct isIntegral <short> : public trueType {};
template <> struct isIntegral <int> : public trueType {};
template <> struct isIntegral <long> : public trueType {};

template <> struct isIntegral <char> : public trueType {};
template <> struct isIntegral <bool> : public trueType {};

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if <true, T> { typedef T type; };

template< class InputIt1, class InputIt2 >
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	for (; first1 != last1; first1++)
	{
		if (*first1 != *first2)
			return false;
		first2++;
	}
	return true;
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
	for ( ; first1 != last1; first1++)
	{
		if (!p(*first1, *first2))
			return false;
		first2++;
	}
	return true;
}

template< class InputIt1, class InputIt2 >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
	for ( ; first1 != last1; first1++)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		if (*first1 < *first2)
			return true;
		first2++;
	}
	return (first2 != last2);
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
	for ( ; first1 != last1; first1++)
	{
		if (first2 == last2 || comp(*first2, *first1))
			return false;
		if (comp(*first1, *first2))
			return true;
		first2++;
	}
	return true;
}

}

#endif