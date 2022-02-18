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

add_executable(PROJECT_NAME main.cpp Game.cpp Game.h Entities/Entity.cpp Entities/Entity.h Entities/Player.cpp Entities/Player.h GUI/PauseMenu.cpp GUI/PauseMenu.h Components/AnimationComponent.cpp Components/AnimationComponent.h Components/AttributeComponent.cpp Components/AttributeComponent.h Components/EnemyAttributeComponent.cpp Components/EnemyAttributeComponent.h Entities/Archer.cpp Entities/Archer.h Entities/Enemy.cpp Entities/Enemy.h Entities/Humanoid.cpp Entities/Humanoid.h Entities/Slime.cpp Entities/Slime.h Entities/Warrior.cpp Entities/Warrior.h Entities/Wizard.cpp Entities/Wizard.h GUI/GUI.cpp GUI/GUI.h GUI/PlayerGUI.cpp GUI/PlayerGUI.h Map/Gold.cpp Map/Gold.h Map/Items.cpp Map/Items.h Map/Level.cpp Map/Level.h Map/Object.cpp Map/Object.h Map/Potion.cpp Map/Potion.h Map/Torch.cpp Map/Torch.h Projectile/Projectile.cpp Projectile/Projectile.h Systems/CharacterSelection.cpp Systems/CharacterSelection.h Systems/MainMenu.cpp Systems/MainMenu.h Systems/Shop.cpp Systems/Shop.h Systems/TextTagSystem.cpp Systems/TextTagSystem.h Achievements.cpp Achievements.h ConditionAchievement.cpp ConditionAchievement.h Input.cpp Input.h Observable.cpp Observable.h Observer.h TextureManager.cpp TextureManager.h Util.h)
target_link_libraries(PROJECT_NAME sfml-audio sfml-network sfml-graphics sfml-window sfml-system -static)
