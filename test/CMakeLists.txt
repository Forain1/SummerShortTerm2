cmake_minimum_required(VERSION 3.19)
project(HealthModelTest LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(HealthModelTest
    healthmodeltest.cpp
    ../model/character.cpp
    ../model/characterstate.cpp
    ../model/topmodel.cpp
    ../model/scenestate.cpp
)

target_include_directories(HealthModelTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../model
    ../common
)

target_link_libraries(HealthModelTest PRIVATE Qt6::Test)

# 运行测试
add_test(NAME HealthModelTest COMMAND HealthModelTest) 