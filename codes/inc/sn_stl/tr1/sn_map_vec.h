//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_TR1_SN_MAP_VEC_H__
#define __SN_STL_TR1_SN_MAP_VEC_H__

#include <sn_stl/sn_vector.h>
#include <sn_stl/sn_pair.h>
#include <sn_stl/sn_move.h>

namespace sn_std
{
	namespace tr1
	{
		template <typename key_t, typename val_t>
		class sn_map_vec
		{
		protected:
			typedef sn_vector<sn_pair<key_t, val_t> > vec_pair_t;

		public:
			////////////////////////////////////////
			// iterator def
			////////////////////////////////////////
			typedef sn_pair<key_t, val_t>* iterator;
			typedef const sn_pair<key_t, val_t>* const_iterator;

			////////////////////////////////////////
			// constructors & destructor
			////////////////////////////////////////
			sn_map_vec(uint32_t capacity)
			{
				m_p_vec = new vec_pair_t(capacity);
			}
			~sn_map_vec()
			{
				delete m_p_vec;
			}

			////////////////////////////////////////
			// iterators
			////////////////////////////////////////
			const_iterator cbegin() const
			{
				return m_p_vec->cbegin();
			}

			const_iterator cend() const
			{
				return m_p_vec->cend();
			}

			iterator begin()
			{
				return m_p_vec->begin();
			}

			iterator end()
			{
				return m_p_vec->end();
			}

			////////////////////////////////////////
			// capacity
			////////////////////////////////////////
			uint32_t size() const
			{
				return m_p_vec->size();
			}

			uint32_t capacity() const
			{
				return m_p_vec->capacity();
			}

			bool empty() const
			{
				return m_p_vec->empty();
			}

			////////////////////////////////////////
			// Lookup
			////////////////////////////////////////
			const_iterator find(const key_t& keyval) const
			{
				const_cast<sn_map_vec<key_t, val_t>*>(this)->find(keyval);
			}

			iterator find(const key_t& keyval)
			{
				uint32_t idx = _find_idx(keyval, 0U, m_p_vec->size() - 1U);

				if (idx < m_p_vec->size())
				{
					if (keyval == (*m_p_vec)[idx].first)
					{
						return &((*m_p_vec)[idx]);
					}
				}
				return m_p_vec->end();
			}

			////////////////////////////////////////
			// modifiers
			////////////////////////////////////////
			sn_pair<iterator, bool> emplace(const key_t& key, const val_t& val)
			{
				if (m_p_vec->size() < 2U)
				{
					if (m_p_vec->empty())
					{
						m_p_vec->push_back(sn_pair<key_t, val_t>(key, val));
						return sn_pair<iterator, bool>(m_p_vec->begin(), true);
					}

					if (m_p_vec->size() == 1U)
					{
						if (key != (*m_p_vec)[0U].first)
						{
							m_p_vec->push_back(sn_pair<key_t, val_t>(key, val));
							uint32_t idx = 0U;
							if ((*m_p_vec)[0U].first > (*m_p_vec)[1U].first)
							{
								sn_swap((*m_p_vec)[0U], (*m_p_vec)[1U]);
								idx = 1U;
							}
							return sn_pair<iterator, bool>(&((*m_p_vec)[idx]), true);
						}
						else
						{
							return sn_pair<iterator, bool>(m_p_vec->begin(), false);
						}
					}
				}
				else
				{
					uint32_t idx = _find_idx(key, 0U, m_p_vec->size() - 1U);
					if (m_p_vec->size() == idx)
					{
						m_p_vec->push_back(sn_pair<key_t, val_t>(key, val));
					}
					else if ((*m_p_vec)[idx].first != key)
					{
						sn_pair<key_t, val_t> newelem(key, val);
						m_p_vec->push_back(newelem);
						memmove(&((*m_p_vec)[idx + 1U]), &((*m_p_vec)[idx]), sizeof(sn_pair<key_t, val_t>) * (m_p_vec->size() - idx));
						(*m_p_vec)[idx] = newelem;

						return sn_pair<iterator, bool>(&((*m_p_vec)[idx]), true);
					}
					else
					{
						return sn_pair<iterator, bool>(&((*m_p_vec)[idx]), false);
					}
				}
				
				return sn_pair<iterator, bool>(m_p_vec->end(), false);
			}

			uint32_t erase(const key_t& keyval)
			{

			}

			void clear()
			{
				m_p_vec->clear();
			}

		public:
			uint32_t _find_idx(const key_t& key, uint32_t start_idx, uint32_t end_idx)
			{
				if ((end_idx - start_idx) <= 1U)
				{
					if (key == (*m_p_vec)[start_idx].first)
					{
						return start_idx;
					}
					else if (key < (*m_p_vec)[start_idx].first)
					{
						return start_idx;
					}
					else if (key == (*m_p_vec)[end_idx].first)
					{
						return end_idx;
					}
					else if (key < (*m_p_vec)[end_idx].first)
					{
						return end_idx;
					}
					else
					{
						return end_idx + 1U;
					}
				}

				uint32_t mid_idx = (start_idx + end_idx) / 2U;
				if ((*m_p_vec)[mid_idx].first > key)
				{
					return _find_idx(key, start_idx, mid_idx);
				}
				else if ((*m_p_vec)[mid_idx].first < key)
				{
					return _find_idx(key, mid_idx, end_idx);
				}
				else
				{
					return mid_idx;
				}
			}
		protected:
			vec_pair_t* m_p_vec;
		};
	}
}

#endif // __SN_STL_TR1_SN_MAP_VEC_H__