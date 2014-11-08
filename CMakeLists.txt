CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(smartdb)

SET(CMAKE_C_FLAGS "-O2 -g -Wall -Wno-unused-function ${CMAKE_C_FLAGS}")

INCLUDE_DIRECTORIES(
    include)

SET(LIB_SOURCE_FILES
    lib/datastruct/buffer.cc
    lib/op/table_reader.cc
    lib/core/storage_interface.cc
    lib/storage/csv.cc
    )

ADD_LIBRARY(libsmartdb SHARED ${LIB_SOURCE_FILES})
