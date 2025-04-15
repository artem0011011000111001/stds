#pragma once

#ifndef _STDS_INT_
#define _STDS_INT_

#include "utils/base_standard_type.hpp"

#if __HAS_CPP20
#include "utils/concepts_hidden.hpp"
#define __INTEGRAL_CONCEPT(T) HSTDS_::__integral_c T
#else
#define __INTEGRAL_CONCEPT(T) typename T, typename HSTDS_::__enable_if_t<HSTDS_::__is_integral_v<T>, T> = 0
#endif // __HAS_CPP20

STDS_START

// --- Numeric types ---
using bool_t = HSTDS_::bool_type;

using int8 = HSTDS_::int8_type;
using uint8 = HSTDS_::uint8_type;
using int16 = HSTDS_::int16_type;
using uint16 = HSTDS_::uint16_type;
using int32 = HSTDS_::int32_type;
using uint32 = HSTDS_::uint32_type;
using int64 = HSTDS_::int64_type;
using uint64 = HSTDS_::uint64_type;
using safe_size = HSTDS_::safe_size_type;

using float32 = HSTDS_::float32_type;
using float64 = HSTDS_::float64_type;
using float128 = HSTDS_::float128_type;

// --- Numeric casts ---
template<__INTEGRAL_CONCEPT(T)>
bool_t bool_cast(T v) { return bool_t(static_cast<bool_t::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
int8 i8_cast(T v) { return int8(static_cast<int8::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
uint8 u8_cast(T v) { return uint8(static_cast<uint8::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
int16 i16_cast(T v) { return int16(static_cast<int16::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
uint16 u16_cast(T v) { return uint16(static_cast<uint16::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
int32 i32_cast(T v) { return int32(static_cast<int32::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
uint32 u32_cast(T v) { return uint32(static_cast<uint32::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
int64 i64_cast(T v) { return int64(static_cast<int64::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
uint64 u64_cast(T v) { return uint64(static_cast<uint64::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
safe_size sfsz_cast(T v) { return safe_size(static_cast<safe_size::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
float32 f32_cast(T v) { return float32(static_cast<float32::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
float64 f64_cast(T v) { return float64(static_cast<float64::type>(v)); }

template<__INTEGRAL_CONCEPT(T)>
float128 f128_cast(T v) { return float128(static_cast<float128::type>(v)); }

STDS_END

#undef __INTEGRAL_CONCEPT // Clear global namespace

#endif // _STDS_INT_