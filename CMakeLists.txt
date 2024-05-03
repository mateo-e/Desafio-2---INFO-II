cmake_minimum_required(VERSION 3.5)

project(desafio-2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(desafio-2 main.cpp
    Red.h
    Linea.h
    Estacion.h
    Red.cpp
    Linea.cpp
    Estacion.cpp

)

include(GNUInstallDirs)
install(TARGETS desafio-2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
