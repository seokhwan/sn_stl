//------------------------------------------------------------------------------
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SATES"
// For conditions of distribution and use, see copyright notice in 
// sates/sates_test_cpp_deploy.h
//------------------------------------------------------------------------------

#include <sates/sates_test_cpp_deploy.h>
#include <iostream>
#include <vector>
#include <string>

#ifdef SATES_FRAMEWORK_INCLUDED
#include <sates/os/stdout_color.h>
#include <sates/internal_use/test_log.h>
#endif

static float32_t _sates_test_help_float32_eq = 0.00001F;
static float64_t _sates_test_help_float64_eq = 0.00001;

static uint32_t tc_err_cnt = 0U;
static uint32_t num_of_tc = 0U;


static float32_t _sates_test_help_abs(float32_t val)
{
	if (val < 0.0F)
	{
		val = val * -1.0F;
	}
	return val;
}

static float64_t _sates_test_help_abs(float64_t val)
{
	if (val < 0.0)
	{
		val = val * -1.0;
	}
	return val;
}

void sates_set_float32_eq_threshold(float32_t val)
{
	_sates_test_help_float32_eq = val;
}

void sates_set_float64_eq_threshold(float64_t val)
{
	_sates_test_help_float64_eq = val;
}

void _sates_test_help_eval_impl(bool expr, int line, const char* p_file_name)
{
	num_of_tc++;
	if (!(expr))
	{
		std::string err_str = "TEST FAILURE, line : ";
		err_str += std::to_string(line);
		err_str += ", file : ";
		err_str += p_file_name;

		++tc_err_cnt;

#ifdef SATES_FRAMEWORK_INCLUDED
		sates::internal_use::test_log::error(err_str);
#endif
		
#ifdef SATES_FRAMEWORK_INCLUDED
		sates::os::set_stdout_color(sates::os::CONSOLE_COLOR::CONSOLE_COLOR_WHITE,
			sates::os::CONSOLE_COLOR::CONSOLE_COLOR_BLUE);
		std::cout << sates::os::get_stdout_color()
#else
		std::cout
#endif
			<< err_str << std::endl;

#ifdef SATES_FRAMEWORK_INCLUDED
		sates::os::clear_stdout_color();
		sates::os::set_stdout_color(sates::os::CONSOLE_COLOR::CONSOLE_COLOR_WHITE,
			sates::os::CONSOLE_COLOR::CONSOLE_COLOR_BLACK);
#endif
	}
}

void _sates_test_help_eval_impl_eq_float32(float32_t val1, float32_t val2, int line, const char* p_file_name)
{
	_sates_test_help_eval_impl(
		(_sates_test_help_abs(val1 - val2) <= _sates_test_help_float32_eq),
		line,
		p_file_name);
}

void _sates_test_help_eval_impl_ne_float32(float32_t val1, float32_t val2, int line, const char* p_file_name)
{
	_sates_test_help_eval_impl(
		(_sates_test_help_abs(val1 - val2) > _sates_test_help_float32_eq),
		line,
		p_file_name);
}

void _sates_test_help_eval_impl_eq_float64(float32_t val1, float32_t val2, int line, const char* p_file_name)
{
	_sates_test_help_eval_impl(
		(_sates_test_help_abs(val1 - val2) <= _sates_test_help_float64_eq),
		line,
		p_file_name);
}

void _sates_test_help_eval_impl_ne_float64(float32_t val1, float32_t val2, int line, const char* p_file_name)
{
	_sates_test_help_eval_impl(
		(_sates_test_help_abs(val1 - val2) > _sates_test_help_float64_eq),
		line,
		p_file_name);
}

void _sates_no_framework_start(const char* p_testcase_name)
{
	num_of_tc = 0U;
	tc_err_cnt = 0U;
}

void _staes_no_framework_terminate(const char* p_testcase_name)
{
	std::cout << "=== Test Case : " << p_testcase_name << ", # of Test Cases : "<< num_of_tc << ", Result : ";
	if (0U == tc_err_cnt)
	{
		std::cout << "SUCCESS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
}

