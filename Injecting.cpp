#include "Injecting.h"
#include "General.h"


eInjectorError MemoryInjector::InjectorError = INJECTOR_ERROR_NONE;

// Gets injector error
eInjectorError MemoryInjector::GetLastError()
{
	return InjectorError;
}

// Gets a relative addresss
uint32_t MemoryInjector::GetRelativeAddress(uint32_t src, uint32_t dest)
{
	return dest - src;
}

// Makes a JMP to a relative address or function
uint32_t MemoryInjector::MakeJMP(Memory* mem, uint32_t dest, bool bProtect)
{
	if (mem == nullptr)
	{
		InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
		return 0;
	}
	mem->Set<BYTE>(0xE9, bProtect);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), dest - 5), bProtect);
	return GetRelativeAddress(mem->GetAddress(), dest - 5);
}

uint32_t MemoryInjector::MakeJMP(Memory* mem, void* dest, bool bProtect)
{
	if (mem == nullptr)
	{
		InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
		return 0;
	}
	mem->Set<BYTE>(0xE9, bProtect);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), (uint32_t)dest - 5), bProtect);
	return GetRelativeAddress(mem->GetAddress(), (uint32_t)dest - 5);
}

uint32_t MemoryInjector::MakeJMP(uint32_t mem, uint32_t dest, bool bProtect)
{
	Memory jmp(mem);
	jmp.Set<BYTE>(0xE9, bProtect);
	jmp.ChangeAddress(jmp.GetAddress() + 1);
	jmp.Set<uint32_t>(GetRelativeAddress(mem, (uint32_t)dest - 5), bProtect);
	return GetRelativeAddress(mem, (uint32_t)dest - 5);
}

uint32_t MemoryInjector::MakeJMP(uint32_t mem, void* dest, bool bProtect)
{
	Memory jmp(mem);
	jmp.Set<BYTE>(0xE9, bProtect);
	jmp.ChangeAddress(jmp.GetAddress() + 1);
	jmp.Set<uint32_t>(GetRelativeAddress(mem, (uint32_t)dest - 5), bProtect);
	return GetRelativeAddress(mem, (uint32_t)dest - 5);
}

template <class T>
T MemoryInjector::ReadMemory(uint32_t address, bool bProtect)
{
	T result;
	General::MemCpyWithMemoryProtect(result, address, sizeof(T));
	return result;
}

template <class T>
void MemoryInjector::WriteMemory(uint32_t address, T value, bool bProtect)
{
	General::MemCpyWithMemoryProtect(address, value, sizeof(T));
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