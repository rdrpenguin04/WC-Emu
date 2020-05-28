cmake_minimum_required(VERSION 3.15)
project(WC-Emu CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_executable(wcEmu src/bus.cpp src/socket.cpp src/main.cpp src/w65c816s.cpp src/components/component.hpp
        src/bus.hpp src/socket.hpp src/w65c816s.hpp)

add_executable(wcConnect src/socket.cpp src/socket.hpp src/connect.cpp)

set(WCEMU_COMPONENTS charPort ram rom)

foreach(component ${WCEMU_COMPONENTS})
    add_library(component-${component} OBJECT src/components/component.hpp src/components/${component}.hpp src/components/${component}.cpp)
    target_link_libraries(wcEmu component-${component})
endforeach()
