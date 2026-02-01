#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct TrieNode { // nó da árvore
    unordered_map<char, TrieNode*> children; // mapa de caracteres para filhos
    bool isEndOfWord; // marca se este nó é o fim de uma palavra válida

    // lista de ids dos nós do grafo que correspondem a este nome de rua
    vector<long long> nodeIds;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    Trie();
    ~Trie(); // limpa memoria

    // insere um nome de rua e associa ao id do nó
    void insert(const string& word, long long nodeId);

    // retorna lista de sugestões dado um prefixo - AUTOCOMPLETE
    vector<string> autocomplete(const string& prefix);

    // retorna o ID do nó associado a uma palavra exata (-1 se nao achar
    long long buscarId(const string& word);

private:
    TrieNode* root;

    void collectWords(TrieNode* node, string currentPrefix, vector<string>& results); // recursao
    void clear(TrieNode* node); // confirma pra limpar memoria
};

#endif // TRIE_H
