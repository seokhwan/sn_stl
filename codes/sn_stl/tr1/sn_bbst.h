//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_TR1_SN_BBST_H__
#define __SN_STL_TR1_SN_BBST_H__

#include <sn_stl/sn_vector.h>
#include <utility>
#include <cstring>
#include <algorithm>

namespace sn_std
{
	namespace tr1
	{
		enum BBST_EXCEPTION
		{
			BBST_EXCEPTION_BEGIN = 4000,
			BBST_EXCEPTION_END
		};
		/**
		BBST : Balanced Binary Search Tree 
		(AKA AVL (Adelson-Velskii and Landis) Tree)
		*/
		template <typename key_t, typename elem_t>
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
					std::memset(&key, 0, sizeof(key_t));
					std::memset(&element, 0, sizeof(elem_t));
				}

				node* p_left;
				node* p_right;
				node* p_parent;
				int32_t height;
				key_t key;
				elem_t element;
			};
		public:
			////////////////////////////////////////
			// iterator def
			////////////////////////////////////////
			class const_iterator : public std::pair<key_t, elem_t>
			{
			public:
				const_iterator() : p_cur(nullptr), p_tree(nullptr) {}
				const_iterator(const node* p_node, const sn_bbst<key_t, elem_t>* ttree) : p_cur(p_node), p_tree(ttree) {}

				const_iterator operator++()
				{
					if (nullptr != p_cur->p_right)
					{
						p_cur = p_tree->_find_min(p_cur->p_right);
					}
					else
					{
						if (this->p_cur->p_parent->key > this->p_cur->key)
						{
							p_cur = p_cur->p_parent;
						}
						else
						{
							p_cur = p_cur->p_parent->p_parent;
						}
					}
					this->first = p_cur->key;
					this->second = p_cur->element;
					return (*this);
				}

			protected:
				
				const node* p_cur;

				const_iterator(node* p) : p_cur(p) {}
				const sn_bbst<key_t, elem_t>* p_tree;

				friend class sn_bbst<key_t, elem_t>;
			};

			sn_bbst(uint32_t capacity) :
				m_capacity(capacity),
				m_size(0),
				m_p_root(nullptr)
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
			}

			const_iterator begin() const
			{
				return const_iterator(find_min(), this);
			}

			const node* find_min() const
			{
				return _find_min(m_p_root);
			}
			const node* find_max() const
			{
				return _find_max(m_p_root);
			}

			bool contains(const key_t& keyval) const
			{
				return _contains(keyval, m_p_root);
			}

			bool empty() const
			{
				return (0U == m_size);
			}

			void insert(const key_t& keyval, const elem_t& val)
			{
				_insert(keyval, m_p_root, m_p_root, val);
			}

			void remove(const key_t& keyval)
			{
				_remove(keyval, m_p_root);
			}

			void clear()
			{
				_clear(m_p_root);
			}

		protected:
			bool _contains(const key_t& keyval, node* p_node) const
			{
				if (nullptr == p_node)
				{
					return nullptr;
				}
				else if (keyval < p_node->key)
				{
					return _contains(keyval, p_node->p_left);
				}
				else if (keyval > p_node->key)
				{
					return _contains(keyval, p_node->p_right);
				}
				else
				{
					return true;
				}
			}

			void _insert(const key_t& keyval, node* p_parent_val, node*& p_node, const elem_t& val)
			{
				if (nullptr == p_node)
				{
					p_node = m_p_vec->back();
					m_p_vec->pop_back();
					p_node->reset();
					p_node->key = keyval;
					p_node->p_parent = p_parent_val;
					p_node->element = val;
				}
				else if (keyval < p_node->key)
				{
					_insert(keyval, p_node, p_node->p_left, val);
				}
				else if (keyval > p_node->key)
				{
					_insert(keyval, p_node, p_node->p_right, val);
				}
				else
				{
					// exception
				}

				_balance(p_node);
			}

			void _remove(const key_t& keyval, node*& p_node)
			{
				if (nullptr == p_node)
				{
					// exception
					return;
				}

				if (keyval < p_node->key)
				{
					_remove(keyval, p_node->p_left);
				}
				else if (keyval > p_node->key)
				{
					_remove(keyval, p_node->p_right);
				}
				// Because it passed abvoe two if statements,
				// it means this node is matched.
				// Below is for when having two children
				else if (
					(nullptr != p_node->p_left) &&
					(nullptr != p_node->p_right))
				{
					p_node->key = _find_min(p_node->p_right)->key;
					_remove(p_node->key, p_node->p_right);
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

		protected:
			uint32_t m_capacity;
			uint32_t m_size;
			node* m_p_root;
			sn_vector<node*>* m_p_vec;
		};
	}
}

#endif // __SN_STL_TR1_SN_BBST_H__