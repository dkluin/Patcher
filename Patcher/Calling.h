#pragma once

#include <cstdint>

/*
	Credits:
	-iFarbod
*/

#include "Memory.h"

class Calling
{
public:
	// Standard function calling
	template<class Ret, class ...Args>
	static inline Ret Call(uint32_t address, Args... args)
	{
		auto fn = (Ret(*)(Args...)) address;
		return fn(std::forward<Args>(args)...);
	}

	// Same, but uses Memory
	template <class Ret, class ...Args>
	static inline Ret Call(Memory* address, Args... args)
	{
		auto fn = (Ret(*)(Args...)) address->GetAddress();
		return fn(std::forward<Args>(args)...);
	}

	// ThisCall
	template<class Ret, class ...Args>
	static inline Ret ThisCall(uint32_t address, Args... args)
	{
		auto fn = (Ret(__thiscall*)(Args...)) address;
		return fn(std::forward<Args>(args)...);
	}

	// Memory alternative
	template <class Ret, class ...Args>
	static inline Ret ThisCall(Memory* address, Args... args)
	{
		auto fn = (Ret(__thiscall*)(Args...)) address->GetAddress();
		return fn(std::forward<Args>(args)...);
	}


	// __stdcall
	template<class Ret, class ...Args>
	static inline Ret StdCall(uint32_t address, Args... args)
	{
		auto fn = (Ret(__stdcall*)(Args...)) address;
		return fn(std::forward<Args>(args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret StdCall(Memory* address, Args... args)
	{
		auto fn = (Ret(__stdcall*)(Args...)) address->GetAddress();
		return fn(std::forward<Args>(args)...);
	}

	// __cdecl
	template<class Ret, class ...Args>
	static inline Ret CDecl(uint32_t address, Args... args)
	{
		auto fn = (Ret(__cdecl*)(Args...)) address;
		return fn(std::forward<Args>(args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret CDecl(Memory* address, Args... args)
	{
		auto fn = (Ret(__cdecl*)(Args...)) address->GetAddress();
		return fn(std::forward<Args>(args)...);
	}

	// __fastcall
	template<class Ret, class ...Args>
	static inline Ret FastCall(uint32_t address, Args... args)
	{
		auto fn = (Ret(__fastcall*)(Args...)) address;
		return fn(std::forward<Args>(args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret FastCall(Memory* address, Args... args)
	{
		auto fn = (Ret(__fastcall*)(Args...)) address->GetAddress();
		return fn(std::forward<Args>(args)...);
	}

	// __vectorcall
	template<class Ret, class ...Args>
	static inline Ret VectorCall(uint32_t address, Args... args)
	{
		auto fn = (Ret(__vectorcall*)(Args...)) address;
		return fn(std::forward<Args>(args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret VectorCall(Memory* address, Args... args)
	{
		auto fn = (Ret(__vectorcall*)(Args...)) address->GetAddress();
		return fn(std::forward<Args>(args)...);
	}

};