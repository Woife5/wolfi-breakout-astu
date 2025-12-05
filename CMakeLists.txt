cmake_minimum_required(VERSION 3.5)

# generate a compile_commands.json file for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(USE_SDL ON)

# set project name
project(ASTUGame)

# add required libraries
add_subdirectory(${PROJECT_SOURCE_DIR}/astu astu)
add_subdirectory(${PROJECT_SOURCE_DIR}/astu-box2d astu_box2d)

# add sub-projects
add_subdirectory(${PROJECT_SOURCE_DIR}/wolfi-breakout wolfibreakout)
