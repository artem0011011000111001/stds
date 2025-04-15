#pragma once

#ifndef _STDS_TYPE_HELPER_
#define _STDS_TYPE_HELPER_

#include "utils/type_helper_hidden.hpp"

#if __HAS_CPP11
#define __CONSTANCY constexpr
#else
#define __CONSTANCY const
#endif // __CONSTANCY

// ==============================
// Public interface
// ==============================

// remove_reference
template<typename T>
using remove_reference = typename HSTDS_::__remove_reference<T>::type;

// remove_const
template<typename T>
using remove_const = typename HSTDS_::__remove_const<T>::type;

// remove_volatile
template<typename T>
using remove_volatile = typename HSTDS_::__remove_volatile<T>::type;

// remove_const_volatile
template<typename T>
using remove_const_volatile = typename HSTDS_::__remove_cv<T>::type;

// is_lvalue_reference
template<typename T>
inline __CONSTANCY bool is_lvalue_reference = HSTDS_::__is_lvalue_reference<T>::value;

// is_rvalue_reference
template<typename T>
inline __CONSTANCY bool is_rvalue_reference = HSTDS_::__is_rvalue_reference<T>::value;

// is_same
template<typename A, typename B>
inline __CONSTANCY bool is_same = HSTDS_::__is_same<A, B>::value;

// is_any_of
template<typename T, typename... Ts>
inline __CONSTANCY bool is_any_of = HSTDS_::__is_any_of<T, Ts...>::value;

// is_void
template<typename T>
inline __CONSTANCY bool is_void = HSTDS_::__is_void<T>::value;

// is_integral
template<typename T>
inline __CONSTANCY bool is_integral = HSTDS_::__is_integral<T>::value;

// is_function
template<typename T>
inline __CONSTANCY bool is_function = HSTDS_::__is_function<T>::value;

// remove_extent
template<typename T>
using remove_extent = typename HSTDS_::__remove_extent<T>::type;

// conditional
template<bool B, typename T, typename F>
using conditional = typename HSTDS_::__conditional<B, T, F>::type;

// enable_if
template<bool B, typename T = void>
using enable_if = typename HSTDS_::__enable_if_t<B, T>;

// decay
template<typename T>
using decay = typename HSTDS_::__decay_impl<T>::type;

// move & forward
using HSTDS_::move;
using HSTDS_::forward;

#undef __CONSTANCY

#endif // _STDS_TYPE_HELPER_