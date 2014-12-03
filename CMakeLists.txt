CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(smartdb)

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall -Wno-deprecated-register -std=c++11 ${CMAKE_CXX_FLAGS}")

INCLUDE_DIRECTORIES(
    include
    storage
)

EXECUTE_PROCESS(
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/lib -name "*.cpp"
    COMMAND grep -v CMakeFiles
    COMMAND tr "\n" ";"
    OUTPUT_VARIABLE LIB_SOURCE_FILES
)
EXECUTE_PROCESS(
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/storageinterface -name "*.cpp"
    COMMAND grep -v CMakeFiles
    COMMAND tr "\n" ";"
    OUTPUT_VARIABLE STORAGEINTERFACE_SOURCE_FILES
)

#
#
# libsmartdb_storageinterface
ADD_LIBRARY(smartdb_storageinterface SHARED ${STORAGEINTERFACE_SOURCE_FILES})
INSTALL(TARGETS smartdb_storageinterface LIBRARY DESTINATION lib)

# To generate ${PARSER_SOURCE_FILES}
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/parser)
INCLUDE(smartdb_parser)

#
# libsmartdb
ADD_LIBRARY(smartdb SHARED ${LIB_SOURCE_FILES} ${PARSER_SOURCE_FILES})
TARGET_LINK_LIBRARIES(smartdb smartdb_storageinterface)
INSTALL(TARGETS smartdb LIBRARY DESTINATION lib)
