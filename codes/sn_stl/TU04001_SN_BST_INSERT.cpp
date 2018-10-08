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
	sn_std::tr1::sn_bbst<int, int> bst(50);
	bst.insert(0, 1);
	bst.insert(4, 1);
	bst.insert(3, 1);
	bst.insert(6, 1);
	bst.insert(5, 1);
	bst.insert(2, 1);
	bst.insert(7, 1);
	bst.insert(8, 1);
	bst.insert(9, 1);
	bst.insert(11, 1);
	bst.contains(1);

	sn_std::tr1::sn_bbst<int, int>::const_iterator bstit = bst.begin();
	
	SATES_EQ(bstit.first, 0);
	++bstit;
	SATES_EQ (bstit.first, 2);
	++bstit;
	SATES_EQ(bstit.first, 3);
	++bstit;
	SATES_EQ(bstit.first, 4);
	++bstit;
	SATES_EQ(bstit.first, 5);
	++bstit;
	SATES_EQ(bstit.first, 6);
	++bstit;
	SATES_EQ(bstit.first, 7);
	++bstit;
	SATES_EQ(bstit.first, 8);
	++bstit;
	SATES_EQ(bstit.first, 9);
	++bstit;
	SATES_EQ(bstit.first, 11);

	bst.remove(5);
	bst.clear();

	std::map<int, int> my_map;

	my_map.emplace(0, 1);
	my_map.emplace(4, 2);
	my_map.emplace(3, 3);
	my_map.emplace(1, 4);
	std::pair<int, int> tmp;
	auto iter = my_map.begin();
	
	SATES_EQ(iter->first, 0);
	iter++;
	SATES_EQ(iter->first, 1);
	iter++;
	SATES_EQ(iter->first, 3);
	iter++;
	SATES_EQ(iter->first, 4);
}

SATES_TEST_TERMINATE(TU00200_SN_BST_INSERT)
{

}
