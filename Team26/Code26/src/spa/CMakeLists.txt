file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/util/LParenToken.h src/util/RParenToken.h src/util/LCurlyToken.h src/util/RCurlyToken.h src/util/AssignToken.h src/util/RelationToken.h src/util/CondToken.h src/util/OpToken.h src/util/ErrorToken.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


