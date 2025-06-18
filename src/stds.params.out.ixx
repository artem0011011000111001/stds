/*****************************************************************//**
 * @file   stds.params.out.ixx
 * @brief  out function parameter
 * 
 * @date   10-6-2025
 *********************************************************************/

export module stds.params.out;

#include "macro_utils.h"

export namespace stds::params {
	/*
	 * @brief Mandatory changeable function parameter
	 *
	 * @tparam T Parameter type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T> struct STDS_API out {
		using type = T;
		using ref_type = type&;

		ref_type ref;
		out(ref_type ref) : ref(ref) {}
		operator ref_type() { return ref; }
	};
}