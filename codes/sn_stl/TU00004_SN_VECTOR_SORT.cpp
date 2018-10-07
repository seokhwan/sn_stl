//------------------------------------------------------------------------------
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_vector.h>

#include <iostream>

#include <algorithm>

SATES_TEST_INIT(TU00004_SN_VECTOR_SORT)
{

}

SATES_TEST_RUN(TU00004_SN_VECTOR_SORT)
{
	sn_std::sn_vector<int> snvec(256);

	for (int32_t i = 32; i >= 0; --i)
	{
		snvec.push_back(i);
	}

	int32_t cursize = snvec.size();

	std::sort(snvec.begin(), snvec.end());

	// check if size is changed
	SATES_EQ(cursize, snvec.size());
	
	for (int32_t i = 0; i <= 32; ++i)
	{
		SATES_EQ(i, snvec[i]);
	}
}

SATES_TEST_TERMINATE(TU00004_SN_VECTOR_SORT)
{

}
