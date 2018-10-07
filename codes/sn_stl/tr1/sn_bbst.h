//------------------------------------------------------------------------------
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_TR1_SN_BBST_H__
#define __SN_STL_TR1_SN_BBST_H__

#include <sn_stl/sn_vector.h>
#include <cstring>
#include <algorithm>

namespace sn_std
{
	namespace tr1
	{
		/**
		BBST : Balanced Binary Search Tree 
		(AKA AVL (Adelson-Velskii and Landis) Tree)
		*/
		template <typename T>
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
					height = 0;
					std::memset(&element, 0, sizeof(T));
				}

				node* p_left;
				node* p_right;
				int32_t height;
				T element;
			};
		public:
			sn_bbst(int32_t capacity) :
				m_capacity(capacity),
				m_size(0),
				m_p_root(nullptr)
			{
				m_p_vec = new sn_vector<node* >(capacity);
				for (int i = 0; i < capacity; ++i)
				{
					m_p_vec->push_back(new node());
				}
			}

			~sn_bbst()
			{
				clear();
				for (int i = 0; i < m_capacity; ++i)
				{
					node* p_node = m_p_vec->back(); 
					delete p_node;
					m_p_vec->pop_back();
				}
				delete m_p_vec;
			}

			const T& find_min() const
			{
				return _find_min(m_p_root);
			}
			const T& find_max() const
			{
				return _find_max(m_p_root);
			}

			bool contains(const T& elem) const
			{
				return _contains(elem, m_p_root);
			}

			bool empty() const
			{

			}

			void insert(const T& elem)
			{
				_insert(elem, m_p_root);
			}

			void remove(const T& elem)
			{
				_remove(elem, m_p_root);
			}

			void clear()
			{
				_clear(m_p_root);
			}

		protected:
			bool _contains(const T& elem, node* p_node) const
			{
				if (nullptr == p_node)
				{
					return nullptr;
				}
				else if (elem < p_node->element)
				{
					return _contains(elem, p_node->p_left);
				}
				else if (elem > p_node->element)
				{
					return _contains(elem, p_node->p_right);
				}
				else
				{
					return true;
				}
			}

			void _insert(const T& elem, node*& p_node)
			{
				if (nullptr == p_node)
				{
					p_node = m_p_vec->back();
					p_node->reset();
					p_node->element = elem;
				}
				else if (elem < p_node->element)
				{
					_insert(elem, p_node->p_left);
				}
				else if (elem > p_node->element)
				{
					_insert(elem, p_node->p_right);
				}
				else
				{
					// exception
				}

				_balance(p_node);
			}

			void _remove(const T& elem, node*& p_node)
			{
				if (nullptr == p_node)
				{
					// exception
					return;
				}

				if (elem < p_node->element)
				{
					_remove(elem, p_node->p_left);
				}
				else if (elem > p_node->element)
				{
					_remove(elem, p_node->p_right);
				}
				// Because it passed abvoe two if statements,
				// it means this node is matched.
				// Below is for when having two children
				else if (
					(nullptr != p_node->p_left) &&
					(nullptr != p_node->p_right))
				{
					p_node->element = _find_min(p_node->p_right)->element;
					_remove(p_node->element, p_node->p_right);
				}
				// when it has only one children / no child
				// actually remove node in here
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
				}

				_balance(p_node);
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

			void _balance(node* p_node)
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
						_rotate_right(p_node);
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
						_rotate_left(p_node);
					}
				}

				p_node->height = std::max(_get_height(p_node->p_left), _get_height(p_node->p_right)) + 1;
			}

			void _rotate_left(node*& p2)
			{
				node* p1 = p2->p_left;
				p2->p_left = p1->p_right;
				p1->p_right = p2;
				p2->height = std::max(_get_height(p2->p_left), _get_height(p2->p_right)) + 1;
				p1->height = std::max(_get_height(p1->p_left), p2->height) + 1;
				p2 = p1;
			}

			void _rotate_right(node*& p2)
			{
				node* p1 = p2->p_right;
				p2->p_right = p1->p_left;
				p1->p_left = p2;
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

		protected:
			int32_t m_capacity;
			int32_t m_size;
			node* m_p_root;
			sn_vector<node*>* m_p_vec;
		};
	}
}

#endif // __SN_STL_TR1_SN_BBST_H__