
if (TARGET Catch2)

else ()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)
endif ()


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include/catch2)


set(CMAKE_CXX_STANDARD 17)

add_executable(webi_test webi_test.cpp)
target_link_libraries(webi_test  webi Catch2::Catch2)
add_test(NAME webi_test COMMAND $<TARGET_FILE:webi_test>) 

