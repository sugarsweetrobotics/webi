set(webi_srcs webi.cpp server.cpp html.cpp)
set(webi_srcs ${webi_srcs} PARENT_SCOPE)

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/rapidjson/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Threads REQUIRED)

add_library(webi ${webi_srcs})
target_link_libraries(webi Threads::Threads)
