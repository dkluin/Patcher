#pragma once

/*
	ProcessHooking

	This class allows you to use the general injection functions (MakeCALL, MakeJMP...) on other processes. 
	Currently, all functions require a ProcessMemory class instance.
	Support for injecting your own functions is not implemented.
*/

#include "ProcessMemory.h"

class ProcessHooking
{
public:
	// Makes a JMP hook
	static void MakeProcessJMP(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress);

	// Makes a CALL hook
	static void MakeProcessCALL(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress);

	// Makes a NOP with a variable size
	static void MakeProcessNOP(ProcessMemory* m_pRemoteSourceAddress, uint32_t m_nSize);

	// Makes a RET (0xC3 variant)
	static void MakeProcessRET(ProcessMemory* m_pRemoteSourceAddress);

	// Makes a RET (0xC2 variant)
	static void MakeProcessRET(ProcessMemory* m_pRemoteSourceAddress, uint16_t m_Pop);

	// Makes a RET with a return value (NULL in this case)
	static void MakeProcessRET0(ProcessMemory* m_pRemoteSourceAddress);

	// Makes a ranged NOP
	static void MakeProcessRangedNOP(ProcessMemory* m_pRemoteSourceAddress, ProcessMemory* m_pRemoteDestinationAddress);

	// Makes a JMP on multiple (processes and) virtual addresses.
	static inline void MakeMultipleProcessJMPs(std::initializer_list<ProcessMemory*> m_pRemoteSourceAddressList, ProcessMemory* m_pRemoteDestinationAddress)
	{
		for (auto m_nRemoteSrcAddr : m_pRemoteSourceAddressList)
		{
			MakeProcessJMP(m_nRemoteSrcAddr, m_pRemoteDestinationAddress);
		}
	}

	// Makes a CALL on multiple (processes and) virtual addresses.
	static inline void MakeMultipleProcessCALLs(std::initializer_list<ProcessMemory*> m_pRemoteSourceAddressList, ProcessMemory* m_pRemoteDestinationAddress)
	{
		for (auto m_nRemoteSrcAddr : m_pRemoteSourceAddressList)
		{
			MakeProcessCALL(m_nRemoteSrcAddr, m_pRemoteDestinationAddress);
		}
	}

	// Writes to multiple (processes and) virtual addresses.
	template <class T>
	static inline void WriteProcessMemoryMultipleAddress(std::initializer_list<ProcessMemory*> m_pRemoteSourceAddressList, T m_Value)
	{
		for (auto m_nRemoteSrcAddr : m_pRemoteSourceAddressList)
		{
			m_nRemoteSrcAddr->ProcessSet(m_Value);
		}
	}

	// Private functions - used internally
private:
	static inline uint32_t GetRelativeProcessAddress(ProcessMemory* src, ProcessMemory* dest)
	{
		return dest - src;
	}

	static inline uint32_t GetRelativeProcessAddress(uint32_t m_pRemoteSourceAddress, uint32_t m_pRemoteDestinationAddress)
	{
		return m_pRemoteDestinationAddress - m_pRemoteSourceAddress;
	}
};