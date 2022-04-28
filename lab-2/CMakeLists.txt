cmake_minimum_required(VERSION 3.20)
project(lab_2)

set(CMAKE_CXX_STANDARD 14)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(
        lab_2
        main.cpp
        Vector.cpp
        Point.cpp
)

target_link_libraries(lab_2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

