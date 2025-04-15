#pragma once

#ifndef _STDS_TYPES_
#define _STDS_TYPES_

#include "config/defines.hpp"

STDS_START

HIDDEN_STDS_START

using i8 = signed char;			// alias int8_t
using i16 = short;				// alias int16_t
using i32 = int;				// alias int32_t
using i64 = long long;			// alias int64_t
using u8 = unsigned char;		// alias uint8_t
using u16 = unsigned short;		// alias uint16_t
using u32 = unsigned int;		// alias uint32_t
using u64 = unsigned long long; // alias uint64_t
using f32 = float;				// alias float32
using f64 = double;				// alias float64
using f128 = long double;		// alias float128

#ifdef ARCH_64
using sz_t = u64;	// alias size_t
using iptr_t = i64;	// alias intptr_t
using uptr_t = u64;	// alias uintptr_t
#else
using sz_t = u32;	// alias size_t
using iptr_t = i32;	// alias intptr_t
using uptr_t = u32;	// alias uintptr_t
#endif

#if SUPPORT_CHAR8
using char_8_t = char8_t;
#else
using char_8_t = unsigned char;
#endif

HIDDEN_STDS_END

using byte = unsigned char;

STDS_END

#endif // _STDS_TYPES_