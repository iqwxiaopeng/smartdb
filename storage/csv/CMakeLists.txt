CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(csv)

SET(CMAKE_C_FLAGS "-O2 -g -Wall ${CMAKE_C_FLAGS}")

INCLUDE_DIRECTORIES(
    ../../include
    ../../lib
)

SET(LIB_SOURCE_FILES
    Csv.cpp
    ../../contrib/csv_parser/libcsv_parser.a
)

ADD_LIBRARY(csv MODULE ${LIB_SOURCE_FILES})
TARGET_LINK_LIBRARIES(csv smartdb)
