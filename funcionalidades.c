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
		Livro *aux = livro->pai;
		int isbnPai = encriptar(aux->isbn);
		int isbnNo = encriptar(livro->isbn);

		while (aux != NULL && isbnPai > isbnNo)
			aux = aux->pai;

		return aux;
	}
}

Livro *coletaDadosNovoLivro()
{
	char isbn[5], titulo[20], autor[30];
	int qtd;

	printf("Informe o ISBN do novo livro: \n");
	scanf("%s", &isbn);
	printf("Agora informe o titulo e autor do livro, respectivamente  ('titulo' 'autor'): \n");
	scanf("%s %s", &titulo, &autor);

	Livro *novoLivro = criaLivro(isbn, titulo, autor);

	return novoLivro;
}

// operações com LIVROS
Livro *buscarLivro(Livro *livros, char *isbn)
{
	int isbnEncriptado = encriptar(isbn);

	if (livros)
	{
		Livro *auxLivro = livros;
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

void inserirLivro(Livro *livros, Livro *novoLivro)
{

	if (livros)
	{
		Livro *livroAtual = livros;
		int atual = encriptar(livroAtual->isbn);
		int isbnNovo = encriptar(novoLivro->isbn);

		while (livroAtual != NULL)
		{
			if (isbnNovo < atual)
			{
				if (livroAtual->esq == NULL)
				{
					livroAtual->esq = novoLivro;
					novoLivro->pai = livroAtual;
				}
				livroAtual = livroAtual->esq;
			}
			else
			{
				if (livroAtual->dir == NULL)
				{
					livroAtual->dir = novoLivro;
					novoLivro->pai = livroAtual;
				}
				livroAtual = livroAtual->dir;
			}
		}
	}
}

void excluirLivro(Livro *livros, char *isbn)
{
	int excluirIsbn = encriptar(isbn);
	int isbnAtual = encriptar(livros->isbn);
	Livro *auxLivro = livros;

	while (auxLivro != NULL)
	{
		if (excluirIsbn == isbnAtual)
			return livros;
		else if (excluirIsbn < isbnAtual)
			isbnAtual = encriptar(auxLivro->esq->isbn);
		else if (excluirIsbn > isbnAtual)
			isbnAtual = encriptar(auxLivro->dir->isbn);

		if (auxLivro)
			isbnAtual = encriptar(auxLivro->isbn);
	}
}

void operacoesFilial(Filial *L, int id)
{
	Filial *filial = buscaFilial(L, id);
	int escolha;

	printf("1 - Imprimir lista de livros em ordem crescente de ISBN.\n"
		   "2 - Inserir novo livro.\n"
		   "3 - Buscar livro.\n"
		   "4 - Imprimir estrutura de arvore dos livros com ISBN.\n"
		   "5 - Excluir livro.\n"
		   "6 - Retornar ao menu principal.\n\n");

	printf("Digite a opcao desejada: ");
	scanf("%d", &escolha);

	while (escolha != 6)
	{
		if (escolha == 1)
			listarLivrosOrdemCrescente(filial->livros);
		else if (escolha == 2)
		{
			Livro *novoLivro = coletaDadosNovoLivro();
			inserirLivro(filial->livros, novoLivro);
		}
		else if (escolha == 3)
		{
			printf("Insira o ISBN do livro que deseja encontrar: \n");
			char isbn[5];
			scanf("%s", &isbn);
			buscarLivro(filial->livros, isbn);
		}
		else if (escolha == 4)
			imprimirEstrutura(filial->livros);
		else if (escolha == 5)
		{
			printf("Insira o ISBN do livro que deseja excluir: \n");
			char isbn[5];
			scanf("%s", &isbn);
			excluirLivro(filial->livros, isbn);
		}
		else if (escolha == 6)
			main();
		else
		{
			printf("Escolha invalida.\n"
				   "Por favor, digite um numero valido.\n");
			system("cls");
		}
	}
}


// operações com FILIAIS