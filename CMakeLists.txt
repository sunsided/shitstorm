cmake_minimum_required(VERSION 2.6)

project(Vector)

#SET(CMAKE_FIND_LIBRARY_PREFIXES "")
#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
set(CMAKE_CXX_FLAGS "-g -Wall")

if(BULLET_ROOT)
else(BULLET_ROOT)
	set(BULLET_ROOT "~/dev/lib/bullet/")
endif(BULLET_ROOT)

find_package(Irrlicht REQUIRED)
find_package(Bullet REQUIRED)
find_package(Squirrel REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OggVorbis REQUIRED)

FILE(GLOB ALL_CPP "*.cpp")
FILE(GLOB ALL_H "*.h")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${IRRLICHT_INCLUDE_DIR})
include_directories(${BULLET_INCLUDE_DIR})
include_directories(${OPENAL_INCLUDE_DIR})
include_directories(${OGG_INCLUDE_DIR})
include_directories(${VORBIS_INCLUDE_DIR})
include_directories(${SQRAT_INCLUDE_DIR})
include_directories(${SQUIRREL_INCLUDE_DIR})
add_subdirectory(src)
add_executable(vector src/main.cpp)
