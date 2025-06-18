#pragma once

#ifndef _STDS_WRAPPER_
#define _STDS_WRAPPER_

#include "config/defines.hpp"

/*
Wrappers to clarify the meaning of arguments
Example:
void* memcpy(out<void>* dest, const in<void>* src, in<size_t> count)
*/

STDS_START

template<typename _Ty>
using in = _Ty;  // input

template<typename _Ty>
using out = _Ty; // output

template<typename _Ty>
using opt = _Ty; // optional

template<typename _Ty>
using out_opt = _Ty; // output optional

STDS_END

#endif // _STDS_WRAPPER_