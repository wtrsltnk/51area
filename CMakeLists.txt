cmake_minimum_required(VERSION 3.1)

project(51Area)

find_package(OpenGL REQUIRED)

set(SRC_APP
    Area.cpp
    GraphicsEngine.cpp
    GraphicsEngine.h
    GraphicsView.cpp
    GraphicsView.h
    Main.cpp
#    Main52.cpp
    resource.h
    scrnsvr.rc
    Settings.cpp
    )

add_executable(51Area WIN32
    ${SRC_APP}
	)

find_file(SCRNSAVE scrnsave)
message(${SCRNSAVE})
target_link_libraries(51Area
    ${OPENGL_LIBRARIES}
    scrnsave
    comctl32
    winmm
    )

target_compile_features(51Area
	PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)
