# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.

cmake_minimum_required(VERSION 3.8)

include(ExternalProject)

ExternalProject_Add(Hana
  URL https://github.com/boostorg/hana/archive/develop.zip
  INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_PREFIX_PATH="${CMAKE_INSTALL_PREFIX}"
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)

ExternalProject_Add(CallableTraits
  URL https://github.com/badair/callable_traits/archive/master.zip
  INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_PREFIX_PATH="${CMAKE_INSTALL_PREFIX}"
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)

ExternalProject_Add(Awful
  URL https://github.com/ldionne/libawful/archive/master.zip
  INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_PREFIX_PATH="${CMAKE_INSTALL_PREFIX}"
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)

ExternalProject_Add(GoogleBenchmark
  URL https://github.com/google/benchmark/archive/master.zip
  INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
  CMAKE_ARGS "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
             "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
             "-DCMAKE_PREFIX_PATH=${CMAKE_INSTALL_PREFIX}"
             "-DBENCHMARK_ENABLE_TESTING=OFF"
             "-DCMAKE_BUILD_TYPE=Release" # Always build in release mode
  UPDATE_COMMAND "" # Disable source work-tree update
)

ExternalProject_Add(Dyno
  URL https://github.com/ldionne/dyno/archive/master.zip
  INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_PREFIX_PATH="${CMAKE_INSTALL_PREFIX}"
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)
add_dependencies(Dyno CallableTraits Hana Awful GoogleBenchmark)
