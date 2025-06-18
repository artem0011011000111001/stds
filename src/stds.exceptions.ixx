/*****************************************************************//**
 * @file   stds.exceptions.ixx
 * @brief  TODO
 * 
 * @date   18-6-2025
 *********************************************************************/

#pragma warning(disable : 4275)

export module stds.exceptions;

import std;

#include "macro_utils.h"

export namespace stds::exceptions {

	struct STDS_API null_reference : std::runtime_error {
		using base = runtime_error;

		null_reference(std::string message) : base(message) {}
		null_reference(const null_reference& other) : base(other) {}
	};
}
