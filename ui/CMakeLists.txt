add_library(ui STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ui PUBLIC
    Qt::Widgets
    Qt::Quick
    Qt::QuickWidgets
    Qt::Location
    Qt::Positioning
    core
)
