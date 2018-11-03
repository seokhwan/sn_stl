//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_PAIR_H__
#define __SN_STL_SN_PAIR_H__

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

	template <typename T1, typename T2>
	class sn_pair
	{
	public:
		sn_pair(T1 t1, T2 t2) : first(t1), second(t2) {}
		sn_pair()
		{
			std::memset(&first, 0, sizeof(T1));
			std::memchr(&second, 0, sizeof(T2));
		}
		T1 first;
		T2 second;
	};

    /** @} */
    /** @} */
}

#endif // __SN_STL_SN_PAIR_H__
