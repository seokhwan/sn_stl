cmake_minimum_required(VERSION 3.8.0)
project(sn_stl CXX)

file(GLOB sn_stl_header ${CMAKE_SOURCE_DIR}/inc/sn_stl/*.h)
source_group(inc\\sn_stl FILES ${sn_stl_header})

file(GLOB tr1_header ${CMAKE_SOURCE_DIR}/inc/sn_stl/tr1_header/*.h)
source_group(inc\\sn_stl\\tr1 FILES ${tr1_header})

file(GLOB sates_header ${CMAKE_SOURCE_DIR}/inc/sates/*.h)
source_group(inc\\sates FILES ${sates_header})

file(GLOB main_src ${CMAKE_SOURCE_DIR}/src/*.cpp)
source_group(src FILES ${main_src})

file(GLOB test_src ${CMAKE_SOURCE_DIR}/src/test/*.cpp)
source_group(src\\test FILES ${test_src})

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_executable(sn_stl ${sn_stl_header} ${tr1_header} ${sates_header} ${main_src} ${test_src})