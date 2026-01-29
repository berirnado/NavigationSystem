add_library(core
    grafo.h grafo.cpp
    # maploader.h maploader.cpp  <-- Comentei com #
    # dijkstra.h dijkstra.cpp    <-- Comentei com #
    trie.h
    trie.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
