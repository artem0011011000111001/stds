/*****************************************************************//**
 * @file   stds.params.in.ixx
 * @brief  in function parameter
 * 
 * @date   10-6-2025
 *********************************************************************/

export module stds.params.in;

#include "macro_utils.h"

export namespace stds::params {
	/*
	 * @brief Mandatory non-changeable function parameter
	 *
	 * @tparam T Parameter type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T> struct STDS_API in {
		using type = T;
		using const_type = const type&;

		const_type ref;
		in(const_type ref) : ref(ref) {}
		operator const_type() const { return ref; }
	};
}