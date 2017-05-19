#pragma once

#include <cstdint>

/*
	TODO:
	- allow Memory class to be used?
	- Vtable?
*/

class Calling
{
public:
	// Standard function calling
	template<class Ret, class ...Args>
	static inline Ret Call(uint32_t p, Args... a)
	{
		auto fn = (Ret(*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}

	// ThisCall
	template<class Ret, class ...Args>
	static inline Ret ThisCall(uint32_t p, Args... a)
	{
		auto fn = (Ret(__thiscall*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}

	// __stdcall
	template<class Ret, class ...Args>
	static inline Ret StdCall(uint32_t p, Args... a)
	{
		auto fn = (Ret(__stdcall*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}

	// __cdecl
	template<class Ret, class ...Args>
	static inline Ret CDecl(uint32_t p, Args... a)
	{
		auto fn = (Ret(__cdecl*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}

	// __fastcall
	template<class Ret, class ...Args>
	static inline Ret FastCall(uint32_t p, Args... a)
	{
		auto fn = (Ret(__fastcall*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}

	// __vectorcall
	template<class Ret, class ...Args>
	static inline Ret VectorCall(uint32_t p, Args... a)
	{
		auto fn = (Ret(__vectorcall*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}
};