CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(smartdb)

SET(LIB_SOURCE_FILES
    lib/datastruct/buffer.cc
    lib/op/table_reader.cc
    lib/core/storage_interface.cc
    lib/storage/csv.cc
    )

ADD_LIBRARY(libsmartdb SHARED ${LIB_SOURCE_FILES})
