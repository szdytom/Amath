cmake_minimum_required(VERSION 3.16)

PROJECT(LighteningSlide)

INCLUDE_DIRECTORIES(
    include/
)

SET(CMAKE_CXX_STANDARD 17)

SET(SRC_LIB_LIST 
    ${PROJECT_SOURCE_DIR}/src/tree.cc
)