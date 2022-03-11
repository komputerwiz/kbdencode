cmake_minimum_required(VERSION 3.12)
project(boost_program_options VERSION 1.57.0)

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

add_library(boost_program_options STATIC
  src/program_options/cmdline.cpp
  src/program_options/config_file.cpp
  src/program_options/options_description.cpp
  src/program_options/parsers.cpp
  src/program_options/variables_map.cpp
  src/program_options/value_semantic.cpp
  src/program_options/positional_options.cpp
  src/program_options/utf8_codecvt_facet.cpp
  src/program_options/convert.cpp
  src/program_options/winmain.cpp
  src/program_options/split.cpp
)
target_include_directories(boost_program_options PUBLIC include)
