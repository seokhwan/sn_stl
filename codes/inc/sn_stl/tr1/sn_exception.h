//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_TR1_SN_EXCEPTION_H__
#define __SN_STL_TR1_SN_EXCEPTION_H__

#include <sn_stl/sn_stl.h>
#include <cstring>
#include <algorithm>

/*
VECTOR_EXCEPTION_BEGIN = 1000,
DEQUE_EXCEPTION_BEGIN = 2000,
LIST_EXCEPTION_BEGIN = 3000,
BBST_EXCEPTION_BEGIN = 4000,
MAP_EXCEPTION_BEGIN = 5000
*/

namespace sn_std
{
	namespace tr1
	{
		class sn_exception
		{
		public:
			typedef void(*handler_t)(void);
			static void handle(int32_t exception_code, const char* p_format, ...);
			static void register_handler(int32_t exception_code, handler_t p_func);
		};
	}
}

#endif // __SN_STL_TR1_SN_EXCEPTION_H__
