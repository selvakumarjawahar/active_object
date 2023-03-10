cmake_minimum_required(VERSION 3.15)

project(active_object
	VERSION 0.1
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(GCC_COMPILE_FLAGS -Werror -Wall -Wextra -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wdouble-promotion -Wformat=2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SRCS
	${PROJECT_SOURCE_DIR}/src/concurrent_queue.h
	${PROJECT_SOURCE_DIR}/src/command.h
	${PROJECT_SOURCE_DIR}/src/command.cpp
	${PROJECT_SOURCE_DIR}/src/executor.h
	${PROJECT_SOURCE_DIR}/src/interface_proxy.h
	${PROJECT_SOURCE_DIR}/src/interface_proxy.cpp)

set (EXAMPLE_SRCS
	${PROJECT_SOURCE_DIR}/example/client.cpp)

add_library(active_object STATIC 
	${SRCS})

target_compile_options(active_object PRIVATE  ${GCC_COMPILE_FLAGS})

target_link_libraries(active_object
	PRIVATE pthread)

add_executable(client example/client.cpp)

target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_compile_options(client PRIVATE ${GCC_COMPILE_FLAGS})

target_link_libraries(client PRIVATE active_object)

add_custom_target(
	clang-tidy-check clang-tidy -extra-arg=-Wno-unknown-warning-option -p build/compile_commands.json -header-filter=.* ${SRCS} ${EXAMPLE_SRCS} ${TEST_SRCS}
	DEPENDS ${SRCS} ${EXAMPLE_SRCS} ${TEST_SRCS} )

add_custom_target(
        clangformat
		COMMAND clang-format -style=WebKit -i ${SRCS} ${EXAMPLE_SRCS} ${TEST_SRCS}
		DEPENDS ${SRCS} ${EXAMPLE_SRCS} ${TEST_SRCS}
)
