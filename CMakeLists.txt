# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.

cmake_minimum_required(VERSION 3.8)

enable_testing()

add_custom_target(check
  COMMAND "${CMAKE_CTEST_COMMAND}" --output-on-failure
  COMMENT "Build and run all the unit tests."
  USES_TERMINAL)

find_package(Dyno REQUIRED)
find_package(CallableTraits REQUIRED)
find_package(Hana REQUIRED)

file(GLOB examples RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/code" "code/*.cpp")
foreach(example IN LISTS examples)
  string(REGEX REPLACE "\\.cpp" "" example "${example}")
  add_executable(${example} code/${example}.cpp)
  target_compile_features(${example} PRIVATE cxx_std_14)
  target_link_libraries(${example} PRIVATE Dyno::dyno)
  add_dependencies(check ${example})

  add_test(${example} ${example})
endforeach()
