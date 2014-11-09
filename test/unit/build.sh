#!/bin/sh

proj_root_dir=../..
gtest_dir=${proj_root_dir}/contrib/gtest
gtest_src="${gtest_dir}/src/gtest-all.cc ${gtest_dir}/src/gtest_main.cc"
# smartdb_lib_src=${proj_root_dir}/lib/datastruct/Record.cpp
target=run_gtest

smartdb_lib_test=$(find . -name '*.cpp')
smartdb_lib_src=$(find ${proj_root_dir}/lib -name '*.cpp')

compile_cmd="\
g++ \
    -g \
    -fno-exceptions -fno-rtti \
    -I${gtest_dir} -I${gtest_dir}/include -I${proj_root_dir}/lib -I${proj_root_dir}/include \
    ${gtest_src} \
    ${smartdb_lib_src} ${smartdb_lib_test} \
    -o ${target} \
"

echo ${compile_cmd}
eval ${compile_cmd}
