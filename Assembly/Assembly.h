#pragma once

#include "Registers.h"
#include "../Injecting.h" 

/*
	TODO:
	- Introduce a sense of control after destructing the functor?
	- Memory support
	- Restorable patching
*/

template <class T>
struct WrapperFunctor
{
	static void CallFunctor(Registers* m_pRegisters)
	{
		T m_Functor;
		m_Functor(*m_pRegisters);
	}
};

template <class Wrapper>
__declspec(naked) inline void CallAssemblyFunctor()
{
	_asm
	{
		pushad
		add [esp + 0xC], 4
		pushfd

		push esp
		call Wrapper::CallFunctor
		add esp, 4

		sub [esp + 0x10], 4 
		popfd
		popad
		ret
	}
}

template <class Functor>
static void MakeAssemblyFunctor(uint32_t m_dwAddress, bool bProtect = true)
{
	using fuck = WrapperFunctor<Functor>;
	if (0)
	{
		fuck::CallFunctor(nullptr);
	}
	MemoryInjector::MakeCALL(m_dwAddress, CallAssemblyFunctor<fuck>, bProtect);
}

template <uint32_t m_dwAddress, class Functor>
static void MakeAssemblyFunctor(Functor m_Functor, bool bProtect = true)
{
	static Functor m_StaticFunctor = m_Functor; 

	struct fuck
	{
		void operator()(Registers& m_Registers)
		{
			m_StaticFunctor(m_Registers);
		}
	};

	MakeAssemblyFunctor<fuck>(m_dwAddress, bProtect);
}