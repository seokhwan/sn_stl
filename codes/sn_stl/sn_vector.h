//------------------------------------------------------------------------------
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------

#ifndef __SN_STL_SN_VECTOR_H__
#define __SN_STL_SN_VECTOR_H__

#include <sn_stl/sn_stl.h>

namespace sn_std
{
	template <typename T>
	class sn_vector
	{
	public:
		sn_vector(uint32_t vec_capacity)
		{
			m_p_arr = new T[vec_capacity];
			m_capacity = vec_capacity;
			m_size = 0;
		}
		~sn_vector()
		{
			destroy();
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
			m_size = 0;
		}

		bool empty() const
		{
			return (0 == m_size);
		}

		void push_back(const T& val)
		{
			m_p_arr[m_size] = val;
			++m_size;
		}

		void pop_back()
		{
			if (m_size > 0)
			{
				--m_size;
			}
		}

		const T& back() const
		{
			return m_p_arr[m_size];
		}

		const T& front() const
		{
			return m_p_arr[0];
		}

		T& at(uint32_t idx)
		{
			if (idx < m_size)
			{
				return m_p_arr[idx];
			}
			else
			{
				// elegant way to make an error necessary
			}
		}

		T& operator[] (uint32_t idx)
		{
			return this->at(idx);
		}

		void reserve(uint32_t new_capacity)
		{
			// run if new_capacity  is bigger than current capacity
			// otherwise, do nothing
			if (new_capacity > m_capacity)
			{
				// - make a new array
				T* new_arr = new T[new_capacity];

				// - backup all data
				for (uint32_t i = 0; i < m_size; i++)
				{
					new_arr[i] = m_p_arr[i];
				}
				uint32_t cursize = m_size;

				// - destroy current array
				destroy();

				// replace it with new values
				m_p_arr = new_arr;
				m_capacity = new_capacity;
				m_size = cursize;
			}
		}


		typedef T* iterator;
		typedef const T& const_iterator;

		iterator begin()
		{
			return &(m_p_arr[0]);
		}

		const_iterator begin() const
		{
			return const_cast<sn_vector<T>*>(this)->begin();
		}

		iterator end()
		{
			return &(m_p_arr[m_size]);
		}

		const_iterator end() const
		{
			return const_cast<sn_vector<T>*>(this)->end();
		}
	
	protected:
		void destroy()
		{
			if (nullptr != m_p_arr)
			{
				delete[] m_p_arr;
				m_size = 0;
				m_capacity = 0;
			}
		}

	protected:
		T* m_p_arr;
		int32_t m_size;
		int32_t m_capacity;
	};
}

#endif // __SN_STL_SN_VECTOR_H__