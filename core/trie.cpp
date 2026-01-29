#include "trie.h"

Trie::Trie() { // construtor que inicializa a raiz
    root = new TrieNode();
}

Trie::~Trie() { // destrutor que limpa toda a memória ao fechar o programa
    clear(root);
}

void Trie::clear(TrieNode* node) { // função auxiliar para deletar nós recursivamente
    if (!node) return;

    for (auto& pair : node->children) { // deleta todos os filhos
        clear(pair.second);
    }
    delete node;
}

void Trie::insert(const string& word, long long nodeId) { // insere uma palavra na árvore
    TrieNode* current = root;

    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) { //se a letra não existe, cria um novo nó
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch]; //avança para o próximo nó
    }
    current->isEndOfWord = true; //marca o final da palavra e salva o ID do nó do grafo
    current->nodeIds.push_back(nodeId);
}

vector<string> Trie::autocomplete(const string& prefix) { // busca sugestões de autocomplete
    vector<string> results;
    TrieNode* current = root;

    for (char ch : prefix) { // navega até o final do prefixo digitado
        if (current->children.find(ch) == current->children.end()) { // se o caminho não existe, retorna vazio
            return results;
        }
        current = current->children[ch];
    }
    collectWords(current, prefix, results); // a partir dali coleta todas as palavras completas abaixo
    return results;
}

void Trie::collectWords(TrieNode* node, string currentPrefix, vector<string>& results) { // função recursiva pra achar as palavras
    if (node->isEndOfWord) { // se achou uma palavra válida adiciona na lista
        results.push_back(currentPrefix);
    }


    for (auto& pair : node->children) { // continua procurando nos filhos
        char ch = pair.first;
        TrieNode* childNode = pair.second;
        collectWords(childNode, currentPrefix + ch, results);
    }
}
