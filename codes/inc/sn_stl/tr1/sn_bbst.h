//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_TR1_SN_BBST_H__
#define __SN_STL_TR1_SN_BBST_H__

#include <sn_stl/sn_vector.h>
#include <sn_stl/sn_pair.h>
#include <utility>
#include <cstring>
#include <algorithm>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

namespace sn_std
{
	namespace tr1
	{
        /** \addtogroup CODE
        *  @{
        */
        /** \addtogroup sn_std
        *  @{
        */
        /** \addtogroup tr1
        *  @{
        */

		enum BBST_EXCEPTION
		{
			BBST_EXCEPTION_BEGIN = 4000,
			BBST_EXCEPTION_END
		};
		/**
		BBST : Balanced Binary Search Tree 
		(AKA AVL (Adelson-Velskii and Landis) Tree)
		*/
		template <typename key_t, typename val_t>
		class sn_bbst
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
					p_left = nullptr;
					p_right = nullptr;
					p_parent = nullptr;
					height = 0;
					std::memset(&elem, 0, sizeof(sn_std::sn_pair<key_t, val_t>));
				}

				node* p_left;
				node* p_right;
				node* p_parent;
				int32_t height;
				sn_std::sn_pair<key_t, val_t> elem;
			};
		public:
			////////////////////////////////////////
			// iterator def
			////////////////////////////////////////
			class iterator
			{
			public:
				iterator() : p_cur(nullptr), p_tree(nullptr) {}
				iterator(const iterator& rhs) : p_cur(rhs.p_cur), p_tree(rhs.p_tree) {}

				iterator operator++()
				{
					p_cur = p_tree->_iterator_plus_plus(p_cur);
					return (*this);
				}

				iterator operator++(int)
				{
					iterator old = *this;
					operator++();
					return old;
				}

				iterator operator--()
				{
					p_cur = p_tree->_iterator_minus_minus(p_cur);
					return (*this);
				}

				iterator operator--(int)
				{
					iterator old = *this;
					operator--();
					return old;
				}

				bool operator==(const iterator rhs)
				{
					return (this->p_cur == rhs.p_cur) && (this->p_tree == rhs.p_tree);
				}

				bool operator!=(const iterator rhs)
				{
					return (!this->operator==(rhs));
				}

				sn_pair<key_t, val_t>* operator->() const
				{
					return const_cast<sn_pair<key_t, val_t>*>(&(p_cur->elem));
				}

			protected:
				const node* p_cur;
				const sn_bbst<key_t, val_t>* p_tree;
				iterator(const node* p_node, const sn_bbst<key_t, val_t>* p_tree_ptr) : p_cur(p_node), p_tree(p_tree_ptr) {}
				friend class sn_bbst<key_t, val_t>;
			};

			class const_iterator: public iterator
			{
			public:
				const_iterator() : iterator() {}

			protected:
				const_iterator(iterator iter) : iterator(iter) {}
				const_iterator(const node* p_node, const sn_bbst<key_t, val_t>* p_tree_ptr) : iterator(p_node, p_tree_ptr) {}
				friend class sn_bbst<key_t, val_t>;
			};

			////////////////////////////////////////
			// constructor & destructor
			////////////////////////////////////////
			sn_bbst(uint32_t capacity) :
				m_capacity(capacity),
				m_size(0U),
				m_p_root(nullptr),
				m_iter_end(new node(), this),
				m_iter_max(nullptr, this),
				m_iter_min(nullptr, this)
			{
				m_p_vec = new sn_vector<node* >(capacity);
				for (uint32_t i = 0U; i < capacity; ++i)
				{
					m_p_vec->push_back(new node());
				}
			}

			~sn_bbst()
			{
				clear();
				for (uint32_t i = 0U; i < m_capacity; ++i)
				{
					node* p_node = m_p_vec->back(); 
					delete p_node;
					m_p_vec->pop_back();
				}
				delete m_p_vec;

				delete m_iter_end.p_cur;
			}

			////////////////////////////////////////
			// iterators
			////////////////////////////////////////
			const_iterator cbegin() const
			{
				return const_iterator(m_iter_min);
			}

			const_iterator cend() const
			{
				return const_iterator(m_iter_end);
			}

			iterator begin()
			{
				return iterator(m_iter_min);
			}

			iterator end()
			{
				return m_iter_end;
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
				return (0U == m_size);
			}

			////////////////////////////////////////
			// element access
			////////////////////////////////////////


			////////////////////////////////////////
			// Lookup
			////////////////////////////////////////
			const_iterator find(const key_t& keyval) const
			{
				return const_iterator(_find(keyval, m_p_root));
			}

			iterator find(const key_t& keyval)
			{
				return _find(keyval, m_p_root);
			}

			////////////////////////////////////////
			// modifiers
			////////////////////////////////////////
			sn_pair<iterator, bool> emplace(const key_t& keyval, const val_t& val)
			{
				return _emplace(keyval, m_p_root, m_p_root, val);
			}

			uint32_t erase(const key_t& keyval)
			{
				return _erase(keyval, m_p_root);
			}

			void clear()
			{
				_clear(m_p_root);
				m_p_root = nullptr;
			}

		protected:
			iterator _find(const key_t& keyval, node* p_node) const
			{
				iterator retval;
				if (nullptr == p_node)
				{
					retval = m_iter_end;
				}
				else if (keyval < p_node->elem.first)
				{
					retval = _find(keyval, p_node->p_left);
				}
				else if (keyval > p_node->elem.first)
				{
					retval = _find(keyval, p_node->p_right);
				}
				else
				{
					retval.p_cur = p_node;
					retval.p_tree = this;
					return retval;
				}
				return retval;
			}

			sn_pair<iterator, bool> _emplace(const key_t& keyval, node* p_parent_val, node*& p_node, const val_t& val)
			{
				sn_pair<iterator, bool> retval;
				if (nullptr == p_node)
				{
					m_size++;
					p_node = m_p_vec->back();
					m_p_vec->pop_back();
					p_node->reset();
					p_node->p_parent = p_parent_val;
					p_node->elem.second = val;
					p_node->elem.first = keyval;
					iterator iter(p_node, this);
					retval.first = iter;
					retval.second = true;
				}
				else if (keyval < p_node->elem.first)
				{
					retval = _emplace(keyval, p_node, p_node->p_left, val);
				}
				else if (keyval > p_node->elem.first)
				{
					retval = _emplace(keyval, p_node, p_node->p_right, val);
				}
				else
				{
					iterator iter(p_node, this);
					retval.first = iter;
					retval.second = false;
				}

				if (retval.second)
				{
					_balance(p_node);
				}
				return retval;
			}

			uint32_t _erase(const key_t& keyval, node*& p_node)
			{
				uint32_t retval = 0U;
				if (nullptr != p_node)
				{
					if (keyval < p_node->elem.first)
					{
						retval = _erase(keyval, p_node->p_left);
					}
					else if (keyval > p_node->elem.first)
					{
						retval = _erase(keyval, p_node->p_right);
					}
					// Because it passed abvoe two if statements,
					// it means this node is matched.
					// Below is for when having two children
					else if (
						(nullptr != p_node->p_left) &&
						(nullptr != p_node->p_right))
					{
						p_node->elem.first = _find_min(p_node->p_right)->elem.first;
						retval = _erase(p_node->elem.first, p_node->p_right);
					}
					// when it has only one child / no child
					// remove the node in here
					else
					{
						node* p_old = p_node;
						if (nullptr != p_node->p_left)
						{
							p_node = p_node->p_left;
						}
						else
						{
							p_node = p_node->p_right;
						}
						p_old->reset();
						m_p_vec->push_back(p_old);
						retval = 1U;
					}

					_balance(p_node);
				}
				return retval;
			}

			void _clear(node*& p_node)
			{
				if (nullptr != p_node)
				{
					_clear(p_node->p_left);
					_clear(p_node->p_right);
					p_node->reset();
					m_p_vec->push_back(p_node);
				}
			}

			node* _find_min(node* p_node) const
			{
				if (nullptr != p_node)
				{
					while (nullptr != p_node->p_left)
					{
						p_node = p_node->p_left;
					}
				}
				return p_node;

				//////////////////////////////
				// recursive solution : 
				//////////////////////////////
				//if (nullptr == p_node)
				//{
				//	return nullptr;
				//}
				//if (nullptr == p_node->p_left)
				//{
				//	return p_node;
				//}
				//return find_min(p_node->left);
			}

			node* _find_max(node* p_node) const
			{
				if (nullptr != p_node)
				{
					while (nullptr != p_node->p_right)
					{
						p_node = p_node->p_right;
					}
				}
				return p_node;
			}

			void _balance(node*& p_node)
			{
				static const int32_t ALLOWED_IMBALANCE = 1;
				if (nullptr == p_node)
				{
					return;
				}

				// if left is nullptr,
				// it cannot be bigger than 0.
				// so, doesn't need to check nullptr
				if ((_get_height(p_node->p_left) - _get_height(p_node->p_right)) > ALLOWED_IMBALANCE)
				{
					if (_get_height(p_node->p_left->p_left) >= _get_height(p_node->p_left->p_right))
					{
						_rotate_left(p_node);
					}
					else
					{
						_double_rotate_left(p_node);
					}
				}
				else if ((_get_height(p_node->p_right) - _get_height(p_node->p_left)) > ALLOWED_IMBALANCE)
				{
					if (_get_height(p_node->p_right->p_right) >= _get_height(p_node->p_right->p_left))
					{
						_rotate_right(p_node);
					}
					else
					{
						_double_rotate_right(p_node);
					}
				}

				p_node->height = std::max(_get_height(p_node->p_left), _get_height(p_node->p_right)) + 1;
				m_iter_max.p_cur = _find_max(m_p_root);
				m_iter_min.p_cur = _find_min(m_p_root);
			}

			void _rotate_left(node*& p2)
			{
				node* p1 = p2->p_left;
				p2->p_left = p1->p_right;
				if (nullptr != p1->p_right)
				{
					p1->p_right->p_parent = p2;
				}

				p1->p_right = p2;
				p1->p_parent = p2->p_parent;
				p2->p_parent = p1;

				p2->height = std::max(_get_height(p2->p_left), _get_height(p2->p_right)) + 1;
				p1->height = std::max(_get_height(p1->p_left), p2->height) + 1;
				p2 = p1;
			}

			void _rotate_right(node*& p2)
			{
				node* p1 = p2->p_right;
				p2->p_right = p1->p_left;
				if (nullptr != p1->p_left)
				{
					p1->p_left->p_parent = p2;
				}

				p1->p_left = p2;
				p1->p_parent = p2->p_parent;
				p2->p_parent = p1;

				p2->height = std::max(_get_height(p2->p_right), _get_height(p2->p_left)) + 1;
				p1->height = std::max(_get_height(p1->p_right), p2->height) + 1;
				p2 = p1;
			}

			void _double_rotate_left(node*& p3)
			{
				_rotate_right(p3->p_left);
				_rotate_left(p3);
			}

			void _double_rotate_right(node*& p3)
			{
				_rotate_left(p3->p_right);
				_rotate_right(p3);
			}

			int32_t _get_height(node* p_node)
			{
				if (nullptr == p_node)
				{
					return -1;
				}
				else
				{
					return p_node->height;
				}
			}

			const node* _iterator_minus_minus(const node* p_node) const
			{
				const node* retval = m_iter_min.p_cur;

				if (p_node != m_iter_min.p_cur)
				{
					if (p_node == m_iter_end.p_cur)
					{
						retval = m_iter_max.p_cur;
					}
					else if (nullptr != p_node->p_left)
					{
						retval = _find_max(p_node->p_left);
					}
					else
					{
						if (p_node->p_parent->elem.first < p_node->elem.first)
						{
							retval = p_node->p_parent;
						}
						else
						{
							node* p_parent = p_node->p_parent->p_parent;
							while (p_node->elem.first < p_parent->elem.first)
							{
								p_parent = p_parent->p_parent;
							}
							retval = p_parent;
						}
					}
				}
				else
				{
					// exception
				}

				return retval;
			}

			const node* _iterator_plus_plus(const node* p_node) const
			{
				const node* retval = m_iter_end.p_cur;
				if (p_node != m_iter_end.p_cur)
				{
					if (p_node == m_iter_max.p_cur)
					{
						retval = m_iter_end.p_cur;
					}
					else if (nullptr != p_node->p_right)
					{
						retval = _find_min(p_node->p_right);
					}
					else
					{
						if (p_node->p_parent->elem.first > p_node->elem.first)
						{
							retval = p_node->p_parent;
						}
						else
						{
							node* p_parent = p_node->p_parent->p_parent;
							while (p_node->elem.first > p_parent->elem.first)
							{
								p_parent = p_parent->p_parent;
							}
							retval = p_parent;
						}
					}
				}
				else
				{
					// exception
				}
				return retval;
			}

		protected:
			uint32_t m_capacity;
			uint32_t m_size;
			node* m_p_root;
			iterator m_iter_end;
			iterator m_iter_max;
			iterator m_iter_min;
			sn_vector<node*>* m_p_vec;
		};
        /** @} */
        /** @} */
        /** @} */
	}
}

#endif // __SN_STL_TR1_SN_BBST_H__