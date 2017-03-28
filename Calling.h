#pragma once

#include <cstdint>


class Calling
{
public:
	template<class Ret, class ...Args>
	static Ret Call(uint32_t p, Args... a);

	template<class Ret, class ...Args>
	static Ret ThisCall(uint32_t p, Args... a);
};