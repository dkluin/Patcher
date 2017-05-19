#include "../Shared.hpp"
#include "ProcessHooking.h"

void ProcessHooking::MakeProcessJMP(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress)
{
	m_pRemoteSourceAddress->ProcessSet<BYTE>(0xE9);
	m_pRemoteSourceAddress->ProcessSet<uint32_t>(GetRelativeProcessAddress(m_pRemoteSourceAddress, m_pRemoteDestinationAddress - 5));
}

void ProcessHooking::MakeProcessJMP(ProcessMemory* m_pRemoteSourceAddress, void* m_pRemoteDestinationAddress)
{
	m_pRemoteSourceAddress->ProcessSet<BYTE>(0xE9);
	m_pRemoteSourceAddress->ProcessSet<uint32_t>(GetRelativeProcessAddress(m_pRemoteSourceAddress->GetAddress(), reinterpret_cast<uint32_t>(m_pRemoteDestinationAddress) - 5));
}

void ProcessHooking::MakeProcessCALL(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress)
{
	m_pRemoteSourceAddress->ProcessSet<BYTE>(0xE8);
	m_pRemoteSourceAddress->ProcessSet<uint32_t>(GetRelativeProcessAddress(m_pRemoteSourceAddress, m_pRemoteDestinationAddress - 5));
}

void ProcessHooking::MakeProcessCALL(ProcessMemory* m_pRemoteSourceAddress, void* m_pRemoteDestinationAddress)
{
	m_pRemoteSourceAddress->ProcessSet<BYTE>(0xE8);
	m_pRemoteSourceAddress->ProcessSet<uint32_t>(GetRelativeProcessAddress(m_pRemoteSourceAddress->GetAddress(), reinterpret_cast<uint32_t>(m_pRemoteDestinationAddress) - 5));
}

void ProcessHooking::MakeProcessNOP(ProcessMemory* m_pRemoteSourceAddress, uint32_t m_nSize)
{
	for (uint32_t i = 0; i < m_nSize; i++)
	{
		m_pRemoteSourceAddress->ProcessSet<uint8_t>(0x90);
	}
}