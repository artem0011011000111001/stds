/*****************************************************************//**
 * @file   stds.low.manual_holder.ixx
 * @brief  TODO
 * 
 * @date   17-6-2025
 *********************************************************************/

export module stds.low.manual_holder;

import std;
import stds.traits.error;
import stds.utility.nothrow;

#include "macro_utils.h"

export namespace stds::low {

	/**
	 * TODO
	 */
	template<class T>
	struct manual_holder {
		using type = T;
	private:
		using nothrow = utility::nothrow<type>;
	public:
		alignas(type) std::byte buffer[sizeof(type)];

		template<typename... Args>
		constexpr type* construct(Args&&... args)
			noexcept(nothrow::template constructible<Args...>)
		{
			return std::construct_at(get(), std::forward<Args>(args)...);
		}

		constexpr void destroy() 
			noexcept(nothrow::destructible) 
		{
			std::destroy_at(get());
		}

		constexpr type* get() noexcept {
			return std::launder(reinterpret_cast<type*>(buffer));
		}

		constexpr const type* get() const noexcept {
			return std::launder(reinterpret_cast<const type*>(buffer));
		}
	};

	/**
	 * TODO
	 */
	template<class T, traits::error_policy_i Policy = traits::throw_policy>
	struct manual_holder_with_policy {
		using type = T;
	private:
		using nothrow = utility::nothrow<type>;
		bool constructed = false;
	public:
		alignas(type) std::byte buffer[sizeof(type)];

		constexpr bool is_constructed() const noexcept { return constructed; }

		template<typename... Args>
		constexpr type* construct(Args&&... args)
			noexcept(
				nothrow::template constructible<Args...> &&
				traits::is_policy_nothrow_v<Policy>
				)
		{
			traits::make_error_if<Policy>(constructed, "manual_holder has already constructed");
			constructed = true;
			return std::construct_at(get(), std::forward<Args>(args)...);
		}

		constexpr void destroy()
			noexcept(
				nothrow::destructible &&
				traits::is_policy_nothrow_v<Policy>
				)
		{
			traits::make_error_if<Policy>(!constructed, "manual_holder was not constructed");
			std::destroy_at(get());
		}

		constexpr type* get() noexcept {
			return std::launder(reinterpret_cast<type*>(buffer));
		}

		constexpr const type* get() const noexcept {
			return std::launder(reinterpret_cast<const type*>(buffer));
		}
	};
}
