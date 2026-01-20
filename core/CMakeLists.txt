add_library(core
    grafo.cpp
    maploader.h maploader.cpp
    dijkstra.h dijkstra.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
