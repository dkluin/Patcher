#include "Injecting.hpp"

namespace Memory
{
	// Gets a relative addresss
	Memory* MemoryInjector::GetRelativeAddress(Memory* src, Memory* dest) 
	{

	}

	uint32_t MemoryInjector::GetRelativeAddress(uint32_t src, uint32_t dest)
	{

	}

	// Makes a JMP to a relative address or function
	void MemoryInjector::MakeJMP(Memory* mem, uint32_t dest, bool bProtect)
	{

	}

	void MemoryInjector::MakeJMP(Memory* mem, void* dest, bool bProtect)
	{

	}

	void MemoryInjector::MakeJMP(uint32_t mem, uint32_t dest, bool bProtect)
	{

	}

	void MemoryInjector::MakeJMP(uint32_t mem, void* dest, bool bProtect)
	{

	}

	// Makes a CALL to a relative address or function
	void MemoryInjector::MakeCALL(Memory* mem, uint32_t dest, bool bProtect)
	{

	}

	void MemoryInjector::MakeCALL(Memory* mem, uint32_t dest, bool bProtect)
	{

	}

	void MemoryInjector::MakeCALL(uint32_t mem, uint32_t dest, bool bProtect)
	{

	}

	void MemoryInjector::MakeCALL(uint32_t mem, void* dest, bool bProtect)
	{

	}
}