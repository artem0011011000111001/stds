#pragma once

#ifndef _STDS_ARRAY_
#define _STDS_ARRAY_

#include "config/types.hpp"
#include "utils/null.hpp"
#include "utils/code.hpp"
#include "utils/base_standard_type.hpp"

STDS_START

/*
Wrapper for regular array
*/

template<typename _Ty, HSTDS_::sz_t N>
class array {
    static_assert(N != 0, "Cannot create array with size 0");
    static_assert(sizeof(_Ty) != 0, "_Ty size is unknown");

    using type = _Ty;
    using size_type = HSTDS_::sz_t;

    type data[N]{};
public:

    constexpr array() = default;

    constexpr array(const type(&init)[N]) {
        for (size_type i = 0; i < N; ++i) data[i] = init[i];
    }

    constexpr size_type size() const {
        return N;
    }

    constexpr HSTDS_::safe_size_type find(const type& value) const {
        for (size_type i = 0; i < N; ++i)
            if (data[i] == value) return static_cast<HSTDS_::safe_size_type::type>(i);
        return null;
    }

    constexpr bool contains(const type& value) const {
        return !find(value).is_null();
    }

    constexpr void swap(array& other) noexcept {
        for (size_type i = 0; i < N; ++i) {
            type temp = data[i];
            data[i] = other.data[i];
            other.data[i] = temp;
        }
    }

    constexpr type& operator[](size_type index) {
        if (index >= N) throw code::out_of_bounds;
        return data[index];
    }
    constexpr const type& operator[](size_type index) const {
        if (index >= N) throw code::out_of_bounds;
        return data[index];
    }
};

template<typename T, std::size_t N1, std::size_t N2>
constexpr array<T, N1 + N2> operator+(const array<T, N1>& lhs, const array<T, N2>& rhs) {
    array<T, N1 + N2> result;
    for (std::size_t i = 0; i < N1; ++i) result[i] = lhs[i];
    for (std::size_t i = 0; i < N2; ++i) result[N1 + i] = rhs[i];
    return result;
}

STDS_END

#endif // _STDS_ARRAY_
