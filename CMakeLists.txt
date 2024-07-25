project(C-gtk C)

cmake_minimum_required(VERSION 3.22)
set(CMAKE_C_STANDARD 11)

execute_process(COMMAND bash -c "pkg-config --modversion gtk4"
        OUTPUT_VARIABLE gtk4_version
        RESULT_VARIABLE gtk4_success)

message(STATUS "The gtk4 version is: ${gtk4_version}")

if(NOT ${gtk4_success} EQUAL 0)
    message("The shell command failed with error: ${gtk4_success}")
endif()


add_executable(C-gtk main.c)

target_link_libraries(C-gtk PRIVATE m)
