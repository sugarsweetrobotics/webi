#set(webi_srcs webi.cpp server.cpp html.cpp)
set(webi_srcs webi.cpp server_lws.cpp html.cpp server_lws_wrapper.c)
set(webi_srcs ${webi_srcs} PARENT_SCOPE)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/)

include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/rapidjson/include)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/libwebsockets/include)


find_package(Threads REQUIRED)

set(EXT_LIBS websockets_shared)

message("EXT_LIBS: ${EXT_LIBS}")


if(MSVC)
add_compile_options(/D _USRDLL)
# add_compile_options(/D _CRT_SECURE_NO_DEPRECATE)
# _CRT_NONSTDC_NO_DEPRECATE
endif(MSVC)

#add_compile_options(-std=gnu++14)
set(CMAKE_CXX_STANDARD 17)


add_library(webi ${webi_srcs})
target_link_libraries(webi Threads::Threads ${EXT_LIBS})
add_dependencies(webi websockets_shared)
