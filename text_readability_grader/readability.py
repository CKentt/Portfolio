import re

while True:
    try:
        texto = input("Digite o texto a ser avaliado: ")
        if texto == False:
            raise TypeError
        break
    except TypeError:
        print("Nenhum texto digitado")


def n_palavras(texto):
    palavras = texto.split(" ")
    return len(palavras)


def n_sentencas(texto):
    sentencas = re.split("[.?!]", texto)
    return len(sentencas) - 1


def n_letras(texto):
    caracteres = tuple(texto)
    letras = []
    for caractere in caracteres:
        if caractere == caractere.upper() and caractere == caractere.lower():
            pass
        else:
            letras.append(caractere)
    return len(letras)


l = n_letras(texto) * 100 / n_palavras(texto)
s = n_sentencas(texto) * 100 / n_palavras(texto)
indice = 0.0588 * l - 0.296 * s - 15.8
if indice >= 16:
    print("Grade 16+\n")
elif indice < 1:
    print("Before Grade 1\n")
else:
    print(f"Grade {round(indice)}")
