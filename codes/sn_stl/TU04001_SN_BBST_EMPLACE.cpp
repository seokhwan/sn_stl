//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/tr1/sn_bbst.h>

#include <map>
#include <iostream>



SATES_TEST_INIT(TU00200_SN_BST_INSERT)
{
}

SATES_TEST_RUN(TU00200_SN_BST_INSERT)
{
	sn_std::tr1::sn_bbst<int, int> bst(256U);
	std::map<int, int> stdmap;

	for (int i = 100; i > 0; i = i-10)
	{
		bst.emplace(i, i);
		stdmap.emplace(i, i);
	}

	
	SATES_EQ(bst.end(), bst.find(1));
	SATES_EQ(stdmap.end(), stdmap.find(1));


	bst.emplace(1, 1);
	stdmap.emplace(1, 1);

	SATES_EQ(bst.begin(), bst.find(1));
	SATES_EQ(stdmap.begin(), stdmap.find(1));

	bst.emplace(300, 1);
	stdmap.emplace(300, 1);

	SATES_NE(bst.end(), bst.find(300));
	SATES_NE(stdmap.end(), stdmap.find(300));

	auto bstresult = bst.emplace(300, 1);
	auto stdresult = stdmap.emplace(300, 1);

	SATES_EQ(bstresult.second, stdresult.second);

	SATES_EQ(bstresult.first, bst.end());
	SATES_EQ(stdresult.first, stdmap.end());

	SATES_EQ(stdmap.size(), bst.size());

	// for test right rotation

	for (int i = 100; i < 200; i = i + 10)
	{
		bst.emplace(i, i);
		stdmap.emplace(i, i);
	}

	SATES_EQ(stdmap.size(), bst.size());
}

SATES_TEST_TERMINATE(TU00200_SN_BST_INSERT)
{

}
