
//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_map.h>
#include <sn_stl/tr1/sn_map_vec.h>
#include <sn_stl/tr1/sn_bbst.h>

#include <chrono>
#include <ctime>
#include <map>
#include <cstdlib>

#include <vector>
#include <iostream>
#include <ctime>

static const int ITEM_SIZE = 10000;

static const uint32_t MAP_SIZE = ITEM_SIZE + 10;
static const int TEST_COUNT = 10;

static std::vector<std::vector<int> > varvec;

template<typename T>
static void emplace_test(T& testitem, const std::vector<std::vector<int> >& vec, const char* p_mapname)
{
	double accum = 0.0;
	for (int k = 0; k < TEST_COUNT; k++)
	{
		testitem.clear();
		auto start = std::chrono::system_clock::now();

		for (int item : vec[k])
		{
			testitem.emplace(item, item);
		}
		 
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;

		accum += elapsed.count();
	}

	std::cout << p_mapname << "::emplace : " << accum * (double)1000 * 1000 / (double)TEST_COUNT << "us" << std::endl;
}

template<typename T>
static void find_test(T& testitem, const std::vector<std::vector<int> >& vec, const char* p_mapname)
{
	double accum = 0.0;
	for (int k = 0; k < TEST_COUNT; ++k)
	{
		auto start = std::chrono::system_clock::now();

		for (int item : vec[k])
		{
			auto result = testitem.find(item);
		}

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		accum += elapsed.count();
	}
	std::cout << p_mapname << "::find : " << accum * (double)1000 * 1000 / (double)TEST_COUNT << "us" << std::endl;
}

SATES_TEST_INIT(TF0001_STDMAP_PERF)
{
}

SATES_TEST_RUN(TF0001_STDMAP_PERF)
{
	std::srand(std::time(0U));

	sn_std::tr1::sn_map_deq<int, int> deq_map(MAP_SIZE);
	sn_std::tr1::sn_bbst<int, int> bbst(MAP_SIZE);
	sn_std::tr1::sn_map_vec<int, int> vec_map(MAP_SIZE);
	std::map<int, int> std_map;

	for (int i = 0; i < TEST_COUNT; ++i)
	{
		std::vector<int> curvec;
		for (int j = 0; j < ITEM_SIZE; ++j)
		{
			curvec.push_back(std::rand() % 1000000);
		}
		varvec.push_back(curvec);
	}
	
	emplace_test(std_map, varvec, "std_map");
	emplace_test(vec_map, varvec, "sn_map_vec");
	emplace_test(bbst, varvec, "sn_bbst");
	emplace_test(deq_map, varvec, "sn_map_deq");
	
	
	

	std::cout << std::endl << std::endl;

	find_test(std_map, varvec, "std_map");
	find_test(vec_map, varvec, "sn_map_vec");
	find_test(bbst, varvec, "sn_bbst");
	find_test(deq_map, varvec, "sn_map_deq");
}

SATES_TEST_TERMINATE(TF0001_STDMAP_PERF)
{

}
