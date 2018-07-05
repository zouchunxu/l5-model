cmake_minimum_required(VERSION 3.7)

project(l5_model)
add_custom_target(makefile COMMAND make && sudo make install WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})