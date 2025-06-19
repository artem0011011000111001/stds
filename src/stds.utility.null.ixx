/*****************************************************************//**
 * @file   stds.utility.null.ixx
 * @brief  TODO
 * 
 * @date   18-6-2025
 *********************************************************************/

export module stds.utility.null;

import std;

export namespace stds::utility {

	using null_t = std::nullptr_t;

	/// @brief Null value
	/// 
	/// Usage example:
	/// @code
	/// optional<int> value = null;
	/// @endcode
	inline constexpr null_t null = nullptr;
}
