/*
	RawHooks.h
*/
#pragma once

#include <cstdint>
#include <Windows.h>

#define THERAWHOOKS_SPACE 0xFFFF

class RawHook
{
public:
	RawHook(uint32_t m_dwJumpFrom, uint32_t m_dwJumpTo);
	~RawHook();

	// Start using this hook - meaning that we set the old position before we add anything to the global position value so we can make a JMP instruction to this position inside the heap when Finish() is called
	void Start();

	// Writes a JMP to an address specified on the current raw hook
	void MakeRawJMP(uint32_t m_dwReturnAddr);

	// Same, but just calls a function
	void MakeRawCALL(uint32_t m_dwReturnAddr);

	// Can be used to write raw hexadecimal instructions onto the heap space 
	void Write(const void* m_nData, size_t m_iSize);

	// Finishes with the current raw hook - this will add a JMP opcode to m_dwJumpOutAddr specified and then adds 2 NOP instructions (just to make it easier to identify patches)
	void Finish();

private:
	uint32_t m_dwJumpedFromAddr;
	uint32_t m_dwJumpOutAddr;
	uint32_t m_dwPositionOnStart;
	bool m_bFinished;
	bool m_bStarted;
};

class TheRawHooks
{
public:
	bool Initialize();
	bool Shutdown();

	static uint8_t* ms_pTheRawHooks;
	static uint32_t ms_nGlobalPos;
};