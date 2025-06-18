#pragma once

#ifndef _STDS_CONCEPTS_HIDDEN_
#define _STDS_CONCEPTS_HIDDEN_

#include "utils/type_helper_hidden.hpp"

#if !__HAS_CPP20
#error Concepts are supported only since C++20
#endif // __HAS_CPP20

STDS_START

HIDDEN_STDS_START

template<class T>
concept __integral_c = HSTDS_::__is_integral_v<T>;

template<class T>
concept __voidable_c = HSTDS_::__is_void_v<T>;

template<class T>
concept __lvalue_c = HSTDS_::__is_lvalue_reference_v<T>;

template<class T>
concept __rvalue_c = HSTDS_::__is_rvalue_reference_v<T>;

HIDDEN_STDS_END

STDS_END

#endif // _STDS_CONCEPTS_HIDDEN_