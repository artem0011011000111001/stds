/*****************************************************************//**
 * @file   stds.traits.utils.ixx
 * @brief  Utils for concepts and typedefs
 * 
 * @date   14-6-2025
 *********************************************************************/

export module stds.traits.utils;

import std;

export namespace stds::traits {

	/**
	 * @brief Creating concepts with templates
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	using concept_template = int;

	/**
	 * TODO
	 */
	template<typename T>
	concept exception_i = std::is_class_v<T> && std::is_base_of_v<std::exception, T>;
}
