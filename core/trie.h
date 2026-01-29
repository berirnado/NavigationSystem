#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


struct TrieNode { // nó da árvore
    unordered_map<char, TrieNode*> children; // mapa de caracteres para filhos (flexível)
    bool isEndOfWord; // marca se este nó é o fim de uma palavra válida

    //lista de ids dos nós do grafo que correspondem a este nome de rua(util depois para saber onde a rua fica no mapa)
    vector<long long> nodeIds;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    Trie();
    ~Trie(); // destrutor para limpar a memória

    void insert(const string& word, long long nodeId); // insere um nome de rua e associa ao id do nó

    vector<string> autocomplete(const string& prefix); // retorna lista de sugestões dado um prefixo

private:
    TrieNode* root;

    void collectWords(TrieNode* node, string currentPrefix, vector<string>& results); // auxiliar recursivo para buscar palavras
    void clear(TrieNode* node); //auxiliar para limpar memória
};

#endif
