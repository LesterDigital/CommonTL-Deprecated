#pragma once

#ifndef CTL_QUEUE_H
#define CTL_QUEUE_H

#include "ctl/Allocator.h"

namespace ctl
{
	template<typename Ty>
	class Queue : private Allocator<Ty>
	{
	public:
		class Iterator
		{
		public:
			Iterator(Ty* pointer) { m_Ptr = pointer; }

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

			Ty& operator[](int index) const { return *(m_Ptr + index); }
			Ty* operator->() const { return m_Ptr; }
			Ty& operator*() const { return *m_Ptr; }

			bool operator==(const Iterator& other) const { return m_Ptr == other.m_Ptr; }
			bool operator!=(const Iterator& other) const { return m_Ptr != other.m_Ptr; }
		private:
			Ty* m_Ptr;
		};
	public:
		void Enqueue(const Ty& data)
		{
			this->PushBack(data);
		}
		void Dequeue()
		{
			this->PopFront();
		}

		Ty Back () const { return this->m_Buffer[this->m_Size - 1]; }
		Ty Front() const { return this->m_Buffer[0]; }

		size_t Length() const { return this->m_Size; }

		bool IsEmpty() const { return !(this->m_Size); }

		Iterator begin() const
		{
			return Iterator(this->m_Buffer);
		}		
		Iterator end() const
		{
			return Iterator(this->m_Buffer + this->m_Size);
		}
	};
}

#endif
