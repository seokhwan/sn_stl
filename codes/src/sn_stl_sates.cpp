//------------------------------------------------------------------------------
// Copyright (C) 2018 - present, Seokhwan Kim (kim at seokhwan.net)
// This file is part of "the SN_STL"
// For conditions of distribution and use, see copyright notice in 
// <sn_stl/sn_stl.h>
//------------------------------------------------------------------------------


#include <sates/testcode_list.h>
#include <sates/api_caller.h>
#include <sates/os/tcp_client.h>
#include <sates/report/reporter_local_json.h>

int main()
{
    const std::string default_path = "C:/sn_stl";
    sates::report::reporter_local_json reporter_json;
    
    sates::api_caller::connect("127.0.0.1", 5000);
    sates::api_caller::call("read_dir", (default_path + "/docs/SPEC").c_str() , "spec");
    sates::api_caller::call("read_dir", (default_path + "/docs/TESTCASE").c_str(), "testcase");
    sates::api_caller::call("read_dir", (default_path + "/docs/REVISION_HISTORY").c_str(), "revision_history");

    sates::testcode_list::set_reporter(&reporter_json);

    sates::testcode_list::create();
    sates::testcode_list::run();
    sates::testcode_list::print_result();

    sates::api_caller::call("generate_doc", "cpp", (default_path + "/build/docs/doxy").c_str());

    sates::api_caller::call("generate_doxygen",
        "cpp",
        (default_path + "/deps/win").c_str(),
        (default_path + "/deps").c_str(),
        (default_path + "/build/docs/doxy").c_str(),
        (default_path + "/resource/sates_doxy").c_str());


    
    sates::testcode_list::destroy();
}

