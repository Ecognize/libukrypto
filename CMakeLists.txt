# MIT License
#
# Copyright (c) 2016 Erint Labs OÜ
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.1)
project(libukrypto)

# FIXME make testing optional and disabled if check not found

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeModules/)
find_package(Check REQUIRED)
find_package(OpenSSL REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/)
enable_testing()

# TODO: make legacy.c a conditional source
add_library(ukrypto SHARED src/e_ukrypto.c 
    src/gost_hash.c
    src/gost_dsa.c
    src/magma.c
    src/kalyna.c
    src/kupyna.c
    src/dstu_ecdsa.c
    src/legacy.c)
set_property(TARGET ukrypto PROPERTY C_STANDARD 99)

link_directories(${CHECK_LIBRARY_DIRS})
# add_executable(test_gost_34.311-95 tests/test_gost_34.311-95.c)
target_link_libraries(ukrypto ${OPENSSL_LIBRARIES})
# target_link_libraries(test_gost_34.311-95 ${CHECK_LIBRARIES} ukrypto)
# set_property(TARGET test_gost_34.311-95 PROPERTY C_STANDARD 99)
add_test(test_openssl_engine ${PROJECT_SOURCE_DIR}/tests/test_openssl_engine.sh ${CMAKE_CURRENT_BINARY_DIR})
# add_test(test_gost_34.311-95 ${CMAKE_CURRENT_BINARY_DIR}/test_gost_34.311-95)
