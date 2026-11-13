// Trabalho P2 - Estruturas de Dados - Busca Binaria
// Dupla: João Victor de Moraes da Cruz - Matricula: 202512557
//        Paulo Marques de Araujo - Matricula: 202512490
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool lerInteiro(int& valor) {
    string entrada;
    if (!(cin >> entrada)) return false;
    istringstream conversor(entrada);
    return static_cast<bool>(conversor >> valor) && conversor.eof();
}

int buscaBinaria(const vector<int>& valores, int procurado) {
    // O vetor deve estar ordenado. O intervalo [inicio, fim] contem os candidatos.
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
    if (!lerInteiro(quantidade) || quantidade < 0 || quantidade > 10000) {
        cerr << "Quantidade invalida.\n";
        return 1;
    }

    vector<int> valores(quantidade);
    cout << "Digite os valores em ordem crescente (repetidos sao permitidos):\n";
    for (int i = 0; i < quantidade; i++) {
        if (!lerInteiro(valores[i])) {
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
    if (!lerInteiro(procurado)) {
        cerr << "Valor invalido.\n";
        return 1;
    }
    int indice = buscaBinaria(valores, procurado);
    if (indice == -1) cout << "Valor nao encontrado.\n";
    else cout << "Valor encontrado no indice " << indice << " (contagem a partir de 0).\n";
    return 0;
}
