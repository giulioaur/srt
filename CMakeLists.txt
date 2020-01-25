cmake_minimum_required(VERSION 3.0)
project(SRT)

set(CMAKE_CXX_STANDARD 17)

######################### DEFAULT MODE #########################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

######################### TARGET FILE #########################
if(NOT TARGET_FILE)
  set(TARGET_FILE basic_raytracer)
endif(NOT TARGET_FILE)

######################### RAYTRACER FILES #########################
set(SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/source)
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${SOURCE_DIRECTORY}/*.cpp)
file(GLOB_RECURSE PROJECT_INCLUDE_FILES ${SOURCE_DIRECTORY}/*.hpp ${SOURCE_DIRECTORY}/*.h)
list (APPEND PROJECT_FILES ${PROJECT_SOURCE_FILES})
list (APPEND PROJECT_FILES ${PROJECT_INCLUDE_FILES})

foreach(_source IN ITEMS ${PROJECT_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

######################### EXAMPLES #########################
set(EXAMPLE_SOURCE_FILES ${PROJECT_SOURCE_DIR}/example/cornell_box.cpp)

######################### EXECUTABLE #########################
add_executable(${TARGET_FILE} ${EXAMPLE_SOURCE_FILES} ${PROJECT_FILES})

######################### COMPILER OPTIONS #########################
set (CMAKE_CXX_FLAGS_DEBUG "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

######################### ADD LIBRARIES #########################
include_directories(libraries ${SOURCE_DIRECTORY}/includes)

######################### CONFIGURE FILES #########################
set(CONFIGURE_DIR ${PROJECT_SOURCE_DIR}/source/configuration_files)
configure_file(${CONFIGURE_DIR}/paths.h.in ${SOURCE_DIRECTORY}/includes/paths.h)

######################### THREAD OPTIONS #########################
# if(NOT TARGET_FILE STREQUAL "basic_raytracer")
#   message("Using thread")
#   set(THREADS_PREFER_PTHREAD_FLAG ON)
#   find_package(Threads REQUIRED)
#   target_link_libraries(${TARGET_FILE} Threads::Threads)
# endif(NOT TARGET_FILE STREQUAL "basic_raytracer")

######################### OPENMP #########################
find_package(OpenMP)
if (OPENMP_CXX_FOUND)
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenMP_CXX_FLAGS}")
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif(OPENMP_CXX_FOUND)

######################### PROFILING #########################
if(PROFILE)
  MESSAGE(STATUS "Profiling...")
  set (CMAKE_CXX_FLAGS_DEBUG "-pg -no-pie")
  set (CMAKE_CXX_FLAGS_RELEASE "-pg -no-pie")
endif(PROFILE)