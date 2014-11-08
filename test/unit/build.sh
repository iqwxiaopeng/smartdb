#!/bin/sh

proj_root_dir=../..
gtest_dir=${proj_root_dir}/contrib/gtest
gtest_src="${gtest_dir}/src/gtest-all.cc ${gtest_dir}/src/gtest_main.cc"
# smartdb_lib_src=${proj_root_dir}/lib/datastruct/Record.cpp
target=run_gtest

smartdb_lib_test=$(find . -name '*.cpp')

_possible_cpp=$(grep '#include' $smartdb_lib_test |sed -e 's/.*"\(.*\).h".*/\1.cpp/g')
smartdb_lib_src=$(for cpp in ${_possible_cpp} ; do test -f ${proj_root_dir}/lib/${cpp} && echo ${proj_root_dir}/lib/${cpp} ; done)

g++ \
    -g \
    -I${gtest_dir} -I${gtest_dir}/include -I${proj_root_dir}/lib -I${proj_root_dir}/include \
    ${gtest_src} \
    ${smartdb_lib_src} ${smartdb_lib_test} \
    -o ${target} \
