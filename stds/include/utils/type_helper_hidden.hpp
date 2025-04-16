#pragma once

#ifndef _STDS_TYPE_HELPER_HIDDEN_
#define _STDS_TYPE_HELPER_HIDDEN_

#include "config/defines.hpp"

#if SUPPORT_CONSTEXPR
#define __CONSTANCY constexpr
#else
#define __CONSTANCY const
#endif // __CONSTANCY

STDS_START

HIDDEN_STDS_START

// ------------------------------
// remove_reference
// ------------------------------
template<typename T>
struct __remove_reference { using type = T; };
template<typename T>
struct __remove_reference<T&> { using type = T; };
template<typename T>
struct __remove_reference<T&&> { using type = T; };
template<typename T>
using __remove_reference_t = typename __remove_reference<T>::type;

// ------------------------------
// remove_const
// ------------------------------
template<typename T>
struct __remove_const { using type = T; };
template<typename T>
struct __remove_const<const T> { using type = T; };
template<typename T>
using __remove_const_t = typename __remove_const<T>::type;

// ------------------------------
// remove_volatile
// ------------------------------
template<typename T>
struct __remove_volatile { using type = T; };
template<typename T>
struct __remove_volatile<volatile T> { using type = T; };
template<typename T>
using __remove_volatile_t = typename __remove_volatile<T>::type;

// ------------------------------
// remove_const_volatile
// ------------------------------
template<typename T>
struct __remove_cv { using type = T; };
template<typename T>
struct __remove_cv<const T> { using type = T; };
template<typename T>
struct __remove_cv<volatile T> { using type = T; };
template<typename T>
struct __remove_cv<const volatile T> { using type = T; };
template<typename T>
using __remove_cv_t = typename __remove_cv<T>::type;

// ------------------------------
// is_lvalue_reference
// ------------------------------
template<typename T>
struct __is_lvalue_reference { static __CONSTANCY bool value = false; };
template<typename T>
struct __is_lvalue_reference<T&> { static __CONSTANCY bool value = true; };
template<typename T>
__CONSTANCY bool __is_lvalue_reference_v = __is_lvalue_reference<T>::value;

// ------------------------------
// is_rvalue_reference
// ------------------------------
template<typename T>
struct __is_rvalue_reference { static __CONSTANCY bool value = false; };
template<typename T>
struct __is_rvalue_reference<T&&> { static __CONSTANCY bool value = true; };
template<typename T>
__CONSTANCY bool __is_rvalue_reference_v = __is_rvalue_reference<T>::value;

// ------------------------------
// is_same
// ------------------------------
template<typename A, typename B>
struct __is_same { static __CONSTANCY bool value = false; };
template<typename A>
struct __is_same<A, A> { static __CONSTANCY bool value = true; };
template<typename A, typename B>
__CONSTANCY bool __is_same_v = __is_same<A, B>::value;

// ------------------------------
// is_any_of
// ------------------------------
template<typename T, typename... Ts>
struct __is_any_of {
    static constexpr bool value = (false || ... || __is_same_v<T, Ts>);
};
template<typename T, typename... Ts>
__CONSTANCY bool __is_any_of_v = __is_any_of<T, Ts...>::value;

// ------------------------------
// is_void
// ------------------------------
template<typename T>
struct __is_void { static __CONSTANCY bool value = false; };
template<> struct __is_void<void> { static __CONSTANCY bool value = true; };
template<typename T>
__CONSTANCY bool __is_void_v = __is_void<T>::value;

// ------------------------------
// is_integral
// ------------------------------
template<typename T>
struct __is_integral { static __CONSTANCY bool value = false; };
template<> struct __is_integral<bool> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<char> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<signed char> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<unsigned char> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<wchar_t> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<char16_t> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<char32_t> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<short> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<unsigned short> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<int> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<unsigned int> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<long> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<unsigned long> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<long long> { static __CONSTANCY bool value = true; };
template<> struct __is_integral<unsigned long long> { static __CONSTANCY bool value = true; };
template<typename T>
__CONSTANCY bool __is_integral_v = __is_integral<T>::value;

// ------------------------------
// conditional
// ------------------------------
template<bool B, typename T, typename F>
struct __conditional { using type = T; };
template<typename T, typename F>
struct __conditional<false, T, F> { using type = F; };
template<bool B, typename T, typename F>
using __conditional_t = typename __conditional<B, T, F>::type;

// ------------------------------
// enable_if
// ------------------------------
template<bool B, typename T = void>
struct __enable_if {};
template<typename T>
struct __enable_if<true, T> { using type = T; };
template<bool B, typename T = void>
using __enable_if_t = typename __enable_if<B, T>::type;

// ------------------------------
// remove_extent
// ------------------------------
template<typename T>
struct __remove_extent { using type = T; };
template<typename T, sz_t N>
struct __remove_extent<T[N]> { using type = T; };
template<typename T>
struct __remove_extent<T[]> { using type = T; };
template<typename T>
using __remove_extent_t = typename __remove_extent<T>::type;

// ------------------------------
// is_array
// ------------------------------
template<typename T>
struct __is_array { static __CONSTANCY bool value = false; };
template<typename T, sz_t N>
struct __is_array<T[N]> { static __CONSTANCY bool value = true; };
template<typename T>
struct __is_array<T[]> { static __CONSTANCY bool value = true; };
template<typename T>
__CONSTANCY bool __is_array_v = __is_array<T>::value;

// ------------------------------
// is_function
// ------------------------------
template<typename T>
struct __is_function { static __CONSTANCY bool value = false; };
template<typename R, typename... Args>
struct __is_function<R(Args...)> { static __CONSTANCY bool value = true; };
template<typename R, typename... Args>
struct __is_function<R(Args..., ...)> { static __CONSTANCY bool value = true; };
template<typename T>
__CONSTANCY bool __is_function_v = __is_function<T>::value;

// ------------------------------
// decay
// ------------------------------
template<typename T>
struct __decay_impl {
private:
    using U = __remove_reference_t<T>;
public:
    using type = __conditional_t<
        __is_array_v<U>,
        typename __remove_cv_t<__remove_extent_t<U>>*,
        __conditional_t<
        __is_function_v<U>,
        typename __remove_cv_t<U>*,
        typename __remove_cv_t<U>
        >
    >;
};
template<typename T>
using __decay_t = typename __decay_impl<T>::type;

// ------------------------------
// remove_pointer
// ------------------------------
template<typename T>
struct __remove_pointer { using type = T; };
template<typename T>
struct __remove_pointer<T*> { using type = T; };
template<typename T>
using __remove_pointer_t = typename __remove_pointer<T>::type;

// ------------------------------
// remove_all
// ------------------------------
template<typename T>
struct __remove_all {
private:
    using __no_ref = __remove_reference_t<T>;
    using __no_cv = __remove_cv_t<__no_ref>;
    using __core = __conditional_t<
        __is_same_v<__no_cv, void>,
        void,
        __conditional_t<
        __is_array_v<__no_cv>,
        __remove_extent_t<__no_cv>,
        __conditional_t<
        __is_function_v<__no_cv>,
        __no_cv,
        __conditional_t<
        __is_same_v<__no_cv, __remove_pointer_t<__no_cv>>,
        __no_cv,
        __remove_pointer_t<__no_cv>
        >
        >
        >
    >;
public:
    using type = __core;
};
template<typename T>
using __remove_all_t = typename __remove_all<T>::type;

// ------------------------------
// move
// ------------------------------
template<typename T>
__CONSTANCY __remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<__remove_reference_t<T>&&>(t);
}

// ------------------------------
// forward
// ------------------------------
template<typename T>
__CONSTANCY T&& forward(__remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}

template<typename T>
__CONSTANCY T&& forward(__remove_reference_t<T>&& t) noexcept {
    static_assert(!__is_lvalue_reference_v<T>, "bad forward of rvalue as lvalue");
    return static_cast<T&&>(t);
}

HIDDEN_STDS_END
STDS_END

#undef __CONSTANCY // Clear global namespace

#endif // _STDS_TYPE_HELPER_HIDDEN_
