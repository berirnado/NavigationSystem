qt_add_library(ui
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(ui
    PRIVATE Qt::Widgets
)
