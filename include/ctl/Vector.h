#pragma once

#ifndef CTL_VECTOR_H
#define CTL_VECTOR_H

#include <ostream>

#include "ctl/Allocator.h"

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

	template<typename Ty>
	class Vector 
		: public Allocator<Ty>
	{
	public:
		using ValueType = Ty;
		using Iterator = VectorIterator<Vector<Ty>>;
	public:
		Vector()
		{
			this->Reserve(2);
		}
		Vector(const size_t& size)
		{
			this->Reserve(size);
		}

		void Insert(size_t index, const Ty& data)
		{
			if (index <= this->m_Size)
			{
				if (this->m_Capacity < this->m_Size + 1)
					this->Reserve(this->m_Capacity + this->m_Capacity / 2);

				// Push back the last element of an array
				this->PushBack(this->m_Buffer[this->m_Size - 1]);

				// Swap adjacent elements from the end until the insertion index, to shift them to the left
				for (size_t i = this->m_Size - 2; i > index; i--)
				{
					Ty tmp = this->m_Buffer[i];
					this->m_Buffer[i] = this->m_Buffer[i - 1];
					this->m_Buffer[i - 1] = tmp;
				}

				this->m_Buffer[index] = data;
			}
		}

		void Remove(size_t index)
		{
			if (index >= 0 && index < this->m_Size)
			{ 
				for (size_t i = 0, i2 = 0; i < this->m_Size - 1; i2++)
					if (i2 != index)
						(*this)[i++] = (*this)[i2];
				this->Pop();
			}
		}

		Iterator begin()
		{
			return Iterator(this->m_Buffer);
		}

		Iterator end()
		{
			return Iterator(this->m_Buffer + this->m_Size);
		}

	};

	template<typename Ty>
	std::ostream& operator << (std::ostream& stream, const Vector<Ty> vec)
	{
		stream << "[";
		if (vec.Size() > 0)
		{
			for (size_t i = 0; i < vec.Size() - 1; i++)
				stream << ' ' << vec[i] << ",";
			stream << ' ' << vec[vec.Size() - 1];
		}
		stream << " ]";

		return stream;
	}
}

#endif
