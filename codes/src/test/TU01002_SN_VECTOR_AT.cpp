//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_vector.h>

#include <vector>

SATES_TEST_INIT(TU01002_SN_VECTOR_AT)
{

}

SATES_TEST_RUN(TU01002_SN_VECTOR_AT)
{
	std::vector<uint32_t> stdvec;
	sn_std::sn_vector<uint32_t> snvec(256U);

	for (uint32_t i = 0; i < 32U; ++i)
	{
		stdvec.push_back(i);
		snvec.push_back(i);
	}
	
	// The standard vector if unassigned index is accessed,
	// it makes a segmentation violation
	//stdvec.at(40U); 

	// exception handler shall be called
	snvec.at(40U);
}

SATES_TEST_TERMINATE(TU01002_SN_VECTOR_AT)
{

}
