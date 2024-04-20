#include <stdio.h>
#include <stdlib.h>
#include "ArvoreGenealogica.h"
#include <string.h>

// Função para criar uma fila de irmãos
Fila *criarFila() {
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    novaFila->frente = NULL;
    novaFila->fundo = NULL;
    return novaFila;
}

Pessoa *desenfileirar(Fila *fila) {
    if (fila == NULL || fila->frente == NULL) {
        return NULL;
    }

    Pessoa *pessoaDesenfileirada = fila->frente;
    fila->frente = fila->frente->irmao[0];

    if (fila->frente == NULL) {
        fila->fundo = NULL;
    }

    free(pessoaDesenfileirada);

    return fila->frente;
}

// Função para criar uma pilha de operações
PilhaOperacoes *criarPilha(int tamanho) {
    PilhaOperacoes *novaPilha = (PilhaOperacoes *)malloc(sizeof(PilhaOperacoes));
    novaPilha->topo = -1;
    novaPilha->tamanho = tamanho;
    novaPilha->elementos = (OperacaoHistorico *)malloc(tamanho * sizeof(OperacaoHistorico));
    return novaPilha;
}

Pessoa *criarPessoa(char nome[]) {
    Pessoa *novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));
    strcpy(novaPessoa->nome, nome);
    novaPessoa->conjuge = NULL;
    for(int i = 0; i < 50; i++){
    novaPessoa->irmao[i] = NULL;
    }
    novaPessoa->filaIrmaos = criarFila();
    for (int i = 0; i < 50; i++) {
    novaPessoa->filhosIrmao[i] = NULL;
    }
    for (int i = 0; i < 50; i++) {
        novaPessoa->filhos[i] = NULL;
    }
    return novaPessoa;
}

ArvoreGenealogica *criarArvoreGenealogica() {
    ArvoreGenealogica *novaArvore = (ArvoreGenealogica *)malloc(sizeof(ArvoreGenealogica));
    novaArvore->raiz = NULL;
    return novaArvore;
}

Pessoa *encontrarPessoa(Pessoa *raiz, char nome[]) {
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }

    Pessoa *pessoaEncontrada = NULL;

    // Verificar os filhos da pessoa atual
    for (int i = 0; raiz->filhos[i] != NULL; i++) {
        pessoaEncontrada = encontrarPessoa(raiz->filhos[i], nome);
        if (pessoaEncontrada != NULL) {
            return pessoaEncontrada;
        }
    }

    for (int i = 0; raiz->irmao[i] != NULL; i++) {
        pessoaEncontrada = encontrarPessoa(raiz->irmao[i], nome);
        if (pessoaEncontrada != NULL) {
            return pessoaEncontrada; // A pessoa foi encontrada nos irmãos
        }
    }

    return pessoaEncontrada;
}

void adicionarPai(Pessoa *pessoa, char nomePai[]){
    Pessoa *pais = criarPessoa(nomePai);
    pessoa->pai = pais;
}

void adicionarMae(Pessoa *pessoa, char nomeMae[]){
    Pessoa *maes = criarPessoa(nomeMae);
    pessoa->mae = maes;
}

void adicionarConjuge(Pessoa *pessoa, char nomeConjuge[]) {
    Pessoa *conjuge = criarPessoa(nomeConjuge);
    pessoa->conjuge = conjuge;
}
void adicionarFilhoAoIrmao(Pessoa *irmao, const char *nomeFilho) {

       if (irmao != NULL) {
        Pessoa *filho = criarPessoa(nomeFilho);

        // Encontrar o primeiro slot vazio no array de filhos do irmão
        int i;
        for (i = 0; irmao->filhosIrmao[i] != NULL; i++);

        // Adicionar o novo filho ao array
        irmao->filhosIrmao[i] = filho;
        irmao->filhosIrmao[i + 1] = NULL;  // Certificar-se de que o próximo slot está nulo
    }
}

void adicionarFilho(Pessoa *pai, char nomeFilho[]) {
    for (int i = 0; i < 50; i++) {
        if (pai->filhos[i] == NULL) {
            Pessoa *filho = criarPessoa(nomeFilho);
            pai->filhos[i] = filho;
            break;
        }
    }
}

void adicionarIrmao(Pessoa *pessoa, char nomeIrmao[], char conjugeIrmao[], char filhoIrmao[], char pai[], char mae[]){
    if (pessoa == NULL) {
        printf("Erro: O ponteiro Pessoa e NULL.\n");
        return;
    }

    Pessoa *irmao = criarPessoa(nomeIrmao);

    if (strlen(conjugeIrmao) > 0) {
        adicionarConjuge(irmao, conjugeIrmao);
    }
    if(strlen(filhoIrmao) > 0){
        adicionarFilhoAoIrmao(irmao, filhoIrmao);
    }

    if(strlen(pai) > 0 ){
        adicionarPai(irmao, pai);
    }
    if(strlen(mae) > 0){
        adicionarMae(irmao, mae);
    }
  int i;
    // Encontrar o último irmão
    for (i = 0; pessoa->irmao[i] != NULL; i++);

    // Adicionar o novo irmão ao final da lista
    pessoa->irmao[i] = irmao;
    irmao->irmao[0] = NULL;
    irmao->irmao[1] = NULL;
    irmao->irmao[2] = NULL;
}

void mostrarArvore(Pessoa *pessoa, int nivel) {
        if (pessoa != NULL) {

        if (pessoa->pai != NULL) {
            for (int i = 0; i < nivel; i++) {
                printf("  ");
            }
            printf("(Pai: %s)\n", pessoa->pai->nome);
        }
        if (pessoa->mae != NULL) {
            for (int i = 0; i < nivel; i++) {
                printf("  ");
            }
            printf("(Mae: %s)\n", pessoa->mae->nome);
        }

        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        printf("%s\n", pessoa->nome);

        if (pessoa->conjuge != NULL) {
            for (int i = 0; i < nivel; i++) {
                printf("  ");
            }
            printf("(Esposa: %s)\n", pessoa->conjuge->nome);
        }

        for (int i = 0; pessoa->filhos[i] != NULL; i++) {
            if (pessoa->filhos[i]->nome != NULL) {
                mostrarArvore(pessoa->filhos[i], nivel + 1);
            }
        }

        for (int i = 0; pessoa->irmao[i] != NULL; i++) {
            for (int j = 0; j < nivel; j++) {
                printf("  ");
            }
            printf("(Irmao %s: %s)\n", pessoa->nome, pessoa->irmao[i]->nome);
            if (pessoa->irmao[i]->conjuge != NULL) {
                for (int j = 0; j < nivel + 1; j++) {
                    printf("  ");
                }
                printf("(Esposa de %s: %s)\n", pessoa->irmao[i]->nome, pessoa->irmao[i]->conjuge->nome);
            }
            for (int j = 0; pessoa->irmao[i]->filhosIrmao[j] != NULL; j++) {
                if (pessoa->irmao[i]->filhosIrmao[j]->nome != NULL) {
                mostrarArvore(pessoa->irmao[i]->filhosIrmao[j], nivel + 2);
                }
            }
        }
    }
}

void mostrarFilhosIrmao(Pessoa *irmao, char nomeIrmao[]) {
    if (irmao != NULL) {
        for(int i = 0; irmao->filhosIrmao[i] != NULL; i++){
        Pessoa *filhoAtual = irmao->filhosIrmao[i];

        while (filhoAtual != NULL) {
            printf("Filho de %s: %s\n", irmao->nome, filhoAtual->nome);
            filhoAtual = filhoAtual->irmao[0];
            }
        }
    }
}
void mostrarIrmaos(Pessoa *pessoa) {
     if (pessoa != NULL) {
        for (int i = 0; pessoa->irmao[i] != NULL; i++) {
            Pessoa *irmaoAtual = pessoa->irmao[i];

        while (irmaoAtual != NULL) {
            printf("Irmao de %s: %s\n", pessoa->nome, irmaoAtual->nome);
            irmaoAtual = irmaoAtual->irmao[i];
            }
        }
    }
}
void liberarFila(Fila *fila) {
    if (fila != NULL) {
        while(fila->frente != NULL){
            Pessoa *proximo = desenfileirar(fila);
            free(proximo);
        }
        free(fila);
    }
}
void removerPessoaRecursivo(Pessoa *raiz, const char *nome) {
     if (raiz == NULL) {
        return;
    }

    // Remover da lista de irmãos
    if (raiz->irmao[0] != NULL && strcmp(raiz->irmao[0]->nome, nome) == 0) {
        Pessoa *remover = raiz->irmao[0];
        raiz->irmao[0] = remover->irmao[0];
        free(remover);
        return;
    }

    // Remover da lista de esposa
    if (raiz->conjuge != NULL && strcmp(raiz->conjuge->nome, nome) == 0) {
        Pessoa *remover = raiz->conjuge;
        raiz->conjuge = remover->conjuge;
        free(remover);
        return;
    }

    if(raiz->filhosIrmao[0] != NULL && strcmp(raiz->filhosIrmao[0]->nome, nome) == 0){
        Pessoa *remover = raiz->filhosIrmao[0];
        raiz->filhosIrmao[0] = remover->filhosIrmao[0];
        free(remover);
        return;
    }

    // Remover da lista de filhos
    for (int i = 0; raiz->filhos[i] != NULL; i++) {
        if (strcmp(raiz->filhos[i]->nome, nome) == 0) {
            Pessoa *remover = raiz->filhos[i];

            // Deslocar os filhos restantes para preencher o espaço vazio
            for (int j = i; raiz->filhos[j + 1] != NULL; j++) {
                raiz->filhos[j] = raiz->filhos[j + 1];
                raiz->filhos[j] = NULL;
            }
            free(remover);
            return;
        }
    }

    // Recursivamente procurar nos filhos
    for (int i = 0; raiz->filhos[i] != NULL; i++) {
        removerPessoaRecursivo(raiz->filhos[i], nome);
    }

    // Recursivamente procurar nos irmãos
    if (raiz->irmao[0] != NULL) {
        removerPessoaRecursivo(raiz->irmao[0], nome);
    }
}

void removerPessoa(ArvoreGenealogica *arvore, const char *nome) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("A arvore esta vazia.\n");
        return;
    }

    Pessoa *raiz = arvore->raiz;

    if (strcmp(raiz->nome, nome) == 0) {
        free(raiz);
        arvore->raiz = NULL;
        return;
    }
    removerPessoaRecursivo(raiz, nome);
}

void enfileirar(Fila *fila, Pessoa *pessoa){
       if(fila == NULL || pessoa == NULL){
        return;
    }
    if(fila->fundo == NULL){
        fila->frente = pessoa;
        fila->fundo = pessoa;
    } else {
        int i;
        for (i = 0; fila->fundo->irmao[i] != NULL; i++);
        fila->fundo->irmao[i] = pessoa;
        fila->fundo = pessoa;
    }
}

void adicionarOperacao(PilhaOperacoes *pilha, int tipoOperacao, Pessoa *pessoa) {
    if (pilha == NULL) {
        return;
    }

    if (pilha->topo == pilha->tamanho - 1) {
        // A pilha está cheia, você pode decidir o que fazer nesse caso
        return;
    }

    pilha->elementos[++pilha->topo].tipoOperacao = tipoOperacao;
    pilha->elementos[pilha->topo].pessoa = pessoa;
}

void adicionarPessoa(ArvoreGenealogica *arvore, char nome[]) {
    Pessoa *novaPessoa = criarPessoa(nome);

    // Definir a raiz da árvore genealógica se ainda não estiver definida
    if (arvore->raiz == NULL) {
        arvore->raiz = novaPessoa;
    }
}

void desfazerOperacao(ArvoreGenealogica *arvore, PilhaOperacoes *pilha) {
    if (arvore == NULL || pilha == NULL) {
        printf("Erro: Arvore ou pilha invalida.\n");
        return;
    }

    if (pilha->topo == -1) {
        printf("Nenhuma operacao para desfazer.\n");
        return;
    }

    OperacaoHistorico operacao = pilha->elementos[pilha->topo];
    pilha->topo--;

    printf("Tipo de operacao no topo: %d\n", operacao.tipoOperacao);

    if (operacao.tipoOperacao == 0 && operacao.pessoa != NULL) {  // Adição
        if (arvore->raiz == NULL) {
            printf("Erro: A arvore esta vazia.\n");
            return;
        }
        removerPessoaRecursivo(arvore->raiz, operacao.pessoa->nome);
        free(operacao.pessoa->nome);
        printf("Desfeita a adicao de uma pessoa.\n");
    } else {
        printf("Tipo de operacao nao reconhecido ou pessoa nula.\n");
    }
}

// Função para refazer uma operação
void refazerOperacao(ArvoreGenealogica *arvore, PilhaOperacoes *pilha) {
if (arvore == NULL || pilha == NULL || pilha->topo == pilha->tamanho - 1) {
        printf("Nenhuma operacao para refazer.\n");
        return;
    }

    OperacaoHistorico operacao = pilha->elementos[++pilha->topo];

    if (operacao.tipoOperacao == 0 && operacao.pessoa != NULL) {  // Adição
        adicionarPessoa(arvore, operacao.pessoa);
    }

    printf("Operacao refeita.\n");
}

void liberarArvore(ArvoreGenealogica *arvore) {
    if (arvore != NULL) {
        liberarPessoaRecursivo(arvore->raiz);
        free(arvore);
    }
}

void liberarPilhaOperacoes(PilhaOperacoes *pilha) {
    if (pilha != NULL) {
        free(pilha->elementos);
        free(pilha);
    }
}

void liberarPessoaRecursivo(Pessoa *raiz) {
    if (raiz != NULL) {
        for (int i = 0; raiz->filhos[i] != NULL; i++) {
            liberarPessoaRecursivo(raiz->filhos[i]);
        }
        liberarFila(raiz->filaIrmaos);
        free(raiz);
    }
}
