/*
	Assertion helper
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>

/*
	Assertion helper
*/

void _assert(bool result, const char* expr, const char* msg, const char* file, int line);

#ifdef _DEBUG

#define assert(expr) assertm(expr, "Assertion failure")

#define assertm(expr, msg) _assert((expr) != 0, #expr, msg, __FILE__, __LINE__)

#else

#define assert(expr)

#define assertm(expr, msg)

#endif