#pragma once

#include <cstdint>

#ifdef _WIN32
#include <Windows.h>
#else
#define NULL 0
#endif

#define THERAWHOOKS_SPACE 0xFFFF

class RawHook
{
public:
	RawHook();
	~RawHook();

	void MakeRawJMP(uint32_t m_dwReturnAddr);
	void MakeRawCALL(uint32_t m_dwReturnAddr);

	void Write(const void* m_nData);
private:
	uint32_t m_dwJumpedFromAddr;
	uint32_t m_dwJumpOutAddr;
};

class TheRawHooks
{
public:
	bool Initialize();
	bool Shutdown();
private:
	static uint8_t* ms_pTheRawHooks;
	static uint32_t ms_nGlobalPos;
};