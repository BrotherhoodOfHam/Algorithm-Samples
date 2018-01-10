/*
	Assertion helper
*/

#include "assert.h"

#include <stdio.h>

#ifdef WIN32
#include <Windows.h>
#define INVOKE_DEBUGGER DebugBreak 
#else
#define INVOKE_DEBUGGER()
#endif

void _assert(bool result, const char* expr, const char* msg, const char* file, int line)
{
	if (!result)
	{
		fprintf(stderr, "ERROR: %s\nexpression = \"%s\"\nfile = %s\nline = %d", msg, expr, file, line);

		INVOKE_DEBUGGER();

		exit(EXIT_FAILURE);
	}
}
