/*****************************************************************//**
 * @file   stds.traits.error.ixx
 * @brief  Interfaces for error handling
 * 
 * @date   14-6-2025
 *********************************************************************/

export module stds.traits.error;

import std;
import stds.params.not_utils;
import stds.utility.null;

#include "macro_utils.h"

using namespace stds::params;


template<class TName, class /* must be error_policy_i */ TPolicy> using fv /* decoding 'fixed_value_type' */ = if_not_specified_default_t<TName, typename TPolicy::default_value_type>;
template<class TName, class /* must be error_policy_i */ TPolicy> using fe /* decoding 'fixed_error_type' */ = if_not_specified_default_t<TName, typename TPolicy::default_error_type>;
// for 

#define	__template_part(_policy, _valueT, _errorT)	\
template<								\
	error_policy_i _policy,				\
	class _valueT = not_specified_t,	\
	class _errorT = not_specified_t		\
>										\
	requires requires {					\
	not_void_i<fv<_valueT, _policy>>;	\
	not_void_i<fe<_errorT, _policy>>;	\
}
#define __noexcept_part(_policy, _valueT, _errorT)	\
noexcept(is_policy_nothrow_v<	\
	_policy,					\
	fv<_valueT, _policy>,		\
	fv<_errorT, _policy>		\
>)
// these macros were hardcoded to make writing utilities easier

export namespace stds::traits {
	/**
	 * TODO
	 */
	template<typename T>
	concept exception_i = std::is_class_v<T> && std::is_base_of_v<std::exception, T>;

	/**
	 * @brief Static interface for any error handler
	 *
	 * @tparam T Type for check
	 * @tparam ValueT Value type. Default is T::default_value_type
	 * @tparam ErrorT Error type. Default is T::default_error_type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T, class ValueT = not_specified_t, class ErrorT = not_specified_t>
	concept error_policy_i = requires {
		typename T::default_value_type;
		typename T::default_error_type;
		not_void_i<typename T::default_value_type>;
		not_void_i<typename T::default_error_type>;
		not_void_i<ValueT>;
		not_void_i<ErrorT>;
		{ T::template on_error<
			fv<ValueT, T>,
			fe<ErrorT, T>>
			(std::declval<std::string>()) } -> std::same_as<
			fv<ValueT, T>&
			/* default value, when error has been invoked and isn't [[noreturn]]. don't return a rubbish it lead to a UB */>;
	};

	/**
	 * @brief It is used for know if the Policy throws
	 * 
	 * @tparam Policy Error policy
	 * @tparam ValueT Value type. Default is Policy::default_value_type
	 * @tparam ErrorT Error type. Default is Policy::default_error_type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 * 
	 * @returns If the Policy throws
	 */
	__template_part(Policy, ValueT, ErrorT)
	inline constexpr bool is_policy_nothrow_v = noexcept(Policy::template on_error<
		fv<ValueT, Policy>,
		fe<ErrorT, Policy>
	>(std::declval<std::string>()));

	/**
	 * @brief It is used for inform a error
	 *
	 * @tparam Policy Error policy
	 * @tparam ValueT Value type. Default is Policy::default_value_type
	 * @tparam ErrorT Error type. Default is Policy::default_error_type
	 *
	 * Usage example:
	 * TODOEXAMPLE
	 *
	 * @returns Default value reference
	 */
	__template_part(Policy, ValueT, ErrorT)
	constexpr auto& make_error(std::string message = "")
		__noexcept_part(Policy, ValueT, ErrorT)
	{
		return Policy::template on_error<
			fv<ValueT, Policy>,
			fe<ErrorT, Policy>
		>(message);
	}

	/**
	 * @brief It is used for inform a error if the condition is true
	 * 
	 * @tparam Policy Error policy
	 * @tparam ValueT Value type. Default is Policy::default_value_type
	 * @tparam ErrorT Error type. Default is Policy::default_error_type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 * 
	 * @returns If the error has been informed returns error default_value, otherwise returns null
	 */
	__template_part(Policy, ValueT, ErrorT)
	constexpr auto* make_error_if(bool condition, std::string message = "")
		__noexcept_part(Policy, ValueT, ErrorT)
	{
		return condition ?
			&Policy::template on_error<
			fv<ValueT, Policy>,
			fe<ErrorT, Policy>
			>(message) :
			utility::null;
	}

	/**
	 * TODO
	 */
	struct throw_policy {
		using default_value_type = not_specified_t; // stub
		using default_error_type = std::exception;

		template<class ValueT = default_value_type, class ErrorT = default_error_type>
			requires requires { not_void_i<ValueT>; not_void_i<ErrorT>; }
		static ValueT& on_error(const std::string& msg) {
			throw ErrorT(msg.c_str());
		}

		/*
		* Example to show what you can return as the default value
		* 
		*	template<class ValueT = default_value_type, class ErrorT = default_error_type>
		*		requires requires { not_void_i<ValueT>; not_void_i<ErrorT>; }
		*	static ValueT& on_error(const std::string& msg) {
		*		static ValueT default_value = ValueT();
		*		// logging...
		*		return default_value;
		*	}
		* 
		* // you should not return a rubbish it can lead to a undefined behaviour
		*/
	};

	static_assert(error_policy_i<throw_policy>, "stds error: " stringof(throw_policy) " does not match for " stringof(error_policy_i));
}

#undef __template_part
#undef __noexcept_part