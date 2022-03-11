cmake_minimum_required(VERSION 3.12)

project(kbdencode VERSION 0.1.3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		string(APPEND CMAKE_CXX_FLAGS_RELEASE " -s")
	endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
endif()

add_subdirectory(libs/boost_1_57_0/program_options)

add_executable(kbdencode src/kbdencode.cc)
target_link_libraries(kbdencode boost_program_options)
install(TARGETS kbdencode)

set(CPACK_PACKAGE_VENDOR "Matthew Barry <matthew@komputerwiz.net>")
include(CPack)
