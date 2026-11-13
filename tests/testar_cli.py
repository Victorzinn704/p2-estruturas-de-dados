"""Valida os três programas independentes usando suas entradas de terminal."""

from pathlib import Path
import re
import subprocess
import sys


def executar(pasta, programa, entrada, codigo=0):
    executavel = pasta / programa
    if sys.platform == "win32":
        executavel = executavel.with_suffix(".exe")
    resultado = subprocess.run(
        [str(executavel.resolve())], input=entrada, text=True,
        capture_output=True, timeout=30,
    )
    assert resultado.returncode == codigo, (programa, resultado)
    return resultado.stdout + resultado.stderr


def testar(pasta):
    casos = 0
    buscas = [
        ([], 1, None), ([5], 5, 0), ([5], 4, None),
        ([-2147483648, -2, 0, 7, 2147483647], -2147483648, 0),
        ([-2147483648, -2, 0, 7, 2147483647], 2147483647, 4),
        ([1, 3, 5, 7, 9], 7, 3), ([1, 3, 5], 2, None),
        ([2, 2, 2], 2, 1), (list(range(10000)), 9999, 9999),
    ]
    for valores, alvo, indice in buscas:
        entrada = f"{len(valores)}\n{' '.join(map(str, valores))}\n{alvo}\n"
        saida = executar(pasta, "busca_B", entrada)
        if indice is None:
            assert "Valor nao encontrado." in saida
        else:
            assert f"Valor encontrado no indice {indice} " in saida
        casos += 1

    selecoes = [[], [5], [3, 2, 1], [1, 2, 3], [7, 7, 7],
                [2147483647, 0, -2147483648, -1, -1],
                list(range(9999, -1, -1))]
    for valores in selecoes:
        entrada = f"{len(valores)}\n{' '.join(map(str, valores))}\n"
        saida = executar(pasta, "ordem_S", entrada)
        numeros = saida.split("Valores ordenados:", 1)[1].split()
        assert list(map(int, numeros)) == sorted(valores)
        casos += 1

    for programa in ("busca_B", "ordem_S"):
        for entrada in ("-1\n", "10001\n", "x\n", "2\n1 x\n", "2\n1\n",
                        "1x\n9\n", "1\n9x\n", "1\n9.5\n",
                        "1\n2147483648\n", "1\n-2147483649\n"):
            executar(pasta, programa, entrada, 1)
            casos += 1
    for entrada in ("3\n3 2 1\n2\n", "1\n5\nx\n", "1\n5\n",
                    "1\n7\n7x\n", "1\n7\n7.5\n", "1\n7\n2147483648\n"):
        executar(pasta, "busca_B", entrada, 1)
        casos += 1

    entrada = "".join(f"1\n{v}\n" for v in (50, 30, 70, 20, 40, 60, 80, 65))
    entrada += "1\n50\n2\n65\n2\n999\n4\n5\n6\n"
    entrada += "".join(f"3\n{v}\n" for v in (20, 60, 50, 999, 30, 40, 65, 70, 80))
    entrada += "4\n0\n"
    saida = executar(pasta, "tree_B", entrada)
    for percurso in ("20 30 40 50 60 65 70 80", "50 30 20 40 70 60 65 80",
                     "20 40 30 65 60 80 70 50"):
        assert re.search(re.escape(percurso) + r"\s*\n", saida)
    assert saida.count("Valor inserido.") == 8
    assert saida.count("Valor removido.") == 8
    assert "Valor ja existe." in saida and "Arvore vazia." in saida
    assert "Valor encontrado." in saida and "Valor nao encontrado." in saida
    casos += 1

    saida = executar(pasta, "tree_B", "4\n5\n6\n2\n0\n3\n0\n0\n")
    assert saida.count("Arvore vazia.") == 3
    assert saida.count("Valor nao encontrado.") == 2
    casos += 1
    saida = executar(pasta, "tree_B", "1\n-2147483648\n1\n2147483647\n4\n3\n-2147483648\n4\n0\n")
    assert "-2147483648 2147483647 " in saida
    assert "Valor removido." in saida
    casos += 1
    for entrada in ("x\n", "7\n", "-1\n", "1\nx\n", "2\n", "1\n5\n3\nx\n",
                    "0x\n", "1\n9x\n", "1\n9.5\n", "1\n2147483648\n",
                    "1\n-2147483649\n"):
        executar(pasta, "tree_B", entrada, 1)
        casos += 1
    assert "Valores ordenados: -2 0 3" in executar(pasta, "ordem_S", "+3\n+3 -2 +0\n")
    casos += 1
    print(f"OK: {casos} cenários de terminal nos três programas.")


if __name__ == "__main__":
    testar(Path(sys.argv[1]) if len(sys.argv) > 1 else Path("build"))
