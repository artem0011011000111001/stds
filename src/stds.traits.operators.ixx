/*****************************************************************//**
 * @file   stds.traits.operators.ixx
 * @brief  TODO
 * 
 * @date   18-6-2025
 *********************************************************************/

export module stds.traits.operators;

import std;

export namespace stds::traits::operators {

	// =================== Arithmetic Operators ===================

	/// @brief Check if T has operator l + r
	template<class T> concept add_i =		 requires(T l, T r) { { l + r } -> std::same_as<T>; };
	/// @brief Check if T has operator l - r
	template<class T> concept subtract_i =	 requires(T l, T r) { { l - r } -> std::same_as<T>; };
	/// @brief Check if T has operator l * r
	template<class T> concept multiply_i =	 requires(T l, T r) { { l * r } -> std::same_as<T>; };
	/// @brief Check if T has operator l / r
	template<class T> concept divide_i =	 requires(T l, T r) { { l / r } -> std::same_as<T>; };
	/// @brief Check if T has operator l % r
	template<class T> concept modulo_i =	 requires(T l, T r) { { l % r } -> std::same_as<T>; };
	/// @brief Check if T has operators l + r; l - r; l * r; l / r
	template<class T> concept arithmetic_i = add_i<T> && subtract_i<T> && multiply_i<T> && divide_i<T>;;

	// =================== Assignment Operators ===================

	/// @brief Check if T has operator l = r
	template<class T> concept assign_i =		  requires(T l, T r) { { l = r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l += r
	template<class T> concept add_assign_i =	  requires(T l, T r) { { l += r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l -= r
	template<class T> concept subtract_assign_i = requires(T l, T r) { { l -= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l *= r
	template<class T> concept multiply_assign_i = requires(T l, T r) { { l *= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l /= r
	template<class T> concept divide_assign_i =	  requires(T l, T r) { { l /= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l %= r
	template<class T> concept modulo_assign_i =   requires(T l, T r) { { l %= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l &= r
	template<class T> concept and_assign_i =	  requires(T l, T r) { { l &= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l |= r
	template<class T> concept or_assign_i =		  requires(T l, T r) { { l |= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l ^= r
	template<class T> concept xor_assign_i =	  requires(T l, T r) { { l ^= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l <<= r
	template<class T> concept shl_assign_i =	  requires(T l, T r) { { l <<= r } -> std::same_as<T&>; };
	/// @brief Check if T has operator l >>= r
	template<class T> concept shr_assign_i =	  requires(T l, T r) { { l >>= r } -> std::same_as<T&>; };


	// =================== Comparison Operators ===================

	/// @brief Check if T has operator l == r
	template<class T> concept equal_i =			requires(T l, T r) { { l == r } -> std::same_as<bool>; };
	/// @brief Check if T has operator l != r
	template<class T> concept not_equal_i =		requires(T l, T r) { { l != r } -> std::same_as<bool>; };
	/// @brief Check if T has operator l < r
	template<class T> concept less_i =			requires(T l, T r) { { l < r } -> std::same_as<bool>; };
	/// @brief Check if T has operator l > r
	template<class T> concept greater_i =		requires(T l, T r) { { l > r } -> std::same_as<bool>; };
	/// @brief Check if T has operator l <= r
	template<class T> concept less_equal_i =	requires(T l, T r) { { l <= r } -> std::same_as<bool>; };
	/// @brief Check if T has operator l >= r
	template<class T> concept greater_equal_i = requires(T l, T r) { { l >= r } -> std::same_as<bool>; };
	/// @brief Check if T has operator l <=> r
	template<class T> concept spaceship_i =		requires(T l, T r) { { l <=> r }; };
	/// @brief Check if T has operators l == r; l != r; l < r; l > r; l <= r; l >= r;
	template<class T> concept compare_i =		equal_i<T> && not_equal_i<T> && less_i<T> && greater_i<T> && less_equal_i<T> && greater_equal_i<T>;

	// =================== Increment/Decrement ===================

	/// @brief Check if T has operator ++x
	template<class T> concept pre_increment_i =  requires(T x) { { ++x } -> std::same_as<T&>; };
	/// @brief Check if T has operator --x
	template<class T> concept pre_decrement_i =  requires(T x) { { --x } -> std::same_as<T&>; };
	/// @brief Check if T has operator x++
	template<class T> concept post_increment_i = requires(T x) { { x++ } -> std::same_as<T>; };
	/// @brief Check if T has operator x--
	template<class T> concept post_decrement_i = requires(T x) { { x-- } -> std::same_as<T>; };


	// =================== Logical ===================

	/// @brief Check if T has operator !x
	template<class T> concept not_i = requires(T x) { { !x } -> std::same_as<bool>; };


	// =================== Bitwise ===================

	/// @brief Check if T has operator ~x
	template<class T> concept bitnot_i = requires(T x) { { ~x } -> std::same_as<T>; };
	/// @brief Check if T has operator l & r
	template<class T> concept bitand_i = requires(T l, T r) { { l & r } -> std::same_as<T>; };
	/// @brief Check if T has operator l | r
	template<class T> concept bitor_i =  requires(T l, T r) { { l | r } -> std::same_as<T>; };
	/// @brief Check if T has operator l ^ r
	template<class T> concept bitxor_i = requires(T l, T r) { { l ^ r } -> std::same_as<T>; };
	/// @brief Check if T has operator l << r
	template<class T> concept shl_i =	 requires(T l, T r) { { l << r } -> std::same_as<T>; };
	/// @brief Check if T has operator l >> r
	template<class T> concept shr_i =	 requires(T l, T r) { { l >> r } -> std::same_as<T>; };


	// =================== Access ===================

	/// @brief Check if T has operator x[i]
	template<class T, class I> concept subscript_i =				 requires(T x, I i) { { x[i] }; };
	/// @brief Check if T has operator x(args)
	template<class T, class ReturnT, class... Args> concept call_i = requires(T x, Args&&... args) { { x(std::forward<Args>(args)...) } -> std::same_as<ReturnT>; };
	/// @brief Check if T has operator x->member
	template<class T> concept arrow_i =								 requires(T x) { x.operator->(); };
	/// @brief Check if T has operator x->*p
	template<class T, class P> concept arrow_star_i =				 requires(T t, P p) { { t->*p }; };


	// =================== Casts ===================

	/// @brief Check if T can be cast to U using static_cast
	template<class T, class U> concept static_cast_i =  requires(T t) { { static_cast<U>(t) } -> std::same_as<U>; };
	/// @brief Check if T can be cast to U using dynamic_cast
	template<class T, class U> concept dynamic_cast_i = std::is_polymorphic_v<std::remove_reference_t<T>> && requires(T& t) { { dynamic_cast<U>(&t) } -> std::same_as<U>; };
	/// @brief Check if T can be cast to U using C-style cast (U)(t)
	template<class T, class U> concept c_cast_i =		requires(T t) { { (U)(t) } -> std::same_as<U>; };
}