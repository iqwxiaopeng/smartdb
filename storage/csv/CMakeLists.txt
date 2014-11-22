CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(csv)

SET(CMAKE_C_FLAGS "-O0 -g -Wall ${CMAKE_C_FLAGS}")

INCLUDE_DIRECTORIES(
    ../../include
    ../../lib
    contrib/csv_parser
)

SET(LIB_SOURCE_FILES
    Csv.cpp
)

ADD_LIBRARY(csv SHARED ${LIB_SOURCE_FILES})

#
# Link external libraries (both dynamic & static)
TARGET_LINK_LIBRARIES(csv smartdb)
TARGET_LINK_LIBRARIES(csv ${CMAKE_CURRENT_SOURCE_DIR}/contrib/csv_parser/libcsv_parser.a)

INSTALL(TARGETS csv LIBRARY DESTINATION lib)
