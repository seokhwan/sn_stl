//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------

#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_list.h>

class sn_list_empty_clear_test : public sn_std::sn_list<int>
{
public:
	sn_list_empty_clear_test(uint32_t cap) : sn_std::sn_list<int>(cap)
	{

	}
	uint32_t get_vec_size()
	{
		return m_p_vec->size();
	}
};

/** \addtogroup CODE
*  @{
*/
/** \addtogroup TESTCODE
*  @{
*/
/** \addtogroup T01_UNIT_CODE
*  @{
*/

/** \addtogroup TU03003_SN_LIST_FULL_EMPTY_CLEAR
*  @{
*/

/**
@see TU03003_SN_LIST_FULL_EMPTY_CLEAR.cpp
*/
SATES_TEST_INIT(TU03003_SN_LIST_FULL_EMPTY_CLEAR)
{

}

SATES_TEST_RUN(TU03003_SN_LIST_FULL_EMPTY_CLEAR)
{
	sn_list_empty_clear_test mylist(128U);

	for (int i = 0; i < 128; i++)
	{
		mylist.push_back(i);
	}

	SATES_EQ(mylist.full(), true);
	SATES_EQ(mylist.size(), 128U);
	SATES_EQ(mylist.get_vec_size(), 0U);
	mylist.clear();
	SATES_EQ(mylist.get_vec_size(), 129U);
	SATES_EQ(mylist.empty(), true);
	SATES_EQ(mylist.size(), 0U);
}

SATES_TEST_TERMINATE(TU03003_SN_LIST_FULL_EMPTY_CLEAR)
{

}

/** @} */
/** @} */
/** @} */
/** @} */