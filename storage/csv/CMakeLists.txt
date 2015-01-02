CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(csv)

#
# setting variables
SET(PROJ_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)


SET(CMAKE_CXX_FLAGS "-O2 -g -Wall -std=c++11 ${CMAKE_CXX_FLAGS}")

INCLUDE_DIRECTORIES(
    ${PROJ_ROOT_DIR}/include
    ${PROJ_ROOT_DIR}/contrib/PartialCsvParser/include
)

SET(LIB_SOURCE_FILES
    Csv.cpp
)

ADD_LIBRARY(csv SHARED ${LIB_SOURCE_FILES})

#
# Link external libraries (both dynamic & static)
TARGET_LINK_LIBRARIES(csv smartdb_storageinterface)

INSTALL(TARGETS csv LIBRARY DESTINATION lib)
