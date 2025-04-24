
cmake_minimum_required(VERSION 3.10)
project(OpenGlings)

set(CMAKE_CXX_STANDARD 17)

add_executable(Main src/main.cpp)


# open gl
include_directories(${CMAKE_SOURCE_DIR}/include)

# Dodaj pliki źródłowe GLAD do projektu
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/glad.c)

# Linkuj GLAD z Twoim plikiem wykonywalnym
target_link_libraries(Main glad)

