//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
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
	enum LIST_EXCEPTION
	{
		LIST_EXCEPTION_BEGIN = 3000,
		LIST_EXCEPTION_FRONT_NO_ELEM,
		LIST_EXCEPTION_BACK_NO_ELEM,
		LIST_EXCEPTION_PUSH_FRONT_OVERFLOW,
		LIST_EXCEPTION_PUSH_BACK_OVERFLOW,
		LIST_EXCEPTION_POP_FRONT_NO_ELEM,
		LIST_EXCEPTION_POP_BACK_NO_ELEM,
		LIST_EXCEPTION_END
	};

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
		////////////////////////////////////////
		// iterator def
		////////////////////////////////////////
		class iterator
		{
		public:
			iterator() : p_cur(nullptr) {}

			T& operator*() const
			{
				return const_cast<T&>(p_cur->element);
			}

			iterator operator++()
			{
				this->p_cur = this->p_cur->p_next;
				return (*this);
			}

			iterator operator++(int)
			{
				iterator old = *this;
				++(*this);
				return old;
			}

			iterator operator--()
			{
				this->p_cur = this->p_cur->p_prev;
				return (*this);
			}

			iterator operator--(int)
			{
				const_iterator old = *this;
				--(*this);
				return old;
			}

			bool operator==(const iterator& rhs) const
			{
				return (rhs.p_cur == p_cur);
			}
			bool operator!=(const iterator& rhs) const
			{
				return (rhs.p_cur != p_cur);
			}

		protected:
			const node* p_cur;
			
			iterator(const node* p) : p_cur(p) {}
			friend class sn_list<T>;
		};


		class const_iterator : public iterator
		{
		public:
			const_iterator() {}

			const T& operator*() const
			{
				return iterator::operator*();
			}
			
			const_iterator operator--()
			{
				return const_iterator(iterator::operator--());
			}

			const_iterator operator--(int)
			{
				return const_iterator(iterator::operator--(0));
			}

			const_iterator operator++()
			{
				return const_iterator(iterator::operator++());
			}

			const_iterator operator++(int)
			{
				return const_iterator(iterator::operator++(0));
			}

		protected:
			const_iterator(const node* p) : iterator(p) {}
			const_iterator(const iterator iter) : iterator(iter) {}

			friend class sn_list<T>;
		};

	public:
		////////////////////////////////////////
		// constructor & destructor
		////////////////////////////////////////
		sn_list(uint32_t capacity) : 
			m_capacity(capacity),
			m_vecsize(capacity + 1U),
			m_size(0),
			m_p_head(nullptr),
			m_p_tail(nullptr)
		{
			m_p_vec = new sn_vector<node* >(m_vecsize);
			for (uint32_t i = 0; i < m_vecsize; ++i)
			{
				m_p_vec->push_back(new node());
			}
		}
		~sn_list()
		{
			clear();
			for (uint32_t i = 0; i < m_vecsize; ++i)
			{
				delete (m_p_vec->at(i));
			}
			delete m_p_vec;
		}

		////////////////////////////////////////
		// iterators
		////////////////////////////////////////
		iterator begin()
		{
			return m_p_head;
		}

		iterator end()
		{
			return m_p_tail;
		}

		const_iterator cbegin() const
		{
			return const_iterator(m_p_head);
		}

		const_iterator cend() const
		{
			return const_iterator(m_p_tail);
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

		bool empty() const
		{
			return (0 == m_size);
		}

		bool full() const
		{
			return (m_size == m_capacity);
		}

		////////////////////////////////////////
		// element access
		////////////////////////////////////////
		const T& front() const
		{
			if (0U == m_size)
			{
				tr1::sn_exception::handle(LIST_EXCEPTION_FRONT_NO_ELEM, "sn_list::front()");
			}

			return m_p_head->element;
		}

		const T& back() const
		{
			if (0U == m_size)
			{
				tr1::sn_exception::handle(LIST_EXCEPTION_BACK_NO_ELEM, "sn_list::back()");
			}

			return m_p_tail->p_prev->element;
		}

		////////////////////////////////////////
		// modifiers
		////////////////////////////////////////
		void push_front(const T& elem)
		{
			if (m_size < m_capacity)
			{
				if (nullptr == m_p_head)
				{
					push_back(elem);
				}
				else
				{
					m_size++;
					node* p_node = m_p_vec->back();
					p_node->reset();
					m_p_vec->pop_back();

					p_node->element = elem;

					m_p_head->p_prev = p_node;
					p_node->p_next = m_p_head;
					m_p_head = p_node;
				}
			}
			else
			{
				tr1::sn_exception::handle(LIST_EXCEPTION_PUSH_FRONT_OVERFLOW, "sn_list::push_front()");
			}
		}

		void push_back(const T& elem)
		{
			if (m_size < m_capacity)
			{
				m_size++;
				node* p_node = m_p_vec->back();
				p_node->reset();
				m_p_vec->pop_back();

				p_node->element = elem;

				if (nullptr == m_p_head)
				{
					m_p_head = p_node;
					m_p_tail = m_p_vec->back();
					m_p_vec->pop_back();

					m_p_tail->reset();

					m_p_head->p_next = m_p_tail;
					m_p_tail->p_prev = m_p_head;
				}

				else
				{
					m_p_tail->p_prev->p_next = p_node;
					p_node->p_prev = m_p_tail->p_prev;
					p_node->p_next = m_p_tail;
					m_p_tail->p_prev = p_node;
				}
			}
			else
			{
				tr1::sn_exception::handle(LIST_EXCEPTION_PUSH_BACK_OVERFLOW, "sn_list::push_back()");
			}
		}

		void pop_front()
		{
			if (0U == m_size)
			{
				tr1::sn_exception::handle(LIST_EXCEPTION_POP_FRONT_NO_ELEM, "sn_list::pop_front()");
			}
			else
			{
				if (1U == m_size)
				{
					m_p_vec->push_back(m_p_tail);
					m_p_vec->push_back(m_p_head);
				}
				else
				{
					m_p_vec->push_back(m_p_head);
					m_p_head = m_p_head->p_next;
					m_p_head->p_prev = nullptr;
				}
				--m_size;
			}
		}

		void pop_back()
		{
			if (0U == m_size)
			{
				tr1::sn_exception::handle(LIST_EXCEPTION_POP_BACK_NO_ELEM, "sn_list::pop_back()");
			}
			else
			{
				if (1U == m_size)
				{
					m_p_vec->push_back(m_p_tail);
					m_p_vec->push_back(m_p_head);
				}
				else
				{
					node* p_last = m_p_tail->p_prev;
					p_last->p_prev->p_next = m_p_tail;
					m_p_tail->p_prev = p_last->p_prev;
					m_p_vec->push_back(p_last);
				}
				--m_size;
			}
		}

		void clear()
		{
			uint32_t cursize = m_size;
			for (uint32_t i = 0; i < cursize; ++i)
			{
				pop_back();
			}
		}
		
	protected:
		uint32_t m_capacity;
		uint32_t m_vecsize;
		uint32_t m_size;
		node* m_p_head;
		node* m_p_tail;
		
		sn_vector<node*>* m_p_vec;
	};
}

#endif // __SN_STL_SN_LIST_H__