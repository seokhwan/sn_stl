//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_vector.h>
#include <vector>

SATES_TEST_INIT(TU01001_SN_VECTOR_PUSH_BACK)
{

}

SATES_TEST_RUN(TU01001_SN_VECTOR_PUSH_BACK)
{
	std::vector<int> stdvec;
	sn_std::sn_vector<int> snvec(256U);

	stdvec.push_back(1);
	snvec.push_back(1);

	SATES_EQ(snvec.size(), stdvec.size());

	for (uint32_t i = 0; i < 32U; ++i)
	{
		stdvec.push_back(i);
		snvec.push_back(i);
	}

	SATES_EQ(snvec.size(), stdvec.size());
	SATES_EQ(snvec.size(), 33U);
	SATES_EQ(stdvec.size(), 33U);

	for (uint32_t i = 0U; i < 33U; i++)
	{
		SATES_EQ(stdvec.at(i), snvec.at(i));
	}
}

SATES_TEST_TERMINATE(TU01001_SN_VECTOR_PUSH_BACK)
{

}
