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
	static inline Ret Call(uint32_t m_Address, Args... m_Args)
	{
		auto fn = (Ret(*)(Args...)) m_Address;
		return fn(std::forward<Args>(m_Args)...);
	}

	// Same, but uses Memory
	template <class Ret, class ...Args>
	static inline Ret Call(Memory* m_pAddress, Args... m_Args)
	{
		auto fn = (Ret(*)(Args...)) m_pAddress->GetAddress();
		return fn(std::forward<Args>(m_Args)...);
	}

	// ThisCall
	template<class Ret, class ...Args>
	static inline Ret ThisCall(uint32_t m_Address, Args... m_Args)
	{
		auto fn = (Ret(__thiscall*)(Args...)) m_Address;
		return fn(std::forward<Args>(m_Args)...);
	}

	// Memory alternative
	template <class Ret, class ...Args>
	static inline Ret ThisCall(Memory* m_pAddress, Args... m_Args)
	{
		auto fn = (Ret(__thiscall*)(Args...)) m_pAddress->GetAddress();
		return fn(std::forward<Args>(m_Args)...);
	}


	// __stdcall
	template<class Ret, class ...Args>
	static inline Ret StdCall(uint32_t m_Address, Args... m_Args)
	{
		auto fn = (Ret(__stdcall*)(Args...)) m_Address;
		return fn(std::forward<Args>(m_Args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret StdCall(Memory* m_pAddress, Args... m_Args)
	{
		auto fn = (Ret(__stdcall*)(Args...)) m_pAddress->GetAddress();
		return fn(std::forward<Args>(m_Args)...);
	}

	// __cdecl
	template<class Ret, class ...Args>
	static inline Ret CDecl(uint32_t m_Address, Args... m_Args)
	{
		auto fn = (Ret(__cdecl*)(Args...)) m_Address;
		return fn(std::forward<Args>(m_Args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret CDecl(Memory* m_pAddress, Args... m_Args)
	{
		auto fn = (Ret(__cdecl*)(Args...)) m_pAddress->GetAddress();
		return fn(std::forward<Args>(m_Args)...);
	}

	// __fastcall
	template<class Ret, class ...Args>
	static inline Ret FastCall(uint32_t m_Address, Args... m_Args)
	{
		auto fn = (Ret(__fastcall*)(Args...)) m_Address;
		return fn(std::forward<Args>(m_Args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret FastCall(Memory* m_pAddress, Args... m_Args)
	{
		auto fn = (Ret(__fastcall*)(Args...)) m_pAddress->GetAddress();
		return fn(std::forward<Args>(m_Args)...);
	}

	// __vectorcall
	template<class Ret, class ...Args>
	static inline Ret VectorCall(uint32_t m_Address, Args... m_Args)
	{
		auto fn = (Ret(__vectorcall*)(Args...)) m_Address;
		return fn(std::forward<Args>(m_Args)...);
	}

	template <class Ret, class ...Args>
	static inline Ret VectorCall(Memory* m_pAddress, Args... m_Args)
	{
		auto fn = (Ret(__vectorcall*)(Args...)) m_pAddress->GetAddress();
		return fn(std::forward<Args>(m_Args)...);
	}
};