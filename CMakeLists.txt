cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

project(webi LANGUAGES CXX VERSION 0.0.1)

option(WEBI_DO_TEST "Do Webi's test" OFF)

# add_subdirectory(thirdparty/libwebsockets)
# add_subdirectory(thirdparty/websocketpp)
add_subdirectory(thirdparty/IXWebsocket)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(samples)

if (${WEBI_DO_TEST})
add_subdirectory(test)
endif ()