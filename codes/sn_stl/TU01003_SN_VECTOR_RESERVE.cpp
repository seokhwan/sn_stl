//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------

#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_vector.h>

#include <vector>

SATES_TEST_INIT(TU01003_SN_VECTOR_RESERVE)
{

}

SATES_TEST_RUN(TU01003_SN_VECTOR_RESERVE)
{
	std::vector<uint32_t> stdvec;
	sn_std::sn_vector<uint32_t> snvec(2048U);
	stdvec.reserve(2048U);

	// compare size after 2048 items are assigned
	SATES_EQ(stdvec.capacity(), snvec.capacity());

	for (uint32_t i = 0; i < 32U; ++i)
	{
		stdvec.push_back(i);
		snvec.push_back(i);
	}

	// resizing to 1024 
	stdvec.reserve(1024U);
	snvec.reserve(1024U);

	// nothing happens, still the capacity is 2048
	SATES_EQ(stdvec.capacity(), 2048U);
	SATES_EQ(snvec.capacity(), 2048U);
	SATES_EQ(stdvec.capacity(), snvec.capacity());

	// items are also reserved
	for (uint32_t i = 0; i < 32U; ++i)
	{
		SATES_EQ(stdvec.at(i), snvec.at(i));
	}

	// let's do it to 4096
	stdvec.reserve(4096U);
	snvec.reserve(4096U);

	SATES_EQ(stdvec.capacity(), 4096U);
	SATES_EQ(snvec.capacity(), 4096U);
	SATES_EQ(stdvec.capacity(), snvec.capacity());

	// items are also reserved
	for (uint32_t i = 0; i < 32U; ++i)
	{
		SATES_EQ(stdvec.at(i), snvec.at(i));
	}
}

SATES_TEST_TERMINATE(TU01003_SN_VECTOR_RESERVE)
{

}
