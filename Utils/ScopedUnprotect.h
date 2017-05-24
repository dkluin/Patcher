#pragma once

/*
	ScopedUnprotect

	Used to unprotect memory data untill the instance of this class goes out of scope, in that case it will apply the original memory protection
*/
#include "../Memory.h"

class ScopedUnprotect
{
private:
	union
	{
		Memory* m_pMemory;
		uint32_t m_Address;
	};

	size_t m_iSizeOfMemory;
	bool m_bUseMemoryClass = false;

	DWORD m_dwOldVirtualProtect[2];

public:
	ScopedUnprotect(Memory* pStartMemory, size_t iSizeOfMemory);
	ScopedUnprotect(uint32_t dwAddress, size_t iSizeOfMemory);

	~ScopedUnprotect();
};