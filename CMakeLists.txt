cmake_minimum_required(VERSION 3.0.2)

#-------------------------------------------------------------------------------
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "The build directory can not equal source!!!")
endif()

if(NOT (CMAKE_BUILD_TYPE))
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Тип сборки" FORCE)
  message(STATUS "Set default build type: ${CMAKE_BUILD_TYPE}")
else()
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()

#-------------------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------------------------------------------------------
project(GTK_EXAMPLE LANGUAGES C CXX)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#-------------------------------------------------------------------------------
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtkmm-3.0)

#-------------------------------------------------------------------------------
set(SOURCES_FILES
  main.cpp
  global.cpp
  gui.cpp
  worker.cpp
)

set(HEADERS_FILES
  global.h
  gui.h
  worker.h
)

#-------------------------------------------------------------------------------
set(app_target "gtk-example")
add_executable(${app_target}
  ${SOURCES_FILES}
  ${HEADERS_FILES}
)

target_include_directories(${app_target} PRIVATE ${GTK_INCLUDE_DIRS})

target_link_libraries(${app_target} PRIVATE Threads::Threads)
target_link_libraries(${app_target} PRIVATE ${GTK_LIBRARIES})
