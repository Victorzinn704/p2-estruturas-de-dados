"""Gera e confere o ZIP da P2 com os três fontes exigidos."""

import argparse
from pathlib import Path
import zipfile


ARQUIVOS = ("busca_B.cpp", "ordem_S.cpp", "tree_B.cpp")
INTEGRANTES = (
    "João Victor de Moraes da Cruz - Matricula: 202512557",
    "Paulo Marques de Araujo - Matricula: 202512490",
)
NOME_ZIP = "P2_Joao_Victor_202512557_e_Paulo_Marques_de_Araujo_202512490.zip"


def preparar_entrega(destino):
    origem = Path(__file__).resolve().parent
    fontes = {nome: (origem / nome).read_bytes() for nome in ARQUIVOS}
    for nome, dados in fontes.items():
        texto = dados.decode("utf-8")
        if not all(integrante in texto for integrante in INTEGRANTES):
            raise ValueError(f"Identificação da dupla incompleta em {nome}")

    destino.mkdir(parents=True, exist_ok=True)
    arquivo_zip = destino / NOME_ZIP
    with zipfile.ZipFile(arquivo_zip, "w", zipfile.ZIP_DEFLATED) as pacote:
        for nome, dados in fontes.items():
            pacote.writestr(nome, dados)

    with zipfile.ZipFile(arquivo_zip) as pacote:
        if pacote.namelist() != list(ARQUIVOS) or pacote.testzip() is not None:
            raise ValueError("Conteúdo inválido no ZIP de entrega")
        for nome, dados in fontes.items():
            if pacote.read(nome) != dados:
                raise ValueError(f"Conteúdo divergente em {nome}")
    return arquivo_zip


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--saida", type=Path, default=Path("dist"))
    argumentos = parser.parse_args()
    print(preparar_entrega(argumentos.saida))
