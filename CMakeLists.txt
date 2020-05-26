cmake_minimum_required(VERSION 2.8)

project(trab_visao2)
LINK_LIBRARIES(SDL2main SDL2 SDL2_image)
add_executable(${PROJECT_NAME} main.c sprites.c)
