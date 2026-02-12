#include "trie.h"

//construtor
Trie::Trie() {// inicializa a trie criando apenas o no raiz
    root = new TrieNode();
}

//destrutor
Trie::~Trie() {//chamado automaticamente quando o objeto trie deixa de existir
    clear(root); //chamado na funcao clear pra que nao tenha vazamento de memoria
}

void Trie::clear(TrieNode* node) {//funcao recursiva que percorre a arvore inteira para deletar cada no criado
    if (!node) return;
    for (auto& pair : node->children) {//percorre todos os filhos do no atual e chama clear neles
        clear(pair.second);
    }
    delete node;
}

//adiciona um nome de rua na arvore e vincula ele ao ID do no do grafo
void Trie::insert(const string& word, long long nodeId) {
    TrieNode* current = root;
    
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {//se a letra atual nao existe nos filhos do no atual
            current->children[ch] = new TrieNode();//cria um novo no para essa letra
        }
        current = current->children[ch];
    }
    
    current->isEndOfWord = true;
    
    current->nodeIds.push_back(nodeId); //adiciona o id do grafo na lista
}

vector<string> Trie::autocomplete(const string& prefix) {//recebe o que o usuario digitou e retorna lista de palavras
    vector<string> results;
    TrieNode* current = root;
    
    for (char ch : prefix) {//se o usuario digitou av ele desce no 'A' e depois no 'v'.
        if (current->children.find(ch) == current->children.end()) {
            return results;
        }
        current = current->children[ch];
    }
    
    collectWords(current, prefix, results);//agora chama a funcao auxiliar para coletar todas as palavras que nascem desse ponto
    return results;
}


void Trie::collectWords(TrieNode* node, string currentPrefix, vector<string>& results) {// navega recursivamente por todos os ramos abaixo de um no para achar palavras completas
    if (node->isEndOfWord) { //se o no atual estiver marcado como final de uma palavra valida adiciona na lista de resultados
        results.push_back(currentPrefix);
    }

    for (auto& pair : node->children) {//continua explorando todos os filhos deste no
        char ch = pair.first;
        TrieNode* childNode = pair.second;
        
        collectWords(childNode, currentPrefix + ch, results);//chama a função novamente adicionando a nova letra ao prefixo
    }
}

// busca id

long long Trie::buscarId(const string& word) {
    TrieNode* current = root;

    // navega exatamente pela palavra digitada
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            return -1; // nao encontrada
        }
        current = current->children[ch];
    }

    // se chegou ao fim, verifica se é uma palavra valida e retorna o primeiro ID
    if (current->isEndOfWord && !current->nodeIds.empty()) {
        return current->nodeIds[0];
    }

    return -1; // palavra existe como prefixo, mas nao é um destino marcado
}
