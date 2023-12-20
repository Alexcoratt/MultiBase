cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MultiBase CXX)

add_subdirectory(modules/dynvalues)

file(GLOB SOURCES "src/*/sources/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME}_lib
	PUBLIC DynValues_lib
)
target_include_directories(${PROJECT_NAME}_lib
	PUBLIC src/iterators/headers
	PUBLIC src/tables/headers
	PUBLIC src/auxillary/headers
	PUBLIC src/parsers/headers
	PUBLIC src/exceptions
)
