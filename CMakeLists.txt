# [Copy and paste] - Bumped to 3.14 because FetchContent works best with this version or newer
cmake_minimum_required(VERSION 3.14)

# [Must understand] - Sets the name of your project
project(Meridian)

# [Must understand] - Tells CMake to generate a database of all compiler flags and include paths
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# [Must understand] - Sets C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Forces the line above by failing rather than falling back

# [Can understand if you really want to, but not necessary] - This block automatically 
# downloads the official SDL2 source code from GitHub and builds it right inside your project 
# so it works identically on Linux, Windows, and macOS without needing system-wide installers.
include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-2.30.0
)
FetchContent_MakeAvailable(SDL2)

# [Must understand] - Defines your executable and lists your source files
add_executable(Meridian 
    main.cpp
    Core/Window.cpp
    Core/Input.cpp
    Core/Game.cpp
    Scenes/Level.hpp
    Scenes/Level1.cpp
)

# [Must understand] - Links the automatically downloaded SDL2 library to your game
target_link_libraries(Meridian PRIVATE SDL2::SDL2)
