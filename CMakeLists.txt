cmake_minimum_required(VERSION 3.0)

# set project name
project(ASTUGame)

# add required libraries
add_subdirectory(${PROJECT_SOURCE_DIR}/astu astu)
add_subdirectory(${PROJECT_SOURCE_DIR}/astu-box2d astu_box2d)

# add sub-projects
add_subdirectory(${PROJECT_SOURCE_DIR}/wolfi-breakout wolfibreakout)