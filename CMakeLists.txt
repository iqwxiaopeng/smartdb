CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(smartdb)

SET(CMAKE_C_FLAGS "-O2 -g -Wall ${CMAKE_C_FLAGS}")

INCLUDE_DIRECTORIES(
    include
    lib
)

SET(LIB_SOURCE_FILES
    lib/api/Smartdb.cpp
    lib/ast/Node.cpp
    lib/core/Scheduler.cpp
    lib/core/StorageInterface.cpp
    lib/datastruct/Buffer.cpp
    lib/datastruct/Record.cpp
    lib/datastruct/RecordQueue.cpp
    lib/datastruct/FixedLengthColumn.cpp
    lib/mem/MallocMemoryManager.cpp
    lib/mem/MemoryManager.cpp
    lib/op/Operator.cpp
    lib/op/TableReader.cpp
    lib/storage/Csv.cpp
    lib/storage/StorageEngine.cpp
    test/unit/datastruct/RecordQueueTest.cpp
    test/unit/datastruct/RecordTest.cpp
)

ADD_LIBRARY(libsmartdb SHARED ${LIB_SOURCE_FILES})
