//------------------------------------------------------------------------------
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_list.h>

SATES_TEST_INIT(TU00100_SN_LIST_PUSH_BACK)
{

}

SATES_TEST_RUN(TU00100_SN_LIST_PUSH_BACK)
{
	sn_std::sn_list<int> mylist(200);
	mylist.push_back(50);

}

SATES_TEST_TERMINATE(TU00100_SN_LIST_PUSH_BACK)
{

}
