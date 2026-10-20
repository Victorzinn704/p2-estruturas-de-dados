# Trabalho P2 - Estruturas de Dados em C++

Integrante: **Joao Victor de Moraes da Cruz**. Trabalho individual.

O enunciado solicita dupla; esta entrega registra a escolha do estudante por realizar o trabalho sozinho, sem presumir autorização do professor.

## Arquivos para entrega

| Arquivo (não renomear) | Conteúdo |
| --- | --- |
| `busca_B.cpp` | Busca binária iterativa em vetor previamente ordenado. |
| `ordem_S.cpp` | Ordenação por seleção em ordem crescente. |
| `tree_B.cpp` | Árvore binária de busca com inserção, busca, remoção, três percursos e liberação de memória. |

Cada arquivo é um programa independente com sua própria função `main`. O ZIP de entrega contém somente esses três arquivos na raiz. Documentação, testes e automação ficam apenas no repositório.

## Compilar e executar

Com GCC e suporte a C++17:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic busca_B.cpp -o busca_B
g++ -std=c++17 -Wall -Wextra -pedantic ordem_S.cpp -o ordem_S
g++ -std=c++17 -Wall -Wextra -pedantic tree_B.cpp -o tree_B
```

Execute o programa desejado e acompanhe as perguntas no terminal. Em Linux, use `./busca_B`, por exemplo; em Windows, `./busca_B.exe`.

Na busca e na ordenação, informe a quantidade e depois os inteiros separados por espaços ou quebras de linha. A busca pede ainda o valor procurado. São aceitos de zero a 10.000 elementos; entrada inválida encerra o programa com mensagem e código 1. A busca rejeita dados fora de ordem e informa índice a partir de zero. Com repetições, retorna uma ocorrência, sem garantir a primeira.

Exemplo de busca: quantidade `5`, valores `1 3 5 7 9`, alvo `7`; resultado: índice `3`. Exemplo de seleção: valores `9 -1 5 0 5`; resultado: `-1 0 5 5 9`.

A árvore possui menu de 0 a 6 e não armazena duplicatas. A remoção cobre folha, nó com um filho e nó com dois filhos (sucessor em ordem). Não há balanceamento; entradas ordenadas podem gerar uma árvore degenerada. Inserção, remoção, percursos e liberação usam recursão e são destinados a demonstrações acadêmicas de tamanho moderado.

## Algoritmos

- Busca binária: divide o intervalo de busca ao meio; tempo O(log n) e espaço auxiliar O(1). A leitura e validação do vetor no programa custam O(n).
- Seleção: escolhe o menor elemento do trecho ainda não ordenado e troca com a posição atual; tempo O(n²), espaço auxiliar O(1).
- Árvore: busca, inserção e remoção custam O(h), sendo h a altura; no pior caso, O(n). Percursos custam O(n).

Os algoritmos dos arquivos de entrega foram implementados diretamente, sem funções prontas de busca ou ordenação. A biblioteca padrão aparece nos testes como referência independente.

## Validação e evidência

```sh
g++ -std=c++17 -Wall -Wextra -pedantic tests/testes.cpp -o testes
./testes
```

Os testes verificam vetor vazio, elemento único, negativos, repetições, extremos de inteiros, presença/ausência, 101 vetores comparados à ordenação de referência, três percursos, remoções e 1.000 operações de árvore comparadas a um conjunto. GitHub Actions também compila os programas independentes, testa entradas/saídas e executa verificadores de memória e comportamento indefinido.

O histórico Git registra a implementação e a adição da validação. Consulte a aba Actions para o resultado da execução no GitHub; a existência do workflow, por si só, não comprova aprovação.
