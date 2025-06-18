#pragma once

#ifndef _STDS_CONCEPTS_
#define _STDS_CONCEPTS_

#include "utils/concepts_hidden.hpp"

STDS_START

template<class T>
concept integral = HSTDS_::__integral_c<T>;

template<class T>
concept voidable = HSTDS_::__voidable_c<T>;

template<class T>
concept lvalue = HSTDS_::__lvalue_c<T>;

template<class T>
concept rvalue = HSTDS_::__rvalue_c<T>;

STDS_END

#endif // _STDS_CONCEPTS_