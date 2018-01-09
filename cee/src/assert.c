/*
	Assertion helper
*/

#include "assert.h"

#include <stdio.h>

#ifdef WIN32
#include <Windows.h>
#define invoke_debugger DebugBreak 
#else
#define invoke_debugger()
#endif

void _assert(bool result, const char* expr, const char* msg, const char* file, int line)
{
	if (!result)
	{
		fprintf(stderr, "ERROR: \"%s\"\n%s\nfile = %s\nline = %d", expr, msg, file, line);

		invoke_debugger();

		exit(EXIT_FAILURE);
	}
}
