/*
	Common header include in all source files
*/

#pragma once

#include <stdlib.h>

#ifdef WIN32

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

inline void init_debug()
{
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
}

#else
inline void init_debug()
{
	//stub
}
#endif // WIN32
