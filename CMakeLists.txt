cmake_minimum_required(VERSION 3.0.0)
project(Cpp-Pong VERSION 0.1.0)

include(CTest)
enable_testing()

set (SFML_DIR "C:/Users/alija/Documents/GitHub/Cpp-Pong/SFML-2.5.1/lib/cmake/SFML/")
find_package(SFML 2.5.1 COMPONENTS graphics window system audio REQUIRED)
add_executable (Cpp-Pong pong3.cpp SFML-2.5.1/include/SFML/Graphics.hpp)
target_link_libraries(Cpp-Pong PRIVATE sfml-audio sfml-window sfml-system sfml-graphics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
