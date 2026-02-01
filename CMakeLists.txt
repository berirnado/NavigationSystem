cmake_minimum_required(VERSION 3.19)

project(sistema_navegacao LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Quick QuickWidgets Location Positioning)

qt_standard_project_setup()

add_subdirectory(ui)
add_subdirectory(core)

qt_add_executable(sistema_navegacao
    main.cpp
)

qt_add_resources(sistema_navegacao "recursos_mapa"
    PREFIX "/"
    BASE "ui"
    FILES "ui/mapa.qml"
)

target_link_libraries(sistema_navegacao
    PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Quick
    Qt::QuickWidgets
    Qt::Location
    Qt::Positioning
    core
    ui
)

add_custom_command(TARGET sistema_navegacao POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMENT "Copiando pasta data para o diretório de execução..."
)
