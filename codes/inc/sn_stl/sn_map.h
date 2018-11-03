//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_MAP_H__
#define __SN_STL_SN_MAP_H__

#include <sn_stl/tr1/sn_map_deq.h>

namespace sn_std
{
    /** \addtogroup CODE
    *  @{
    */
    /** \addtogroup sn_std
    *  @{
    */

	template <typename key_t, typename val_t>
	using sn_map = sn_std::tr1::sn_map_deq<key_t, val_t>;
    /** @} */
    /** @} */
}

#endif // __SN_STL_SN_MAP_H__