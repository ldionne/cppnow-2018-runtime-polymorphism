#!/usr/bin/env bash

set -e

CMAKE_SOURCE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CMAKE_BINARY_DIR="${CMAKE_SOURCE_DIR}/build"
CMAKE_INSTALL_PREFIX="${CMAKE_SOURCE_DIR}/install"

rm -rf "${CMAKE_INSTALL_PREFIX}" "${CMAKE_BINARY_DIR}"
mkdir -p "${CMAKE_INSTALL_PREFIX}" "${CMAKE_BINARY_DIR}"
(cd "${CMAKE_BINARY_DIR}" &&
  cmake "${CMAKE_SOURCE_DIR}" -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" "${@}" >2)
cmake --build "${CMAKE_BINARY_DIR}" >&2

echo "${CMAKE_INSTALL_PREFIX}"