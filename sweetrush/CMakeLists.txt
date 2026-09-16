cmake_minimum_required(VERSION 3.16)

project(sweetrush LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sweetrush main.cpp
    tablero.cpp
    tablero.h
    juego.h
    juego.cpp)

include(GNUInstallDirs)
install(TARGETS sweetrush
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
