# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(project_anemoi)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

include_directories(
    bigint
)

set (SRCS
    bigint/vec.h
    bigint/auxiliary.cpp
    bigint/auxiliary.h
    bigint/bigint.h
    bigint/constructors.cpp
    bigint/functions.cpp
    bigint/functions.h
    bigint/operators.cpp
    main.cpp
)


add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

