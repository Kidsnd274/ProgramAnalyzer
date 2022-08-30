file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/QueryPreprocessor.cpp src/QueryEvaluator.cpp src/QueryHandler.cpp src/QueryHandler.h src/Tokenizer.cpp src/Tokenizer.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(Tokenizer src/Tokenizer.cpp)


