#pragma once

#ifndef _STDS_DEFINES_
#define _STDS_DEFINES_

// C++ version macros
#define __CPP __cplusplus

#define __CPP23 202302L
#define __CPP20 202002L
#define __CPP17 201703L
#define __CPP14 201402L
#define __CPP11 201103L
#define __CPP98 199711L

#if __CPP >= __CPP23
#define __HAS_CPP23 1
#else
#define __HAS_CPP23 0
#endif

#if __CPP >= __CPP20
#define __HAS_CPP20 1
#else
#define __HAS_CPP20 0
#endif

#if __CPP >= __CPP17
#define __HAS_CPP17 1
#else
#define __HAS_CPP17 0
#endif

#if __CPP >= __CPP14
#define __HAS_CPP14 1
#else
#define __HAS_CPP14 0
#endif

#if __CPP >= __CPP11
#define __HAS_CPP11 1
#else
#define __HAS_CPP11 0
#endif

#if __CPP >= __CPP98
#define __HAS_CPP98 1
#else
#define __HAS_CPP98 0
#endif

#ifdef BUILDING_STDS
#define STDS_EXPORT __declspec(dllexport)
#elif defined(USING_STDS)
#define STDS_EXPORT __declspec(dllimport)
#else
#define STDS_EXPORT
#endif

// Supports
#ifdef __cpp_char8_t
#define SUPPORT_CHAR8 1
#else
#define SUPPORT_CHAR8 0
#endif // __cpp_char8_t

#ifdef __cpp_constexpr
#define SUPPORT_CONSTEXPR 1
#else
#define SUPPORT_CONSTEXPR 0
#endif // __cpp_constexpr

// Architecture bits amount
#ifndef ARCH_BITS
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
#define ARCH_BITS 64
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__)
#define ARCH_BITS 32
#else
#error "Not supported architecture"
// #define ARCH_BITS (sizeof(void*) * 8) // fallback
#endif
#endif

// Has 64-bit
#ifndef ARCH_64
#if ARCH_BITS >= 64
#define ARCH_64 1
#endif // ARCH_BITS == 64
#endif

// Has 32-bit
#ifndef ARCH_32
#if ARCH_BITS >= 32
#define ARCH_32 1
#endif // ARCH_BITS == 32
#endif

#define STDS_NAMESPACE stds
#define STDS_ ::stds

#define STDS_START namespace STDS_NAMESPACE {
#define STDS_END }

#define HIDDEN_STDS_NAMESPACE __hidden
#define HSTDS_ ::stds::__hidden

#define HIDDEN_STDS_START namespace HIDDEN_STDS_NAMESPACE {
#define HIDDEN_STDS_END }

#define EXPER_STDS_NAMESPACE __experimental
#define EXPRSTDS_ ::stds::__hidden::__experimental

#define EXPER_STDS_START namespace EXPER_STDS_NAMESPACE {
#define EXPER_STDS_END }

#endif // _STDS_DEFINES_