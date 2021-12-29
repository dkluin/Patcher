#include "../Shared.hpp"
#include "ProcessHooking.h"

// Simple variant of MakeProcessJMP - this 
void ProcessHooking::MakeProcessJMP(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress)
{
	if (m_pRemoteSourceAddress->m_hProcessHandle == m_pRemoteDestinationAddress->m_hProcessHandle)
	{
		m_pRemoteSourceAddress->ProcessSet<BYTE>(0xE9);
		m_pRemoteSourceAddress->ProcessSet<uint32_t>(GetRelativeProcessAddress(m_pRemoteSourceAddress, m_pRemoteDestinationAddress - 5));
	}
}

void ProcessHooking::MakeProcessCALL(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress)
{
	if (m_pRemoteSourceAddress->m_hProcessHandle == m_pRemoteDestinationAddress->m_hProcessHandle)
	{
		m_pRemoteSourceAddress->ProcessSet<BYTE>(0xE8);
		m_pRemoteSourceAddress->ProcessSet<uint32_t>(GetRelativeProcessAddress(m_pRemoteSourceAddress, m_pRemoteDestinationAddress - 5));
	}
}

void ProcessHooking::MakeProcessNOP(ProcessMemory* m_pRemoteSourceAddress, uint32_t m_nSize)
{
	for (uint32_t i = 0; i < m_nSize; i++)
	{
		m_pRemoteSourceAddress->ProcessSet<uint8_t>(0x90);
	}
}

void ProcessHooking::MakeProcessRET(ProcessMemory* m_pRemoteSourceAddress)
{
	m_pRemoteSourceAddress->ProcessSet<uint8_t>(0xC3);
}

void ProcessHooking::MakeProcessRET(ProcessMemory* m_pRemoteSourceAddress, uint16_t m_Pop)
{
	m_pRemoteSourceAddress->ProcessSet<uint8_t>(0xC2);
	m_pRemoteSourceAddress->ChangeAddress(m_pRemoteSourceAddress->GetAddress() + 1);
	m_pRemoteSourceAddress->ProcessSet<uint16_t>(m_Pop);
	m_pRemoteSourceAddress->ChangeAddress(m_pRemoteSourceAddress->GetAddress() - 1);
}

void ProcessHooking::MakeProcessRET0(ProcessMemory* m_pRemoteSourceAddress)
{
	m_pRemoteSourceAddress->ProcessSet<uint8_t>(0x33);
	m_pRemoteSourceAddress->ChangeAddress(m_pRemoteSourceAddress->GetAddress() + 1);
	m_pRemoteSourceAddress->ProcessSet<uint8_t>(0xC0);
	m_pRemoteSourceAddress->ChangeAddress(m_pRemoteSourceAddress->GetAddress() + 1);
	MakeProcessRET(m_pRemoteSourceAddress, 4);
	m_pRemoteSourceAddress->ChangeAddress(m_pRemoteSourceAddress->GetAddress() - 2);
}

void ProcessHooking::MakeProcessRangedNOP(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress)
{
	MakeProcessNOP(m_pRemoteSourceAddress, m_pRemoteDestinationAddress->GetAddress() - m_pRemoteSourceAddress->GetAddress());
}