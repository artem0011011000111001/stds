#pragma once

#ifndef _STDS_NULL_
#define _STDS_NULL_

#include "config/defines.hpp"

STDS_START

HIDDEN_STDS_START

struct base_null_t {
/*
	Base class for a class that can be null
*/
protected:
	bool _is_null_ = false; // field responsible for validity

	// call this on null
	constexpr void reset() { _is_null_ = true; }

	constexpr base_null_t() = default;
	constexpr base_null_t(bool _is_null_) : _is_null_(_is_null_) {}

	// you need to call a null check everywhere. This is in case you don't have your own
	template<class _ThrowTy>
	constexpr void check_is_null_and_throw(const _ThrowTy& v) const {
		UNLIKELY_IF(is_null()) throw v;
	}

public:
	constexpr bool is_null() const { return _is_null_; }
};

HIDDEN_STDS_END
// null class
struct null_t final : HSTDS_::base_null_t {
	constexpr null_t() : base_null_t(true) {}
	null_t(const null_t&) = delete;
	null_t(null_t&&) = delete;
	null_t& operator=(const null_t&) = delete;
	null_t& operator=(null_t&&) = delete;
	~null_t() = default;
};

HIDDEN_STDS_START

template<class _Ty>
struct null_taker {
	_Ty value;
	constexpr null_taker(const null_t&) {}
	constexpr null_taker(null_t&&) {}
};

/*
*  |
*  |
This class is designed to allow null to be passed as an argument
	without using more loaded types.
See the usage in make_ptr.
*  |
*  |
*/

template<>
struct null_taker<void*> {
	constexpr null_taker(const null_t&) {}
	constexpr null_taker(null_t&&) {}
};

HIDDEN_STDS_END

STDS_END

#define null null_t{} // null value

#endif // _STDS_NULL_