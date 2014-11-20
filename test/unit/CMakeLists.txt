CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(run_gtest)

#
# setting variables
SET(PROJ_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
SET(GTEST_DIR ${PROJ_ROOT_DIR}/contrib/gtest)
SET(GTEST_SRC
    ${GTEST_DIR}/src/gtest-all.cc
    ${GTEST_DIR}/src/gtest_main.cc
)

SET(STATIC_LIBS
    ${PROJ_ROOT_DIR}/storage/csv/contrib/csv_parser/libcsv_parser.a
)

EXECUTE_PROCESS(
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/lib -name "*.cpp"
    COMMAND grep -v CMakeFiles
    COMMAND tr "\n" ";"
    OUTPUT_VARIABLE SMARTDB_LIB_TEST
)
EXECUTE_PROCESS(
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/storage -name "*.cpp"
    COMMAND grep -v CMakeFiles
    COMMAND tr "\n" ";"
    OUTPUT_VARIABLE SMARTDB_STORAGE_TEST
)
EXECUTE_PROCESS(
    COMMAND find ${PROJ_ROOT_DIR}/lib -name "*.cpp"
    COMMAND grep -v CMakeFiles
    COMMAND tr "\n" ";"
    OUTPUT_VARIABLE SMARTDB_LIB_SRC
)
EXECUTE_PROCESS(
    COMMAND find ${PROJ_ROOT_DIR}/storage -name "*.cpp"
    COMMAND grep -v CMakeFiles
    COMMAND tr "\n" ";"
    OUTPUT_VARIABLE SMARTDB_STORAGE_SRC
)

#
# compile environments
ADD_DEFINITIONS(
    -DSMARTDB_GTEST
)

SET(CMAKE_CXX_FLAGS "-O0 -g -Wall ${CMAKE_C_FLAGS}")

INCLUDE_DIRECTORIES(
    ${GTEST_DIR}
    ${GTEST_DIR}/include
    ${PROJ_ROOT_DIR}/lib
    ${PROJ_ROOT_DIR}/include
    ${PROJ_ROOT_DIR}/storage
    ${PROJ_ROOT_DIR}/storage/csv/contrib/csv_parser
)

SET(SOURCE_FILES
    ${GTEST_SRC}
    ${SMARTDB_LIB_SRC}
    ${SMARTDB_LIB_TEST}
    ${SMARTDB_STORAGE_SRC}
    ${SMARTDB_STORAGE_TEST}
)

ADD_EXECUTABLE(run_gtest ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(run_gtest ${STATIC_LIBS})
