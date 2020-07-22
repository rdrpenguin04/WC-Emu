cmake_minimum_required(VERSION 3.15)
project(WC-Emu CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(LCLib-CXX)

add_executable(wcEmu src/bus.cpp src/main.cpp src/w65c816s.cpp src/components/component.hpp
        src/bus.hpp src/w65c816s.hpp)
target_link_libraries(wcEmu lc-c++)

add_executable(wcConnect src/connect.cpp)
target_link_libraries(wcConnect lc-c++)

set(WCEMU_COMPONENTS charPort ram rom)

foreach(component ${WCEMU_COMPONENTS})
    add_library(component-${component} OBJECT src/components/component.hpp src/components/${component}.hpp src/components/${component}.cpp)
    target_link_libraries(wcEmu component-${component})
endforeach()
