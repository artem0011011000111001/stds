#pragma once

#ifndef _STDS_WRAPPER_
#define _STDS_WRAPPER_

#include "config/defines.hpp"

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