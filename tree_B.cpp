// Joao Victor de Moraes da Cruz - Trabalho P2 (individual)
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* esquerda;
    No* direita;
};

No* inserir(No* raiz, int valor) {
    if (raiz == nullptr) return new No{valor, nullptr, nullptr};
    if (valor < raiz->valor) raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor) raiz->direita = inserir(raiz->direita, valor);
    return raiz; // Valores repetidos nao criam novos nos.
}

bool buscar(const No* raiz, int valor) {
    while (raiz != nullptr) {
        if (valor == raiz->valor) return true;
        raiz = valor < raiz->valor ? raiz->esquerda : raiz->direita;
    }
    return false;
}

No* remover(No* raiz, int valor) {
    if (raiz == nullptr) return nullptr;
    if (valor < raiz->valor) raiz->esquerda = remover(raiz->esquerda, valor);
    else if (valor > raiz->valor) raiz->direita = remover(raiz->direita, valor);
    else {
        if (raiz->esquerda == nullptr) {
            No* filho = raiz->direita;
            delete raiz;
            return filho;
        }
        if (raiz->direita == nullptr) {
            No* filho = raiz->esquerda;
            delete raiz;
            return filho;
        }
        No* sucessor = raiz->direita;
        while (sucessor->esquerda != nullptr) sucessor = sucessor->esquerda;
        raiz->valor = sucessor->valor;
        raiz->direita = remover(raiz->direita, sucessor->valor);
    }
    return raiz;
}

void emOrdem(const No* raiz) {
    if (raiz == nullptr) return;
    emOrdem(raiz->esquerda);
    cout << raiz->valor << " ";
    emOrdem(raiz->direita);
}

void preOrdem(const No* raiz) {
    if (raiz == nullptr) return;
    cout << raiz->valor << " ";
    preOrdem(raiz->esquerda);
    preOrdem(raiz->direita);
}

void posOrdem(const No* raiz) {
    if (raiz == nullptr) return;
    posOrdem(raiz->esquerda);
    posOrdem(raiz->direita);
    cout << raiz->valor << " ";
}

void liberar(No* raiz) {
    if (raiz == nullptr) return;
    liberar(raiz->esquerda);
    liberar(raiz->direita);
    delete raiz;
}

int main() {
    No* raiz = nullptr;
    int opcao, valor;
    do {
        cout << "\n1 - Inserir\n2 - Buscar\n3 - Remover\n4 - Em ordem\n"
             << "5 - Pre-ordem\n6 - Pos-ordem\n0 - Sair\nOpcao: ";
        if (!(cin >> opcao) || opcao < 0 || opcao > 6) {
            cerr << "Opcao invalida.\n";
            liberar(raiz);
            return 1;
        }
        if (opcao >= 1 && opcao <= 3) {
            cout << "Valor: ";
            if (!(cin >> valor)) {
                cerr << "Valor invalido.\n";
                liberar(raiz);
                return 1;
            }
            if (opcao == 1) {
                if (buscar(raiz, valor)) cout << "Valor ja existe.\n";
                else {
                    raiz = inserir(raiz, valor);
                    cout << "Valor inserido.\n";
                }
            } else if (opcao == 2) {
                cout << (buscar(raiz, valor) ? "Valor encontrado.\n" : "Valor nao encontrado.\n");
            } else {
                if (!buscar(raiz, valor)) cout << "Valor nao encontrado.\n";
                else {
                    raiz = remover(raiz, valor);
                    cout << "Valor removido.\n";
                }
            }
        } else if (opcao >= 4 && opcao <= 6) {
            if (raiz == nullptr) cout << "Arvore vazia.";
            else if (opcao == 4) emOrdem(raiz);
            else if (opcao == 5) preOrdem(raiz);
            else posOrdem(raiz);
            cout << "\n";
        }
    } while (opcao != 0);
    liberar(raiz);
    return 0;
}
