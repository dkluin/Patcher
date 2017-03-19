#include "VersionMgr.hpp"
#include <Psapi.h>


namespace Memory
{
	// Initializes version manager
	bool VersionMgr::InitializeVersionMgr()
	{
		switch (GetEntryPoint())
		{
		case 0x82457C:
		case 0x824570:
			return true;
		}

		return true;
	}

	// Shutdown version manager
	bool VersionMgr::ShutdownVersionMgr()
	{
		return true;
	}

	uint32_t VersionMgr::GetEntryPoint()
	{
		MODULEINFO info;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &info, sizeof(MODULEINFO));

		return (uint32_t)info.EntryPoint;
	}
}