add_library(core
    grafo.h grafo.cpp
    #maploader.h maploader.cpp // ainda vou arrumar isso
    dijkstra.h dijkstra.cpp
    trie.h
    trie.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
