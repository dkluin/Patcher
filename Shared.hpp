#pragma once

/*
	TODO: 

	- define all macroes tied to Patcher here and not in UG's Shared.hpp...
*/

#ifndef _M_IX86
#error Patcher only supports x86.
#endif

// Useful macroes
#define X86_PUSHAD _asm pushad
#define X86_POPAD _asm popad