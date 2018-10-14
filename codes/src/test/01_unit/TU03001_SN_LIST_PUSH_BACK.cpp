//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------

#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_list.h>

#include <list>

SATES_TEST_INIT(TU03001_SN_LIST_PUSH_BACK)
{

}

SATES_TEST_RUN(TU03001_SN_LIST_PUSH_BACK)
{
	sn_std::sn_list<int> mylist(200);
	mylist.push_back(50);
	mylist.push_back(51);
	mylist.push_back(52);
	mylist.push_back(53);
	mylist.push_back(54);

	sn_std::sn_list<int>::const_iterator it = mylist.cbegin();
	SATES_EQ(*it, 50);
	++it;
	SATES_EQ(*it, 51);
	it++;
	SATES_EQ(*it, 52);
	++it;
	SATES_EQ(*it, 53);
	++it;
	SATES_EQ(*it, 54);
	++it;
	SATES_EQ(it, mylist.cend());

	mylist.pop_back();
	
	it = mylist.cbegin();
	SATES_EQ(*it, 50);
	++it;
	SATES_EQ(*it, 51);
	++it;
	SATES_EQ(*it, 52);
	++it;
	SATES_EQ(*it, 53);
	++it;
	SATES_EQ(it, mylist.cend()); 

	std::list<int> stdlist;
	stdlist.push_back(50); 
	stdlist.push_back(51);
	stdlist.push_back(52);
	stdlist.push_back(53);
	stdlist.push_back(54);

	std::list<int>::iterator iter = stdlist.begin();
	
	SATES_EQ(*iter, 50);
	++iter;
	SATES_EQ(*iter, 51);

	++iter;
	SATES_EQ(*iter, 52);

	++iter;
	SATES_EQ(*iter, 53);

	++iter;
	SATES_EQ(*iter, 54);

	++iter;
	SATES_EQ(iter, stdlist.end());
	
}

SATES_TEST_TERMINATE(TU03001_SN_LIST_PUSH_BACK)
{

}
