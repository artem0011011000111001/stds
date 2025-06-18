/*****************************************************************//**
 * @file   stds.utility.nothrow.ixx
 * @brief  TODO
 * 
 * @date   17-6-2025
 *********************************************************************/

export module stds.utility.nothrow;

import std;

export namespace stds::utility {
	/**
	 * @brief Convenience wrapper around std::is_nothrow_* traits
	 *
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T>
	struct nothrow {
		static constexpr bool default_constructible = std::is_nothrow_default_constructible_v<T>;
		static constexpr bool copy_constructible = std::is_nothrow_copy_constructible_v<T>;
		static constexpr bool move_constructible = std::is_nothrow_move_constructible_v<T>;

		static constexpr bool copy_assignable = std::is_nothrow_copy_assignable_v<T>;
		static constexpr bool move_assignable = std::is_nothrow_move_assignable_v<T>;

		static constexpr bool destructible = std::is_nothrow_destructible_v<T>;
		
		template<class... Args>
		static constexpr bool constructible = std::is_nothrow_constructible_v<T, Args...>;

		template<class... Args>
		static constexpr bool invocable = std::is_nothrow_invocable_v<T, Args...>;

		template<class R, class... Args>
		static constexpr bool invocable_r = std::is_nothrow_invocable_r_v<R, T, Args...>;
	};
}
