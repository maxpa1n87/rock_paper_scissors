cmake_minimum_required(VERSION 4.4)

project(rock_paper_scissors  VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_C_FLAGS /IGNORE:C4996)
endif()

configure_file(rock_paper_scissors_config.h.in rock_paper_scissors_config.h)

add_executable(rock_paper_scissors)

target_include_directories(rock_paper_scissors PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_sources(rock_paper_scissors
  PRIVATE
    main.c
)
