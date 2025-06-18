/*****************************************************************//**
 * @file   stds.low.manual_holder.ixx
 * @brief  TODO
 * 
 * @date   17-6-2025
 *********************************************************************/

export module stds.low.manual_holder;

import std;
import stds.traits.error_policy;
import stds.utility.nothrow;

#include "macro_utils.h"

export namespace stds::low {

	/**
	 * TODO
	 */
	template<class T>
	struct manual_holder {
	private:
		using nothrow = utility::nothrow<T>;
	public:
		alignas(T) std::byte buffer[sizeof(T)];

		template<typename... Args>
		constexpr T* construct(Args&&... args) 
			noexcept(nothrow::template constructible<Args...>)
		{
			return std::construct_at(get(), std::forward<Args>(args)...);
		}

		constexpr void destroy() 
			noexcept(nothrow::destructible) 
		{
			std::destroy_at(get());
		}

		constexpr T* get() noexcept {
			return std::launder(reinterpret_cast<T*>(buffer));
		}

		constexpr const T* get() const noexcept {
			return std::launder(reinterpret_cast<const T*>(buffer));
		}
	};

	/**
	 * TODO
	 */
	template<class T, traits::error_policy_i Policy = traits::throw_policy>
	struct manual_holder_with_policy {
	private:
		using nothrow = utility::nothrow<T>;
		bool constructed = false;
	public:
		alignas(T) std::byte buffer[sizeof(T)];

		constexpr bool is_constructed() const noexcept { return constructed; }

		template<typename... Args>
		constexpr T* construct(Args&&... args)
			noexcept(
				nothrow::template constructible<Args...> &&
				traits::is_policy_nothrow<Policy>
				)
		{
			traits::error_if<Policy>(constructed, "manual_holder has already constructed");
			constructed = true;
			return std::construct_at(get(), std::forward<Args>(args)...);
		}

		constexpr void destroy()
			noexcept(
				nothrow::destructible &&
				traits::is_policy_nothrow<Policy>
				)
		{
			traits::error_if<Policy>(!constructed, "manual_holder was not constructed");
			std::destroy_at(get());
		}

		constexpr T* get() noexcept {
			return std::launder(reinterpret_cast<T*>(buffer));
		}

		constexpr const T* get() const noexcept {
			return std::launder(reinterpret_cast<const T*>(buffer));
		}
	};
}
