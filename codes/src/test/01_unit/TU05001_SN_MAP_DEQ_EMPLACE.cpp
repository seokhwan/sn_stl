
//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/tr1/sn_map_deq.h>
#include <iostream>
#include <map>

SATES_TEST_INIT(TU05001_SN_MAP_DEQ_EMPLACE)
{
}

SATES_TEST_RUN(TU05001_SN_MAP_DEQ_EMPLACE)
{
	sn_std::tr1::sn_map_deq<int, int> mine(256U);
	std::map<int, int> stdmap;

	for (int i = 100; i > 0; i = i - 10)
	{
		mine.emplace(i, i);
		stdmap.emplace(i, i);
	}


	SATES_EQ(mine.end(), mine.find(1));
	SATES_EQ(stdmap.end(), stdmap.find(1));


	mine.emplace(1, 1);
	stdmap.emplace(1, 1);

	SATES_EQ(mine.begin(), mine.find(1));
	SATES_EQ(stdmap.begin(), stdmap.find(1));

	auto mineresult = mine.emplace(300, 1);
	auto stdresult = stdmap.emplace(300, 1);

	SATES_NE(mine.end(), mine.find(300));
	SATES_NE(stdmap.end(), stdmap.find(300));

	mineresult = mine.emplace(300, 1);
	stdresult = stdmap.emplace(300, 1);

	SATES_EQ(mineresult.second, stdresult.second);

	SATES_EQ(mineresult.first, mine.find(300));
	SATES_EQ(stdresult.first, stdmap.find(300));

	SATES_EQ(mineresult.second, false);
	SATES_EQ(stdresult.second, false);

	SATES_EQ(stdmap.size(), mine.size());

	// for test right rotation

	for (int i = 100; i < 200; i = i + 10)
	{
		mine.emplace(i, i);
		stdmap.emplace(i, i);
	}

	SATES_EQ(stdmap.size(), mine.size());
}

SATES_TEST_TERMINATE(TU05001_SN_MAP_DEQ_EMPLACE)
{

}
