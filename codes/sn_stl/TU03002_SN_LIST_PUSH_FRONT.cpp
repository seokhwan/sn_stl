//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------

#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_list.h>

#include <list>

SATES_TEST_INIT(TU03002_SN_LIST_PUSH_FRONT)
{

}

SATES_TEST_RUN(TU03002_SN_LIST_PUSH_FRONT)
{
	sn_std::sn_list<int> mylist(200);
	mylist.push_front(50);
	mylist.push_front(51);
	mylist.push_front(52);
	mylist.push_front(53);
	mylist.push_front(54);

	sn_std::sn_list<int>::iterator it = mylist.end();
	--it;
	SATES_EQ(*it, 50);
	--it;
	SATES_EQ(*it, 51);

	it--;
	SATES_EQ(*it, 52);

	--it;
	SATES_EQ(*it, 53);

	--it;
	SATES_EQ(*it, 54);

	SATES_EQ(it, mylist.begin());

	
	mylist.pop_front();
	it = mylist.end();
	--it;
	SATES_EQ(*it, 50);
	--it;
	SATES_EQ(*it, 51);

	--it;
	SATES_EQ(*it, 52);

	--it;
	SATES_EQ(*it, 53);

	SATES_EQ(it, mylist.begin());

	mylist.clear();

	std::list<int> stdlist;
	stdlist.push_front(50);
	stdlist.push_front(51);
	stdlist.push_front(52);
	stdlist.push_front(53);
	stdlist.push_front(54);

	std::list<int>::iterator iter = stdlist.end();

	--iter;
	SATES_EQ(*iter, 50);
	--iter;
	SATES_EQ(*iter, 51);

	--iter;
	SATES_EQ(*iter, 52);

	--iter;
	SATES_EQ(*iter, 53);

	--iter;
	SATES_EQ(*iter, 54);

	SATES_EQ(iter, stdlist.begin());

}

SATES_TEST_TERMINATE(TU03002_SN_LIST_PUSH_FRONT)
{

}
