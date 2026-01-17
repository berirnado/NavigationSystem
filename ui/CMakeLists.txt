qt_add_library(ui
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_include_directories(ui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ui
    PRIVATE Qt::Widgets
)
