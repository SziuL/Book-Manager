#include "funcionalidades.h"

// Funções de estrutura
Livro *criaLivro(char *isbn, char *titulo, char *autor)
{
	Livro *novo = (Livro *)calloc(1, sizeof(Livro));
	if (!novo)
	{
		printf("Erro ao alocar novo livro.\n");
		exit(1);
	}
	strcpy(novo->isbn, isbn);
	strcpy(novo->titulo, titulo);
	strcpy(novo->autor, autor);
	novo->qtd = 0;

	return novo;
}

Filial *criaFilial(char *endereco, char *gerente, int id)
{
	Filial *novaFilial = (Filial *)calloc(1, sizeof(Filial));
	if (!novaFilial)
	{
		printf("Erro ao alocar novaFilial livro.\n");
		exit(1);
	}
	strcpy(novaFilial->endereco, endereco);
	strcpy(novaFilial->gerente, gerente);
	novaFilial->id = id;

	return novaFilial;
}

// Complementares
int encriptar(char isbn[5])
{
	char nome[4];
	int soma = 0;
	strcpy(nome, isbn);

	for (int i = 0; i < 5; i++)
	{
		soma += nome[i];
	}

	return soma;
}

Filial *buscaFilial(Filial *L, int id)
{
	Filial *aux = L;
	while (aux->id != id && aux != NULL)
		aux = aux->prox;

	return aux;
}

Livro *menor(Livro *livro)
{
	if (livro == NULL)
	{
		return NULL;
	}
	else
	{
		Livro *aux = livro;
		while (aux != NULL)
		{
			if (aux->esq == NULL)
				return aux;
			else
				aux = aux->esq;
		}
	}
}

Livro *maior(Livro *livro)
{
	if (livro == NULL)
	{
		return NULL;
	}
	else
	{
		Livro *aux = livro;
		while (aux != NULL)
		{
			if (aux->dir == NULL)
				return aux;
			else
				aux = aux->dir;
		}
	}
}

Livro *sucessor(Livro *livro)
{
	if (livro == NULL)
		return NULL;

	if (livro->dir != NULL)
		return menor(livro->dir);
	else
	{
		Livro *aux = livro->pai;
		int isbnPai = encriptar(aux->isbn);
		int isbnNo = encriptar(livro->isbn);

		while (aux != NULL && isbnPai < isbnNo)
			aux = aux->pai;

		return aux;
	}
}

Livro *predecessor(Livro *livro)
{
	if (livro == NULL)
		return NULL;
	
	if (livro->esq != NULL)
		return maior(livro->esq);
	else
	{
		Livro *aux = livro;
		int isbnPai = encriptar(aux->isbn);
		int isbnNo = encriptar(livro->isbn);

		while (aux != NULL && isbnPai > isbnNo)
		{
			/* code */
		}
		
	}
	

	
	

	
	
}

// Funções para filiais
Livro *buscarLivro(Filial *L, int idFilial, char *isbn)
{
	Filial *aux = buscaFilial(L, idFilial);
	int isbnEncriptado = encriptar(isbn);

	if (aux)
	{
		Livro *auxLivro = aux->livros;
		int isbnAtual = encriptar(auxLivro->isbn);

		while (auxLivro != NULL)
		{
			if (isbnEncriptado == isbnAtual)
				return auxLivro;
			else if (isbnEncriptado < isbnAtual)
				isbnAtual = encriptar(auxLivro->esq->isbn);
			else if (isbnEncriptado > isbnAtual)
				isbnAtual = encriptar(auxLivro->dir->isbn);

			if (auxLivro)
				isbnAtual = encriptar(auxLivro->isbn);
		}
	}
	else
	{
		printf("Filial nao econtrada.\n");
		return NULL;
	}

	printf("Livro nao encontrado.\n");
	return NULL;
}

void inserirLivro(Livro *livro, Filial *L, int idFilial)
{
	Filial *aux = buscaFilial(L, idFilial);

	if (aux)
	{
		Livro *livroAtual = aux->livros;
		int atual = encriptar(livroAtual->isbn);
		int isbnNovo = encriptar(livro->isbn);

		while (livroAtual != NULL)
		{
			if (isbnNovo < atual)
			{
				if (livroAtual->esq == NULL)
				{
					livroAtual->esq = livro;
					livro->pai = livroAtual;
				}
				livroAtual = livroAtual->esq;
			}
			else
			{
				if (livroAtual->dir == NULL)
				{
					livroAtual->dir = livro;
					livro->pai = livroAtual;
				}
				livroAtual = livroAtual->dir;
			}
		}
	}
}

void excluirLivro(Livro *livro)
{
}