//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_deque.h>
#include <deque>

SATES_TEST_INIT(TU02003_SN_DEQUE_PUSH_CLEAR)
{

}

SATES_TEST_RUN(TU02003_SN_DEQUE_PUSH_CLEAR)
{
	std::deque<int> stddeq;
	sn_std::sn_deque<int> sndeq(256U);

	stddeq.push_back(1);
	sndeq.push_back(1);

	SATES_EQ(sndeq.size(), stddeq.size());

	for (uint32_t i = 0; i < 32U; ++i)
	{
		stddeq.push_front(i);
		sndeq.push_front(i);
	}

	for (uint32_t i = 0; i < 32U; ++i)
	{
		stddeq.push_back(i);
		sndeq.push_back(i);
	}

	SATES_EQ(sndeq.size(), stddeq.size());
	SATES_EQ(sndeq.size(), 65U);
	SATES_EQ(stddeq.size(), 65U);

	for (uint32_t i = 0U; i < 65U; i++)
	{
		SATES_EQ(stddeq.at(i), sndeq.at(i));
	}

	stddeq.clear();
	sndeq.clear();

	SATES_EQ(sndeq.size(), 0U);
	SATES_EQ(stddeq.size(), 0U);
}

SATES_TEST_TERMINATE(TU02003_SN_DEQUE_PUSH_CLEAR)
{

}
