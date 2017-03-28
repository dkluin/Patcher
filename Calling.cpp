#include "Calling.h"

namespace Patcher
{
	// Standard function calling
	template<class Ret, class ...Args>
	Ret Calling::Call(uint32_t p, Args... a)
	{
		auto fn = (Ret(*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}

	// ThisCall
	template<class Ret, class ...Args>
	Ret Calling::ThisCall(uint32_t p, Args... a)
	{
		auto fn = (Ret(__thiscall*)(Args...)) p;
		return fn(std::forward<Args>(a)...);
	}
}