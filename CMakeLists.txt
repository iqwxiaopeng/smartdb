CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(smartdb)

SET(CMAKE_C_FLAGS "-O2 -g -Wall ${CMAKE_C_FLAGS}")

INCLUDE_DIRECTORIES(
    include
    lib
    storage
)

SET(LIB_SOURCE_FILES
    lib/api/Smartdb.cpp
    lib/ast/Node.cpp
    lib/datastruct/ColumnDef.cpp
    lib/datastruct/FixedLengthColumn.cpp
    lib/datastruct/Records.cpp
    lib/log/StderrLogger.cpp
    lib/mem/Buffer.cpp
    lib/op/Operator.cpp
    lib/op/TableReader.cpp
)

ADD_LIBRARY(smartdb SHARED ${LIB_SOURCE_FILES})
