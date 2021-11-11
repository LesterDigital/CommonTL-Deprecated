#pragma once

#ifndef CTL_LIST_H
#define CTL_LIST_H

#include <ostream>

namespace ctl
{
	template<typename Ty>
	class List
	{
	public:
		struct Node
		{
			Ty Data;
			Node* Previous;
			Node* Next;

			Node(Ty value, Node* prev = nullptr, Node* next = nullptr)
				: Data(value), Previous(prev), Next(next) {}
		};
		class Iterator
		{
		public:
			Iterator(Node* node)
				: m_Node(node) {}

			Iterator& operator ++ () // prefix increment
			{
				m_Node = m_Node->Next;
				return *this;
			}
			Iterator operator ++ (int) // postfix increment
			{
				Iterator iterator = *this;
				m_Node = m_Node->Next;
				return iterator;
			}
			Iterator& operator -- () // prefix decrement
			{
				m_Node = m_Node->Previous;
				return *this;
			}
			Iterator operator -- (int) // postfix decrement
			{
				Iterator iterator = *this;
				m_Node = m_Node->Previous;
				return iterator;
			}

			Ty& operator *() const { return m_Node->Data; }

			bool operator == (const Iterator& other) { return m_Node == other.m_Node; }
			bool operator != (const Iterator& other) { return m_Node != other.m_Node; }

		private:
			Node* m_Node;
		};
	public:
		List() : m_Head(nullptr), m_Tail(nullptr), m_Size(0) {}
		~List()
		{
			Node* current = m_Head;

			while (current != nullptr)
			{
				if (current->Previous)
					delete current->Previous;
				current = current->Next;
			}
		}

		const Node* Head() const { return m_Head; }
		const Node* Foot() const { return m_Tail; }

		size_t Size() const { return m_Size; }

		void PushBack(const Ty& value)
		{
			if (m_Head == nullptr)
			{
				m_Head = new Node(value);
				m_Tail = m_Head;
			}
			else if (m_Tail->Previous == nullptr)
			{
				m_Tail = new Node(value, m_Head);
				m_Head->Next = m_Tail;
			}
			else
			{
				Node* tmp = m_Tail;
				m_Tail = new Node(value, tmp);

				tmp->Next = m_Tail;
			}

			m_Size++;
		}
		void PushFront(const Ty& value)
		{
			if (m_Head == nullptr)
			{
				m_Head = new Node(value);
				m_Tail = m_Head;
			}
			else if (m_Tail->Previous == nullptr)
			{
				m_Tail = new Node(value, m_Head);
				m_Head->Next = m_Tail;
			}
			else
			{
				Node* tmp = m_Head;
				m_Head = new Node(value, nullptr, tmp);
			}

			m_Size++;
		}
		void PopBack()
		{
			if (m_Head == nullptr) {}
			else if (m_Head->Next == nullptr) 
			{
				delete m_Head;
				m_Head = nullptr;
				m_Tail = nullptr;

				m_Size--;
			}
			else
			{
				Node* tmp = m_Tail;

				m_Tail = tmp->Previous;
				m_Tail->Next = nullptr;

				delete tmp;

				m_Size--;
			}

		}
		void PopFront()
		{
			if (m_Head == nullptr) {}
			else if (m_Head->Next == nullptr)
			{
				delete m_Head;
				m_Head = nullptr;
				m_Tail = nullptr;

				m_Size--;
			}
			else
			{
				Node* tmp = m_Head;

				m_Head = tmp->Next;
				m_Head->Previous = nullptr;

				delete tmp;

				m_Size--;
			}
		}

		void Insert(size_t index, const Ty& value)
		{
			size_t counter = 0;
			Node* current = m_Head;

			if (index == 0)
			{
				PushFront(value);
				m_Size++;
			}
			else
			{
				while (true)
				{
					if (counter == index && current->Next == nullptr)
						PushBack(value);
					else if (counter == index)
					{
						// Insert
						Node* tmp = current;
						Node* newNode = new Node(value);

						current->Previous->Next = newNode;
						newNode->Previous = current->Previous;
						newNode->Next = current;
						current->Previous = newNode;

						m_Size++;

						break;
					}
					else if (current == nullptr)
						break;

					counter++;
					current = current->Next;
				}
			}
		}

		void Sort()
		{
			bool isSorted = true;

			do
			{
				isSorted = true;
				Node* current = m_Head;

				while (current != nullptr)
				{
					if (current->Previous != nullptr)
					{
						if (current->Data < current->Previous->Data)
						{
							Ty tmp = current->Data;
							current->Data = current->Previous->Data;
							current->Previous->Data = tmp;

							isSorted = false;
						}
					}

					current = current->Next;
				}
			} while (!isSorted);
		}

		Iterator begin() const { return Iterator(m_Head); }
		Iterator end() const { return Iterator(m_Tail->Next); }

		friend std::ostream& operator << (std::ostream& stream, const List& list)
		{
			Node* current = m_Head;

			std::cout << "[ ";
			while (current != nullptr)
			{
				std::cout << current->Data << ", ";
				current = current->Next;
			}
			std::cout << ']' << std::endl;
		}

	private:
		Node* m_Head;
		Node* m_Tail;
		size_t m_Size;
	};


}

#endif