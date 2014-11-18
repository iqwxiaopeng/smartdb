#!/bin/sh

proj_root_dir=../..
gtest_dir=${proj_root_dir}/contrib/gtest
gtest_src="${gtest_dir}/src/gtest-all.cc ${gtest_dir}/src/gtest_main.cc"
target=run_gtest

smartdb_lib_test=$(find ./lib -name '*.cpp')
smartdb_lib_src=$(find ${proj_root_dir}/lib -name '*.cpp')
smartdb_storage_test=$(find ./storage -name '*.cpp')
smartdb_storage_src=$(find ${proj_root_dir}/storage -name '*.cpp')

compile_cmd="\
g++ \
    -g \
    -DSMARTDB_GTEST \
    -I${gtest_dir} -I${gtest_dir}/include -I${proj_root_dir}/lib -I${proj_root_dir}/storage -I${proj_root_dir}/include \
    ${gtest_src} \
    ${smartdb_lib_src} ${smartdb_lib_test} ${smartdb_storage_src} ${smartdb_storage_test} \
    -o ${target} \
"

echo ${compile_cmd}
eval ${compile_cmd}
