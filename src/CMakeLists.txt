set(webi_srcs webi.cpp server.cpp http_server.cpp http_server_cpphttplib.cpp 
	      html.cpp websocket_server_ixwebsocket.cpp css.cpp
	      remote_dom.cpp 
		${headers}
	      )
#set(webi_srcs webi.cpp server_lws.cpp html.cpp server_lws_wrapper.c)
set(webi_srcs ${webi_srcs} PARENT_SCOPE)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/)

include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/rapidjson/include)
# include_directories(${CMAKE_SOURCE_DIR}/thirdparty/libwebsockets/include)
# include_directories(${CMAKE_SOURCE_DIR}/thirdparty/websocketpp)
# include_directories(${CMAKE_SOURCE_DIR}/thirdparty/websocketpp/websocketpp)

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/IXWebsocket)

find_package(Threads REQUIRED)

# set(EXT_LIBS websockets_shared)
set(EXT_LIBS ixwebsocket)

# message("EXT_LIBS: ${EXT_LIBS}")


if(MSVC)
add_compile_options(/D _USRDLL)
endif(MSVC)

#add_compile_options(-std=gnu++14)
set(CMAKE_CXX_STANDARD 17)


add_library(webi ${webi_srcs})
target_link_libraries(webi Threads::Threads ${EXT_LIBS})
# add_dependencies(webi websockets_shared)
