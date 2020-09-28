#include "parque.h"
#include <vector>
#include <algorithm>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli) {
	vagas = lot;
}

unsigned ParqueEstacionamento::getNumLugares() const {
	return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string& nome) const {
	for (size_t i = 0; i < clientes.size(); i++) {
		if (clientes[i].nome == nome) {
			return i;
		}
	}

	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string& nome) {
	if (clientes.size() == numMaximoClientes) {
		return false;
	}
	InfoCartao cartao(nome,false);
	clientes.push_back(cartao);
	return true;
}

bool ParqueEstacionamento::entrar(const string& nome) {
	int posicao = posicaoCliente(nome);
	if (posicao == -1) {
		return false;
	}

	if (clientes[posicao].presente) {
		return false;
	}

	if (!vagas) {
		return false;
	}

	clientes[posicao].presente = true;
	vagas--;
	return true;
}

bool ParqueEstacionamento::retiraCliente(const string& nome) {
	int posicao = posicaoCliente(nome);

	if (posicao == -1) {
		return false;
	}

	if (clientes[posicao].presente) {
		return false;
	}

	clientes.erase(clientes.begin() + posicao);
}

bool ParqueEstacionamento::sair(const string& nome) {
	int posicao = posicaoCliente(nome);

	if (posicao == -1) {
		return false;
	}

	if (!clientes[posicao].presente) {
		return false;
	}

	clientes[posicao].presente = false;
	return true;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
	return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
	return clientes.size();
}

