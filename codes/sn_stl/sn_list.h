//------------------------------------------------------------------------------
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_LIST_H__
#define __SN_STL_SN_LIST_H__

#include <sn_stl/sn_vector.h>
#include <cstring>

namespace sn_std
{
	template <typename T>
	class sn_list
	{
	protected:
		class node
		{
		public:
			node()
			{
				reset();
			}

			void reset()
			{
				p_prev = nullptr;
				p_next = nullptr;
				std::memset(&element, 0, sizeof(T));
			}

			node* p_prev;
			node* p_next;
			T element;
		};
	public:
		sn_list(int32_t capacity) : 
			m_capacity(capacity),
			m_size(0),
			m_p_front(nullptr)
		{
			m_p_vec = new sn_vector<node* >(capacity);
			for (int i = 0; i < capacity; ++i)
			{
				m_p_vec->push_back(new node());
			}
		}
		~sn_list()
		{
			for (int32_t i = 0; i < m_capacity; ++i)
			{
			}
			delete m_p_vec;
		}

		int32_t size() const
		{
			return m_size;
		}

		int32_t capacity() const
		{
			return m_capacity;
		}

		void clear()
		{
		}

		bool empty() const
		{
			return (0 == m_size);
		}

		bool full() const
		{
			return (m_size == m_capacity);
		}

		void push_back(const T& elem)
		{
			node* p_node = m_p_vec->back();
			p_node->reset();
			m_p_vec->pop_back();

			p_node->element = elem;

			if (nullptr == m_p_front)
			{
				m_p_front = p_node;
			}
			else
			{
				node* p_tail = _get_tail();
				p_tail->p_next = p_node;
				p_node->p_prev = p_tail;
			}
		}

		void pop_back()
		{
		}

		void push_front(const T& elem)
		{
		}

		void pop_front()
		{

		}

		const T& back() const
		{
		}

		const T& front() const
		{
		}

		T& at(uint32_t idx)
		{
		}

		T& operator[] (uint32_t idx)
		{
			return this->at(idx);
		}

	protected:
		node* _get_tail()
		{
			if (nullptr == m_p_front)
			{
				return m_p_front;
			}
			else
			{
				node* p_node = m_p_front;
				while (nullptr != p_node->p_next)
				{
					p_node = p_node->p_next;
				}
				return p_node;
			}
		}

	protected:
		int32_t m_size;
		node* m_p_front;
		int32_t m_capacity;
		sn_vector<node*>* m_p_vec;
	};
}

#endif // __SN_STL_SN_LIST_H__