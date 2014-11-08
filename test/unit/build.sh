#!/bin/sh

proj_root_dir=../..
gtest_dir=${proj_root_dir}/contrib/gtest
gtest_src="${gtest_dir}/src/gtest-all.cc ${gtest_dir}/src/gtest_main.cc"
# smartdb_lib_src=${proj_root_dir}/lib/datastruct/Record.cpp
target=run_gtest

smartdb_lib_test=$(find . -name '*.cpp')

_proj_root_dir_for_sed=$(echo $proj_root_dir |sed -e 's/\./\\./g' |sed -e 's/\//\\\//g')
smartdb_lib_src=$(echo $smartdb_lib_test |sed -e "s/\.\//${_proj_root_dir_for_sed}\/lib\//g" |sed -e 's/Test\.cpp/.cpp/g')

g++ \
    -g \
    -I${gtest_dir} -I${gtest_dir}/include -I${proj_root_dir}/lib \
    ${gtest_src} \
    ${smartdb_lib_src} ${smartdb_lib_test} \
    -o ${target} \
