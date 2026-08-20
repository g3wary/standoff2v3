cmake_minimum_required(VERSION 3.18.1)
project("standoff2external")

add_library(
    standoff2external
    SHARED
    src/main/cpp/main.cpp
)

find_library(log-lib log)

target_link_libraries(
    standoff2external
    ${log-lib}
)
