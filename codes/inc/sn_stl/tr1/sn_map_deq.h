//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_TR1_SN_MAP_DEQUE_H__
#define __SN_STL_TR1_SN_MAP_DEQUE_H__

#include <sn_stl/sn_deque.h>
#include <sn_stl/sn_pair.h>
#include <sn_stl/sn_move.h>

namespace sn_std
{
	namespace tr1
	{
		template <typename key_t, typename val_t>
		class sn_map_deq
		{
		protected:
			typedef sn_deque<sn_pair<key_t, val_t> > deq_pair_t;

		public:
			////////////////////////////////////////
			// iterator def
			////////////////////////////////////////
			typedef deq_iterator<sn_pair<key_t, val_t> > iterator;
			typedef const_deq_iterator<sn_pair<key_t, val_t> > const_iterator;

			////////////////////////////////////////
			// constructors & destructor
			////////////////////////////////////////
			sn_map_deq(uint32_t capacity)
			{
				m_p_deq = new deq_pair_t(capacity);
			}
			~sn_map_deq()
			{
				delete m_p_deq;
			}

			////////////////////////////////////////
			// iterators
			////////////////////////////////////////
			//const_iterator cbegin() const
			//{	
			//	return m_p_deq->cbegin();
			//}

			//const_iterator cend() const
			//{
			//	return m_p_deq->cend();
			//}

			iterator begin()
			{
				return m_p_deq->begin();
			}

			iterator end()
			{
				return m_p_deq->end();
			}

			////////////////////////////////////////
			// capacity
			////////////////////////////////////////
			uint32_t size() const
			{
				return m_p_deq->size();
			}

			uint32_t capacity() const
			{
				return m_p_deq->capacity();
			}

			bool empty() const
			{
				return m_p_deq->empty();
			}

			////////////////////////////////////////
			// Lookup
			////////////////////////////////////////
			const_iterator find(const key_t& keyval) const
			{
				const_cast<sn_map_deq<key_t, val_t>*>(this)->find(keyval);
			}

			iterator find(const key_t& keyval)
			{
				uint32_t idx = _find_idx(keyval, 0U, m_p_deq->size());
				if (keyval == (*m_p_deq)[idx].first)
				{
					return iterator(idx, m_p_deq);
				}
				else
				{
					return m_p_deq->end();
				}
			}

			////////////////////////////////////////
			// modifiers
			////////////////////////////////////////
			sn_pair<iterator, bool> emplace(const key_t& key, const val_t& val)
			{
				if (m_p_deq->empty())
				{
					m_p_deq->push_back(sn_pair<key_t, val_t>(key, val));
					return sn_pair<iterator, bool>(m_p_deq->begin(), true);
				}

				if (m_p_deq->back().first < key)
				{
					m_p_deq->push_back(sn_pair<key_t, val_t>(key, val));
					// return back() iterator
					return sn_pair<iterator, bool>(iterator(m_p_deq->size() - 1U, m_p_deq), true);
				}

				if (m_p_deq->front().first > key)
				{
					m_p_deq->push_front(sn_pair<key_t, val_t>(key, val));
					// return front() iterator
					return sn_pair<iterator, bool>(iterator(0U, m_p_deq), true);
				}

				uint32_t idx = _find_idx(key, 0U, m_p_deq->size());
				if ((*m_p_deq)[idx].first != key)
				{
					sn_pair<key_t, val_t> tmp;
					uint32_t mid_idx = m_p_deq->size() / 2U;
					if (mid_idx > idx)
					{
						m_p_deq->push_front(sn_pair<key_t, val_t>(key, val));
						for (uint32_t i = 0U;
							i < idx;
							++i)
						{
							//sn_std::sn_swap((*m_p_deq)[i], (*m_p_deq)[i + 1U]);
							tmp = (*m_p_deq)[i];
							(*m_p_deq)[i] = (*m_p_deq)[i + 1U];
							(*m_p_deq)[i + 1U] = tmp;
						}
					}
					else
					{
						m_p_deq->push_back(sn_pair<key_t, val_t>(key, val));
						for (uint32_t i = (m_p_deq->size() - 1U);
							i > idx;
							--i)
						{
							//sn_std::sn_swap((*m_p_deq)[i], (*m_p_deq)[i - 1U]);
							tmp = (*m_p_deq)[i];
							(*m_p_deq)[i] = (*m_p_deq)[i - 1U];
							(*m_p_deq)[i - 1U] = tmp;
						}
						return sn_pair<iterator, bool>(iterator(idx, m_p_deq), true);
					}
				}
				else
				{
					return sn_pair<iterator, bool>(iterator(idx, m_p_deq), false);
				}

				return sn_pair<iterator, bool>(m_p_deq->end(), false);
			}


			uint32_t erase(const key_t& keyval)
			{

			}

			void clear()
			{
				m_p_deq->clear();
			}

		public:
			uint32_t _find_idx(const key_t& key, uint32_t start_idx, uint32_t end_idx)
			{
				if ((end_idx - start_idx) <= 1U)
				{
					if (key == (*m_p_deq)[start_idx].first)
					{
						return start_idx;
					}
					else
					{
						return end_idx;
					}
				}

				uint32_t mid_idx = (start_idx + end_idx) / 2U;
				if (key < (*m_p_deq)[mid_idx].first)
				{
					return _find_idx(key, start_idx, mid_idx);
				}
				return _find_idx(key, mid_idx, end_idx);
			} 
		protected:
			deq_pair_t* m_p_deq;
		};
	}
}

#endif // __SN_STL_TR1_SN_MAP_DEQUE_H__