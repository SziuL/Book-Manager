#ifndef estruturas_h
#define estruturas_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct livro
{
	char isbn[5];
	char titulo[20];
	char autor[30];
	int qtd;
	struct livro *dir, *esq, *pai;
} Livro;

typedef struct filial
{
	int id;
	char endereco[50];
	char gerente[30];
	struct filial *prox;
	Livro *livros;
} Filial;

Filial *criaFilial(char *endereco, char *gerente, int id);
Livro *criaLivro(char *isbn, char *titulo, char *autor, int qtd);

#endif
