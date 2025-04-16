#pragma once

#ifndef _STDS_DYNAMIC_ARRAY_
#define _STDS_DYNAMIC_ARRAY_

#include "config/types.hpp"
#include "utils/code.hpp"
#include "utils/base_standard_type.hpp"
#include "utils/utility_hidden.hpp"
#include "utils/null.hpp"
#include "ptr.hpp"

STDS_START

HIDDEN_STDS_START
EXPER_STDS_START

/*
Dynamic array
Still in experimental
*/

template<typename _Ty, class _Allocator = HSTDS_::base_alloc<_Ty>>
class dynamic_array : public HSTDS_::base_null_t {
    static_assert(sizeof(_Ty) != 0, "_Ty size is unknown");

    using type = _Ty;
    using allocator = _Allocator;
    using pointer = ptr<type, allocator>;
    using size_type = HSTDS_::sz_t;

    pointer data;
    size_type _size = 0;
    size_type _capacity = 0;

    void reset() {
        base_null_t::reset();
        data = null;
        _size = 0;
        _capacity = 0;
    }

    void reallocate(size_type new_capacity) {
        pointer new_data = make_ptr<type, nullptr>(new_capacity);
        for (size_type i = 0; i < _size; ++i)
            new_data[i] = HSTDS_::move(data[i]);
        data = HSTDS_::move(new_data);
        _capacity = new_capacity;
    }

public:

    dynamic_array() { reset(); }

    dynamic_array(const dynamic_array& other) {
        if (other.is_null()) {
            reset();
            return;
        }
        data = make_ptr<type, nullptr>(other._capacity);
        for (size_type i = 0; i < other._size; ++i)
            data[i] = other.data[i];
        _size = other._size;
        _capacity = other._capacity;
        _is_null_ = false;
    }

    template <typename... Args>
    dynamic_array(Args&&... args) {
        static_assert((HSTDS_::__is_same_v<type, Args> && ...),
            "All arguments must be same to type");

        constexpr size_type count = sizeof...(Args);

        data = make_ptr<type, count>();
        size_type index = 0;
        ((data[index++] = HSTDS_::forward<Args>(args)), ...);

        _size = count;
        _capacity = count;
        _is_null_ = false;
    }

    dynamic_array(const null_t&) { reset(); }

    size_type size() const { return _size; }
    size_type capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    void clear() { reset(); }

    void reserve(size_type new_capacity) {
        check_is_null_and_throw(code::reference_to_null);
        if (new_capacity > _capacity)
            reallocate(new_capacity);
    }

    void shrink_to_fit() {
        check_is_null_and_throw(code::reference_to_null);
        if (_capacity > _size)
            reallocate(_size);
    }

    void append(const type& value) {
        check_is_null_and_throw(code::reference_to_null);
        if (_size == _capacity)
            reserve((_capacity == 0) ? 1 : _capacity * 2);
        data[_size++] = value;
    }

    type pop_back() {
        check_is_null_and_throw(code::reference_to_null);
        if (_size == 0) throw code::out_of_bounds;

        return HSTDS_::move(data[--_size]);
    }

    void insert(size_type index, const type& value) {
        check_is_null_and_throw(code::reference_to_null);
        if (index > _size) throw code::out_of_bounds;

        if (_size == _capacity)
            reserve((_capacity == 0) ? 1 : _capacity * 2);
        for (size_type i = _size; i > index; --i)
            data[i] = HSTDS_::move(data[i - 1]);
        data[index] = value;
        ++_size;
    }

    void erase(size_type index) {
        check_is_null_and_throw(code::reference_to_null);
        if (index >= _size) throw code::out_of_bounds;

        for (size_type i = index; i < _size - 1; ++i)
            data[i] = HSTDS_::move(data[i + 1]);
        --_size;
    }

    bool remove(const type& value) {
        check_is_null_and_throw(code::reference_to_null);
        for (size_type i = 0; i < _size; ++i) {
            if (data[i] == value) {
                erase(i);
                return true;
            }
        }
        return false;
    }

    void resize(size_type new_size, const type& default_value = type{}) {
        check_is_null_and_throw(code::reference_to_null);
        if (new_size > _capacity)
            reserve(new_size);
        for (size_type i = _size; i < new_size; ++i)
            data[i] = default_value;
        _size = new_size;
    }

    void swap(size_type i, size_type j) {
        check_is_null_and_throw(code::reference_to_null);
        if (i >= _size || j >= _size) throw code::out_of_bounds;

        HSTDS_::swap(data[i], data[j]);
    }

    void reverse() {
        check_is_null_and_throw(code::reference_to_null);
        for (size_type i = 0; i < _size / 2; ++i)
            swap(i, _size - i - 1);
    }

    HSTDS_::safe_size_type find(const type& value) const {
        check_is_null_and_throw(code::reference_to_null);
        for (size_type i = 0; i < _size; ++i)
            if (data[i] == value)
                return static_cast<HSTDS_::safe_size_type::type>(i);
        return null;
    }

    bool contains(const type& value) const {
        return !find(value).is_null();
    }

    size_type count(const type& value) const {
        check_is_null_and_throw(code::reference_to_null);
        size_type c = 0;
        for (size_type i = 0; i < _size; ++i)
            if (data[i] == value) ++c;
        return c;
    }

    template<typename Func>
    auto map(Func func) const -> dynamic_array<decltype(func(data[0]))> {
        check_is_null_and_throw(code::reference_to_null);
        using result_type = decltype(func(data[0]));
        dynamic_array<result_type> result;
        result.reserve(_size);
        for (size_type i = 0; i < _size; ++i)
            result.append(func(data[i]));
        return result;
    }

    template<typename Pred>
    dynamic_array filter(Pred pred) const {
        check_is_null_and_throw(code::reference_to_null);
        dynamic_array result;
        for (size_type i = 0; i < _size; ++i)
            if (pred(data[i]))
                result.append(data[i]);
        return result;
    }

    template<typename Comp = HSTDS_::__less<type>>
    dynamic_array sort(Comp comp = Comp{}) {
        check_is_null_and_throw(code::reference_to_null);
        dynamic_array result = *this;
        for (size_type i = 0; i < _size; ++i)
            for (size_type j = i + 1; j < _size; ++j)
                if (comp(result[j], result[i]))
                    HSTDS_::swap(result[i], result[j]);
        return result;
    }

    void sort_desc() {
        sort<HSTDS_::__greater<type>>();
    }

    void unique() {
        check_is_null_and_throw(code::reference_to_null);
        if (_size < 2) return;
        dynamic_array result = *this;
        result = result.sort();
        size_type write = 1;
        for (size_type read = 1; read < _size; ++read) {
            if (!(data[read] == data[write - 1]))
                data[write++] = data[read];
        }
        _size = write;
    }

    dynamic_array slice(size_type start, size_type end) const {
        check_is_null_and_throw(code::reference_to_null);
        if (start > end || end > _size) throw code::out_of_bounds;
        dynamic_array result;
        result.reserve(end - start);
        for (size_type i = start; i < end; ++i)
            result.append(data[i]);
        return result;
    }

    dynamic_array concat(const dynamic_array& other) const {
        check_is_null_and_throw(code::reference_to_null);
        dynamic_array result;
        result.reserve(_size + other._size);
        for (size_type i = 0; i < _size; ++i)
            result.append(data[i]);
        for (size_type i = 0; i < other._size; ++i)
            result.append(other.data[i]);
        return result;
    }

    template<typename Func, typename Acc>
    Acc reduce(Func func, Acc initial) const {
        check_is_null_and_throw(code::reference_to_null);
        for (size_type i = 0; i < _size; ++i)
            initial = func(initial, data[i]);
        return initial;
    }

    dynamic_array<HSTDS_::__pair<type, type>> zip(const dynamic_array& other) const {
        check_is_null_and_throw(code::reference_to_null);
        dynamic_array<HSTDS_::__pair<type, type>> result;
        size_type min_size = _size < other._size ? _size : other._size;
        result.reserve(min_size);
        for (size_type i = 0; i < min_size; ++i)
            result.append({ data[i], other[i] });
        return result;
    }

    void fill(const type& value) {
        check_is_null_and_throw(code::reference_to_null);
        for (size_type i = 0; i < _size; ++i)
            data[i] = value;
    }

    dynamic_array& operator=(const dynamic_array& other) {
        if (this == &other)
            return *this;
        if (other.is_null()) {
            reset();
            return *this;
        }
        data = make_ptr<type, nullptr>(other._capacity);
        for (size_type i = 0; i < other._size; ++i)
            data[i] = other.data[i];
        _size = other._size;
        _capacity = other._capacity;
        _is_null_ = false;
        return *this;
    }

    dynamic_array& operator=(dynamic_array&& other) noexcept {
        if (this == &other)
            return *this;
        data = HSTDS_::move(other.data);
        _size = other._size;
        _capacity = other._capacity;
        _is_null_ = other._is_null_;
        other.reset();
        return *this;
    }

    dynamic_array& operator=(const null_t&) { reset(); }

    dynamic_array operator+(const dynamic_array& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        return this->concat(rhs);
    }

    dynamic_array& operator+=(const dynamic_array& rhs) {
        check_is_null_and_throw(code::reference_to_null);
        for (size_type i = 0; i < rhs.size(); ++i)
            this->append(rhs[i]);
        return *this;
    }

    bool operator==(const dynamic_array& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        if (_size != rhs._size) return false;
        for (size_type i = 0; i < _size; ++i)
            if (!(data[i] == rhs[i])) return false;
        return true;
    }

    bool operator!=(const dynamic_array& rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const dynamic_array& rhs) const {
        check_is_null_and_throw(code::reference_to_null);
        size_type min_size = _size < rhs._size ? _size : rhs._size;
        for (size_type i = 0; i < min_size; ++i) {
            if (data[i] < rhs[i]) return true;
            if (rhs[i] < data[i]) return false;
        }
        return _size < rhs._size;
    }

    bool operator<=(const dynamic_array& rhs) const {
        return *this < rhs || *this == rhs;
    }

    bool operator>(const dynamic_array& rhs) const {
        return !(*this <= rhs);
    }

    bool operator>=(const dynamic_array& rhs) const {
        return !(*this < rhs);
    }

    type& operator[](size_type index) {
        check_is_null_and_throw(code::reference_to_null);
        return data[index];
    }

    const type& operator[](size_type index) const {
        check_is_null_and_throw(code::reference_to_null);
        return data[index];
    }

    type& front() {
        check_is_null_and_throw(code::reference_to_null);
        return data[0];
    }

    const type& front() const {
        check_is_null_and_throw(code::reference_to_null);
        return data[0];
    }

    type& back() {
        check_is_null_and_throw(code::reference_to_null);
        return data[_size - 1];
    }

    const type& back() const {
        check_is_null_and_throw(code::reference_to_null);
        return data[_size - 1];
    }
};

EXPER_STDS_END
HIDDEN_STDS_END

STDS_END

#endif // _STDS_DYNAMIC_ARRAY_
