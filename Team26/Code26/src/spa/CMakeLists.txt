file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/pkb/Variable.cpp src/pkb/Variable.h src/pkb/VariableTable.cpp src/pkb/VariableTable.h src/pkb/StatementTable.cpp src/pkb/StatementTable.h src/pkb/PKBParserInterface.cpp src/pkb/PKBQueryInterface.cpp src/pkb/Statement.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


