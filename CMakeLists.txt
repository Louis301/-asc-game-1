cmake_minimum_required(VERSION 3.20)
project(ProjectSB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавьте все ваши .cpp файлы
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCES})