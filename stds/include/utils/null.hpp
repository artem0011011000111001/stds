#pragma once

#ifndef _STDS_NULL_
#define _STDS_NULL_

#include "config/defines.hpp"

STDS_START

HIDDEN_STDS_START

struct base_null_t {
protected:
	bool _is_null_ = false;

	constexpr void reset() { _is_null_ = true; }

	constexpr base_null_t() = default;
	constexpr base_null_t(bool _is_null_) : _is_null_(_is_null_) {}

	template<class _ThrowTy>
	constexpr void check_is_null_and_throw(const _ThrowTy& v) const {
#if !defined(__cpp_constexpr_dynamic_alloc)
		if (is_null()) throw v;
#else
		if (is_null()) [[unlikely]] throw v;
#endif
	}

public:
	constexpr bool is_null() const { return _is_null_; }
};

HIDDEN_STDS_END

struct null_t final : HSTDS_::base_null_t {
	constexpr null_t() : base_null_t(true) {}
	null_t(const null_t&) = delete;
	null_t(null_t&&) = delete;
	null_t& operator=(const null_t&) = delete;
	null_t& operator=(null_t&&) = delete;
	~null_t() = default;
};

HIDDEN_STDS_START

struct null_taker {
public:
	constexpr null_taker(const null_t&) {}
	constexpr null_taker(null_t&&) {}
};

HIDDEN_STDS_END

STDS_END

#define null null_t{}

#endif // _STDS_NULL_