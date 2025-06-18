/*****************************************************************//**
 * @file   stds.params.opt.ixx
 * @brief  opt and opt_out function parameters
 * 
 * @date   10-6-2025
 *********************************************************************/

export module stds.params.opt;

import std;
import stds.utility;

export namespace stds::params {
	/*
	 * @brief Optional non-changeable function parameter
	 *
	 * @tparam T Parameter type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T> using opt = utility::optional<T>;/*
	 * @brief Optional changeable function parameter
	 *
	 * @tparam T Parameter type
	 * 
	 * Usage example:
	 * TODOEXAMPLE
	 */
	template<class T> using opt_out = opt<std::reference_wrapper<T>>;
}