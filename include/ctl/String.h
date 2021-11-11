#pragma once

#ifndef CTL_STRING_H
#define CTL_STRING_H

#include <ostream>
#include <cstring>

#include "ctl/Allocator.h"

namespace ctl
{
	// Dynamically allocated String
	class String : public Allocator<char>
	{
	public:
		static size_t s_MaxSize;
	public:
		String() {}

		String(size_t size);
		String(char* string); 
		String(const char* string);
		
		void Copy(char* string);
		void Copy(const char* string);

		void PushBack(const char& c) override;

		void PushString(const String& string);
		void PushString(const char* string);
		void PushString(char*& string);

		String Cut(const size_t& rLeft, const size_t& rRight);

		char* Cstr() const;

		void operator = (const char* string);
		void operator = (char* string);

		String operator + (const String& string) const;
		void operator += (const String& string);
		void operator += (const char* string);

		bool operator == (const String& string) const;
		bool operator != (const String& string) const;

		friend std::ostream& operator << (std::ostream& stream, const String& string);

	private:
		size_t ComputeSize(size_t size) const;
	};

	// Static string
	class StringView
	{
	public:
		StringView(char* str, size_t start, size_t end)
		{
			m_ViewBuffer = str;
		}

	private:
		const char* m_ViewBuffer;
	};
}

#endif