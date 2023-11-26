#ifndef funcionalidades_h
#define funcionalidades_h

#include "estruturas.h"

// funções para filiais
void listarLivrosOrdemCrescente(Filial *filiais, Livro *livros, int id);
void inserirLivro(Livro **livros, Livro *novoLivro);
Livro *buscarLivro(Livro *livros, char isbn[5]);
void imprimirEstrutura(Livro *livros, int n);
Livro *excluirLivro(Livro *livros, char isbn[5]);

// operações de menu
void listarTodasFiliais(Filial *filiais);
void listarFilial(Filial *filiais, int id);
Filial *coletaDadosFilial();
void excluirFilial(Filial *filiais, int idOrigem, int idDestino);
void operacoesFilial(Filial *filiais, Livro *livros, int id);

// complementares
void imprimeMenuPrincipal();
int comparar(char atual[5], char isbn[5], int i);
Filial *buscaFilial(Filial *filiais, int id, Filial **pred);
Livro *maior(Livro *livro);
Livro *coletaDadosNovoLivro(Livro *livros);
void imprimeIsbn(char isbn[5], int n);
void selecionaFilial(Filial *filiais, int id);
void inserirFilial(Filial **filiais, Filial *novaFilial);
Livro *percorreLivros(Livro *livrosOrigem, char isbn[5], int qtd);
void percorreLivrosExcluir(Livro *livrosOrigem, Livro *baseDadosDestino);
void excluirFolhas(Livro *livrosOrigem);

// programa principal
void programa(Filial *filiais);

#endif