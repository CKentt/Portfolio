try:
    key = input("Digite uma cifra de 26 caracteres: \n")
    key = key.upper()
    if len(list(key)) != 26:
        raise ValueError
    elif len(set(key)) != 26:
        raise TypeError
    else:
        for char in list(key):
            if ord(char) < 65 and ord(char) > 90:
                raise TypeError
except TypeError:
    print("Uso: ./ chave de substituição\n")
except ValueError:
    print("A chave deve conter 26 caracteres.\n")

cifra = {}

aux = 65
for char in key:
    cifra[aux] = ord(char)
    aux += 1

text = input("Digite um texto: \n")
text = list(text)

i = 0
for char in text:
    if ord(char) >= 65 and ord(char) <= 90:
        text[i] = chr(cifra[ord(char)])
    elif ord(char) >= 97 and ord(char) <= 122:
        char = char.upper()
        char = chr(cifra[ord(char)])
        text[i] = char.lower()
    i += 1

text = ''.join(text)
print(f"ciphertext: {text}")

