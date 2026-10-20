#include <algorithm>
#include <cassert>
#include <climits>
#include <random>
#include <set>
#include <sstream>
#include <vector>

#define main mainBusca
#include "../busca_B.cpp"
#undef main
#define main mainSelecao
#include "../ordem_S.cpp"
#undef main
#define main mainArvore
#include "../tree_B.cpp"
#undef main

void coletar(const No* raiz, std::vector<int>& valores) {
    if (!raiz) return;
    coletar(raiz->esquerda, valores);
    valores.push_back(raiz->valor);
    coletar(raiz->direita, valores);
}

int main() {
    assert(buscaBinaria({}, 1) == -1);
    assert(buscaBinaria({5}, 5) == 0);
    assert(buscaBinaria({5}, 4) == -1);
    std::vector<int> extremos{INT_MIN, -1, 0, 0, 9, INT_MAX};
    for (int valor : extremos) {
        int indice = buscaBinaria(extremos, valor);
        assert(indice >= 0 && extremos[indice] == valor);
    }
    assert(buscaBinaria(extremos, 8) == -1);

    std::mt19937 gerador(42);
    std::uniform_int_distribution<int> valores(-100, 100);
    for (int tamanho = 0; tamanho <= 100; tamanho++) {
        std::vector<int> entrada(tamanho);
        for (int& valor : entrada) valor = valores(gerador);
        auto esperado = entrada;
        std::sort(esperado.begin(), esperado.end());
        ordenacaoSelecao(entrada);
        assert(entrada == esperado);
        for (int alvo = -101; alvo <= 101; alvo++) {
            int indice = buscaBinaria(entrada, alvo);
            bool existe = std::binary_search(esperado.begin(), esperado.end(), alvo);
            assert((indice != -1) == existe);
            if (existe) assert(entrada[indice] == alvo);
        }
    }
    for (std::vector<int> entrada : {std::vector<int>{INT_MAX, 0, INT_MIN},
                                    std::vector<int>{1, 2, 3},
                                    std::vector<int>{3, 2, 1},
                                    std::vector<int>{7, 7, 7}}) {
        auto esperado = entrada;
        std::sort(esperado.begin(), esperado.end());
        ordenacaoSelecao(entrada);
        assert(entrada == esperado);
    }

    No* raiz = nullptr;
    assert(!buscar(raiz, 5));
    assert(remover(raiz, 5) == nullptr);
    for (int valor : {50, 30, 70, 20, 40, 60, 80, 65}) raiz = inserir(raiz, valor);
    raiz = inserir(raiz, 50);
    std::ostringstream saida;
    auto* original = std::cout.rdbuf(saida.rdbuf());
    emOrdem(raiz);
    assert(saida.str() == "20 30 40 50 60 65 70 80 ");
    saida.str("");
    preOrdem(raiz);
    assert(saida.str() == "50 30 20 40 70 60 65 80 ");
    saida.str("");
    posOrdem(raiz);
    assert(saida.str() == "20 40 30 65 60 80 70 50 ");
    std::cout.rdbuf(original);
    std::set<int> referencia{20, 30, 40, 50, 60, 65, 70, 80};
    // Folha, no com um filho, raiz com dois filhos e valor ausente.
    for (int valor : {20, 60, 50, 999, 30, 40, 65, 70, 80}) {
        raiz = remover(raiz, valor);
        referencia.erase(valor);
        std::vector<int> atual;
        coletar(raiz, atual);
        assert(atual == std::vector<int>(referencia.begin(), referencia.end()));
    }
    assert(raiz == nullptr);
    for (int i = 0; i < 1000; i++) {
        int valor = valores(gerador);
        if (i % 3) {
            raiz = inserir(raiz, valor);
            referencia.insert(valor);
        } else {
            raiz = remover(raiz, valor);
            referencia.erase(valor);
        }
        std::vector<int> atual;
        coletar(raiz, atual);
        assert(atual == std::vector<int>(referencia.begin(), referencia.end()));
        assert(buscar(raiz, valor) == (referencia.count(valor) != 0));
    }
    liberar(raiz);
    std::cout << "OK: busca, selecao, percursos e remocoes; 101 vetores e 1000 operacoes de arvore.\n";
    return 0;
}
