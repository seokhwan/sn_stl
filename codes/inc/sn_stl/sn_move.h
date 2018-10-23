//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_MOVE_H__
#define __SN_STL_SN_MOVE_H__

#include <sn_stl/tr1/sn_exception.h>
#include <cstring>

namespace sn_std
{
    /** \addtogroup CODE
    *  @{
    */
    /** \addtogroup sn_std
    *  @{
    */
	template <typename T>
	void sn_swap(T& val1, T& val2)
	{
		T tmp = val1;
		val1 = val2;
		val2 = tmp;
	}
    /** @} */
    /** @} */
}

#endif // __SN_STL_SN_MOVE_H__
