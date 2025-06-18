/*****************************************************************//**
 * @file   stds.utility.optional.ixx
 * @brief  Struct optional declare
 * 
 * @date   10-6-2025
 *********************************************************************/

export module stds.utility.optional;

import std;
import stds.exceptions;
import stds.low.manual_holder;
import stds.traits.error_policy;
import stds.utility.nothrow;
import stds.traits.operators;

#include "macro_utils.h"

export namespace stds::utility {
	using null_t = std::nullptr_t;

	/*
	 * @brief Class for working with a value that may not exist
	 * 
	 * @tparam T Value type
	 * @tparam Policy Error policy
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T, traits::error_policy_i Policy = traits::throw_policy>
	struct STDS_API optional : private Policy {
		using type = T;
	private:
		bool has = false; // has_value
		union {
			low::manual_holder<T> val; // value
			unsigned char dummy;
		};
		using nothrow = nothrow<T>;

		constexpr void throw_null_reference_error() const 
			noexcept(traits::is_policy_nothrow<Policy>)
		{
			this->on_error<exceptions::null_reference>("Reference to null value in optional");
		}
	public:
		/// @brief Null optional
		constexpr optional() noexcept { reset(); }
		/// @brief Null optional
		constexpr optional(null_t) noexcept : optional() {}

		/// @brief Construct optional of value
		constexpr optional(const type& value) 
			noexcept(nothrow::copy_constructible)
		{
			val.construct(value);
			has = true;
		}
		/// @brief Construct optional of moved value
		constexpr optional(type&& value) 
			noexcept(nothrow::move_constructible)
		{
			val.construct(std::move(value));
			has = true;
		}

		/// @brief Construct optional of another optional
		constexpr optional(const optional& other) 
			noexcept(nothrow::copy_constructible)
		{
			if (other.has) {
				val.construct(*other);
				has = true;
			}
			else has = false;
		}
		/// @brief Construct optional of another moved optional
		constexpr optional(optional&& other)
			noexcept(nothrow::move_constructible)
		{
			if (other.has) {
				val.construct(std::move(*other));
				has = true;
			}
			else has = false;
		}

		/// @brief Reset value
		constexpr ~optional()
			noexcept(nothrow::destructible)
		{
			reset();
		}

		/// @returns If value exists
		constexpr explicit operator bool() const noexcept {
			return has;
		}

		/// @brief Get value reference if it exists
		/// @returns Value reference
		constexpr type& value() &
			noexcept(traits::is_policy_nothrow<Policy>)
		{
			if (has) {
				return *val.get();
			}
			throw_null_reference_error();
		}

		/// @brief Get const value reference if it exists
		/// @returns Const value reference
		constexpr const type& value() const&
			noexcept(traits::is_policy_nothrow<Policy>)
		{
			if (has) {
				return *val.get();
			}
			throw_null_reference_error();
		}

		/// @brief Get value reference if it exists, otherwise return default_value
		/// @param default_value Default value for return
		/// @returns Value or default_value
		constexpr type value_or(const type& default_value) const& {
			return has ? *val.get() : default_value;
		}

		/// @brief Get value reference if it exists, otherwise return default_value
		/// @param default_value Default value for return
		/// @returns Value or default_value
		constexpr type value_or(type&& default_value) && {
			return has ? std::move(*val.get()) : std::move(default_value);
		}

		/// @returns If value exists
		constexpr bool has_value() const noexcept { return has; }
		
		/// @brief Emplace value
		/// @returns Value reference
		template<typename... Args>
		constexpr type& emplace(Args&&... args)
			noexcept(
				nothrow::destructible &&
				nothrow::template constructible<Args...>
				)
		{
			reset();
			val.construct(std::forward<Args>(args)...);
			has = true;
			return *val.get();
		}

		/// @brief Reset value
		/// @returns Has value been reset
		constexpr bool reset()
			noexcept(nothrow::destructible)
		{
			if (has) {
				val.destroy();
				has = false;
			}
			return !has;
		}

		/// **************************************************************** ///
		/// ========================== Operators =========================== ///
		/// **************************************************************** ///

		// =================== Assignment =================== //

		/// @brief Null assignment
		constexpr optional& operator=(null_t)
			noexcept(nothrow::destructible)
		{
			reset(); // 'has' will be false
			return *this;
		}
		/// @brief Copy-assignment from another optional
		constexpr optional& operator=(const optional& other)
			noexcept(
				nothrow::destructible&&
				nothrow::copy_constructible
				)
		{
			if (this != &other) {
				if (has) reset(); // 'has' will be false
				if (other.has) {
					val.construct(*other);
					has = true;
				}
			}
			return *this;
		}
		/// @brief Move-assignment from another optional
		constexpr optional& operator=(optional&& other)
			noexcept(
				nothrow::destructible&&
				nothrow::move_constructible
				)
		{
			if (this != &other) {
				if (has) reset(); // 'has' will be false
				if (other.has) {
					val.construct(std::move(*other));
					has = true;
				}
			}
			return *this;
		}
		/// @brief Copy-assignment from value
		constexpr optional& operator=(const type& other) {
			reset();
			val.construct(other);
			has = true;
			return *this;
		}
		/// @brief Move-assignment from value
		constexpr optional& operator=(type&& other) {
			reset();
			val.construct(std::move(other));
			has = true;
			return *this;
		}
		
		// =================== Dereferencing =================== //

		/// @brief Get mutable reference to value if exists
		/// @returns Value reference
		constexpr type& operator*()
			noexcept(traits::is_policy_nothrow<Policy>)
		{
			return value();
		}
		/// @brief Get const reference to value if exists
		/// @returns Const value reference
		constexpr const type& operator*() const
			noexcept(traits::is_policy_nothrow<Policy>)
		{
			return value();
		}

		/// @brief Get pointer to value if exists
		/// @returns Value pointer
		constexpr type* operator->()
			noexcept(traits::is_policy_nothrow<Policy>)
		{
			if (has) {
				return val.get();
			}
			throw_null_reference_error();
		}
		/// @brief Get const pointer to value if exists
		/// @returns Const value pointer
		constexpr const type* operator->() const
			noexcept(traits::is_policy_nothrow<Policy>)
		{
			if (has) {
				return val.get();
			}
			throw_null_reference_error();
		}

		// =================== Comparison operators optional<T> vs optional<T> =================== //

		/// @returns If both optionals are equal
		friend constexpr bool operator==(const optional& a, const optional& b)
			requires(traits::operators::equal_i<type>)
		{
			return (!a && !b) || (a && b && *a == *b);
		}

		/// @returns If both optionals are not equal
		friend constexpr bool operator!=(const optional& a, const optional& b)
			requires(traits::operators::not_equal_i<type> || traits::operators::equal_i<type>)
		{
			if constexpr (traits::operators::not_equal_i<type>) {
				return (!a && !b) ? false
					: (a && b) ? (*a != *b)
					: true;
			}
			else {
				return !(a == b);
			}
		}

		/// @returns If a < b
		friend constexpr bool operator<(const optional& a, const optional& b)
			requires(traits::operators::less_i<type>)
		{
			if (!b) return false;     // b empty => a>=b
			if (!a) return true;      // a empty, b non-empty => a<b
			return *a < *b;
		}

		/// @returns If a > b
		friend constexpr bool operator>(const optional& a, const optional& b)
			requires(traits::operators::greater_i<type> || traits::operators::less_i<type>)
		{
			// Use '<' if '>' not directly available
			if constexpr (traits::operators::greater_i<type>) {
				if (!a) return false;
				if (!b) return true;
				return *a > *b;
			}
			else {
				return b < a;
			}
		}

		/// @returns If a <= b
		friend constexpr bool operator<=(const optional& a, const optional& b)
			requires(
			traits::operators::less_equal_i<type> ||
			traits::operators::less_i<type> ||
			traits::operators::equal_i<type>
			)
		{
			if constexpr (traits::operators::less_equal_i<type>) {
				if (!a && !b) return true;
				if (!a) return true;
				if (!b) return false;
				return *a <= *b;
			}
			else {
				return !(b < a);
			}
		}

		/// @returns If a >= b
		friend constexpr bool operator>=(const optional& a, const optional& b)
			requires(
			traits::operators::greater_equal_i<type> ||
			traits::operators::greater_i<type> ||
			traits::operators::equal_i<type>
			)
		{
			if constexpr (traits::operators::greater_equal_i<type>) {
				if (!a && !b) return true;
				if (!b) return true;
				if (!a) return false;
				return *a >= *b;
			}
			else {
				return !(a < b);
			}
		}

		/// @brief Three-way compare optional vs optional
		/// @returns ordering: empty < non-empty, both empty equal, otherwise *a <=> *b
		friend constexpr auto operator<=>(const optional& a, const optional& b)
			requires(traits::operators::spaceship_i<type>)
		{
			if (!b && !a) return std::strong_ordering::equal;
			if (!a) return std::strong_ordering::less;
			if (!b) return std::strong_ordering::greater;
			return *a <=> *b;
		}

		// =================== Comparison operators optional<T> vs T ===================

		/// @returns If optional equals value
		friend constexpr bool operator==(const optional& a, const type& v)
			requires(traits::operators::equal_i<type>)
		{
			return a.has && *a == v;
		}

		/// @returns If optional not equals value
		friend constexpr bool operator!=(const optional& a, const type& v)
			requires(traits::operators::not_equal_i<type> || traits::operators::equal_i<type>)
		{
			if constexpr (traits::operators::not_equal_i<type>) {
				return !a.has ? true
					: (*a != v);
			}
			else {
				return !(a == v);
			}
		}

		/// @returns If optional < value
		friend constexpr bool operator<(const optional& a, const type& v)
			requires(traits::operators::less_i<type>)
		{
			if (!a) return true;      // empty < any value
			return *a < v;
		}

		/// @returns If optional > value
		friend constexpr bool operator>(const optional& a, const type& v)
			requires(traits::operators::greater_i<type> || traits::operators::less_i<type>)
		{
			if constexpr (traits::operators::greater_i<type>) {
				if (!a) return false;  // empty not > any value
				return *a > v;
			}
			else {
				return v < a;
			}
		}

		/// @returns If optional <= value
		friend constexpr bool operator<=(const optional& a, const type& v)
			requires(
			traits::operators::less_equal_i<type> ||
			traits::operators::less_i<type> ||
			traits::operators::equal_i<type>
			)
		{
			if (!a) return true;      // empty <= any
			if constexpr (traits::operators::less_equal_i<type>) {
				return *a <= v;
			}
			else {
				return !(v < a);
			}
		}

		/// @returns If optional >= value
		friend constexpr bool operator>=(const optional& a, const type& v)
			requires(
		traits::operators::greater_equal_i<type> ||
			traits::operators::greater_i<type> ||
			traits::operators::equal_i<type>
			)
		{
			if (!a) return false;     // empty not >= any (except if compare to default? but follow std: empty < any)
			if constexpr (traits::operators::greater_equal_i<type>) {
				return *a >= v;
			}
			else {
				return !(a < v);
			}
		}

		/// @brief Three-way compare optional vs value
		/// @returns ordering: empty < value, otherwise *a <=> v
		friend constexpr auto operator<=>(const optional& a, const type& v)
			requires(traits::operators::spaceship_i<type>)
		{
			if (!a) return std::strong_ordering::less;
			return *a <=> v;
		}

		// =================== Comparison operators T vs optional<T> ===================

		/// @returns If value equals optional
		friend constexpr bool operator==(const type& v, const optional& a)
			requires(traits::operators::equal_i<type>)
		{
			return a.has && v == *a;
		}

		/// @returns If value not equals optional
		friend constexpr bool operator!=(const type& v, const optional& a)
			requires(traits::operators::not_equal_i<type> || traits::operators::equal_i<type>)
		{
			if constexpr (traits::operators::not_equal_i<type>) {
				return !a.has ? true
					: (v != *a);
			}
			else {
				return !(v == a);
			}
		}

		/// @returns If value < optional
		friend constexpr bool operator<(const type& v, const optional& a)
			requires(traits::operators::less_i<type>)
		{
			if (!a) return false;     // any value not < empty
			return v < *a;
		}

		/// @returns If value > optional
		friend constexpr bool operator>(const type& v, const optional& a)
			requires(traits::operators::greater_i<type> || traits::operators::less_i<type>)
		{
			if constexpr (traits::operators::greater_i<type>) {
				if (!a) return true;   // any value > empty
				return v > *a;
			}
			else {
				return a < v;
			}
		}

		/// @returns If value <= optional
		friend constexpr bool operator<=(const type& v, const optional& a)
			requires(
			traits::operators::less_equal_i<type> ||
			traits::operators::less_i<type> ||
			traits::operators::equal_i<type>
			)
		{
			if (!a) return false;
			if constexpr (traits::operators::less_equal_i<type>) {
				return v <= *a;
			}
			else {
				return !(*a < v);
			}
		}

		/// @returns If value >= optional
		friend constexpr bool operator>=(const type& v, const optional& a)
			requires(
			traits::operators::greater_equal_i<type> ||
			traits::operators::greater_i<type> ||
			traits::operators::equal_i<type>
			)
		{
			if (!a) return true;      // any >= empty
			if constexpr (traits::operators::greater_equal_i<type>) {
				return v >= *a;
			}
			else {
				return !(v < *a);
			}
		}

		/// @brief Three-way compare value vs optional
		/// @returns ordering: value > empty, otherwise v <=> *a
		friend constexpr auto operator<=>(const type& v, const optional& a)
			requires(traits::operators::spaceship_i<type>)
		{
			if (!a) return std::strong_ordering::greater;
			return v <=> *a;
		}
	};

	static_assert(traits::operators::compare_i<stds::utility::optional<int, traits::throw_policy>>, "stds error:" _stringof(optional) "does not match for " _stringof(compare_i));

	/// @brief Null value
	/// 
	/// Usage example:
	/// @code
	/// optional<int> value = null;
	/// @endcode
	inline constexpr null_t null = nullptr;
}