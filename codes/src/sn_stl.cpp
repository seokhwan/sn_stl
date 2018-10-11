//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <iostream>
#include <sates/sates_test_cpp_deploy.h>


int main()
{
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU01001_SN_VECTOR_PUSH_BACK);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU01002_SN_VECTOR_AT);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU01003_SN_VECTOR_RESERVE);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU01004_SN_VECTOR_SORT);


	SATES_TEST_RUN_MAIN_FUNC_RUN(TU02001_SN_DEQUE_PUSH_BACK);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU02002_SN_DEQUE_PUSH_FRONT);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU02003_SN_DEQUE_PUSH_CLEAR);

	
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU03001_SN_LIST_PUSH_BACK);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU03002_SN_LIST_PUSH_FRONT);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU03003_SN_LIST_FULL_EMPTY_CLEAR);
	
	
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU00200_SN_BST_INSERT);
	SATES_TEST_RUN_MAIN_FUNC_RUN(TU04002_SN_BST_ITERATOR);
	
}
