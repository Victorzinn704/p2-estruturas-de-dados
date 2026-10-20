// Joao Victor de Moraes da Cruz - Trabalho P2 (individual)
#include <iostream>
#include <vector>
using namespace std;

int buscaBinaria(const vector<int>& valores, int procurado) {
    int inicio = 0;
    int fim = static_cast<int>(valores.size()) - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (valores[meio] == procurado) return meio;
        if (valores[meio] < procurado) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int main() {
    int quantidade;
    cout << "Quantidade de valores (0 a 10000): ";
    if (!(cin >> quantidade) || quantidade < 0 || quantidade > 10000) {
        cerr << "Quantidade invalida.\n";
        return 1;
    }

    vector<int> valores(quantidade);
    cout << "Digite os valores em ordem crescente (repetidos sao permitidos):\n";
    for (int i = 0; i < quantidade; i++) {
        if (!(cin >> valores[i])) {
            cerr << "Valor invalido.\n";
            return 1;
        }
        if (i > 0 && valores[i] < valores[i - 1]) {
            cerr << "A busca binaria exige valores ordenados.\n";
            return 1;
        }
    }

    int procurado;
    cout << "Valor procurado: ";
    if (!(cin >> procurado)) {
        cerr << "Valor invalido.\n";
        return 1;
    }
    int indice = buscaBinaria(valores, procurado);
    if (indice == -1) cout << "Valor nao encontrado.\n";
    else cout << "Valor encontrado no indice " << indice << " (contagem a partir de 0).\n";
    return 0;
}
