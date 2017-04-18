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

void MemoryInjector::MakeNOP(Memory* mem, uint32_t m_dwSize, bool bProtect)
{
	uint8_t m_dwNop = 0x90;
	General::MemCpyWithMemoryProtect(mem->GetAddress(), &m_dwNop, m_dwSize);
}

void MemoryInjector::MakeNOP(uint32_t mem, uint32_t m_dwSize, bool bProtect)
{
	uint8_t m_dwNop = 0x90;
	General::MemCpyWithMemoryProtect(mem, &m_dwNop, m_dwSize);
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
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), dest - 4), bProtect);
	return GetRelativeAddress(mem->GetAddress(), dest - 4);
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
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), (uint32_t)dest - 4), bProtect);
	return GetRelativeAddress(mem->GetAddress(), (uint32_t)dest - 4);
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

uint32_t MemoryInjector::MakeJMP(HMODULE mem, uint32_t dest, bool bProtect)
{
	Memory jmp((uint32_t)mem);
	jmp.Set<BYTE>(0xE9, bProtect);
	jmp.ChangeAddress(jmp.GetAddress() + 1);
	jmp.Set<uint32_t>(GetRelativeAddress((uint32_t)mem, (uint32_t)dest - 5), bProtect);
	return GetRelativeAddress((uint32_t)mem, (uint32_t)dest - 5);
}

uint32_t MemoryInjector::MakeJMP(HMODULE mem, void* dest, bool bProtect)
{
	Memory jmp((uint32_t)mem);
	jmp.Set<BYTE>(0xE9, bProtect);
	jmp.ChangeAddress(jmp.GetAddress() + 1);
	jmp.Set<uint32_t>(GetRelativeAddress((uint32_t)mem, (uint32_t)dest - 5), bProtect);
	return GetRelativeAddress((uint32_t)mem, (uint32_t)dest - 5);
}

void MemoryInjector::MakeRET(Memory* mem, uint16_t pop, bool bProtect)
{
	WriteMemory<uint8_t>(mem->GetAddress(), 0xC2, bProtect);
	WriteMemory<uint16_t>(mem->GetAddress() + 1, pop, bProtect);
}

void MemoryInjector::MakeRET(uint32_t mem, uint16_t pop, bool bProtect)
{
	WriteMemory<uint8_t>(mem, 0xC2, bProtect);
	WriteMemory<uint16_t>(mem + 1, pop, bProtect);
}

void MemoryInjector::MakeRET0(Memory* mem, bool bProtect)
{
	WriteMemory<uint8_t>(mem->GetAddress(), 0x33, bProtect);
	WriteMemory<uint8_t>(mem->GetAddress() + 1, 0xC0, bProtect);
	MakeRET(mem->GetAddress() + 2, 4, bProtect);
}

void MemoryInjector::MakeRET0(uint32_t mem, bool bProtect)
{
	WriteMemory<uint8_t>(mem, 0x33, bProtect);
	WriteMemory<uint8_t>(mem + 1, 0xC0, bProtect);
	MakeRET(mem + 2, 4, bProtect);
}

void MemoryInjector::MakeRET(Memory* mem, bool bProtect)
{
	WriteMemory<uint8_t>(mem->GetAddress(), 0xC3, bProtect);
}

void MemoryInjector::MakeRET(uint32_t mem, bool bProtect)
{
	WriteMemory<uint8_t>(mem, 0xC3, bProtect);
}

// Makes a CALL to a relative address or function
uint32_t MemoryInjector::MakeCALL(Memory* mem, uint32_t dest, bool bProtect)
{
	if (mem == nullptr)
	{
		InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
		return 0;
	}
	mem->Set<BYTE>(0xE8, bProtect);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), dest - 4), bProtect);
	return GetRelativeAddress(mem->GetAddress(), dest - 4);
}

uint32_t MemoryInjector::MakeCALL(Memory* mem, void* dest, bool bProtect)
{
	if (mem == nullptr)
	{
		InjectorError = INJECTOR_ERROR_INVALID_MEMORY_PTR;
		return 0;
	}
	mem->Set<BYTE>(0xE8, bProtect);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), (uint32_t)dest - 4), bProtect);
	return GetRelativeAddress(mem->GetAddress(), (uint32_t)dest - 4);
}

uint32_t MemoryInjector::MakeCALL(uint32_t mem, uint32_t dest, bool bProtect)
{
	Memory call(mem);
	call.Set<BYTE>(0xE8, bProtect);
	call.ChangeAddress(call.GetAddress() + 1);
	call.Set<uint32_t>(GetRelativeAddress(mem, (uint32_t)dest - 5), bProtect);
	return GetRelativeAddress(mem, (uint32_t)dest - 5);
}

uint32_t MemoryInjector::MakeCALL(uint32_t mem, void* dest, bool bProtect)
{
	Memory call(mem);
	call.Set<BYTE>(0xE8, bProtect);
	call.ChangeAddress(call.GetAddress() + 1);
	call.Set<uint32_t>(GetRelativeAddress(mem, (uint32_t)dest - 5), bProtect);
	return GetRelativeAddress(mem, (uint32_t)dest - 5);
}