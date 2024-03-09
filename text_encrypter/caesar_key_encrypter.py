while True:
    try:
        key = int(input("Digite a chave a ser utilizada: \n"))
        if key < 0:
            raise ValueError
        else:
            break
    except ValueError:
        print("Usage: ./caesar key")

text_input = input("Digite o texto a ser criptografado: \n")

def caesar(texto, chave):
    lista = list(texto)
    lista_cripto = []
    for char in lista:
        if (ord(char) >= 65 and ord(char) <= 90):
            lista_cripto.append(chr(((ord(char) - 65 + chave) % 26) + 65))
        elif (ord(char) >= 97 and ord(char) <= 122):
            lista_cripto.append(chr(((ord(char) - 97 + chave) % 26) + 97))
        else:
            lista_cripto.append(char)

    print(''.join(lista_cripto))


caesar(text_input, key)
