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
		DEQUE_EXCEPTION_PUSH_FRONT_OVERFLOW,
		DEQUE_EXCEPTION_PUSH_BACK_OVERFLOW,
		DEQUE_EXCEPTION_POP_FRONT_NO_ELEM,
		DEQUE_EXCEPTION_POP_BACK_NO_ELEM,
		DEQUE_EXCEPTION_FRONT_NO_ELEM,
		DEQUE_EXCEPTION_AT_NO_ELEM,
		DEQUE_EXCEPTION_BACK_NO_ELEM,
		DEQUE_EXCEPTION_END
	};

	template <typename T>
	class sn_deque
	{
	public:
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

		uint32_t capacity() const
		{
			return m_capacity;
		}

		void clear()
		{
			m_size = 0;
		}

		bool empty() const
		{
			return (0 == m_size);
		}
			
		void push_front(const T& data)
		{
			if (full())
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_PUSH_FRONT_OVERFLOW, "sn_deque::push_front()");
			}
			else
			{
				m_front--;
				if (-1 == m_front)
				{
					m_front = m_index_max;
				}

				m_p_arr[m_front] = data;

				_increment_size();
				if (full())
				{
					m_tail = m_front;
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
					m_front = m_tail;
				}
			}
		}

		void pop_front()
		{
			if (m_size > 0U)
			{
				if (m_index_max == m_front)
				{
					m_front = 0U;
				}
				else
				{
					m_front++;
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

		T& front()
		{
			if (m_size < 1U)
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_FRONT_NO_ELEM, "sn_deque::front()");
			}
			return (m_p_arr[m_front]);
		}

		T& at(uint32_t index) const
		{
			if (m_size < 1U)
			{
				tr1::sn_exception::handle(DEQUE_EXCEPTION_AT_NO_ELEM, "sn_deque::at()");
			}

			if (m_index_max >= m_front + index)
			{
				return (m_p_arr[m_front + index]);
			}
			else
			{
				return (m_p_arr[m_front + index - m_capacity]);
			}
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

		uint32_t size() const
		{
			return m_size;
		}

		bool empty()
		{
			return (0U == m_size);
		}

		bool full()
		{
			return (m_capacity == m_size);
		}

	protected:
		void _init()
		{
			m_front = 0;
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
		uint32_t m_front;
		uint32_t m_size;

		uint32_t m_index_max;

		T* m_p_arr;
		bool m_is_allocated;
	};
}

#endif // __SN_STL_SN_DEQUE_H__
