// Trabalho P2 - Estruturas de Dados - Ordenacao por Selecao
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

void ordenacaoSelecao(vector<int>& valores) {
    int quantidade = static_cast<int>(valores.size());
    for (int i = 0; i < quantidade - 1; i++) {
        // A cada passagem, coloca o menor valor restante na posicao i.
        int menor = i;
        for (int j = i + 1; j < quantidade; j++) {
            if (valores[j] < valores[menor]) menor = j;
        }
        if (menor != i) {
            int auxiliar = valores[i];
            valores[i] = valores[menor];
            valores[menor] = auxiliar;
        }
    }
}

int main() {
    int quantidade;
    cout << "Quantidade de valores (0 a 10000): ";
    if (!lerInteiro(quantidade) || quantidade < 0 || quantidade > 10000) {
        cerr << "Quantidade invalida.\n";
        return 1;
    }
    vector<int> valores(quantidade);
    cout << "Digite os valores:\n";
    for (int i = 0; i < quantidade; i++) {
        if (!lerInteiro(valores[i])) {
            cerr << "Valor invalido.\n";
            return 1;
        }
    }
    ordenacaoSelecao(valores);
    cout << "Valores ordenados:";
    for (int valor : valores) cout << " " << valor;
    cout << "\n";
    return 0;
}
