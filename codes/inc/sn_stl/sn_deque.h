//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_DEQUE_H__
#define __SN_STL_SN_DEQUE_H__

#include <sn_stl/tr1/sn_exception.h>

namespace sn_std
{
	enum DEQUE_EXCEPTION
	{
		DEQUE_EXCEPTION_BEGIN = 2000,
		DEQUE_EXCEPTION_FRONT_NO_ELEM,
		DEQUE_EXCEPTION_BACK_NO_ELEM,
		DEQUE_EXCEPTION_AT_NO_ELEM,
		DEQUE_EXCEPTION_PUSH_FRONT_OVERFLOW,
		DEQUE_EXCEPTION_PUSH_BACK_OVERFLOW,
		DEQUE_EXCEPTION_POP_FRONT_NO_ELEM,
		DEQUE_EXCEPTION_POP_BACK_NO_ELEM,
		DEQUE_EXCEPTION_END
	};

	template <typename T>
	class sn_deque
	{
	public:
		////////////////////////////////////////
		// iterator def
		////////////////////////////////////////
		typedef T* iterator;
		typedef const T& const_iterator;

		////////////////////////////////////////
		// constructors & destructor
		////////////////////////////////////////
		sn_deque(uint32_t capacity)
		{
			m_is_allocated = true;
			m_p_arr = new T[capacity];
			m_capacity = capacity;
			_init();
		}
		~sn_deque()
		{
			if (m_is_allocated)
			{
				delete[] m_p_arr;
			}
		}

		////////////////////////////////////////
		// iterators
		////////////////////////////////////////
		iterator begin()
		{
			return &(m_p_arr[m_head]);
		}

		iterator end()
		{
			return &(m_p_arr[m_tail]);
		}

		const_iterator cbegin() const
		{
			return const_cast<sn_deque<T>*>(this)->begin();
		}

		const_iterator cend() const
		{
			return const_cast<sn_deque<T>*>(this)->end();
		}

		////////////////////////////////////////
		// capacity
		////////////////////////////////////////
		uint32_t size() const
		{
			return m_size;
		}

		uint32_t capacity() const
		{
			return m_capacity;
		}

		bool empty()
		{
			return (0U == m_size);
		}

		bool full()
		{
			return (m_capacity == m_size);
		}

		////////////////////////////////////////
		// element access
		////////////////////////////////////////
		T& front()
		{
			if (m_size < 1U)
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_FRONT_NO_ELEM, "sn_deque::front()");
			}
			return (m_p_arr[m_head]);
		}

		T& back() const
		{
			if (m_size < 1U)
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_BACK_NO_ELEM, "sn_deque::back()");
			}

			if (0U == m_tail)
			{
				return m_p_arr[m_index_max];
			}
			else
			{
				return (m_p_arr[m_tail - 1U]);
			}
		}

		T& operator[] (uint32_t idx)
		{
			return this->at(idx);
		}

		T& at(uint32_t index) const
		{
			if (m_size < 1U)
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_AT_NO_ELEM, "sn_deque::at()");
			}

			if (m_index_max >= m_head + index)
			{
				return (m_p_arr[m_head + index]);
			}
			else
			{
				return (m_p_arr[m_head + index - m_capacity]);
			}
		}

		////////////////////////////////////////
		// modifiers
		////////////////////////////////////////
		void push_front(const T& data)
		{
			if (full())
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_PUSH_FRONT_OVERFLOW, "sn_deque::push_front()");
			}
			else
			{
				m_head--;
				if (-1 == m_head)
				{
					m_head = m_index_max;
				}

				m_p_arr[m_head] = data;

				_increment_size();
				if (full())
				{
					m_tail = m_head;
				}
			}
		}

		void push_back(const T& data)
		{
			if (full())
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_PUSH_BACK_OVERFLOW, "sn_deque::push_back()");
			}
			else
			{
				m_p_arr[m_tail] = data;

				_increment_size();
				m_tail++;
				if (m_tail > m_index_max)
				{
					m_tail = 0U;
				}
				if (full())
				{
					m_head = m_tail;
				}
			}
		}

		void pop_front()
		{
			if (m_size > 0U)
			{
				if (m_index_max == m_head)
				{
					m_head = 0U;
				}
				else
				{
					m_head++;
				}
				m_size--;
			}
			else
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_POP_FRONT_NO_ELEM, "sn_deque::pop_front()");
			}
		}

		void pop_back()
		{
			if (m_size > 0U)
			{
				if (m_tail == 0U)
				{
					m_tail = m_index_max;
				}
				else
				{
					m_tail--;
				}
				m_size--;
			}
			else
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_POP_BACK_NO_ELEM, "sn_deque::pop_back()");
			}
		}

		void clear()
		{
			m_size = 0;
		}


	protected:
		void _init()
		{
			m_head = 0;
			m_tail = 0;
			m_index_max = m_capacity - 1U;
			m_size = 0;
		}

		void _increment_size()
		{
			if (m_size < m_capacity)
			{
				m_size++;
			}
		}


	protected:
		uint32_t m_tail;
		uint32_t m_capacity;
		uint32_t m_head;
		uint32_t m_size;

		uint32_t m_index_max;

		T* m_p_arr;
		bool m_is_allocated;
	};
}

#endif // __SN_STL_SN_DEQUE_H__
