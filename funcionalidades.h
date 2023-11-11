#include "estruturas.h"

// funções para filiais
Livro *buscarLivro(Filial *L, int idFilial, char *isbn);
void listarLivros(Filial *filial);
void inserirLivro(Livro *livro, Filial *L, int idFilial);
void excluirLivro(Livro *livro);
void atualizarExemplar(Livro *livro);

// operações de menu
void listarTodasFiliais();
void listarFilial();
void coletaDadosFilial();
void excluirFilial();
void operacoesFilial();

// complementares
void transferirBaseDados(Filial *L, int idAntiga, int idNova);
int encriptar(char isbn[5]);
Filial *buscaFilial(Filial *L, int id);
Livro *menor(Livro *livro);
Livro *maior(Livro *livro);
Livro *sucessor(Livro *livro);
Livro *predecessor(Livro *livro);