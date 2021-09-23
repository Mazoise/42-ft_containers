/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enableIf.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:28:30 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/23 14:22:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

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

}

#endif