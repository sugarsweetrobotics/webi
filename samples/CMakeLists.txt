
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)


set(CMAKE_CXX_STANDARD 17)

add_executable(webi_simplehtml webi_simplehtml.cpp)
target_link_libraries(webi_simplehtml  webi)

add_executable(webi_bootstrap webi_bootstrap.cpp)
target_link_libraries(webi_bootstrap  webi)


