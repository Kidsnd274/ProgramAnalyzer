file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/pkb/ModifiesTable.h src/pkb/ModifiesTable.cpp src/pkb/CallTable.cpp src/qps/type/Next.cpp src/qps/type/Next.h src/qps/type/Calls.cpp src/qps/type/Calls.h src/qps/type/Affects.cpp src/qps/type/Affects.h src/qps/type/Entity.cpp src/qps/type/Entity.h src/pkb/ContainerTable.cpp src/pkb/ContainerTable.h src/qps/type/ModifiesUses.cpp src/qps/type/ModifiesUses.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
