#pragma once

#ifndef _STDS_PTR_
#define _STDS_PTR_

#include "utils/null.hpp"
#include "utils/code.hpp"
#include "utils/wrapper.hpp"
#include "utils/type_helper_hidden.hpp"
#include "config/types.hpp"

STDS_START

HIDDEN_STDS_START

template<typename T, typename U>
T* raw_ptr_cast(U* ptr) {
	if (!ptr) return nullptr;
	return static_cast<T*>(static_cast<void*>(ptr));
}

template<class _Ty>
class allocated_data : public base_null_t {
	template<typename T>
	struct control_block {
		T* data = nullptr;
		size_t ref_count = 1;

		control_block(T* ptr) : data(ptr) {}
	};

	using pointer = _Ty;

	control_block<_Ty>* ctrl = nullptr;
public:
	allocated_data() { reset(); }

	void reset() {
		base_null_t::reset();
		if (ctrl) {
			if (--ctrl->ref_count == 0) {
				delete[] ctrl->data;
				delete ctrl;
			}
			ctrl = nullptr;
		}
	}

	void set_data(pointer* data) {
		if (data) {
			ctrl = new control_block<_Ty>(data);
			_is_null_ = false;
		}
		else {
			reset();
		}
	}

	// May return nullptr. Check this with is_valid
	pointer* get_data() const {
		return ctrl ? ctrl->data : nullptr;
	}

	bool is_valid() const {
		return !is_null() && ctrl && ctrl->data;
	}

	void increment() {
		if (ctrl) ++ctrl->ref_count;
	}

	void decrement() {
		if (ctrl && --ctrl->ref_count == 0) {
			delete[] ctrl->data;
			delete ctrl;
			ctrl = nullptr;
		}
	}

	size_t use_count() const {
		return ctrl ? ctrl->ref_count : 0;
	}
};

template<class _Ty>
struct base_alloc {
	using type = _Ty;

	template<class... Args>
	static allocated_data<type> alloc(sz_t count, Args&&... args) {
		if (count == 0 || sizeof(type) == 0) throw code::zero_allocation;

		allocated_data<type> data;

		type* raw = new type[count];

		for (sz_t i = 0; i < count; ++i) {
			new (raw + i) type(HSTDS_::forward<Args>(args)...);
		}

		data.set_data(raw);

		return data;
	}

	static void deallocate(allocated_data<type>& data) {
		if (data.is_valid()) {
			data.reset();
		}
	}
};

HIDDEN_STDS_END

template<class _Ty, class _Allocator = HSTDS_::base_alloc<_Ty>>
class ptr : public HSTDS_::base_null_t {
	static_assert(!HSTDS_::__is_void_v<_Ty>, "ptr does not support void type");

	using data = _Ty;
	using allocator = _Allocator;
	using pointer = HSTDS_::allocated_data<data>;
	using size_type = HSTDS_::sz_t;

	pointer base;

	data* start = nullptr;
	data* end = nullptr;

	void reset() {
		base_null_t::reset();
		if (base.is_valid()) {
			allocator::deallocate(base);
			if (base.is_valid()) { // In case allocator does not call
				base.reset();
			}
		}
		start = nullptr;
		end = nullptr;
	}

public:

	// Returns validity of data
	bool is_valid() const {
		return !is_null() && base.is_valid();
	}

	ptr() noexcept {
		_is_null_ = true;
		start = end = nullptr;
	}

	template<class... Args>
	ptr(size_type count, Args&&... args) {
		base = allocator::alloc(count, HSTDS_::forward<Args>(args)...);
		if (!base.is_valid()) {
			throw code::invalid_allocate;
		}
		start = base.get_data();
		end = start + count;
		this->_is_null_ = false;
	}

	ptr(const ptr& other) {
		base = other.base;
		base.increment();
		start = other.start;
		end = other.end;
		_is_null_ = other._is_null_;
	}

	ptr(const null_t&) { reset(); }

	size_type size() const {
		if (!is_valid()) throw code::reference_to_null;
		return end - start;
	}

	size_type ram_size() const {
		return size() * sizeof(data); // size() already does is_valid test
	}

	data* get() {
		if (!is_valid()) throw code::reference_to_null;
		return base.get_data();
	}

	const data* get() const {
		if (!is_valid()) throw code::reference_to_null;
		return base.get_data();
	}

	ptr& operator=(const ptr& other) {
		if (this != &other) {
			reset();
			base = other.base;
			base.increment();
			start = other.start;
			end = other.end;
			_is_null_ = other._is_null_;
		}
		return *this;
	}

	ptr& operator=(const null_t&) {
		reset();
		return *this;
	}

	data& operator*() {
		if (!is_valid()) throw code::reference_to_null;
		return *base.get_data();
	}

	const data& operator*() const {
		if (!is_valid()) throw code::reference_to_null;
		return *base.get_data();
	}

	data* operator->() {
		if (!is_valid()) throw code::reference_to_null;
		return base.get_data();
	}

	const data* operator->() const {
		if (!is_valid()) throw code::reference_to_null;
		return base.get_data();
	}

	data& operator[](size_type index) {
		if (!is_valid()) throw code::reference_to_null;

		if (index >= size()) throw code::out_of_bounds;

		return *(base.get_data() + index);
	}

	const data& operator[](size_type index) const {
		if (!is_valid()) throw code::reference_to_null;

		if (index >= size()) throw code::out_of_bounds;

		return *(base.get_data() + index);
	}

	~ptr() {
		reset();
	}
};

template<class _Ty, HSTDS_::sz_t count = 1, class _Allocator = HSTDS_::base_alloc<_Ty>, class... Args>		// make_ptr<type, count, alloc>()
ptr<_Ty> make_ptr(Args&&... args) {
	return ptr<_Ty, _Allocator>(count, HSTDS_::forward<Args>(args)...);
}

template<class _Ty, void*, class _Allocator = HSTDS_::base_alloc<_Ty>, class... Args>						// make_ptr<type, nullptr, alloc>(count)
ptr<_Ty> make_ptr(HSTDS_::sz_t count, Args&&... args) {
	return ptr<_Ty, _Allocator>(count, HSTDS_::forward<Args>(args)...);
}

//#if __HAS_CPP20
//template<class _Ty, HSTDS_::null_taker<nullptr>, class _Allocator = HSTDS_::base_alloc<_Ty>, class... Args>	// make_ptr<type, null, alloc>(count)
//ptr<_Ty> make_ptr(HSTDS_::sz_t count, Args&&... args) {
//	return ptr<_Ty, _Allocator>(count, HSTDS_::forward<Args>(args)...);
//}
//#endif // __HAS_CPP20

STDS_END

#endif // _STDS_PTR_