#include "Injecting.h"

namespace Patcher
{
	eInjectorError MemoryInjector::InjectorError = INJECTOR_ERROR_NONE;

	// Gets injector error
	eInjectorError MemoryInjector::GetLastError()
	{
		return InjectorError;
	}

	// Gets a relative addresss
	uint32_t MemoryInjector::GetRelativeAddress(uint32_t src, uint32_t dest)
	{

	}

	// Makes a JMP to a relative address or function
	uint32_t MemoryInjector::MakeJMP(Memory* mem, uint32_t dest, bool bProtect)
	{
		if (mem == nullptr)
		{
			InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
			return 0;
		}
	}

	uint32_t MemoryInjector::MakeJMP(Memory* mem, void* dest, bool bProtect)
	{
		if (mem == nullptr)
		{
			InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
			return 0;
		}
	}

	uint32_t MemoryInjector::MakeJMP(uint32_t mem, uint32_t dest, bool bProtect)
	{

	}

	uint32_t MemoryInjector::MakeJMP(uint32_t mem, void* dest, bool bProtect)
	{

	}

	// Makes a CALL to a relative address or function
	uint32_t MemoryInjector::MakeCALL(Memory* mem, uint32_t dest, bool bProtect)
	{
		if (mem == nullptr)
		{
			InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
			return 0;
		}
	}

	uint32_t MemoryInjector::MakeCALL(Memory* mem, void* dest, bool bProtect)
	{
		if (mem == nullptr)
		{
			InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
			return 0;
		}
	}

	uint32_t MemoryInjector::MakeCALL(uint32_t mem, uint32_t dest, bool bProtect)
	{

	}

	uint32_t MemoryInjector::MakeCALL(uint32_t mem, void* dest, bool bProtect)
	{

	}
}