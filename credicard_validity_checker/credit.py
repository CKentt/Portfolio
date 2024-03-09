validity = True
while True:
    try:
        number = input("Digite o número do cartão de crédito: ")
        if (
            len(list(number)) != 13
            and len(list(number)) != 15
            and len(list(number)) != 16
        ):
            print("INVALID")
            validity = False
            break
        if int(number) < 0:
            raise ValueError
        break
    except ValueError:
        print("Digite um número")


def type(number):
    if int(list(number)[0]) == 4:
        return "VISA"
    elif int(list(number)[0]) == 3:
        if int(list(number)[1]) == 4 or int(list(number)[1]) == 7:
            return "AMEX"
        else:
            return "INVALID"
    elif int(list(number)[0]) == 5:
        if int(list(number)[1]) > 0 and int(list(number)[1]) < 6:
            return "MASTERCARD"
        else:
            return "INVALID"
    else:
        return "INVALID"


def luhn(number):
    first_multiplication = []
    soma_first = 0
    second_multiplication = []
    soma_second = 0
    for numero in range(len(list(number)) - 2, -1, -2):
        first_multiplication.append(int(list(number)[numero]))
    for numero in range(len(list(number)) - 1, -1, -2):
        second_multiplication.append(int(list(number)[numero]))
    for numero in second_multiplication:
        soma_second = soma_second + numero
    for index in range(len(first_multiplication)):
        first_multiplication[index] = first_multiplication[index] * 2
    for numero in first_multiplication:
        if numero > 9:
            soma_first = soma_first + 1
            soma_first = soma_first + numero - 10
        else:
            soma_first = soma_first + numero

    soma_final = soma_first + soma_second
    if soma_final // 10 == soma_final / 10:
        return True
    else:
        return False


if validity == True:
    if luhn(number) == True:
        print(f"{type(number)}")
    else:
        print("INVALID")
