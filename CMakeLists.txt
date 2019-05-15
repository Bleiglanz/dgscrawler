cmake_minimum_required(VERSION 3.1)
project(dgscrawler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dgscrawler
        cpl_config.h
        cpl_conv.cpp
        cpl_conv.h
        cpl_dir.cpp
        cpl_error.cpp
        cpl_error.h
        cpl_multiproc.cpp
        cpl_multiproc.h
        cpl_path.cpp
        cpl_port.h
        cpl_string.cpp
        cpl_string.h
        cpl_vsi.h
        cpl_vsil_simple.cpp
        cpl_vsisimple.cpp
        dgndump.c
        dgnfloat.cpp
        dgnhelp.cpp
        dgnlib.h
        dgnlibp.h
        dgnopen.cpp
        dgnread.cpp
        dgnstroke.cpp
        dgnwrite.cpp
        dgnwritetest.c
        main.cpp)
