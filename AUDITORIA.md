# Auditoria da P2 de Estruturas de Dados

Revisão realizada em 13 de novembro de 2026.

- João Victor de Moraes da Cruz — matrícula 202512557.
- Paulo Marques de Araujo — matrícula 202512490.

## Achados e correções

| Achado | Correção | Verificação |
| --- | --- | --- |
| Fontes e README identificavam a entrega como individual. | Inclusão dos nomes e matrículas da dupla nos três programas e na documentação. | Conferência do texto e do ZIP gerado. |
| A extração direta para `int` aceitava prefixos numéricos de entradas como `9x` e `7.5`. | Leitura de cada token completo, com validação da conversão e do intervalo de `int`. | Testes pelo terminal para sufixos, decimais e estouro de inteiro nos três programas. |
| Os testes de terminal anteriores cobriam poucos fluxos. | Ampliação para 57 cenários executados contra os programas independentes. | Execução de `python tests/testar_cli.py build`. |
| O pacote era preparado sem uma conferência reproduzível da identificação. | Script de empacotamento com verificação de nomes, autoria, CRC e igualdade dos bytes. | Execução de `python preparar_entrega.py --saida dist`. |

## Conferência do enunciado

| Exigência | Resultado |
| --- | --- |
| Busca binária em C ou C++ | Implementação iterativa em `busca_B.cpp`, com verificação da ordenação da entrada. |
| Ordenação por seleção | Implementação própria em `ordem_S.cpp`. |
| Árvore binária de busca | `tree_B.cpp` oferece inserção, busca, remoção, três percursos e liberação dos nós. |
| Nomes exatos dos fontes | `busca_B.cpp`, `ordem_S.cpp` e `tree_B.cpp`. |
| Trabalho em dupla | Nomes e matrículas nos comentários iniciais e no README. |
| Um arquivo compactado com os três códigos | ZIP com exatamente os três fontes na raiz, identificado com a dupla. |

## Evidências locais

Compilação com MSVC, padrão C++17, `/W4` e `/WX`, executada separadamente para os três programas e para `tests/testes.cpp`.

A suíte existente passou com 101 vetores e 1.000 operações de árvore comparadas às referências da biblioteca padrão. Os 57 cenários adicionais verificaram os programas pelo terminal, incluindo vetor vazio, 10.000 elementos, extremos de inteiros, negativos, duplicatas, entrada incompleta, opção inválida, percursos e remoções de folha, nó com um filho e nó com dois filhos.

O workflow do GitHub compila com GCC e `-Werror`, executa a suíte de algoritmos com AddressSanitizer e UndefinedBehaviorSanitizer, executa os testes de terminal e confere o empacotamento. O resultado de cada execução está disponível na aba Actions.

## Características da implementação

A busca informa índices a partir de zero e retorna uma ocorrência em caso de duplicatas. A árvore mantém valores únicos e usa recursão em inserção, remoção, percursos e liberação. A altura depende da sequência inserida, podendo chegar a O(n) com dados ordenados. O consumo da pilha acompanha essa altura.

## Atualizar a entrega

1. Revisar os três fontes e os dados da dupla.
2. Compilar cada programa e executar a suíte de algoritmos.
3. Executar `python tests/testar_cli.py build`.
4. Executar `python preparar_entrega.py --saida dist`.
5. Extrair o ZIP em uma pasta temporária, compilar os três fontes extraídos e repetir os testes de terminal.
6. Enviar ao AVA o ZIP identificado com a dupla.
