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

Filial *buscaFilial(Filial *filiais, int id, Filial **pred)
{
	Filial *aux = filiais;
	if (!aux)
	{
		printf("Nao ha filiais registradas!\n");
		programa(filiais);
	}
	while (aux->id != id && aux != NULL)
		aux = aux->prox;

	if (aux == NULL)
	{
		printf("Filial nao enconteada.\n");
		programa(filiais);
	}
	return aux;
}

Livro *menor(Livro *livro)
{
	Livro *aux = livro;

	if (livro == NULL)
	{
		return NULL;
	}
	else
	{
		while (aux != NULL)
		{
			if (aux->esq == NULL)
				return aux;
			else
				aux = aux->esq;
		}
	}

	return aux;
}

Livro *maior(Livro *livro)
{
	Livro *aux = livro;
	if (livro == NULL)
	{
		return NULL;
	}
	else
	{
		while (aux != NULL)
		{
			if (aux->dir == NULL)
				return aux;
			else
				aux = aux->dir;
		}
	}

	return aux;
}

Livro *coletaDadosNovoLivro()
{
	char isbn[5], titulo[20], autor[30];
	int qtd;

	printf("Informe o ISBN do novo livro: \n");
	scanf("%s", isbn);
	printf("Agora informe o titulo e autor do livro, respectivamente  ('titulo' 'autor'): \n");
	scanf("%s %s", titulo, autor);

	Livro *novoLivro = criaLivro(isbn, titulo, autor);

	return novoLivro;
}

/**
 * A função "imprimeIsbn" imprime o número ISBN fornecido com um nível de recuo especificado.
 */
void imprimeIsbn(char *isbn, int n)
{
	for (int i = 0; i < n; i++)
		printf("   ");
	if (strcmp(isbn, "0000") != 0)
		printf("%s\n", isbn);
	else
		printf(" \n");
}

void inserirFilial(Filial *filiais, Filial *novaFilial)
{
	Filial *aux = filiais;
	if (aux == NULL)
	{
		filiais = novaFilial;
	}
	else
	{
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novaFilial;
	}

	printf("Filial inserida com sucesso!\n");
}

void percorreLivros(Livro *livrosOrigem, Livro *baseDadosDestino)
{
	Livro *aux = livrosOrigem;
	if (aux != NULL)
	{
		aux = livrosOrigem->esq;
		percorreLivros(aux, baseDadosDestino);
		inserirLivro(baseDadosDestino, aux);
		aux = livrosOrigem->dir;
		percorreLivros(aux, baseDadosDestino);
	}
	Livro *excluir;

	if (excluir != NULL)
	{
		excluir = livrosOrigem->esq;
		percorreLivros(excluir, baseDadosDestino);
		free(excluir);
		excluir = livrosOrigem->dir;
		percorreLivros(excluir, baseDadosDestino);
	}
}

// operações com LIVROS
void listarLivrosOrdemCrescente(Filial *filiais, Livro *livros)
{
	if (livros == NULL)
	{
		printf("Filial nao possui livros!\n");
		operacoesFilial(filiais, livros);
	}
	else
	{
		listarLivrosOrdemCrescente(filiais, livros->esq);
		printf("%s\t", livros->isbn);
		listarLivrosOrdemCrescente(filiais, livros->dir);
	}
}

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

void imprimirEstrutura(Livro *livros, int n)
{
	if (livros == NULL)
	{
		imprimeIsbn("0000", n);
		return;
	}
	imprimirEstrutura(livros->dir, n + 1);
	imprimeIsbn(livros->isbn, n);
	imprimirEstrutura(livros->esq, n + 1);
}

Livro *excluirLivro(Livro *livros, char *isbn)
{
	int excluirIsbn = encriptar(isbn);
	Livro *auxLivro = buscarLivro(livros, isbn);

	if (auxLivro->esq == NULL && auxLivro->dir == NULL)
	{
		if (auxLivro == livros)
			livros = NULL;
		else
		{
			if (excluirIsbn < encriptar(auxLivro->pai->isbn))
				auxLivro->pai->esq = NULL;
			else
				auxLivro->pai->dir = NULL;
		}
	}
	else if (auxLivro->esq != NULL && auxLivro->dir == NULL)
	{
		if (auxLivro == livros)
		{
			livros = auxLivro->esq;
			livros->pai = NULL;
		}
		else
		{
			auxLivro->esq->pai = auxLivro->pai; // ligação do filho de auxLivro com seu "avô"
			if (excluirIsbn < encriptar(auxLivro->pai->isbn))
				auxLivro->pai->esq = auxLivro->esq;
			else
				auxLivro->pai->dir = auxLivro->esq;
		}
	}
	else if (auxLivro->esq == NULL && auxLivro->dir != NULL)
	{
		if (auxLivro == livros)
		{
			livros = auxLivro->dir;
			livros->pai = NULL;
		}
		else
		{
			auxLivro->dir->pai = auxLivro->pai;
			if (excluirIsbn < encriptar(auxLivro->pai->isbn))
				auxLivro->pai->esq = auxLivro->dir;
			else
				auxLivro->pai->dir = auxLivro->dir;
		}
	}
	else
	{
		Livro *retornoMaior = maior(auxLivro);

		strcpy(auxLivro->isbn, retornoMaior->isbn);
		auxLivro->dir = excluirLivro(auxLivro->dir, isbn);
	}

	return livros;
}

void selecionaFilial(Filial *filiais, int id)
{
	Filial *filial = buscaFilial(filiais, id, NULL);
	operacoesFilial(filiais, filial->livros);
}

void operacoesFilial(Filial *filiais, Livro *livros)
{
	int escolha;

	printf("1 - Imprimir lista de livros em ordem crescente de ISBN.\n"
		   "2 - Inserir novo livro.\n"
		   "3 - Buscar livro.\n"
		   "4 - Imprimir estrutura de arvore dos livros com ISBN.\n"
		   "5 - Excluir livro.\n"
		   "6 - Retornar ao menu principal.\n\n");

	printf("Digite a opcao desejada: ");
	scanf("%d", &escolha);
	int a = 0;
	while (escolha != 6)
	{
		if (escolha == 1)
			listarLivrosOrdemCrescente(filiais, livros);
		else if (escolha == 2)
		{
			Livro *novoLivro = coletaDadosNovoLivro();
			inserirLivro(livros, novoLivro);
		}
		else if (escolha == 3)
		{
			printf("Insira o ISBN do livro que deseja encontrar: \n");
			char isbn[5];
			scanf("%s", isbn);
			buscarLivro(livros, isbn);
		}
		else if (escolha == 4)
			imprimirEstrutura(livros, 0);
		else if (escolha == 5)
		{
			printf("Insira o ISBN do livro que deseja excluir: \n");
			char isbn[5];
			scanf("%s", isbn);
			excluirLivro(livros, isbn);
		}
		else if (escolha == 6)
			programa(filiais);
		else
		{
			printf("Escolha invalida.\n"
				   "Por favor, digite um numero valido.\n");
			system("cls");
		}
	}
}

// operações com FILIAIS
void listarTodasFiliais(Filial *filiais)
{
	Filial *aux = filiais;
	if (!aux)
	{
		printf("Nao ha filiais cadastradas.\n");
		programa(filiais);
	}
	printf("Lista de Filiais\n\n");
	while (aux != NULL)
	{
		printf("1\n\tID: %d\n\tEndereco: %s\n\tGerente: %s\n\n", aux->id, aux->endereco, aux->gerente);
		aux = aux->prox;
	}
}

void listarFilial(Filial *filiais, int id)
{
	Filial *filial = buscaFilial(filiais, id, NULL);

	printf("Dados da Filial selecionada\n\n");
	printf("ID: %d\nEndereco: %s\nGerente: %s", filial->id, filial->endereco, filial->gerente);
}

Filial *coletaDadosFilial()
{
	int id;
	char endereco[50], gerente[30];

	printf("Informe o ID da nova filial: ");
	scanf("%d", &id);
	printf("Informe o endereco da filial: ");
	scanf("%s", endereco);
	printf("Informe o nome do gerente da filial: ");
	scanf("%s", gerente);

	Filial *novaFilial = criaFilial(endereco, gerente, id);

	return novaFilial;
}

void excluirFilial(Filial *filiais, int idOrigem, int idDestino)
{
	Filial *pred;
	Filial *filialOrigem = buscaFilial(filiais, idOrigem, &pred);
	Filial *filialDestino = buscaFilial(filiais, idDestino, NULL);

	if (!filialOrigem && !filialDestino)
	{
		printf("Algo deu errado! Verifique se os IDs estao corretos\n"
			   "ou se as filiais informadas realmente existem.\n");
		programa(filiais);
	}
	else
	{
		percorreLivros(filialOrigem->livros, filialDestino->livros);

		pred->prox = filialOrigem->prox;
		free(filialOrigem);
	}
}