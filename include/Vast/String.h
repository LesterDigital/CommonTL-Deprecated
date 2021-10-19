#pragma once

namespace cmtl
{
	class String
	{
	private:
		void ReAlloc();
	private:
		size_t m_Size;
		size_t m_Capacity;

		char* m_Buffer;
	};
}
