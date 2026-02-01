cmake_minimum_required(VERSION 3.19)

project(sistema_navegacao LANGUAGES CXX)

# O ERRO ESTAVA AQUI: É necessário carregar "Quick" e "QuickWidgets" aqui no topo
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Quick QuickWidgets Location Positioning)

qt_standard_project_setup()

add_subdirectory(ui)
add_subdirectory(core)

qt_add_executable(sistema_navegacao
    main.cpp
)

qt_add_resources(sistema_navegacao "recursos_mapa"
    PREFIX "/"          # O endereço será qrc:/...
    BASE "ui"           # Ignora a pasta "ui" no nome final
    FILES "ui/mapa.qml" # O arquivo real no disco
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
