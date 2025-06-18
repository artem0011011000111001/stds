/*****************************************************************//**
 * @file   stds.traits.error_policy.ixx
 * @brief  Interfaces for error handling
 * 
 * @date   14-6-2025
 *********************************************************************/

export module stds.traits.error_policy;

import std;
import stds.traits.utils;

#include "macro_utils.h"

export namespace stds::traits {
	/**
	 * @brief Static interface for any error handler
	 *
	 * @tparam T Type for check
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T, class ErrorT = std::exception>
	concept error_policy_i = requires {
		{ T::on_error(std::declval<std::string>()) } -> std::same_as<void>;
		{ T::template on_error<ErrorT>(std::declval<std::string>()) } -> std::same_as<void>;
	};

	/**
	 * @brief It is used for know if the Policy throws
	 * 
	 * @tparam Policy Error policy
	 * @tparam ErrorT Error type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 * 
	 * @returns If the Policy throws
	 */
	template<error_policy_i Policy, class ErrorT = std::exception>
	inline constexpr bool is_policy_nothrow =
		noexcept(Policy::template on_error<ErrorT>(std::declval<std::string>())) &&
		noexcept(Policy::on_error(std::declval<std::string>()));

	/**
	 * @brief It is used for inform a error if the condition is true
	 * 
	 * @tparam Policy Error policy
	 * @tparam ErrorT Error type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 * 
	 * @returns Has the error been informed
	 */
	template<error_policy_i Policy, class ErrorT = std::exception>
	constexpr bool error_if(bool condition, std::string message = "")
		noexcept(is_policy_nothrow<Policy, ErrorT>)
	{
		if (condition)
			Policy::template on_error<ErrorT>(message);
		return condition;
	}

	/**
	 * TODO
	 */
	struct throw_policy {
		static void on_error(const std::string& msg) {
			throw std::exception(msg.c_str());
		}

		template<class ErrorT>
		static void on_error(const std::string& msg) {
			throw ErrorT(msg.c_str());
		}
	};

	static_assert(error_policy_i<throw_policy>, "stds error:" _stringof(throw_policy) " does not match for " _stringof(error_policy_i));
}