#pragma once

namespace ctl
{
	class String
	{
	public:
		String()
		{
			Reserve(2);
		}

		void Reserve(const size_t& space);
	private:
		void ReAlloc();
	private:
		size_t m_Size;
		size_t m_Capacity;

		char* m_Buffer;
	};

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
