file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/pkb/ModifiesTable.h src/pkb/ModifiesTable.cpp src/pkb/CallTable.cpp src/qps/type/Next.cpp src/qps/type/Next.h src/qps/type/Calls.cpp src/qps/type/Calls.h src/qps/type/Affects.cpp src/qps/type/Affects.h src/qps/type/Entity.cpp src/qps/type/Entity.h src/qps/type/FollowStar.cpp src/qps/type/FollowStar.h src/qps/type/AffectsStar.cpp src/qps/type/AffectsStar.h src/qps/type/ParentStar.cpp src/qps/type/ParentStar.h src/qps/type/CallsStar.cpp src/qps/type/CallsStar.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
