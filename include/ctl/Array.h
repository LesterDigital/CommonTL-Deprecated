#pragma once

#ifndef CTL_ARRAY_H
#define CTL_ARRAY_H

#include <initializer_list>
#include <iterator>

namespace ctl
{
	template<typename Ty, size_t Sz>
	class Array
	{
	public:
		Ty Buffer[Sz];
	public:
		class Iterator
		{
		public:
			Iterator(const Ty* arr)
				: m_Ptr(arr) {}


			Iterator& operator++()
			{
				m_Ptr++;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator iterator = *this;
				++(*this);
				return iterator;
			}

			Iterator& operator--()
			{
				m_Ptr--;
				return *this;
			}
			Iterator operator--(int)
			{
				Iterator iterator = *this;
				--(*this);
				return iterator;
			}

			const Ty& operator[](int index) const { return *(m_Ptr + index); }
			const Ty* operator->() const { return m_Ptr; }
			const Ty& operator*() const { return *m_Ptr; }

			bool operator==(const Iterator& other) const { return m_Ptr == other.m_Ptr; }
			bool operator!=(const Iterator& other) const { return m_Ptr != other.m_Ptr; }
		private:
			const Ty* m_Ptr;
		};
	public:
		Array() = default;

		Array(const Ty* arr)
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i] = arr[i];
		}
		Array(const Array<Ty, Sz>& other)
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i] = other[i];
		}
		Array(Array<Ty, Sz>&& other)
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i] = other[i];
		}

		~Array()
		{
			Clear();
		}

		const size_t Size() const { return Sz; }

		void Clear()
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i].~Ty();
		}

		const Ty& At(size_t index) const { return Buffer[index]; }
		Ty& At(size_t index) { return Buffer[index]; }

		Iterator begin() const
		{
			return Iterator(Buffer);
		}
		Iterator end() const
		{
			return Iterator(Buffer + Sz);
		}

		const Ty& operator [] (size_t index) const 
		{ 
			return Buffer[index]; 
		}
		Ty& operator [] (size_t index) 
		{ 
			return Buffer[index]; 
		}

	};
}

#endif