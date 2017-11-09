/*
	Variant type header

	A variant type can encapsulate any primitive type or pointer
*/

#pragma once

#include "common.h"

#include <stdint.h>

typedef uint64_t variant_t;

/*
	Variant equality delegate
*/
typedef bool(*variant_eq_f)(variant_t, variant_t);

/*
	Variant comparator delegate
*/
typedef int32_t(*variant_comp_f)(variant_t, variant_t);

/*
	Cast a variant up to a given type
*/
#define V_CAST(type, var) (*(const type*)(&var))

/*
	Cast a type down to a variant
*/
#define D_CAST(val) (*(const variant_t*)(&val))
