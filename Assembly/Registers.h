#pragma once

#include <stdint.h>

class Registers
{
public:
	uint32_t m_dwEFLAGS;
	uint32_t m_dwEDI, m_dwESI, m_dwEBP, m_dwESP, m_dwEBX, m_dwEDX, m_dwECX, m_dwEAX;
};