//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_MAP_H__
#define __SN_STL_SN_MAP_H__

#include <sn_stl/sn_vector.h>
#include <cstring>

namespace sn_std
{
	enum MAP_EXCEPTION
	{
		MAP_EXCEPTION_BEGIN = 5000,
		MAP_EXCEPTION_END
	};
	template <typename key, typename val>
	class sn_map
	{
	protected:
		class node
		{
			key k;
			val v;
		};
	public:
		sn_map(int32_t capacity) :
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
		~sn_map()
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

	protected:

	protected:
		int32_t m_size;
		node* m_p_front;
		int32_t m_capacity;
		sn_vector<node*>* m_p_vec;
	};
}

#endif // __SN_STL_SN_MAP_H__