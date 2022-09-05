file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/QueryPreprocessor.cpp src/QueryEvaluator.cpp src/Tokenizer.cpp src/Tokenizer.h src/QueryEvaluator.h src/QueryPreprocessor.h src/QueryResultProjector.cpp src/QueryResultProjector.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#add_executable(QueryStruct src/QueryStruct.cpp)
#add_executable(Tokenizer src/Tokenizer.cpp src/QueryPreprocessor.cpp src/QueryStruct.cpp src/QueryProcessorTypes.cpp)
#add_executable(ResultTable src/ResultTable.cpp)
#add_executable(QueryManager src/QueryManager.cpp
#        src/Tokenizer.cpp
#        src/QueryPreprocessor.cpp
#        src/QueryStruct.cpp
#        src/QueryProcessorTypes.cpp
#        src/ResultTable.cpp
#        src/QueryEvaluator.cpp
#        src/QueryResultProjector.cpp)
