#pragma once

#include <cstdint>

class Calling
{
public:
	// Default calling convention
	template<class Ret, class ...Args>
	static Ret Call(uint32_t p, Args... a);

	// __thiscall
	template<class Ret, class ...Args>
	static Ret ThisCall(uint32_t p, Args... a);

	// __stdcall
	template<class Ret, class ...Args>
	static Ret StdCall(uint32_t p, Args... a);

	// __cdecl
	template<class Ret, class ...Args>
	static Ret CDecl(uint32_t p, Args... a);

	// __fastcall
	template<class Ret, class ...Args>
	static Ret FastCall(uint32_t p, Args... a);

	// __vectorcall
	template<class Ret, class ...Args>
	static Ret VectorCall(uint32_t p, Args... a);
};