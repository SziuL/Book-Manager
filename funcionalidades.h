#ifndef funcionalidades_h
#define funcionalidades_h

#include "estruturas.h"

// funções para filiais
void listarLivrosOrdemCrescente(Filial *filiais, Livro *livros);
void inserirLivro(Livro *livros, Livro *novoLivro);
Livro *buscarLivro(Livro *livros, char *isbn);
void imprimirEstrutura(Livro *livros, int n);
Livro *excluirLivro(Livro *livros, char *isbn);
void atualizarExemplar(Livro *livro);

// operações de menu
void listarTodasFiliais(Filial *filiais);
void listarFilial(Filial *filiais, int id);
Filial *coletaDadosFilial();
void excluirFilial();
void operacoesFilial(Filial *filiais, Livro *livros);

// complementares
void transferirBaseDados(Filial *L, int idAntiga, int idNova);
int encriptar(char isbn[5]);
Filial *buscaFilial(Filial *L, int id);
Livro *menor(Livro *livro);
Livro *maior(Livro *livro);
Livro *sucessor(Livro *livro);
Livro *predecessor(Livro *livro);
Livro *coletaDadosNovoLivro();
void imprimeIsbn(char *isbn, int n);
void selecionaFilial(Filial *filiais, int id);
void inserirFilial(Filial *filiais, Filial *novaFilial);

// programa principal
void programa(Filial *filiais);

#endif