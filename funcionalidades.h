#ifndef funcionalidades_h
#define funcionalidades_h

#include "estruturas.h"

// funções para filiais
void listarLivrosOrdemCrescente(Livro *livros);
void inserirLivro(Livro *livros, Livro *novoLivro);
Livro *buscarLivro(Livro *livros, char *isbn);
void imprimirEstrutura(Livro *livros);
void excluirLivro(Livro *livros, char *isbn);
void atualizarExemplar(Livro *livro);

// operações de menu
void listarTodasFiliais();
void listarFilial();
void coletaDadosFilial();
void excluirFilial();
void operacoesFilial(Filial *L, int id);

// complementares
void transferirBaseDados(Filial *L, int idAntiga, int idNova);
int encriptar(char isbn[5]);
Filial *buscaFilial(Filial *L, int id);
Livro *menor(Livro *livro);
Livro *maior(Livro *livro);
Livro *sucessor(Livro *livro);
Livro *predecessor(Livro *livro);
Livro *coletaDadosNovoLivro();

#endif