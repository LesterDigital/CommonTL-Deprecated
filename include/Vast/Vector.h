#pragma once

#ifndef VECTOR_H
#define VECTOR_H

namespace ctl
{
	template<typename VectorT>
	class VectorIterator
	{
	public:
		using ValueType = typename VectorT::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
	public:
		VectorIterator(PointerType ptr)
			: m_Ptr(ptr) {}

		VectorIterator& operator++()
		{
			m_Ptr++;
			return *this;
		}
		VectorIterator operator++(int)
		{
			VectorIterator iterator = *this;
			++(*this);
			return iterator;
		}

		VectorIterator& operator--()
		{
			m_Ptr--;
			return *this;
		}
		VectorIterator operator--(int)
		{
			VectorIterator iterator = *this;
			--(*this);
			return iterator;
		}

		ReferenceType operator[](int index) const { return *(m_Ptr + index); }
		PointerType operator->() const { return m_Ptr; }
		ReferenceType operator*() const { return *m_Ptr; }

		bool operator==(const VectorIterator& other) const { return m_Ptr == other.m_Ptr; }
		bool operator!=(const VectorIterator& other) const { return m_Ptr != other.m_Ptr; }
	private:
		PointerType m_Ptr;
	};

	template<typename type>
	class Vector
	{
	public:
		using ValueType = type;
		using Iterator = VectorIterator<Vector<type>>;
	public:
		Vector()
		{
			ReAlloc(2);
		}

		Vector(const size_t& size)
		{
			Reserve(size);
		}

		Vector(const Vector& arr)
		{
			m_Capacity = arr.Capacity();
			m_Size = arr.Size();

			ReAlloc(m_Capacity);

			for (size_t i = 0; i < m_Size; i++)
				m_Array[i] = arr[i];
		}

		~Vector()
		{
			delete[] m_Array;
		}

		size_t Size() const { return m_Size; }

		size_t Capacity() const { return m_Capacity; }

		// If there is a free space in the buffer then it emplaces it (reallocates otherwise)
		void PushBack(type data)
		{
			if (m_Size >= m_Capacity)
				ReAlloc(m_Capacity + m_Capacity / 2);

			m_Array[m_Size] = data;
			m_Size++;
		}

		// Destructs the last element of an array (capacity stays the same)
		void Pop()
		{
			if (m_Size > 0)
			{
				m_Size--;
				m_Array[m_Size].~type();
			}
		}

		// Reallocates an array without a value at the given index
		// TODO: Instead of a reallocation, keep the capacity and just destruct the value and shift other elements 
		void Remove(size_t index = m_Size - 1)
		{
			if (0 <= index && index < m_Size)
			{
				// Making tmp array P.S. decrementing Size
				m_Size--;

				type* newArr = new type[m_Size];
				for (size_t i = 0, i2 = 0; i < m_Size; i2++)
					if (i2 != index)
						newArr[i++] = m_Array[i2];

				delete[] m_Array;
				m_Array = newArr;
			}
		}

		// Destructs all the elements of an array (capacity stays the same)
		void Clear()
		{
			for (size_t i = 0; i < m_Size; i++)
				m_Array[i].~type();

			m_Size = 0;
		}

		// Expands current capacity to a given
		void Reserve(const size_t size)
		{
			if (size > m_Capacity)
			{
				m_Capacity = size;

				ReAlloc(m_Capacity);
			}
		}

		// Access only overload of indexer
		const type& operator[](size_t index) const
		{
			return m_Array[index];
		}
		// Access and alter data using indexer
		type& operator[](size_t index)
		{
			return m_Array[index];
		}

		Iterator begin()
		{
			return Iterator(m_Array);
		}

		Iterator end()
		{
			return Iterator(m_Array + m_Size);
		}

	private:
		// Realocates the array to a given capacity and copies previous elements
		void ReAlloc(size_t capacity)
		{
			type* newBlock = new type[capacity]{};

			if (capacity < m_Size)
				m_Size = capacity;

			for (size_t i = 0; i < m_Size; i++)
				newBlock[i] = m_Array[i];

			delete[] m_Array;
			m_Array = newBlock;
			m_Capacity = capacity;
		}
	private:
		type* m_Array;

		size_t m_Size = 0;
		size_t m_Capacity = 0;
	};
}

#endif
