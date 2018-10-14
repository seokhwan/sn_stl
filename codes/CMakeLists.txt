cmake_minimum_required(VERSION 3.8.0)
project(sn_stl CXX)

file(GLOB sn_stl_header ${CMAKE_SOURCE_DIR}/inc/sn_stl/*.h)
source_group(inc\\sn_stl FILES ${sn_stl_header})

file(GLOB tr1_header ${CMAKE_SOURCE_DIR}/inc/sn_stl/tr1/*.h)
source_group(inc\\sn_stl\\tr1 FILES ${tr1_header})

file(GLOB sates_header ${CMAKE_SOURCE_DIR}/inc/sates/*.h)
source_group(inc\\sates FILES ${sates_header})

file(GLOB main_src ${CMAKE_SOURCE_DIR}/src/*.cpp)
source_group(src FILES ${main_src})

file(GLOB test_01 ${CMAKE_SOURCE_DIR}/src/test/01_unit/*.cpp)
source_group(src\\test\\01_unit FILES ${test_01})

file(GLOB test_02 ${CMAKE_SOURCE_DIR}/src/test/02_integration/*.cpp)
source_group(src\\test\\02_integration FILES ${test_02})

file(GLOB test_03 ${CMAKE_SOURCE_DIR}/src/test/03_perf/*.cpp)
source_group(src\\test\\03_perf FILES ${test_03})

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_executable(sn_stl ${sn_stl_header} ${tr1_header} ${sates_header} ${main_src} ${test_01} ${test_02} ${test_03})