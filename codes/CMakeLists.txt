
if(CLANG_BUILD)
	SET (CMAKE_C_COMPILER             "/usr/bin/clang")
    SET (CMAKE_C_FLAGS                "-Wall -std=c99")
    SET (CMAKE_C_FLAGS_DEBUG          "-g")
    SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
    SET (CMAKE_CXX_FLAGS                "-Wall")
    SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_AR      "/usr/bin/llvm-ar")
    SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
    SET (CMAKE_NM      "/usr/bin/llvm-nm")
    SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
    SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
endif()

cmake_minimum_required(VERSION 3.8.0)

#set(SATES_INCLUDED "yes")

set (CMAKE_CXX_STANDARD 11)

project(sn_stl CXX)

file(GLOB sn_stl_header ${CMAKE_SOURCE_DIR}/inc/sn_stl/*.h)
source_group(inc\\sn_stl FILES ${sn_stl_header})

file(GLOB tr1_header ${CMAKE_SOURCE_DIR}/inc/sn_stl/tr1/*.h)
source_group(inc\\sn_stl\\tr1 FILES ${tr1_header})

file(GLOB sates_header ${CMAKE_SOURCE_DIR}/inc/sates/*.h)
source_group(inc\\sates FILES ${sates_header})

get_filename_component(ROOT_PATH "${CMAKE_SOURCE_DIR}/.." ABSOLUTE)

set(mainsrc ${CMAKE_SOURCE_DIR}/src/sn_exception.cpp)
if(SATES_INCLUDED)
	add_definitions(-DSATES_FRAMEWORK_INCLUDED)
	set(mainsrc ${mainsrc} ${CMAKE_SOURCE_DIR}/src/sn_stl_sates.cpp)
	include_directories(${ROOT_PATH}/deps/sates/inc)
	link_directories(${ROOT_PATH}/deps/sates/win/${CMAKE_BUILD_TYPE})
else()
	set(mainsrc ${mainsrc} ${CMAKE_SOURCE_DIR}/src/sn_stl.cpp)
	set(mainsrc ${mainsrc} ${CMAKE_SOURCE_DIR}/src/sates_test_cpp_deploy.cpp)
endif()
source_group(src FILES ${mainsrc})


file(GLOB test_01 ${CMAKE_SOURCE_DIR}/src/test/01_unit/*.cpp)
source_group(src\\test\\01_unit FILES ${test_01})

file(GLOB test_02 ${CMAKE_SOURCE_DIR}/src/test/02_integration/*.cpp)
source_group(src\\test\\02_integration FILES ${test_02})

file(GLOB test_03 ${CMAKE_SOURCE_DIR}/src/test/03_perf/*.cpp)
source_group(src\\test\\03_perf FILES ${test_03})

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_executable(sn_stl ${sn_stl_header} ${tr1_header} ${sates_header} ${test_01} ${test_02} ${test_03} ${mainsrc})

if(SATES_INCLUDED)
	target_link_libraries(sn_stl sates_test_cpp)
endif()
