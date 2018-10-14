
//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/sates_test_cpp_deploy.h>
#include <sn_stl/sn_map.h>
#include <sn_stl/tr1/sn_bbst.h>

#include <chrono>
#include <ctime>
#include <map>
#include <cstdlib>

#include <vector>
#include <iostream>
#include <ctime>

SATES_TEST_INIT(TF0001_STDMAP_SNMAP_SNBBST)
{
}

SATES_TEST_RUN(TF0001_STDMAP_SNMAP_SNBBST)
{
	std::srand(std::time(0U));

	sn_std::sn_map<int, int> mymap(1000000);
	sn_std::tr1::sn_bbst<int, int> bbst(1000000);
	std::map<int, int> stdmap;
	
	std::vector<int> varvec;

	for (int i = 0; i < 1000; ++i)
	{
		varvec.push_back(std::rand() % 10000000);
	}




	auto start = std::chrono::system_clock::now();
	for (int item : varvec)
	{
		mymap.emplace(item, item);
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "sn_map::emplace : " <<  elapsed.count() * 1000 << "ms" << std::endl;


	start = std::chrono::system_clock::now();
	for (int item : varvec)
	{
		bbst.emplace(item, item);
	}
	end = std::chrono::system_clock::now();
	elapsed = end - start;
	std::cout << "sn_bbst::emplace: " << elapsed.count() * 1000 << "ms" << std::endl;


	start = std::chrono::system_clock::now();
	for (int item : varvec)
	{
		stdmap.emplace(item, item);
	}
	end = std::chrono::system_clock::now();
	elapsed = end - start;
	std::cout << "std::map::emplace: " << elapsed.count() * 1000 << "ms" << std::endl;





	start = std::chrono::system_clock::now();
	for (int item : varvec)
	{
		mymap.find(item);
	}
	end = std::chrono::system_clock::now();
	elapsed = end - start;
	std::cout << "sn_map::find : " << elapsed.count() * 1000 << "ms" << std::endl;


	start = std::chrono::system_clock::now();
	for (int item : varvec)
	{
		bbst.find(item);
	}
	end = std::chrono::system_clock::now();
	elapsed = end - start;
	std::cout << "sn_bbst::find: " << elapsed.count() * 1000 << "ms" << std::endl;


	start = std::chrono::system_clock::now();
	for (int item : varvec)
	{
		stdmap.find(item);
	}
	end = std::chrono::system_clock::now();
	elapsed = end - start;
	std::cout << "std::map::find " << elapsed.count() * 1000 << "ms" << std::endl;

}

SATES_TEST_TERMINATE(TF0001_STDMAP_SNMAP_SNBBST)
{

}
