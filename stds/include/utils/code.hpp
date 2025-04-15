#pragma once

#ifndef _STDS_CODE_
#define _STDS_CODE_

#include "config/types.hpp"

STDS_START

struct code {
	HSTDS_::i16 value = 0;
	code(HSTDS_::i16 code_value) : value(code_value) {}

	static code good;				// code 0
	static code invalid_allocate;	// code 1
	static code out_of_bounds;		// code 2
	static code reference_to_null;	// code 3
	static code zero_allocation;	// code 4
};

code code::good{ 0 };
code code::invalid_allocate{ 1 };
code code::out_of_bounds{ 2 };
code code::reference_to_null{ 3 };
code code::zero_allocation{ 4 };

STDS_END

#endif // _STDS_CODE_