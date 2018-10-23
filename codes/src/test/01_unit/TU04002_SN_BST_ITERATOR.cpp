
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
#include <vector>

/** \addtogroup CODE
*  @{
*/
/** \addtogroup TESTCODE
*  @{
*/
/** \addtogroup T01_UNIT_CODE
*  @{
*/

/** \addtogroup TU04002_SN_BST_ITERATOR
*  @{
*/

/**
@see TU04002_SN_BST_ITERATOR.cpp
*/
SATES_TEST_INIT(TU04002_SN_BST_ITERATOR)
{
}

SATES_TEST_RUN(TU04002_SN_BST_ITERATOR)
{
	sn_std::tr1::sn_bbst<int, int> bst(256U);
	std::map<int, int> stdmap;

	for (int i = 100; i > 0; i = i - 10)
	{
		bst.emplace(i, i);
		stdmap.emplace(i, i);
	}


	SATES_EQ(bst.end(), bst.find(1));
	SATES_EQ(stdmap.end(), stdmap.find(1));

	SATES_EQ(stdmap.size(), bst.size());


	SATES_EQ(bst.begin(), bst.find(10));
	SATES_EQ(stdmap.begin(), stdmap.find(10));

	SATES_NE(bst.end(), bst.find(50));
	SATES_NE(stdmap.end(), stdmap.find(50));

	std::vector<int> bstvec;
	std::vector<int> stdvec;

	for (sn_std::tr1::sn_bbst<int, int>::iterator iter = bst.begin();
		iter != bst.end();
		++iter)
	{
		bstvec.push_back(iter->first);
	}

	for (std::map<int,int>::iterator iter = stdmap.begin();
		iter != stdmap.end();
		++iter)
	{
		stdvec.push_back(iter->first);
	}

	SATES_EQ(stdvec.size(), bstvec.size());

	for (size_t i = 0U; i < stdvec.size(); ++i)
	{
		SATES_EQ(stdvec.at(i), bstvec.at(i));
	}

	auto stditer = stdmap.end();
	stditer--;
	SATES_EQ(stdmap.find(100), stditer);

	auto bstiter = bst.end();
	bstiter--;
	SATES_EQ(bst.find(100), bstiter);

	bstvec.clear();
	stdvec.clear();

	stditer = stdmap.end();
	stditer--;
	while (stditer != stdmap.begin())
	{
		stdvec.push_back(stditer->first);
		stditer--;
	}

	bstiter = bst.end();
	bstiter--;
	while (bstiter != bst.begin())
	{
		bstvec.push_back(bstiter->first);
		bstiter--;
	}

	SATES_EQ(stdvec.size(), bstvec.size());

	for (size_t i = 0U; i < stdvec.size(); ++i)
	{
		SATES_EQ(stdvec.at(i), bstvec.at(i));
	}
}

SATES_TEST_TERMINATE(TU04002_SN_BST_ITERATOR)
{

}

/** @} */
/** @} */
/** @} */
/** @} */