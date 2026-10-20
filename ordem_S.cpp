// Joao Victor de Moraes da Cruz - Trabalho P2 (individual)
#include <iostream>
#include <vector>
using namespace std;

void ordenacaoSelecao(vector<int>& valores) {
    int quantidade = static_cast<int>(valores.size());
    for (int i = 0; i < quantidade - 1; i++) {
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
    if (!(cin >> quantidade) || quantidade < 0 || quantidade > 10000) {
        cerr << "Quantidade invalida.\n";
        return 1;
    }
    vector<int> valores(quantidade);
    cout << "Digite os valores:\n";
    for (int i = 0; i < quantidade; i++) {
        if (!(cin >> valores[i])) {
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
