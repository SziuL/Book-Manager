#ifndef funcionalidades_h
#define funcionalidades_h

#include "estruturas.h"

// funções para filiais
void listarLivrosOrdemCrescente(Filial *filiais, Livro *livros);
void inserirLivro(Livro *livros, Livro *novoLivro);
Livro *buscarLivro(Livro *livros, char *isbn);
void imprimirEstrutura(Livro *livros, int n);
Livro *excluirLivro(Livro *livros, char *isbn);

// operações de menu
void listarTodasFiliais(Filial *filiais);
void listarFilial(Filial *filiais, int id);
Filial *coletaDadosFilial();
void excluirFilial(Filial *filiais, int idOrigem, int idDestino);
void operacoesFilial(Filial *filiais, Livro *livros);

// complementares
void imprimeMenuPrincipal();
int encriptar(char isbn[5]);
Filial *buscaFilial(Filial *filiais, int id, Filial **pred);
Livro *menor(Livro *livro);
Livro *maior(Livro *livro);
Livro *coletaDadosNovoLivro();
void imprimeIsbn(char *isbn, int n);
void selecionaFilial(Filial *filiais, int id);
void inserirFilial(Filial *filiais, Filial *novaFilial);
void percorreLivros(Livro *livrosOrigem, Livro *baseDadosDestino);

// programa principal
void programa(Filial *filiais);

#endif