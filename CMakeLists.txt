cmake_minimum_required(VERSION 3.19)

project(sistema_navegacao LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_subdirectory(ui)

qt_add_executable(sistema_navegacao
    main.cpp
)

target_link_libraries(sistema_navegacao
    PRIVATE
        Qt::Core
        Qt::Widgets
        ui
)
