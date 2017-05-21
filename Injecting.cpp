#include "Shared.hpp"
#include "Injecting.h"
#include "General.h"

// Gets a relative addresss
uint32_t MemoryInjector::GetRelativeAddress(uint32_t src, uint32_t dest)
{
	return dest - src;
}

uint32_t MemoryInjector::GetRelativeAddress(uint32_t src, void* dest)
{
	return reinterpret_cast<uint32_t>(dest) - src;
}

void MemoryInjector::MakeNOP(Memory* mem, uint32_t m_dwSize)
{
	for (uint32_t i = 0; i < m_dwSize; i++)
	{
		Memory nop(mem->GetAddress() + i);
		nop.SetVirtualProtect(mem->GetVirtualProtect());
		WriteMemory<uint8_t>(&nop, 0x90);
	}
}

void MemoryInjector::MakeNOP(uint32_t mem, uint32_t m_dwSize, bool bProtect)
{
	for (uint32_t i = 0; i < m_dwSize; i++)
	{
		WriteMemory<uint8_t>(mem + i, 0x90);
	}
}

void MemoryInjector::MakeJE(Memory* mem, uint32_t dest)
{
	mem->Set<uint16_t>(0x840F);
	mem->ChangeAddress(mem->GetAddress() + 2);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), dest - 6));
	mem->ChangeAddress(mem->GetAddress() - 2);
}

void MemoryInjector::MakeJE(Memory* mem, void* dest)
{
	mem->Set<uint16_t>(0x840F);
	mem->ChangeAddress(mem->GetAddress() + 2);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), reinterpret_cast<uint32_t>(dest) - 6));
	mem->ChangeAddress(mem->GetAddress() - 2);
}

void MemoryInjector::MakeJA(Memory* mem, uint32_t dest)
{
	mem->Set<uint16_t>(0x870F);
	mem->ChangeAddress(mem->GetAddress() + 2);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), dest - 6));
	mem->ChangeAddress(mem->GetAddress() - 2);
}

void MemoryInjector::MakeJA(Memory* mem, void* dest)
{
	mem->Set<uint16_t>(0x870F);
	mem->ChangeAddress(mem->GetAddress() + 2);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), reinterpret_cast<uint32_t>(dest) - 6));
	mem->ChangeAddress(mem->GetAddress() - 2);
}

// Makes a JMP to a relative address or function
void MemoryInjector::MakeJMP(Memory* mem, uint32_t dest)
{
	mem->Set<BYTE>(0xE9);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), dest - 4));
	mem->ChangeAddress(mem->GetAddress() - 1);
}

void MemoryInjector::MakeJMP(Memory* mem, void* dest)
{
	mem->Set<BYTE>(0xE9);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), reinterpret_cast<uint32_t>(dest) - 4));
	mem->ChangeAddress(mem->GetAddress() - 1);
}

void MemoryInjector::MakeRET(Memory* mem, uint16_t pop)
{
	WriteMemory<uint8_t>(mem, 0xC2);

	Memory ret(mem->GetAddress() + 1);
	ret.SetVirtualProtect(mem->GetVirtualProtect());

	WriteMemory<uint16_t>(&ret, pop);
}

void MemoryInjector::MakeRET(uint32_t mem, uint16_t pop, bool bProtect)
{
	WriteMemory<uint8_t>(mem, 0xC2, bProtect);
	WriteMemory<uint16_t>(mem + 1, pop, bProtect);
}

void MemoryInjector::MakeRET0(Memory* mem)
{
	WriteMemory<uint8_t>(mem, 0x33);
	Memory ret(mem->GetAddress() + 1);
	ret.SetVirtualProtect(mem->GetVirtualProtect());
	WriteMemory<uint8_t>(&ret, 0xC0);
	ret.ChangeAddress(mem->GetAddress() + 2);
	MakeRET(&ret, 4);
}

void MemoryInjector::MakeRET0(uint32_t mem, bool bProtect)
{
	WriteMemory<uint8_t>(mem, 0x33, bProtect);
	WriteMemory<uint8_t>(mem + 1, 0xC0, bProtect);
	MakeRET(mem + 2, 4, bProtect);
}

void MemoryInjector::MakeRET(Memory* mem)
{
	WriteMemory<uint8_t>(mem, 0xC3);
}

void MemoryInjector::MakeRET(uint32_t mem, bool bProtect)
{
	WriteMemory<uint8_t>(mem, 0xC3, bProtect);
}

void MemoryInjector::MakeMultipleCALLs(std::initializer_list<uint32_t> m_vAddresses, uint32_t m_pDest, bool bProtect)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeCALL(m_nAddr, m_pDest, bProtect);
	}
}

void MemoryInjector::MakeMultipleCALLs(std::initializer_list<uint32_t> m_vAddresses, void* m_pDest, bool bProtect)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeCALL(m_nAddr, m_pDest, bProtect);
	}
}

void MemoryInjector::MakeMultipleCALLs(std::initializer_list<Memory*> m_vAddresses, uint32_t m_pDest)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeCALL(m_nAddr, m_pDest);
	}
}

void MemoryInjector::MakeMultipleCALLs(std::initializer_list<Memory*> m_vAddresses, void* m_pDest)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeCALL(m_nAddr, m_pDest);
	}
}

void MemoryInjector::MakeMultipleJMPs(std::initializer_list<uint32_t> m_vAddresses, uint32_t m_pDest, bool bProtect)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeJMP(m_nAddr, m_pDest, bProtect);
	}
}

void MemoryInjector::MakeMultipleJMPs(std::initializer_list<uint32_t> m_vAddresses, void* m_pDest, bool bProtect)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeJMP(m_nAddr, m_pDest, bProtect);
	}
}

void MemoryInjector::MakeMultipleJMPs(std::initializer_list<Memory*> m_vAddresses, uint32_t m_pDest)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeJMP(m_nAddr, m_pDest);
	}
}

void MemoryInjector::MakeMultipleJMPs(std::initializer_list<Memory*> m_vAddresses, void* m_pDest)
{
	for (auto m_nAddr : m_vAddresses)
	{
		MakeJMP(m_nAddr, m_pDest);
	}
}

void MemoryInjector::MakeRangedNOP(Memory* m_pMemoryStart, Memory* m_pMemoryEnd)
{
	if (m_pMemoryEnd > m_pMemoryStart)
	{
		MakeNOP(m_pMemoryStart, m_pMemoryEnd - m_pMemoryStart);
	}
}

void MemoryInjector::MakeRangedNOP(uint32_t m_MemoryStart, uint32_t m_MemoryEnd)
{
	if (m_MemoryEnd > m_MemoryStart)
	{
		MakeNOP(m_MemoryStart, m_MemoryEnd - m_MemoryStart);
	}
}

void MemoryInjector::MakeRangedNOP(Memory* m_pMemoryStart, uint32_t m_MemoryEnd)
{
	if (m_MemoryEnd > m_pMemoryStart->GetAddress())
	{
		MakeNOP(m_pMemoryStart, m_MemoryEnd - m_pMemoryStart->GetAddress());
	}
}

void MemoryInjector::MakeRangedNOP(uint32_t m_MemoryStart, Memory* m_pMemoryEnd)
{
	if (m_pMemoryEnd->GetAddress() > m_MemoryStart)
	{
		MakeNOP(m_MemoryStart, m_pMemoryEnd->GetAddress() - m_MemoryStart);
	}
}

// Makes a CALL to a relative address or function
void MemoryInjector::MakeCALL(Memory* mem, uint32_t dest)
{
	mem->Set<BYTE>(0xE8);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), dest - 4));
	mem->ChangeAddress(mem->GetAddress() - 1);
}

void MemoryInjector::MakeCALL(Memory* mem, void* dest)
{
	mem->Set<BYTE>(0xE8);
	mem->ChangeAddress(mem->GetAddress() + 1);
	mem->Set<uint32_t>(GetRelativeAddress(mem->GetAddress(), reinterpret_cast<uint32_t>(dest) - 4));
	mem->ChangeAddress(mem->GetAddress() - 1);
}