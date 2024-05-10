# Não é possível depositar valores negativos
# Não é possivel sacar mais de 500 reais por dia
# Máximo de 3 saques por dia
# Extrato deverá ter todas as operações realizadas no formato R$ xxx,xx

import re

menu = """

[d] Depositar
[s] Sacar
[e] Extrato
[c] Criar Conta
[u] Criar Usuário
[q] Sair

=> """

usuarios = []
contas_correntes = []
nr_conta = 1

class Usuario():
    def __init__(self, nome, cpf, data_nascimento, endereco):
        self.nome = nome
        self.cpf = cpf
        self.data_nascimento = data_nascimento
        self.endereco = endereco

    def __str__(self):
        return f"{self.cpf}"

class Conta_corrente:
    def __init__(self, nro_conta=0, nro_agencia='0001', cpf_usuario=0, saldo=0, limite=500, extrato='', numero_saques=0, limite_saques=3, valor_saques=0, limite_valor_saques=500):
        self.nro_conta = nro_conta
        self.nro_agencia = nro_agencia
        self.cpf_usuario = cpf_usuario
        self.saldo = saldo
        self.limite = limite
        self.extrato = extrato
        self.numero_saques = numero_saques
        self.limite_saques = limite_saques
        self.valor_saques = valor_saques
        self.limite_valor_saques = limite_valor_saques

    def __str__(self):
        return f"{self.__class__.__name__}: {', '.join([f'{chave}={valor}' for chave, valor in self.__dict__.items()])}"


    def deposito(self):
        dep = float(input("Digite o valor a ser depositado: "))
        if dep <= 0:
            return "Erro! Valor deve ser maior que R$ 0,00"
        else:
            self.saldo += dep
            ext = str(self.extrato)
            ext += f"Depósito: R$ {format(dep,'.2f')}\n"
            self.extrato = ext
            return f"Saldo: {self.saldo} \nExtrato: {self.ext()}"

    def saque(self):
        saq = float(input("Digite o valor a ser sacado: "))
        if saq <= 0:
            return("Erro: Valor deve ser maior que R$ 0,00")
        elif self.numero_saques >= self.limite_saques:
            return(f"Erro: Número de {self.limite_saques} saques por dia excedido")
        elif saq > self.saldo:
            return("Erro: Valor do saque maior que valor em Conta Bancária")
        elif saq + self.valor_saques > self.limite_valor_saques:
            return("Erro: Valor de saques ultrapassou o limite de valor diário para saques!")
        else:
            self.saldo -= saq
            ext = str(self.extrato)
            ext += f"Saque: R$ {format(saq,'.2f')}\n"
            self.extrato = ext
            self.numero_saques += 1
            self.valor_saques += saq
            return f"Saldo: {self.saldo} \nExtrato: {self.ext()}"
        

    def ext(self):
        if self.extrato == None:
            return False
        else: 
            return f"""
----------EXTRATO---------

{self.extrato}

--------------------------
Saldo = R$ {format(self.saldo, '.2f')}

        """

def criar_usuario():
    global usuarios
    """TO DO: Armazenar usuários em uma lista. Um usuário é composto
por nome, data de nascimento, cpf e endereço (O endereço é uma string
com fromato: logradouro, cep, bairro, cidade/sigla estado.
Somente os números do CPF deverão ser armazenados. Não podemos cadastrar
dois CPFs iguais."""
    while True:
        cpf_cliente = input("Digite o CPF do cliente (apenas números): ")
        cpf_pattern = re.compile(r'\d{8}')
        if re.match(cpf_pattern, cpf_cliente):
            break
    for usuario in usuarios:
        if cpf_cliente == usuario.cpf_usuario:
            return("Usuário já existe!")
        
    nome = input("Digite seu nome: ")
    while True:
        data_nascimento = input("Digite sua data de nascimento (xx-xx-xxxx): ")
        data_nascimento_pattern = re.compile(r'\d{2}-\d{2}-\d{4}')
        if re.match(data_nascimento_pattern, data_nascimento):
            break
    logradouro = input("Digite seu logradouro: ")
    while True:
        cep = input("Digite seu cep: ")
        cep_pattern = re.compile(r'\d{5}-\d{3}')
        if re.match(cep_pattern, cep):
            break
    bairro = input("Digite seu bairro: ")
    cidade = input("Digite sua cidade: ")
    while True:
        estado = input("Digite seu estado: ")
        estado_pattern = re.compile(r'\w{2}')
        if re.match(estado_pattern, estado):
            estado = estado.upper()
            break
    endereco = f"{logradouro}, {bairro}, {cidade}/{estado}, {cep}"
            
    usuarios.append(Usuario(nome, cpf_cliente, data_nascimento, endereco))
    return f"Usuário {cpf_cliente} criado!"
        

def criar_conta_corrente():
    global contas_correntes
    global nr_conta
    """ O programa deve armazenar contas em uma lista, uma conta é
composta por agência, número da conta e usuário
O número da conta é sequencial, iniciando em 1. O número da agência
é fixo: '0001'. O usuário pode ter mais de uma conta, mas uma conta
corrente pertence a apenas um usuário
"""

    while True:
        cpf_cliente = input("Digite o CPF do cliente (apenas números): ")
        cpf_pattern = re.compile(r'\d{8}')
        if re.match(cpf_pattern, cpf_cliente):
            break
    for user in usuarios:
        if cpf_cliente == user.cpf:
            n_conta = nr_conta
            contas_correntes.append(Conta_corrente(nro_conta=n_conta, cpf_usuario=cpf_cliente))
            n_conta = nr_conta + 1
            nr_conta = n_conta
            return(f"Conta {n_conta - 1} criada!")
        else:
            return("Usuário não existe!")



while True:
    opcao = input(menu)

    if opcao == "d":
        while True:
            cc = input("Digite a conta corrente (Digite 'v' para voltar): ")
            if cc == 'v':
                break
            conta_existe = False
            for conta in contas_correntes:
                try:
                    if int(cc) == conta.nro_conta:
                        conta_existe = True
                        print(conta.deposito())
                except:
                    break
            if not conta_existe:
                print("Conta Inexistente!")
            break
        
    elif opcao == "s":
        while True:
            cc = input("Digite a conta corrente (Digite 'v' para voltar): ")
            if cc == 'v':
                break
            conta_existe = False
            for conta in contas_correntes:
                try:
                    if int(cc) == conta.nro_conta:
                        conta_existe = True
                        print(conta.saque())
                except:
                    break
            if not conta_existe:
                print("Conta Inexistente")
            break
            
    elif opcao == "e":
        while True: 
            cc = input("Digite a conta corrente (Digite 'v' para voltar): ")
            if cc == 'v':
                break

            conta_existe = False
            for conta in contas_correntes:
                try:
                    if int(cc) == conta.nro_conta:
                        conta_existe = True
                        if conta.ext() == None:
                            print("Nenhuma transação realizada")
                        else:
                            print(conta.ext())
                except:
                    break
            if not conta_existe:
                print("Conta Inexistente")
            break
                    

    elif opcao == "u":
        print(criar_usuario())
                
    elif opcao == "c":
        print(criar_conta_corrente())
        
    elif opcao == "q":
        break
    
    else:
        print("Erro! Digite umas das opções no Menu")
