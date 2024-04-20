#ifndef ARVOREGENEALOGICA_H_INCLUDED
#define ARVOREGENEALOGICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct Pessoa {
    char nome[50];
    struct Pessoa *conjuge;
    struct Pessoa *filhos[50];
    struct Pessoa *filhosIrmao[50];
    struct Pessoa *irmao[50];
    struct Pessoa *irmaosIrmao;
    struct Pessoa *pai;
    struct Pessoa *mae;
    struct Pessoa *ultimoIrmao;
    struct Pessoa *proximoIrmao;
    struct Pessoa *filaIrmaos;
    struct Pessoa **lista;
    int numIrmaos;
    int numFilhos;
};
typedef struct Pessoa Pessoa;

// Estrutura de uma fila de irmãos
typedef struct Fila {
    Pessoa *frente;
    Pessoa *fundo;
} Fila;

struct ArvoreGenealogica {
    Pessoa *raiz;
};
typedef struct ArvoreGenealogica ArvoreGenealogica;

typedef struct OperacaoHistorico {
    int tipoOperacao;  // 0 para adição, 1 para remoção
    Pessoa *pessoa;    // Pode ser NULL em caso de remoção
}OperacaoHistorico;

// Estrutura da pilha de operações
typedef struct PilhaOperacoes {
    int topo;
    int tamanho;
    OperacaoHistorico *elementos;
} PilhaOperacoes;

Pessoa *criarPessoa(char nome[]);
ArvoreGenealogica *criarArvoreGenealogica();
Pessoa *encontrarPessoa(Pessoa *raiz, char nome[]);
Fila *criarFila();
PilhaOperacoes *criarPilha(int tamanho);
Pessoa *desenfileirar(Fila *fila);
//adicionar
void adicionarPai(Pessoa *pessoa, char nomePai[]);
void adicionarMae(Pessoa *pessoa, char nomeMae[]);
void adicionarConjuge(Pessoa *pessoa, char nomeConjuge[]);
void adicionarFilho(Pessoa *pai, char nomeFilho[]);
void adicionarPessoa(ArvoreGenealogica *arvore, char nome[]);
//void adicionarFilhoIrmao(Pessoa *irmao, char nomeFilhoIrmao[]);
void adicionarFilhoAoIrmao(Pessoa *irmao, const char *nomeFilho);
void adicionarIrmao(Pessoa *pessoa, char nomeIrmao[], char conjugeIrmao[], char filhoIrmao[], char pai[], char mae[]);
void enfileirar(Fila *fila, Pessoa *pessoa);
//Impressão
void mostrarArvore(Pessoa *pessoa, int nivel);
void mostrarIrmaos(Pessoa *pessoa);
void mostrarFilhos(Pessoa *pessoa);
void mostrarFilhosIrmao(Pessoa *irmao, char nomeIrmao[]);
//desfazer e refazer
void removerPessoaRecursivo(Pessoa *raiz, const char *nome);
void removerPessoa(ArvoreGenealogica *arvore, const char *nome);
void desfazerOperacao(ArvoreGenealogica *arvore, PilhaOperacoes *pilha);
void refazerOperacao(ArvoreGenealogica *arvore, PilhaOperacoes *pilha);
void liberarArvore(ArvoreGenealogica *arvore);
void liberarPessoaRecursivo(Pessoa *raiz);
void liberarPilhaOperacoes(PilhaOperacoes *pilha);
#endif // ARVOREGENEALOGICA_H_INCLUDED
