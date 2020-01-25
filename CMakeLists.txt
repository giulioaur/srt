cmake_minimum_required(VERSION 3.0)
project(SRT)

set(CMAKE_CXX_STANDARD 17)

#########################DEFAULT MODE#########################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

#########################TARGET FILE#########################
if(NOT TARGET_FILE)
  set(TARGET_FILE basic_raytracer)
endif(NOT TARGET_FILE)

#########################DIRECTORIES#########################
set(MYBASE_DIR src/srt)
set(GEOMETRY_DIR ${MYBASE_DIR}/geometry)
set(STRUCTURES_DIR ${MYBASE_DIR}/structures) 
set(UTILITY_DIR ${MYBASE_DIR}/utility)
set(MATERIALS_DIR ${MYBASE_DIR}/materials)
set(DS_DIR ${MYBASE_DIR}/ds)
set(TEXTURES_DIR ${MYBASE_DIR}/textures)

#########################SOURCE FILES#########################
set(SRT_FILES 
              ${MYBASE_DIR}/Scene.cpp
              ${MYBASE_DIR}/Camera.cpp
              ${MYBASE_DIR}/Hitable.cpp )
set(GEOMETRY_FILES
               ${GEOMETRY_DIR}/AABB.cpp
               ${GEOMETRY_DIR}/shapes/Sphere.cpp
               ${GEOMETRY_DIR}/shapes/MovingSphere.cpp
               ${GEOMETRY_DIR}/shapes/AARectangle.cpp
               ${GEOMETRY_DIR}/shapes/AABox.cpp
               ${GEOMETRY_DIR}/instances/Translation.cpp
               ${GEOMETRY_DIR}/instances/Rotation.cpp)
set(UTILITY_FILES 
                  ${UTILITY_DIR}/Stopwatch.cpp
                  ${UTILITY_DIR}/FileManager.cpp
                  )
set(MATERIAL_FILES 
                   ${MATERIALS_DIR}/Lambertian.cpp
                   ${MATERIALS_DIR}/Metal.cpp
                   ${MATERIALS_DIR}/Dielectric.cpp
                   ${MATERIALS_DIR}/lights/DiffuseLight.cpp)
set(DS_FILES 
             ${DS_DIR}/BVH.cpp)
set(TEXTURES_FILES 
                   ${TEXTURES_DIR}/StaticTexture.cpp
                   ${TEXTURES_DIR}/CheckerTexture.cpp
                   ${TEXTURES_DIR}/ImageTexture.cpp)
set(MAIN_FILE example/${TARGET_FILE}.cpp)

#########################EXECUTABLE#########################
add_executable(${TARGET_FILE} ${MAIN_FILE} ${SRT_FILES} ${GEOMETRY_FILES} ${MATERIAL_FILES} ${DS_FILES} ${TEXTURES_FILES} ${UTILITY_FILES})

#########################COMPILER OPTIONS#########################
set (CMAKE_CXX_FLAGS_DEBUG "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

#########################ADD LIBRARIES#########################
include_directories(libraries)

#########################CONFIGURE FILES#########################
set(CONFIGURE_DIR src/configuration_files)
configure_file(${CONFIGURE_DIR}/paths.h.in ${CMAKE_CURRENT_SOURCE_DIR}/${MYBASE_DIR}/paths.h)

#########################THREAD OPTIONS#########################
# if(NOT TARGET_FILE STREQUAL "basic_raytracer")
#   message("Using thread")
#   set(THREADS_PREFER_PTHREAD_FLAG ON)
#   find_package(Threads REQUIRED)
#   target_link_libraries(${TARGET_FILE} Threads::Threads)
# endif(NOT TARGET_FILE STREQUAL "basic_raytracer")

#########################OPENMP#########################
find_package(OpenMP)
if (OPENMP_CXX_FOUND)
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenMP_CXX_FLAGS}")
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif(OPENMP_CXX_FOUND)

#########################PROFILING#########################
if(PROFILE)
  MESSAGE(STATUS "Profiling...")
  set (CMAKE_CXX_FLAGS_DEBUG "-pg -no-pie")
  set (CMAKE_CXX_FLAGS_RELEASE "-pg -no-pie")
endif(PROFILE)