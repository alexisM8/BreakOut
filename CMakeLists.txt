cmake_minimum_required(VERSION 3.21.1)

IF(APPLE)
  SET(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
ENDIF(APPLE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BreakOut)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(BUILD_STATIC FALSE CACHE STRING "Set this to link external libraries statically")

if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")

# Find SFML
if (SFML_OS_WINDOWS AND SFML_COMPILER_MSVC)
    find_package( SFML 2 COMPONENTS main audio graphics window system REQUIRED)
else()
    find_package( SFML 2 COMPONENTS audio graphics window system REQUIRED)
endif()

if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
else()
        set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
        message("\nSFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
        message("Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()


add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(mylib
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AssetManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helperLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainMenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PauseGame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/StateManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/WinOrLose.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Controls.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Textbox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SaveScore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LeaderBoard.cpp
    )

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_link_libraries(${PROJECT_NAME} mylib)
