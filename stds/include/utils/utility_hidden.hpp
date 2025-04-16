#pragma once

#ifndef _STDS_UTILITY_HIDDEN_
#define _STDS_UTILITY_HIDDEN_

#include "utils/type_helper_hidden.hpp"

// Useful utilities, needs to be made global in the future

STDS_START

HIDDEN_STDS_START

template<class _Ty1, class _Ty2>
struct __pair {
	_Ty1 first;
	_Ty2 second;
};

template<class _Ty1, class _Ty2, class _Ty3>
struct __group {
	_Ty1 first;
	_Ty2 second;
	_Ty3 third;
};

template<class _Ty>
struct __less {
	bool operator()(const __less<_Ty>& left, const __less<_Ty>& right) {
		return left < right;
	}
};

template<class _Ty>
struct __greater {
	bool operator()(const __less<_Ty>& left, const __less<_Ty>& right) {
		return left > right;
	}
};

template<class _Ty>
struct __lesseq {
	bool operator()(const __less<_Ty>& left, const __less<_Ty>& right) {
		return left <= right;
	}
};

template<class _Ty>
struct __greatereq {
	bool operator()(const __less<_Ty>& left, const __less<_Ty>& right) {
		return left >= right;
	}
};

template<class _Ty>
struct __equal {
	bool operator()(const __less<_Ty>& left, const __less<_Ty>& right) {
		return left == right;
	}
};

template<class _Ty>
struct __nequal {
	bool operator()(const __less<_Ty>& left, const __less<_Ty>& right) {
		return left != right;
	}
};

template<class _Ty>
void swap(_Ty& left, _Ty& right) {
	_Ty tmp = HSTDS_::move(left);
	left = HSTDS_::move(right);
	right = HSTDS_::move(tmp);
}

HIDDEN_STDS_END

STDS_END

#endif // _STDS_UTILITY_HIDDEN_