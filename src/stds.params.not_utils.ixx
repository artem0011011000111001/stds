/*****************************************************************//**
 * @file   stds.params.not_utils.ixx
 * @brief  TODO
 * 
 * @date   18-6-2025
 *********************************************************************/

export module stds.params.not_utils;

import std;

export namespace stds::params {
	/**
	 * TODO
	 */
	struct not_specified_t {};

	/**
	 * TODO
	 */
	template<class T>
	inline constexpr bool is_not_specified_v = std::is_same_v<not_specified_t, T>;

	/**
	 * TODO
	 */
	template<class T, class DefaultT>
	using if_not_specified_default_t = std::conditional_t<
		!is_not_specified_v<T>,
		T,
		DefaultT
	>;

	/**
	 * TODO
	 */
	template<class T>
	concept not_void_i = requires { !std::is_void_v<T>; };

	/**
	 * TODO
	 */

}
