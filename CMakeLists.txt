cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MultiBase CXX C)

add_subdirectory(modules/dynvalues)
add_subdirectory(modules/matplotplusplus)

file(GLOB SOURCES "src/*/sources/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME}
	PRIVATE DynValues_lib
	PRIVATE matplot
)
target_include_directories(${PROJECT_NAME}
	PRIVATE src/iterators/headers
	PRIVATE src/tables/headers
	PRIVATE src/auxillary/headers
	PRIVATE src/parsers/headers
	PRIVATE src/exceptions
)
