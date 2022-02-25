cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
find_package(SFML REQUIRED COMPONENTS audio network graphics window system)
add_subdirectory(lib)
include_directories(googletest/include googletest)

add_executable(runTests runAllTests.cpp AchievementTest.cpp)
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests sfml-audio sfml-network sfml-graphics sfml-window sfml-system -static)

