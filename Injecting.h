#pragma once

#include "Main.h"

enum eInjectorError
{
	INJECTOR_ERROR_NONE = 0,
	INJECTOR_ERROR_INVALID_MEMORY_PTR,
	INJECTOR_ERROR_UNKNOWN
};

class MemoryInjector
{
public:
	// Makes a JMP to a relative address or function
	static uint32_t MakeJMP(Memory* mem, uint32_t dest, bool bProtect);
	static uint32_t MakeJMP(Memory* mem, void* dest, bool bProtect);
	static uint32_t MakeJMP(uint32_t mem, uint32_t dest, bool bProtect);
	static uint32_t MakeJMP(uint32_t mem, void* dest, bool bProtect);

	// Makes a CALL to a relative address or function
	static uint32_t MakeCALL(Memory* mem, uint32_t dest, bool bProtect);
	static uint32_t MakeCALL(Memory* mem, void* dest, bool bProtect);
	static uint32_t MakeCALL(uint32_t mem, uint32_t dest, bool bProtect);
	static uint32_t MakeCALL(uint32_t mem, void* dest, bool bProtect);

	// Get last error
	static eInjectorError GetLastError();

private:
	// Gets a relative address
	static uint32_t GetRelativeAddress(uint32_t src, uint32_t dest);

	// Error
	static eInjectorError InjectorError;
};