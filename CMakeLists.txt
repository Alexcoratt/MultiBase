cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MultiBase CXX)

add_subdirectory(modules/dynvalues)

file(GLOB SOURCES "src/*/sources/*.cpp")

set(LIB_NAME ${PROJECT_NAME}_lib)
add_library(${LIB_NAME} STATIC ${SOURCES})
target_link_libraries(${LIB_NAME} PUBLIC DynValues_lib)
target_include_directories(${LIB_NAME}
	PUBLIC src/iterators/headers
	PUBLIC src/tables/headers
	PUBLIC src/auxillary/headers
	PUBLIC src/parsers/headers
	PUBLIC src/exceptions
)

if (DEFINED MULTI_BASE_BUILD_TESTS AND MULTI_BASE_BUILD_TESTS)
	link_libraries(${LIB_NAME})
	add_executable(test1 src/tests/test1.cpp)
endif()
