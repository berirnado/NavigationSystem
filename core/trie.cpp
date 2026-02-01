#include "trie.h"

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    clear(root);
}

void Trie::clear(TrieNode* node) {
    if (!node) return;
    for (auto& pair : node->children) {
        clear(pair.second);
    }
    delete node;
}

void Trie::insert(const string& word, long long nodeId) {
    TrieNode* current = root;

    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    current->isEndOfWord = true;
    current->nodeIds.push_back(nodeId);
}

vector<string> Trie::autocomplete(const string& prefix) {
    vector<string> results;
    TrieNode* current = root;

    for (char ch : prefix) {
        if (current->children.find(ch) == current->children.end()) {
            return results;
        }
        current = current->children[ch];
    }
    collectWords(current, prefix, results);
    return results;
}

void Trie::collectWords(TrieNode* node, string currentPrefix, vector<string>& results) {
    if (node->isEndOfWord) {
        results.push_back(currentPrefix);
    }

    for (auto& pair : node->children) {
        char ch = pair.first;
        TrieNode* childNode = pair.second;
        collectWords(childNode, currentPrefix + ch, results);
    }
}

// busca id

long long Trie::buscarId(const string& word) {
    TrieNode* current = root;

    // navega exatamente pela palavra digitada
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            return -1; // não encontrada
        }
        current = current->children[ch];
    }

    // se chegou ao fim, verifica se é uma palavra válida e retorna o primeiro ID
    if (current->isEndOfWord && !current->nodeIds.empty()) {
        return current->nodeIds[0];
    }

    return -1; // palavra existe como prefixo, mas não é um destino marcado
}
