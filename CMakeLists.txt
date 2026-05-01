cmake_minimum_required(VERSION 3.10...3.30)

# Make set() override option() in submodules (so USE_SDL below sticks).
cmake_policy(SET CMP0077 NEW)

# generate a compile_commands.json file for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(USE_SDL ON CACHE BOOL "Enable SDL backend in astu" FORCE)

# set project name
project(WolfiBreakout)

# add required libraries (vendored under third_party/)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/astu astu)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/astu-box2d astu_box2d)

# add sub-projects
add_subdirectory(${PROJECT_SOURCE_DIR}/wolfi-breakout wolfibreakout)
