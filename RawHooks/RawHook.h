/*
	RawHook.h

	Nothing more than unfinished code at this point, but it is in an useable state - except that its still not fully implemented

	TODO:
	- Memory support
	- Refactoring
	- Wrapper functions which create a RawHook but iterate through the data and place variables where needed, see TheRawHooks::StaticRawHook
	- Better destructors which finish the RawHook if not done so when the instance goes out of scope
	- Improved RawHookVariable which uses templates?
*/
#pragma once

#include <cstdint>
#include <Windows.h>
#include <vector>

#include "RawHookVariable.h"

class RawHook
{
public:
	friend class RawHookVariable;

private:
	uint32_t m_dwJumpedFromAddr;
	uint32_t m_dwJumpOutAddr;
	uint32_t m_dwPositionOnStart;
	bool m_bFinished;
	bool m_bStarted;

public:
	// Constructs a RawHook, where m_dwJumpFrom is the address where a JMP to the raw hook will be placed, and m_dwJumpTo is the exit address
	RawHook(uint32_t m_dwJumpFrom, uint32_t m_dwJumpTo);

	// Destructs a RawHook
	~RawHook()
	{
		if (m_bStarted && !m_bFinished)
		{
			Finish();
		}
	}

	// Start using this hook - meaning that we set the old position before we add anything to the global position value so we can make a JMP instruction to this position inside the heap when Finish() is called
	void Start();

	// Writes a JMP to an address specified on the current raw hook
	void MakeRawJMP(uint32_t m_dwReturnAddr);

	// Same, but just calls a function
	void MakeRawCALL(uint32_t m_dwReturnAddr);

	// Can be used to write raw hexadecimal instructions onto the heap space 
	void Write(const void* m_nData, size_t m_iSize);

	// Writes a RET
	void MakeRawRET();

	// Writes a variable's value
	void WriteVariable(std::string m_szVariableName);
	void WriteVariable(RawHookVariable* m_pVar);

	// Finishes with the current raw hook - this will add a JMP opcode to m_dwJumpOutAddr specified and then adds 2 NOP instructions (just to make it easier to identify patches)
	void Finish();
};