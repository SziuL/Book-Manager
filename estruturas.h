#ifndef estruturas_h
#define estruturas_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct livro
{
	char isbn[5];
	char titulo[15];
	char autor[15];
	int qtd;
	struct livro *dir, *esq, *pai;
} Livro;

typedef struct filial
{
	int id;
	char endereco[15];
	char gerente[15];
	struct filial *prox;
	Livro *livros;
} Filial;

Filial *criaFilial(char *endereco, char *gerente, int id);
Livro *criaLivro(char isbn[5], char titulo[15], char autor[15], int qtd);

#endif
