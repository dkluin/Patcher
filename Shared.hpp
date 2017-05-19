#pragma once

#include <Windows.h>
#include <stdio.h>

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

// Prints message box and also stores a new line inside log file
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