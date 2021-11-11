#pragma once

#ifndef CTL_ALLOCATOR_H
#define CTL_ALLOCATOR_H

#include <cstdlib>

namespace ctl
{
	template<typename Ty>
	class Allocator
	{
	public:
		Allocator() {}
		Allocator(const Allocator& other)
		{
			Clear();
			for (size_t i = 0; i < other.Size(); i++)
				PushBack(other[i]);
		}

		~Allocator()
		{
			Clear();
		}

		size_t Size() const { return m_Size; }

		size_t Capacity() const { return m_Capacity; }

		// If there is a free space in the buffer then it emplaces it (reallocates otherwise)
		virtual void PushBack(const Ty& data)
		{
			if (m_Capacity == 0)
				ReAlloc(2);
			else if (m_Size >= m_Capacity)
				ReAlloc(m_Capacity + m_Capacity / 2);

			m_Buffer[m_Size] = data;
			m_Size++;
		}

		// Destructs the last element of an array (capacity stays the same)
		void PopBack()
		{
			if (m_Size > 0)
			{
				m_Size--;
				m_Buffer[m_Size].~Ty();
			}
		}
		void PopFront()
		{
			if (m_Size > 0)
			{
				m_Size--;
				m_Buffer[0].~Ty();
				
				for (size_t i = 0; i < m_Size; i++)
					m_Buffer[i] = m_Buffer[i + 1];
			}
		}

		// Destructs all the elements of an array (capacity stays the same)
		void Clear()
		{
			for (size_t i = 0; i < m_Size; i++)
				m_Buffer[i].~Ty();

			m_Size = 0;
		}

		// Expands current capacity to a given
		void Reserve(size_t size)
		{
			if (size > m_Capacity)
			{
				ReAlloc(size);
			}
		}

		// Access only overload of indexer
		const Ty& operator[](size_t index) const
		{
			return m_Buffer[index];
		}
		// Access and alter data using indexer
		Ty& operator[](size_t index)
		{
			return m_Buffer[index];
		}
	protected:
		// Reallocates the array to a given capacity and copies previous elements
		void ReAlloc(size_t capacity)
		{
			Ty* newBlock = static_cast<Ty*>(::operator new(capacity * sizeof(Ty)));

			if (capacity < m_Size)
				m_Size = capacity;

			for (size_t i = 0; i < m_Size; i++)
				newBlock[i] = m_Buffer[i];

			// Destruct old array elements
			for (size_t i = 0; i < m_Size; i++)
				m_Buffer[i].~Ty();

			::operator delete(m_Buffer, m_Capacity * sizeof(Ty));
			m_Buffer = newBlock;
			m_Capacity = capacity;
		}
	protected:
		Ty* m_Buffer = nullptr;

		size_t m_Size = 0;
		size_t m_Capacity = 0;
	};
}

#endif
