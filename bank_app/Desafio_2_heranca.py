from datetime import datetime


class Conta:
	def __init__(self, saldo=float, numero=int, cliente = any):
		self._saldo = saldo
		self.numero = numero
		self.agencia = "0001"
		self.cliente = cliente

	def saldo(self, saldo=float):
		return self._saldo

	def nova_conta(self, numero=int):
		pass



class Historico(Conta):
	def __init__(self, _saldo, numero, agencia, cliente):
		super().__init__(self, _saldo, numero, agencia, cliente)
		self.transacoes = []

	def mostrar_historico(self, transacao):
		return self.transacoes

	def adicionar_transacao(self, tipo_transacao, valor):
		self.transacoes.append({
			"categoria": tipo_transacao,
			"horario": datetime.now().strftime("%Y/%m/%d %H:%M:%s"),
			"valor": valor
		})


class ContaCorrente(Conta):

	def __init__(self, _saldo, numero, agencia, cliente, limite, limite_saques):
		super().__init__(_saldo, numero, agencia, cliente)
		self.limite = limite
		self.limite_saques = limite_saques


class Cliente(Conta):

	def __init__(self, _saldo, numero, agencia, cliente, endereco=str, contas=list):
		super().__init__(_saldo, numero, agencia, cliente)
		self.endereco = endereco
		self.contas = contas


class Transacao(Historico):
	def __init__(self, _saldo, numero, agencia, cliente):
		super().__init__(_saldo, numero, agencia, cliente)


	def Deposito(valor):
		super()._saldo += valor
		Historico.adicionar_transacao("Deposito", valor)

	def saque(valor):
		if valor > super()._saldo:
			print("Saldo insuficiente")
		elif len(Historico.transacoes["categoria"] == "saque") > ContaCorrente.limite_saques:
			print("Limite de saques atingido")
		else:
			Historico.adicionar_transacao("Saque", valor)
			


class PessoaFisica(Cliente):
	def __init__(self, cpf=str, nome=str, data_nascimento=str):
		self.cpf = cpf
		self.nome = nome
		self.data_nascimento = data_nascimento
	


