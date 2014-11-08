#!/bin/sh

g++ -I../contrib/gtest/include/ -I../contrib/gtest/ -I../lib/  ../contrib/gtest/src/gtest-all.cc ../contrib/gtest/src/gtest_main.cc    ../lib/datastruct/Record.cpp unit/datastruct/RecordTest.cpp  -o run_gtest
