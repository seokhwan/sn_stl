//------------------------------------------------------------------------------
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_CIRCULAR_BUFFER_H__
#define __SN_STL_SN_CIRCULAR_BUFFER_H__

#include <sn_stl/sn_stl.h>

namespace sn_std
{
	namespace common
	{
		
		template <typename T>
		class sn_deque
		{
		public:
			sn_deque(int32_t capacity)
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

			int32_t size() const
			{
				return m_cur_size;
			}

			int32_t capacity() const
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

			void push_back(const T& data)
			{
				m_p_arr[m_tail] = data;
				
				_increment_size();
				m_tail++;
				if (m_tail > m_index_max)
				{
					m_tail = 0;
				}
				if (full())
				{
					m_front = m_tail;
				}
			}

			void pop_front()
			{
				if (m_size > 0)
				{
					if (m_index_max == m_front)
					{
						m_front = 0;
					}
					else
					{
						m_front++;
					}
					m_size--;
				}
				else
				{
					// exception
				}
			}

			void pop_back()
			{
				if (m_size > 0)
				{
					if (m_tail == 0)
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
					// exception
				}
			}

			T& front()
			{
				if (m_size < 1)
				{
					// exception
				}
				return (m_p_arr[m_front]);
			}

			T& at(int32_t index) const
			{
				if (m_size < 1)
				{
					// exception
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
				if (m_size < 1)
				{
					// exception
				}

				if (0 == m_tail)
				{
					return m_p_arr[m_index_max];
				}
				else
				{
					return (m_p_arr[m_tail - 1]);
				}
			}

			int32_t size() const
			{
				return m_size;
			}

			bool empty()
			{
				return (0 == m_size);
			}

			bool full()
			{
				return (m_capacity == m_size);
			}

			void clear()
			{
				while (this->size() > 0)
				{
					this->pop_front();
				}
			}

		protected:
			void _init()
			{
				m_front = 0;
				m_tail = 0;
				m_index_max = m_capacity - 1;
				m_size = 0;
				m_debugSegFaultGen = nullptr;
			}

			void _increment_size()
			{
				if (m_size < m_capacity)
				{
					m_size++;
				}
			}


		protected:
			int32_t m_tail;
			int32_t m_capacity;
			int32_t m_front;
			int32_t m_size;

			int32_t m_index_max;

			T* m_p_arr;
			bool m_is_allocated;
		};
	}
}

#endif // __SN_STL_SN_CIRCULAR_BUFFER_H__
