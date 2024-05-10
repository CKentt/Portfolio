# Não é possível depositar valores negativos
# Não é possivel sacar mais de 500 reais por dia
# Máximo de 3 saques por dia
# Extrato deverá ter todas as operações realizadas no formato R$ xxx,xx

menu = """

[d] Depositar
[s] Sacar
[e] Extrato
[q] Sair

=> """

saldo = 0
limite = 500
extrato = ""
numero_saques = 0
LIMITE_SAQUES = 3

def deposito():
    global saldo
    global extrato
    dep = float(input("Digite o valor a ser depositado: "))
    if dep <= 0:
        return("Erro! Valor deve ser maior que R$ 0,00")
    else:
        saldo += dep
        ext = str(extrato)
        ext += f"Depósito: R$ {format(dep,'.2f')}\n"
        extrato = ext
        return "Depósito realizado"

def saque():
    global saldo
    global extrato
    global numero_saques
    global LIMITE_SAQUES
    saq = float(input("Digite o valor a ser sacado: "))
    if saq <= 0:
        return("Erro: Valor deve ser maior que R$ 0,00")
    elif numero_saques >= LIMITE_SAQUES:
        return("Erro: Número de três saques por dia excedido")
    elif saq > saldo:
        return("Erro: Valor do saque maior que valor em Conta Bancária")
    else:
        saldo -= saq
        ext = str(extrato)
        ext += f"Saque: R$ {format(saq,'.2f')}\n"
        extrato = ext
        numero_saques += 1
        return "Saque Realizado"

def ext():
    global extrato
    return f"""
----------EXTRATO---------

{extrato}

--------------------------

"""

while True:
    opcao = input(menu)

    if opcao == "d":
        print(deposito())
        
    elif opcao == "s":
        print(saque())
            
    elif opcao == "e":
        if ext() == None:
            print("Nenhuma transação realizada")
        else:
            print(ext())
        print(f"Saldo: R$ {format(saldo, '.2f')}")
        
    elif opcao == "q":
        break
    
    else:
        print("Erro! Digite umas das opções no Menu")



        
