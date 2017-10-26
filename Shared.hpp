#pragma once

#include <Windows.h>
#include <stdio.h>

#define PATCHER_VERSION 20
#define PATCHER_VERSION_STRING "2.0"

#ifndef _M_IX86
#error Patcher only supports x86.
#endif

// Pushad/popad macro (not really useful but still)
#ifndef X86_PUSHAD
#define X86_PUSHAD _asm pushad
#endif
#ifndef X86_POPAD
#define X86_POPAD _asm popad
#endif

// Naked/nude/patch macro stuff
#ifndef NAKED
#define NAKED __declspec(naked)
#endif
#ifndef PATCH
#define PATCH __declspec(naked)
#endif
#ifndef NUDE
#define NUDE __declspec(naked)
#endif

//
//	ASM EPILOG and ASM PROLOG macros
//
#define ASM_PROLOG() _asm					\
	{										\
		_asm push	ebp						\
		_asm mov	ebp, esp				\
		_asm sub	esp, __LOCAL_SIZE		\
	}

#define ASM_EPILOG() _asm					\
	{										\
		_asm mov	esp, ebp				\
		_asm pop	ebp						\
	}

// Prints message box (just a wrapper around MessageBoxA to make it like printf
static void PatcherPrintMessageBox(const char* message, ...)
{
	va_list vl;
	va_start(vl, message);

	char buffer[10000];

	_vsnprintf_s(buffer, _countof(buffer), _countof(buffer) - 1, message, vl);

	SetForegroundWindow(GetDesktopWindow());
	ShowCursor(true);

	MessageBoxA(NULL, buffer, "GTA: Underground", MB_OK);

	va_end(vl);
}