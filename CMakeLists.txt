cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME Elaborato-di-Programmazione)

project(${PROJECT_NAME})

set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML REQUIRED COMPONENTS audio network graphics window system)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML NOT FOUND!")
else()
    message("SFML FOUND!")
endif()

add_executable(PROJECT_NAME main.cpp Game.cpp Game.h GraphicSettings.cpp GraphicSettings.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h States/MainMenuState.cpp States/MainMenuState.h GUI.cpp GUI.h)
target_link_libraries(PROJECT_NAME sfml-audio sfml-network sfml-graphics sfml-window sfml-system -static)
