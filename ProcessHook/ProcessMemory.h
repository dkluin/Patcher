#pragma once

#include "../Memory.h"
#include "../Shared.hpp"

/*
	ProcessMemory, the base for patching other processes
*/

class ProcessMemory : public Memory
{
protected:
	HANDLE m_hProcessHandle;

	bool m_bProcessOpen : 1; // Is the process open (can we read/write from its virtual addresses?)

public:
	// Construct a ProcessMemory with a known HANDLE
	ProcessMemory(HANDLE m_Handle, uint32_t m_dwAddress) : Memory(m_dwAddress) 
	{
		if (m_Handle)
		{
			AdjustProcessTokens(m_Handle);
			m_hProcessHandle = m_Handle;
			m_bProcessOpen = true;
		}
	};

	// Construct a ProcessMemory through a window handle
	ProcessMemory(HWND m_Hwnd, uint32_t m_dwAddress) : Memory(m_dwAddress)
	{
		DWORD m_PID;
		HANDLE m_hLocalProcessHandle;

		GetWindowThreadProcessId(m_Hwnd, &m_PID);
		m_hLocalProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, m_PID);
		if (m_hLocalProcessHandle)
		{
			AdjustProcessTokens(m_hLocalProcessHandle);
			m_bProcessOpen = true;

			m_hProcessHandle = m_hLocalProcessHandle;
		}
	}

	// Construct a ProcessMemory merely through the process name
	ProcessMemory(std::string m_szClassName, std::string m_szWindowName, uint32_t m_dwAddress) : Memory(m_dwAddress)
	{
		DWORD m_PID;
		HWND m_Hwnd;
		HANDLE m_hLocalProcessHandle;

		m_Hwnd = FindWindow(m_szClassName.c_str(), m_szWindowName.c_str());

		if (m_Hwnd)
		{
			GetWindowThreadProcessId(m_Hwnd, &m_PID);
			m_hLocalProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, m_PID);
			if (m_hLocalProcessHandle)
			{
				AdjustProcessTokens(m_hLocalProcessHandle);
				m_bProcessOpen = true;

				m_hProcessHandle = m_hLocalProcessHandle;
			}
		}
	}

	// Same as above, but only use a window name
	ProcessMemory(std::string m_szWindowName, uint32_t m_dwAddress) : Memory(m_dwAddress)
	{
		DWORD m_PID;
		HWND m_Hwnd;
		HANDLE m_hLocalProcessHandle;

		m_Hwnd = FindWindow(NULL, m_szWindowName.c_str());

		if (m_Hwnd)
		{
			GetWindowThreadProcessId(m_Hwnd, &m_PID);
	
			m_hLocalProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, m_PID);
			if (m_hLocalProcessHandle)
			{
				AdjustProcessTokens(m_hLocalProcessHandle);
				m_bProcessOpen = true;

				m_hProcessHandle = m_hLocalProcessHandle;
			}
		}
	}

	// Destructs the ProcessMemory if not done so already, as we need to close the process handle anyway
	~ProcessMemory()
	{
		if (m_bProcessOpen)
		{
			AdjustProcessTokens(m_hProcessHandle, false); 
			CloseHandle(m_hProcessHandle);
			m_bProcessOpen = false;
		}
	}

	// Writes to a process's virtual address
	template <class T>
	inline bool ProcessSet(T m_Value)
	{
		bool m_bResult;
		DWORD m_OldVirtualProtect[2];

		if (bRequiresVirtualProtection)
		{
			SetMemoryVirtualProtect(sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			m_bResult = WriteProcessMemory(m_hProcessHandle, reinterpret_cast<void*>(Address), reinterpret_cast<void*>(&m_Value), sizeof(T), nullptr);
			SetMemoryVirtualProtect(sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			m_bResult = WriteProcessMemory(m_hProcessHandle, reinterpret_cast<void*>(Address), reinterpret_cast<void*>(&m_Value), sizeof(T), nullptr);
		}

		return m_bResult;
	}

	// Reads from a process's virtual address
	template <class T>
	inline T ProcessGet()
	{
		T m_Result;
		DWORD m_OldVirtualProtect[2];

		if (bRequiresVirtualProtection)
		{
			SetMemoryVirtualProtect(sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			ReadProcessMemory(m_hProcessHandle, reinterpret_cast<void*>(Address), reinterpret_cast<void*>(&m_Result), sizeof(T), nullptr);
			SetMemoryVirtualProtect(sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			ReadProcessMemory(m_hProcessHandle, reinterpret_cast<void*>(Address), reinterpret_cast<void*>(&m_Result), sizeof(T), nullptr);
		}

		return m_Result;
	}
	
	// Wrapper around VirtualProtectEx for unprotecting/protecting virtual addresses in other processes
	inline bool SetMemoryVirtualProtect(size_t m_iSize, DWORD m_dwNewProtect, PDWORD m_dwOldProtect)
	{
		return VirtualProtectEx(m_hProcessHandle, reinterpret_cast<void*>(Address), m_iSize, m_dwNewProtect, m_dwOldProtect);
	}

private:
	// We need to adjust the process's tokens if we want to gain access to it...
	inline void AdjustProcessTokens(HANDLE m_Handle, bool bEnableProcessAdjustPrivileges = true)
	{
		TOKEN_PRIVILEGES m_TokenPrivileges;
		LUID m_seDebugNameValue;
		HANDLE m_pHandle;

		if (bEnableProcessAdjustPrivileges)
		{
			OpenProcessToken(m_Handle, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &m_pHandle);
			LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &m_seDebugNameValue);

			m_TokenPrivileges.PrivilegeCount = 1;
			m_TokenPrivileges.Privileges[0].Luid = m_seDebugNameValue;
			m_TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			AdjustTokenPrivileges(m_pHandle, false, &m_TokenPrivileges, sizeof(m_TokenPrivileges), NULL, NULL);

			CloseHandle(&m_pHandle);
		}
		else
		{
			// TODO...
		}
	}
};