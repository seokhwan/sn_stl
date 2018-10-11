//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#ifndef __SN_STL_SN_PAIR_H__
#define __SN_STL_SN_PAIR_H__

#include <sn_stl/tr1/sn_bbst.h>

namespace sn_std
{
	template <typename T1, typename T2>
	class sn_pair
	{
	public:
		T1 first;
		T2 second;
	};
}

#endif // __SN_STL_SN_PAIR_H__