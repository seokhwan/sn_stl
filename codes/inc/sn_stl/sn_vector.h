//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------

#ifndef __SN_STL_SN_VECTOR_H__
#define __SN_STL_SN_VECTOR_H__

#include <sn_stl/tr1/sn_exception.h>

namespace sn_std
{
	enum VECTOR_EXCEPTION
	{
		VECTOR_EXCEPTION_BEGIN = 1000,
		VECTOR_EXCEPTION_PUSH_BACK_OVERFLOW,
		VECTOR_EXCEPTION_POP_BACK_NO_ELEM,
		VECTOR_EXCEPTION_AT_INDEX_OUT_OF_RANGE,
		VECTOR_EXCEPTION_END
	};

	template <typename T>
	class sn_vector
	{
	public:
		////////////////////////////////////////
		// iterator def
		////////////////////////////////////////
		typedef T* iterator;
		typedef const T* const_iterator;

		////////////////////////////////////////
		// constructors & destructor
		////////////////////////////////////////
		sn_vector(uint32_t vec_capacity) :
			m_capacity(vec_capacity),
			m_vecsize(vec_capacity + 1U),
			m_size(0U)
		{
			m_p_arr = new T[m_vecsize];
		}
		~sn_vector()
		{
			destroy();
		}

		////////////////////////////////////////
		// iterators
		////////////////////////////////////////
		iterator begin()
		{
			return &(m_p_arr[0U]);
		}

		iterator end()
		{
			return &(m_p_arr[m_size]);
		}

		const_iterator begin() const
		{
			return const_cast<sn_vector<T>*>(this)->begin();
		}

		const_iterator end() const
		{
			return const_cast<sn_vector<T>*>(this)->end();
		}

		////////////////////////////////////////
		// capacity
		////////////////////////////////////////
		uint32_t size() const
		{
			return m_size;
		}

		bool empty() const
		{
			return (0U == m_size);
		}

		uint32_t capacity() const
		{
			return m_capacity;
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
				for (uint32_t i = 0U; i < m_size; ++i)
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

		////////////////////////////////////////
		// element access
		////////////////////////////////////////
		T& front()
		{
			return m_p_arr[0U];
		}

		T& back()
		{
			return m_p_arr[m_size - 1U];
		}
		
		T& operator[] (uint32_t idx)
		{
			return this->at(idx);
		}

		T& at(uint32_t idx)
		{
			if (idx < m_size)
			{
				return m_p_arr[idx];
			}
			else
			{
				tr1::sn_exception::handle(VECTOR_EXCEPTION_AT_INDEX_OUT_OF_RANGE, "sn_vector::at()");
			}
			return m_p_arr[0U];
		}

		const T& front() const
		{
			return const_cast<sn_vector<T*>*>(this)->front();
		}

		const T& back() const
		{
			return const_cast<sn_vector<T*>*>(this)->back();
		}

		const T& operator[] (uint32_t idx) const
		{
			return const_cast<sn_vector<T*>*>(this)->at(idx);
		}

		const T& at(uint32_t idx) const
		{
			return const_cast<sn_vector<T*>*>(this)->at(idx);;
		}

		////////////////////////////////////////
		// modifiers
		////////////////////////////////////////
		void push_back(const T& val)
		{
			if (m_size < m_capacity)
			{
				m_p_arr[m_size] = val;
				++m_size;
			}
			else
			{
				tr1::sn_exception::handle(VECTOR_EXCEPTION_PUSH_BACK_OVERFLOW, "sn_vec::push_back()");
			}
		}

		void pop_back()
		{
			if (m_size > 0U)
			{
				--m_size;
			}
			else
			{
				tr1::sn_exception::handle(VECTOR_EXCEPTION_POP_BACK_NO_ELEM, "sn_vec::pop_back()");
			}
		}

		void clear()
		{
			m_size = 0U;
		}

	
	protected:
		void destroy()
		{
			if (nullptr != m_p_arr)
			{
				delete[] m_p_arr;
				m_size = 0U;
				m_capacity = 0U;
			}
		}

	protected:
		uint32_t m_capacity;
		uint32_t m_vecsize;
		uint32_t m_size;
		T* m_p_arr;
	};
}

#endif // __SN_STL_SN_VECTOR_H__