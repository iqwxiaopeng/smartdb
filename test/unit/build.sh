#!/bin/sh

proj_root_dir=../..
gtest_dir=${proj_root_dir}/contrib/gtest
gtest_src="${gtest_dir}/src/gtest-all.cc ${gtest_dir}/src/gtest_main.cc"
smartdb_lib_src=${proj_root_dir}/lib/datastruct/Record.cpp
smartdb_lib_test=${proj_root_dir}/test/unit/datastruct/RecordTest.cpp
target=run_gtest

g++ \
    -g \
    -I${gtest_dir} -I${gtest_dir}/include -I${proj_root_dir}/lib \
    ${gtest_src} \
    ${smartdb_lib_src} ${smartdb_lib_test} \
    -o ${target} \
