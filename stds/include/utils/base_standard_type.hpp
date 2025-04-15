#pragma once

#ifndef _STDS_BASE_STANDARD_TYPE_
#define _STDS_BASE_STANDARD_TYPE_

#include "config/defines.hpp"
#include "config/types.hpp"
#include "utils/null.hpp"
#include "utils/code.hpp"
#include "utils/type_helper_hidden.hpp"

STDS_START

HIDDEN_STDS_START

#ifdef _MSC_VER 
using _msv__int8_t = __int8;
using _msv__int16_t = __int16;
using _msv__int32_t = __int32;
using _msv__int64_t = __int64;
using _msv__uint8_t = unsigned __int8;
using _msv__uint16_t = unsigned __int16;
using _msv__uint32_t = unsigned __int32;
using _msv__uint64_t = unsigned __int64;
using _msv__wchar_t = __wchar_t;
#else
using _msv__int8_t = HSTDS_::i8;
using _msv__int16_t = HSTDS_::i16;
using _msv__int32_t = HSTDS_::i32;
using _msv__int64_t = HSTDS_::i64;
using _msv__uint8_t = HSTDS_::u8;
using _msv__uint16_t = HSTDS_::u16;
using _msv__uint32_t = HSTDS_::u32;
using _msv__uint64_t = HSTDS_::u64;
using _msv__wchar_t = wchar_t;
#endif // _MSC_VER

// __base_standard_type class supports a wide range of fundamental types.
template<typename _Ty>
class __base_standard_type : public base_null_t {
public:
    using type = __remove_all_t<_Ty>;
private:
    // Supported types:
    // bool, char, char8_t, unsigned char, signed char, __int8,
    // char16_t, __int16, short, unsigned short, wchar_t, __wchar_t,
    // char32_t, float, __int32, int, unsigned int, long, unsigned long,
    // double, __int64, long double, long long, unsigned long long
    static_assert(__is_any_of_v<type,
        bool,
        char,
        signed char,
        unsigned char,
        char_8_t,
        char16_t,
        char32_t,
        _msv__wchar_t,

        _msv__int8_t,
        _msv__uint8_t,
        _msv__int16_t,
        _msv__uint16_t,
        _msv__int32_t,
        _msv__uint32_t,
        _msv__int64_t,
        _msv__uint64_t,

        f32,
        f64,
        f128
    >, "__base_standard_type requires a supported fundamental type");

    using self_t = __base_standard_type<type>;

protected:

    type value = type();

    virtual void reset() { base_null_t::reset(); value = type(); }

public:
    // Constructors
    __base_standard_type() noexcept = default;
    template<typename U/*, typename = __enable_if_t<__is_same_v<__remove_all_t<U>, type>>*/>
    __base_standard_type(U value) noexcept {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        this->value = value;
    }
    explicit __base_standard_type(const self_t& other) noexcept { value = other.value; }
    explicit __base_standard_type(self_t&& other) noexcept { value = move(other.value); }
    __base_standard_type(const null_t&) noexcept { reset(); }

    // Assignment operators
    self_t& operator=(const self_t& other) noexcept {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }
    self_t& operator=(__base_standard_type&& other) noexcept {
        if (this != &other) {
            value = move(other.value);
        }
        return *this;
    }

    template<typename U>
    self_t& operator=(type value) noexcept {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        this->value = value;
        return *this;
    }
    self_t& operator=(const null_t&) noexcept {
        reset();
        return *this;
    }

    // Conversion operators
    explicit operator type& () { check_is_null_and_throw(code::reference_to_null); return value; }
    explicit operator const type& () const { check_is_null_and_throw(code::reference_to_null); return value; }
    explicit operator bool() const { check_is_null_and_throw(code::reference_to_null); return static_cast<bool>(value); }

    // Arithmetic operators
    self_t operator+(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value + rhs.value;
    }
    template<typename U>
    self_t operator+(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return self_t(value + rv);
    }
    self_t operator-(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value - rhs.value;
    }
    template<typename U>
    self_t operator-(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return self_t(value - rv);
    }
    self_t operator*(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value * rhs.value;
    }
    template<typename U>
    self_t operator*(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return self_t(value * rv);
    }
    self_t operator/(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value / rhs.value;
    }
    template<typename U>
    self_t operator/(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return self_t(value / rv);
    }
    self_t operator%(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value % rhs.value;
    }
    template<typename U>
    self_t operator%(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return self_t(value % rv);
    }

    // Compound assignment operators
    self_t& operator+=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value += rhs.value; return *this;
    }
    template<typename U>
    self_t& operator+=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value += rv; return *this;
    }
    self_t& operator-=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value -= rhs.value; return *this;
    }
    template<typename U>
    self_t& operator-=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value -= rv; return *this;
    }
    self_t& operator*=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value *= rhs.value; return *this;
    }
    template<typename U>
    self_t& operator*=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value *= rv; return *this;
    }
    self_t& operator/=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value /= rhs.value; return *this;
    }
    template<typename U>
    self_t& operator/=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value /= rv; return *this;
    }
    self_t& operator%=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value %= rhs.value; return *this;
    }
    template<typename U>
    self_t& operator%=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value %= rv; return *this;
    }

    // Increment and decrement operators
    self_t& operator++() {
        check_is_null_and_throw(code::reference_to_null);
        ++value; return *this;
    }
    self_t operator++(int) {
        check_is_null_and_throw(code::reference_to_null);
        self_t tmp(*this); ++value; return tmp;
    }
    self_t& operator--() {
        check_is_null_and_throw(code::reference_to_null);
        --value; return *this;
    }
    self_t operator--(int) {
        check_is_null_and_throw(code::reference_to_null);
        self_t tmp(*this); --value; return tmp;
    }

    // Comparison operators
    bool operator==(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value == rhs.value;
    }
    template<typename U>
    bool operator==(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value == rv;
    }
    bool operator!=(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value != rhs.value;
    }
    template<typename U>
    bool operator!=(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value != rv;
    }
    bool operator<(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value < rhs.value;
    }
    template<typename U>
    bool operator<(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value < rv;
    }
    bool operator<=(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value <= rhs.value;
    }
    template<typename U>
    bool operator<=(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value <= rv;
    }
    bool operator>(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value > rhs.value;
    }
    template<typename U>
    bool operator>(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value > rv;
    }
    bool operator>=(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value >= rhs.value;
    }
    template<typename U>
    bool operator>=(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value >= rv;
    }

    // Bitwise operators (only for integral types)
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type> operator&(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value & rhs.value;
    }
    template<typename T = type, typename U>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type> operator&(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value & rv;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type> operator|(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value | rhs.value;
    }
    template<typename T = type, typename U>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type> operator|(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value | rv;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type> operator^(const self_t& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        return value ^ rhs.value;
    }
    template<typename T = type, typename U>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type> operator^(U rv) const {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        return value ^ rv;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type> operator~() const {
        check_is_null_and_throw(code::reference_to_null);
        return ~value;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator&=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value &= rhs.value; return *this;
    }
    template<typename T = type, typename U>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator&=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value &= rv; return *this;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator|=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value |= rhs.value; return *this;
    }
    template<typename T = type, typename U>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator|=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value |= rv; return *this;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator^=(const self_t& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        rhs.check_is_null_and_throw(code::reference_to_null);
        value ^= rhs.value; return *this;
    }
    template<typename T = type, typename U>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator^=(U rv) {
        static_assert(__is_same_v<__remove_all_t<U>, type>, "Conversion from _Ty to U is prohibited");
        check_is_null_and_throw(code::reference_to_null);
        value ^= rv; return *this;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator<<=(int shift) {
        check_is_null_and_throw(code::reference_to_null);
        value <<= shift; return *this;
    }
    template<typename T = type>
    HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, __base_standard_type&> operator>>=(int shift) {
        check_is_null_and_throw(code::reference_to_null);
        value >>= shift; return *this;
    }

    // Logical NOT operator
    bool operator!() const {
        check_is_null_and_throw(code::reference_to_null);
        return !value;
    }


    type& get() { check_is_null_and_throw(code::reference_to_null); return value; }
    const type& get() const { check_is_null_and_throw(code::reference_to_null); return value; }

    ~__base_standard_type() = default;
};

HIDDEN_STDS_END

// Global operators to allow operations with a primitive type T and HSTDS_::__base_standard_type<T>

// ------------------ Arithmetic Operators (T left operand) ------------------
template<typename T>
HSTDS_::__base_standard_type<T> operator+(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs + rhs.get());
}

template<typename T>
HSTDS_::__base_standard_type<T> operator-(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs - rhs.get());
}

template<typename T>
HSTDS_::__base_standard_type<T> operator*(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs * rhs.get());
}

template<typename T>
HSTDS_::__base_standard_type<T> operator/(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs / rhs.get());
}

template<typename T>
HSTDS_::__base_standard_type<T> operator%(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs % rhs.get());
}

// ------------------ Comparison Operators (T left operand) ------------------
template<typename T>
bool operator==(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return lhs == rhs.get();
}

template<typename T>
bool operator!=(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return lhs != rhs.get();
}

template<typename T>
bool operator<(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return lhs < rhs.get();
}

template<typename T>
bool operator<=(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return lhs <= rhs.get();
}

template<typename T>
bool operator>(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return lhs > rhs.get();
}

template<typename T>
bool operator>=(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return lhs >= rhs.get();
}

// ------------------ Bitwise Operators for Integral Types (T left operand) ------------------
template<typename T>
HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, HSTDS_::__base_standard_type<T>>
operator&(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs & rhs.get());
}

template<typename T>
HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, HSTDS_::__base_standard_type<T>>
operator|(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs | rhs.get());
}

template<typename T>
HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, HSTDS_::__base_standard_type<T>>
operator^(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs ^ rhs.get());
}

template<typename T>
HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, HSTDS_::__base_standard_type<T>>
operator<<(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs << rhs.get());
}

template<typename T>
HSTDS_::__enable_if_t<HSTDS_::__is_integral<T>::value, HSTDS_::__base_standard_type<T>>
operator>>(const T& lhs, const HSTDS_::__base_standard_type<T>& rhs) {
    return HSTDS_::__base_standard_type<T>(lhs >> rhs.get());
}

HIDDEN_STDS_START

// Integer
using int8_type = __base_standard_type<_msv__int8_t>;
using uint8_type = __base_standard_type<_msv__uint8_t>;
using int16_type = __base_standard_type<_msv__int16_t>;
using uint16_type = __base_standard_type<_msv__uint16_t>;
using int32_type = __base_standard_type<_msv__int32_t>;
using uint32_type = __base_standard_type<_msv__uint32_t>;
using int64_type = __base_standard_type<_msv__int64_t>;
using uint64_type = __base_standard_type<_msv__uint64_t>;
using safe_size_type = uint64_type;

// Floating
using float32_type = __base_standard_type<f32>;
using float64_type = __base_standard_type<f64>;
using float128_type = __base_standard_type<f128>;

// Chars
using char_type = __base_standard_type<char>;
using char8_t_type = __base_standard_type<char_8_t>;
using char16_t_type = __base_standard_type<char16_t>;
using char32_t_type = __base_standard_type<char32_t>;
using wchar_t_type = __base_standard_type<_msv__wchar_t>;

// Bool
using bool_type = __base_standard_type<bool>;

HIDDEN_STDS_END

STDS_END

#endif // _STDS_BASE_STANDARD_TYPE_
