#include "funcionalidades.h"

// Funções de estrutura
Livro *criaLivro(char isbn[5], char titulo[15], char autor[15], int qtd)
{
	Livro *novo = (Livro *)calloc(1, sizeof(Livro));
	if (!novo)
	{
		printf("Erro ao alocar novo livro.\n");
		exit(1);
	}

	strcpy(novo->isbn, isbn);
	strcpy(novo->titulo, titulo);

	printf("Isbn por enquanto: %s\n", novo->isbn);
	printf("titulo por enquanto: %s\n", novo->titulo);

	strcpy(novo->autor, autor);
	novo->qtd = qtd;

	printf("Isbn por enquanto: %s\n", novo->isbn);

	return novo;
}

Filial *criaFilial(char endereco[15], char gerente[15], int id)
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
void imprimeMenuPrincipal()
{
	printf("1 - Listar os dados de todas as filiais.\n"
				 "2 - Listar os dados de uma filial\n"
				 "3 - Criar nova filial\n"
				 "4 - Encerrar atividades de uma filial\n"
				 "5 - Realizar operacoes no estoque de uma filial\n"
				 "6 - Sair\n\n");
}

int comparar(char atual[5], char isbn[5], int i)
{
	if (isbn[i] < atual[i])
		return -1; // ir para a esquerda
	else if (isbn[i] > atual[i])
		return 1; // ir para a direita
	else
		return comparar(atual, isbn, i + 1);
}

Filial *buscaFilial(Filial *filiais, int id, Filial **pred)
{
	Filial *aux = filiais;
	if (filiais == NULL)
	{
		printf("Nao ha filiais registradas!\n");
		programa(filiais);
	}
	while (aux->id != id && aux != NULL)
	{
		(*pred) = aux;
		aux = aux->prox;
	}

	if (aux == NULL)
	{
		printf("Filial nao enconteada.\n");
		programa(filiais);
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

Livro *coletaDadosNovoLivro(Livro *livros)
{
	Livro *novoLivro;
	char *isbn = (char *)calloc(5, sizeof(char));
	char *titulo = (char *)calloc(15, sizeof(char));
	char *autor = (char *)calloc(15, sizeof(char));

	fflush(stdin);
	printf("Informe o ISBN do novo livro: ");
	gets(isbn);

	fflush(stdin);
	printf("Agora informe o titulo do livro: ");
	gets(titulo);

	fflush(stdin);
	printf("Informe o autor do livro: ");
	gets(autor);

	printf("Isbn por enquanto: %s", isbn);
	novoLivro = criaLivro(isbn, titulo, autor, 0);
	printf("Isbn por enquanto: %s", novoLivro->isbn);

	return novoLivro;
}

/**
 * A função "imprimeIsbn" imprime o número ISBN fornecido com um nível de recuo especificado.
 */
void imprimeIsbn(char isbn[5], int n)
{
	for (int i = 0; i < n; i++)
		printf("   ");
	if (strcmp(isbn, "0000") != 0)
		printf("%s\n", isbn);
	else
		printf(" \n");
}

void inserirFilial(Filial **filiais, Filial *novaFilial)
{
	Filial **aux = filiais;
	if (*aux == NULL)
	{
		(*filiais) = novaFilial;
	}
	else
	{
		while ((*aux)->prox != NULL)
			(*aux) = (*aux)->prox;
		(*aux)->prox = novaFilial;
	}

	printf("Filial inserida com sucesso!\n");
}

Livro *percorreLivros(Livro *livros, char isbn[5], int qtd)
{
	Livro *retorno = buscarLivro(livros, isbn);

	if (livros)
	{
		Livro *auxLivro = livros;

		while (auxLivro != NULL)
		{
			if (strcmp(isbn, auxLivro->isbn) == 0)
			{
				qtd++;
				if (auxLivro->esq != NULL)
					auxLivro = auxLivro->esq;
				else if (auxLivro->dir != NULL)
					auxLivro = auxLivro->dir;
				else
					auxLivro = NULL;
			}
			else if (comparar(auxLivro->isbn, isbn, 0) == -1)
				auxLivro = percorreLivros(auxLivro->esq, isbn, qtd);
			else if (comparar(auxLivro->isbn, isbn, 0) == 1)
				auxLivro = percorreLivros(auxLivro->dir, isbn, qtd);
		}
	}
	if (retorno != NULL && qtd > 0)
		retorno->qtd = qtd;

	return retorno;
}

void excluirFolhas(Livro *livrosOrigem)
{
	Livro *aux = livrosOrigem;
	excluirFolhas(aux->esq);
	excluirFolhas(aux->dir);
	free(aux);
}

void percorreLivrosExcluir(Livro *livrosOrigem, Livro *baseDadosDestino)
{
	if (livrosOrigem != NULL)
	{
		percorreLivrosExcluir(livrosOrigem->esq, baseDadosDestino);
		percorreLivrosExcluir(livrosOrigem->dir, baseDadosDestino);
		inserirLivro(&baseDadosDestino, livrosOrigem);

		excluirFolhas(livrosOrigem);
	}
}

// operações com LIVROS
void listarLivrosOrdemCrescente(Filial *filiais, Livro *livros, int id)
{
	if (livros == NULL)
	{
		printf("Filial nao possui livros!\n");
		operacoesFilial(filiais, livros, id);
	}
	else
	{
		listarLivrosOrdemCrescente(filiais, livros->esq, id);
		printf("%s\t", livros->isbn);
		listarLivrosOrdemCrescente(filiais, livros->dir, id);
	}
}

Livro *buscarLivro(Livro *livros, char isbn[5])
{
	Livro *auxLivro = livros;
	strcpy(auxLivro->isbn, isbn);
	if (livros)
	{
		while (auxLivro != NULL)
		{
			if (strcmp(auxLivro->isbn, isbn) == 0)
				return auxLivro;
			else if (comparar(auxLivro->isbn, isbn, 0) == -1)
				auxLivro = buscarLivro(auxLivro->esq, isbn);
			else if (comparar(auxLivro->isbn, isbn, 0) == -1)
				auxLivro = buscarLivro(auxLivro->dir, isbn);
		}
	}

	printf("Base de dados vazia ou livro nao existente.\n");
	return auxLivro;
}

void inserirLivro(Livro **livros, Livro *novoLivro)
{
	if ((*livros) != NULL)
	{
		Livro **livroAtual = livros;

		while (livroAtual != NULL)
		{
			if (comparar((*livroAtual)->isbn, novoLivro->isbn, 0) == -1) // isbn novo é menor que atual
			{
				if ((*livroAtual)->esq == NULL)
				{
					(*livroAtual)->esq = novoLivro;
					novoLivro->pai = (*livroAtual);
				}
				(*livroAtual) = (*livroAtual)->esq;
			}
			else
			{
				if ((*livroAtual)->dir == NULL)
				{
					(*livroAtual)->dir = novoLivro;
					novoLivro->pai = (*livroAtual);
				}
				(*livroAtual) = (*livroAtual)->dir;
			}
		}
	}
	else
	{
		(*livros) = novoLivro;
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

Livro *excluirLivro(Livro *livros, char isbn[5])
{

	Livro *auxLivro = buscarLivro(livros, isbn);

	if (auxLivro->esq == NULL && auxLivro->dir == NULL)
	{
		if (auxLivro == livros)
			livros = NULL;
		else
		{																										// auxLivro->pai->isbn
			if (comparar(auxLivro->pai->isbn, isbn, 0) == -1) // isbn a ser excluido é menor que atual
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
			auxLivro->esq->pai = auxLivro->pai;								// ligação do filho de auxLivro com seu "avô"
			if (comparar(auxLivro->pai->isbn, isbn, 0) == -1) // isbn a ser excluido menor que auxLivro->pai
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
			if (comparar(auxLivro->pai->isbn, isbn, 0) == -1)
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
	system("cls");
	Filial *predDes;
	Filial *filial = buscaFilial(filiais, id, &predDes);
	if (filial)
		printf("Filial encontrada!\n");
	else
	{
		printf("Filial inexistente.\n");
		programa(filiais);
	}
	operacoesFilial(filiais, filial->livros, id);
}

void operacoesFilial(Filial *filiais, Livro *livros, int id)
{
	Sleep(3000);
	system("cls");
	int escolha;

	printf("1 - Imprimir lista de livros em ordem crescente de ISBN.\n"
				 "2 - Inserir novo livro.\n"
				 "3 - Buscar livro.\n"
				 "4 - Imprimir estrutura de arvore dos livros com ISBN.\n"
				 "5 - Excluir livro.\n"
				 "6 - Retornar ao menu principal.\n\n");

	printf("Digite a opcao desejada: ");
	scanf("%d", &escolha);

	if (escolha == 1)
		listarLivrosOrdemCrescente(filiais, livros, id);
	else if (escolha == 2)
	{
		Livro *novoLivro = coletaDadosNovoLivro(livros);
		inserirLivro(&livros, novoLivro);
		novoLivro = percorreLivros(livros, novoLivro->isbn, 0);
	}
	else if (escolha == 3)
	{
		printf("Insira o ISBN do livro que deseja encontrar: \n");
		char isbn[5];
		scanf("%s", isbn);
		Livro *l = buscarLivro(livros, isbn);
		system("cls");
		printf("Livro encontrado:\n\nISBN: %s"
					 "\nTitulo: %s"
					 "\nAutor: %s"
					 "\nQuantidade de exemplares: %d",
					 l->isbn, l->titulo, l->autor, l->qtd);
		Sleep(3000);
	}
	else if (escolha == 4)
		imprimirEstrutura(livros, 0);
	else if (escolha == 5)
	{
		printf("Insira o ISBN do livro que deseja excluir: \n");
		char isbn[5];
		fflush(stdin);
		gets(isbn);
		excluirLivro(livros, isbn);
	}
	else if (escolha == 6)
		programa(filiais);
	else
	{
		printf("Escolha invalida.\n"
					 "Por favor, digite um numero valido.\n");
		operacoesFilial(filiais, livros, id);
	}

	Filial *predDes;
	Filial *filialRetornda = buscaFilial(filiais, id, &predDes);
	filialRetornda->livros = livros;
	Sleep(5000);
	operacoesFilial(filiais, livros, id);
}

// operações com FILIAIS
void listarTodasFiliais(Filial *filiais)
{
	Filial *aux = filiais;
	int espera = 0;
	if (!aux)
	{
		printf("Nao ha filiais cadastradas.\n");
		programa(filiais);
	}
	printf("Lista de Filiais\n\n");
	while (aux != NULL)
	{
		espera += 2000;
		printf("1\n\tID: %d\n\tEndereco: %s\n\tGerente: %s\n\n", aux->id, aux->endereco, aux->gerente);
		aux = aux->prox;
	}

	Sleep(espera); // cálculo básico para determinar o tempo que o leitor terá para observar os resultados.
}

void listarFilial(Filial *filiais, int id)
{
	Filial *predDes;
	Filial *filial = buscaFilial(filiais, id, &predDes);

	printf("Dados da Filial selecionada\n\n");
	printf("ID: %d\nEndereco: %s\nGerente: %s\n", filial->id, filial->endereco, filial->gerente);
}

Filial *coletaDadosFilial()
{
	int id;
	char endereco[15], gerente[15];

	printf("Informe o ID da nova filial: ");
	scanf("%d", &id);

	fflush(stdin);
	printf("Informe o endereco da filial: ");
	gets(endereco);

	fflush(stdin);
	printf("Informe o nome do gerente da filial: ");
	gets(gerente);

	Filial *novaFilial = criaFilial(endereco, gerente, id);

	return novaFilial;
}

void excluirFilial(Filial *filiais, int idOrigem, int idDestino)
{
	Filial *pred, *predDes;
	Filial *filialOrigem = buscaFilial(filiais, idOrigem, &pred);
	Filial *filialDestino = buscaFilial(filiais, idDestino, &predDes);

	if (!filialOrigem && !filialDestino)
	{
		printf("Algo deu errado! Verifique se os IDs estao corretos\n"
					 "ou se as filiais informadas realmente existem.\n");
		programa(filiais);
	}
	else
	{
		percorreLivrosExcluir(filialOrigem->livros, filialDestino->livros);

		pred->prox = filialOrigem->prox;
		free(filialOrigem);
	}
}