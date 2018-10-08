//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/tr1/sn_bbst.h>

SATES_TEST_INIT(TU00200_SN_BST_INSERT)
{
}

SATES_TEST_RUN(TU00200_SN_BST_INSERT)
{
	sn_std::tr1::sn_bbst<int> bst(50);
	bst.insert(1);
	bst.contains(1);

	bst.remove(5);
	bst.clear();

}

SATES_TEST_TERMINATE(TU00200_SN_BST_INSERT)
{

}
