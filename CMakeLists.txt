cmake_minimum_required(VERSION 3.12)
project(Modelisation3D_TP4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GSL REQUIRED)

list(APPEND EXTRA_DIRS ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} ${GSL_INCLUDE_DIRS})
list(APPEND EXTRA_LIBS ${OPENGL_LIBRARIES} ${GSL_LIBRARIES})

if(APPLE)
    list(APPEND EXTRA_LIBS "/Library/Developer/CommandLineTools/SDKs/MacOSX12.3.sdk/System/Library/Frameworks/GLUT.framework")
else()
    list(APPEND EXTRA_LIBS ${GLUT_LIBRARIES})
endif()

include_directories(
        ${EXTRA_DIRS}
)

add_executable(
        tp
        tp.cpp

        src/Camera.cpp src/Camera.h
        src/Trackball.cpp   src/Trackball.h
        src/Vec3.h

        surface_cylindrique/surface_cylindrique.cpp surface_cylindrique/surface_cylindrique.h
        surface_reglee/surface_reglee.cpp surface_reglee/surface_reglee.h
        surface_bernstein/surface_bernstein.cpp surface_bernstein/surface_bernstein.h

        parametric_curves/hermite.cpp parametric_curves/hermite.h
        parametric_curves/berstein.cpp parametric_curves/berstein.h
        parametric_curves/casteljau.cpp parametric_curves/casteljau.h
)
target_link_libraries(
        tp
        ${EXTRA_LIBS}
)
