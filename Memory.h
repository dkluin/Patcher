#pragma once

#include <cstdint>
#include <Windows.h>

namespace Patcher
{
	/////////////// New code which uses operators for comparing, setting, and even adding, multiplying, and much more 
	class Memory
	{
	private:
		uint32_t Address;

	public:
		Memory() { Address = 0; };
		Memory(uint32_t addr) { Address = addr; }

		// Change address
		void ChangeAddress(uint32_t newAddr)
		{
			Address = newAddr;
		}

		// Sets memory value with protect parameter
		template <class T>
		inline void Set(T& value, bool bProtect)
		{
			DWORD dwProtect[2];

			if (bProtect)
			{
				VirtualProtect(this->Address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
				*(T*)this->Address = value;
				VirtualProtect(this->Address, sizeof(T), dwProtect[0], &dwProtect[1]);
			}
			else
			{
				*(T*)this->Address = value;
			}
		}

		// Gets memory value with virtual protect parameter
		template <class T>
		inline T Get(bool bProtect)
		{
			T result;
			DWORD dwProtect[2];

			if (bProtect)
			{
				VirtualProtect((LPVOID)this->Address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
				result = *(T*)this->Address;
				VirtualProtect((LPVOID)this->Address, sizeof(T), dwProtect[0], &dwProtect[1]);
			}
			else
			{
				result = *(T*)this->Address;
			}
			return result;
		}

		// Returns the current address
		inline uint32_t GetAddress()
		{
			return this->Address;
		}

		// Operators
		template <class T>
		inline void operator=(const T& value) { *(T*)this->Address = value; }

		template <class T>
		inline void operator+(const T& value) { *(T*)this->Address = *(T*)this->Address + value; }

		template <class T>
		inline void operator-(const T& value) { *(T*)this->Address = *(T*)this->Address - value; }

		template <class T>
		inline void operator*(const T& value) { *(T*)this->Address = *(T*)this->Address * value; }

		template <class T>
		inline void operator/(const T& value) { *(T*)this->Address = *(T*)this->Address / value; }
		inline void operator%(const int& value) { *(int*)this->Address = *(int*)this->Address % value; }

		template <class T>
		inline void operator==(const T& rvalue) { *(T*)this->Address == rvalue; }

		template <class T>
		inline void operator+=(const T& value) { *(T*)this->Address += value; }

		template <class T>
		inline void operator-=(const T& value) { *(T*) this->Address -= value; }

		template <class T>
		inline void operator*=(const T& value) { *(T*) this->Address *= value; }

		template <class T>
		inline void operator/=(const T& value) { *(T*) this->Address /= value; }
		inline void operator%=(const int& value) { *(int*) this->Address %= value; }
	};
}