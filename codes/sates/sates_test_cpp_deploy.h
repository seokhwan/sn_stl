//------------------------------------------------------------------------------
//
// Copyright (C) 2018, Seokhwan Kim (kim at seokhwan.net)
// 
// The SATES TEST CPP, New BSD License (or Modified BSD Licnese)
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation 
// and / or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors 
// may be used to endorse or promote products derived from this software without 
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
// OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
// THE POSSIBILITY OF SUCH DAMAGE.
//
//------------------------------------------------------------------------------

#ifndef __SATES_TEST_CPP_DEPLOY_H__
#define __SATES_TEST_CPP_DEPLOY_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FLOAT32_T_DEFINED
	typedef float              float32_t;
#define FLOAT32_T_DEFINED
#endif

#ifndef FLOAT64_T_DEFINED
	typedef double             float64_t;
#define FLOAT64_T_DEFINED
#endif
	void _sates_test_help_eval_impl(bool expr, int line, const char* p_file_name);
	void _sates_test_help_eval_impl_eq_float32(float32_t val1, float32_t val2, int line, const char* p_file_name);
	void _sates_test_help_eval_impl_ne_float32(float32_t val1, float32_t val2, int line, const char* p_file_name);
	void _sates_test_help_eval_impl_eq_float64(float32_t val1, float32_t val2, int line, const char* p_file_name);
	void _sates_test_help_eval_impl_ne_float64(float32_t val1, float32_t val2, int line, const char* p_file_name);

	void sates_set_float32_eq_threshold(float32_t val);
	void sates_set_float64_eq_threshold(float64_t val);

#define SATES_TRUE(val) \
    _sates_test_help_eval_impl((val), __LINE__, __FILE__)

#define SATES_FALSE(val) \
    _sates_test_help_eval_impl(!(val), __LINE__, __FILE__)

#define SATES_EQ(val1, val2) \
    _sates_test_help_eval_impl(((val1) == (val2)), __LINE__, __FILE__)

#define SATES_NE(val1, val2) \
    _sates_test_help_eval_impl(((val1) != (val2)), __LINE__, __FILE__)

#define SATES_FLOAT32_EQ(val1, val2) \
    _sates_test_help_eval_impl_eq_float32((val1), (val2), __LINE__, __FILE__)

#define SATES_FLOAT32_NE(val1, val2) \
    _sates_test_help_eval_impl_ne_float32((val1), (val2), __LINE__, __FILE__)

#define SATES_FLOAT64_EQ(val1, val2) \
    _sates_test_help_eval_impl_eq_float64((val1), (val2), __LINE__, __FILE__)

#define SATES_FLOAT64_NE(val1, val2) \
    _sates_test_help_eval_impl_ne_float64((val1), (val2), __LINE__, __FILE__)

	void _sates_no_framework_start(const char* p_testcase_name);
	void _staes_no_framework_terminate(const char* p_testcase_name);

#ifndef SATES_TEST_INIT
#define SATES_TEST_INIT(TEST_CASE_NAME) void sates_test_init##TEST_CASE_NAME()
#endif

#ifndef SATES_TEST_RUN
#define SATES_TEST_RUN(TEST_CASE_NAME) void sates_test_run##TEST_CASE_NAME()
#endif

#ifndef SATES_TEST_TERMINATE
#define SATES_TEST_TERMINATE(TEST_CASE_NAME) void sates_test_terminate##TEST_CASE_NAME()
#endif

#define SATES_TEST_RUN_MAIN_FUNC_RUN(TEST_CASE_NAME) \
	extern void sates_test_init##TEST_CASE_NAME(); \
	extern void sates_test_run##TEST_CASE_NAME(); \
	extern void sates_test_terminate##TEST_CASE_NAME(); \
	_sates_no_framework_start(#TEST_CASE_NAME);\
	sates_test_init##TEST_CASE_NAME(); \
	sates_test_run##TEST_CASE_NAME(); \
	sates_test_terminate##TEST_CASE_NAME(); \
	_staes_no_framework_terminate(#TEST_CASE_NAME);



#ifdef __cplusplus
}
#endif


#endif // __SATES_TEST_CPP_DEPLOY_H__
