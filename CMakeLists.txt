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

add_executable(PROJECT_NAME main.cpp Game.cpp Game.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h Entities/Entity.cpp Entities/Entity.h States/MainMenuState.cpp States/MainMenuState.h GUI.cpp GUI.h Entities/Player.cpp Entities/Player.h GUI/PauseMenu.cpp GUI/PauseMenu.h States/SettingState.cpp States/SettingState.h GraphicsSettings.cpp GraphicsSettings.h Components/AnimationComponent.cpp Components/AnimationComponent.h Components/HitboxComponent.cpp Components/HitboxComponent.h Components/MovementComponent.cpp Components/MovementComponent.h)
target_link_libraries(PROJECT_NAME sfml-audio sfml-network sfml-graphics sfml-window sfml-system -static)
