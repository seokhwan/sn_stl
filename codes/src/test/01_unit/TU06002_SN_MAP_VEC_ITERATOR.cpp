
//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/tr1/sn_map_vec.h>

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

/** \addtogroup TU06002_SN_MAP_VEC_ITERATOR
*  @{
*/

/**
@see TU06002_SN_MAP_VEC_ITERATOR.cpp
*/
SATES_TEST_INIT(TU06002_SN_MAP_VEC_ITERATOR)
{
}

SATES_TEST_RUN(TU06002_SN_MAP_VEC_ITERATOR)
{
	sn_std::tr1::sn_map_vec<int, int> mine(256U);
	std::map<int, int> stdmap;

	for (int i = 100; i > 0; i = i - 10)
	{
		mine.emplace(i, i);
		stdmap.emplace(i, i);
	}


	SATES_EQ(mine.end(), mine.find(1));
	SATES_EQ(stdmap.end(), stdmap.find(1));

	SATES_EQ(stdmap.size(), mine.size());


	SATES_EQ(mine.begin(), mine.find(10));
	SATES_EQ(stdmap.begin(), stdmap.find(10));

	SATES_NE(mine.end(), mine.find(50));
	SATES_NE(stdmap.end(), stdmap.find(50));

	std::vector<int> minevec;
	std::vector<int> stdvec;

	for (sn_std::tr1::sn_map_vec<int, int>::iterator iter = mine.begin();
		iter != mine.end();
		++iter)
	{
		minevec.push_back(iter->first);
	}

	for (std::map<int,int>::iterator iter = stdmap.begin();
		iter != stdmap.end();
		++iter)
	{
		stdvec.push_back(iter->first);
	}

	SATES_EQ(stdvec.size(), minevec.size());

	for (size_t i = 0U; i < stdvec.size(); ++i)
	{
		SATES_EQ(stdvec.at(i), minevec.at(i));
	}

	auto stditer = stdmap.end();
	stditer--;
	SATES_EQ(stdmap.find(100), stditer);

	auto mineiter = mine.end();
	mineiter--;
	SATES_EQ(mine.find(100), mineiter);

	minevec.clear();
	stdvec.clear();

	stditer = stdmap.end();
	stditer--;
	while (stditer != stdmap.begin())
	{
		stdvec.push_back(stditer->first);
		stditer--;
	}

	mineiter = mine.end();
	mineiter--;
	while (mineiter != mine.begin())
	{
		minevec.push_back(mineiter->first);
		mineiter--;
	}

	SATES_EQ(stdvec.size(), minevec.size());

	for (size_t i = 0U; i < stdvec.size(); ++i)
	{
		SATES_EQ(stdvec.at(i), minevec.at(i));
	}
}

SATES_TEST_TERMINATE(TU06002_SN_MAP_VEC_ITERATOR)
{

}

/** @} */
/** @} */
/** @} */
/** @} */