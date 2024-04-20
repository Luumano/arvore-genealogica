#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreGenealogica.h"

int main(){
    ArvoreGenealogica *arvore = criarArvoreGenealogica();
    int opcao;
    char nome[50], conjuge[50], filho[50], irmao[50], conjugeIrmao[50], filhoIrmao[50];
    char pai[50], mae[50];
    PilhaOperacoes *pilhaOperacoes = criarPilha(100);

    do{
        printf("\nMenu:\n");
        printf("1. Adicionar Pessoa\n");
        printf("2. Adicionar Irmao\n");
        printf("3. Adicionar Filho do Irmao\n");
        printf("4. Adicionar Esposa ao Irmao\n");
        printf("5. Imprimir Arvore Genealogica\n");
        printf("6. Adicionar Esposa a Pessoa\n");
        printf("7. Adicionar Filho a Pessoa\n");
        printf("8. Buscar Pessaoas Cadastrada na Arvore\n");
        printf("9. Remover membro\n");
        printf("10. Desfazer\n");
        printf("11. Refazer\n");
        printf("12. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        getchar();

        switch (opcao)
        {
        case 1:
            printf("Digite o nome da pessoa: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            Pessoa * novaPessoa = criarPessoa(nome);
            adicionarConjuge(novaPessoa, "NULL");

                printf("Digiteo nome do Pai: ");
                fgets(pai, sizeof(pai), stdin);
                pai[strcspn(pai, "\n")] = '\0';
                adicionarPai(novaPessoa, pai);

                printf("Digiteo nome da Mae: ");
                fgets(mae, sizeof(mae), stdin);
                mae[strcspn(mae, "\n")] = '\0';
                adicionarMae(novaPessoa, mae);

            printf("A pessoa tem uma esposa ? (Digite 1 para sim, 2 para nao): ");
            int temConjuge;
            scanf("%d", &temConjuge);

            getchar();

            if(temConjuge == 1){
                printf("Digiteo nome da esposa: ");
                fgets(conjuge, sizeof(conjuge), stdin);
                conjuge[strcspn(conjuge, "\n")] = '\0';
                adicionarConjuge(novaPessoa, conjuge);
            }

            printf("A pessoa tem filhos ? (Digite 1 para sim e 2 para nao): ");
            int temFilhos;
            scanf("%d", &temFilhos);

            getchar();

            if(temFilhos == 1){
                    printf("Digite o nome do filho: ");
                    fgets(filho, sizeof(filho), stdin);
                    filho[strcspn(filho, "\n")] = '\0';

                    if(strcmp(filho, "0") == 0){
                        break;
                    }
                    adicionarFilho(novaPessoa, filho);
            }
                            // Definir a raiz da árvore genealógica se ainda não estiver definida
                if (arvore->raiz == NULL) {
                    arvore->raiz = novaPessoa;
                }
            break;

            case 2:
                printf("Digite o nome do irmao: ");
                fgets(irmao, sizeof(irmao), stdin);
                irmao[strcspn(irmao, "\n")] = '\0';

                 printf("O irmao tem uma esposa ? (Digite 1 para sim, 2 para nao): ");
                    int temConjugeIrmao;
                    scanf("%d", &temConjugeIrmao);

                    getchar();

            if(temConjugeIrmao == 1){
                printf("Digite o nome da esposa do irmao: ");
                fgets(conjugeIrmao, sizeof(conjugeIrmao), stdin);
                conjugeIrmao[strcspn(conjugeIrmao, "\n")] = '\0';
            }
            printf("A pessoa tem filhos ? (Digite 1 para sim e 2 para nao): ");
            int temFilhosIrmao;
            scanf("%d", &temFilhosIrmao);

            getchar();

            if(temFilhosIrmao == 1){
                printf("Digite o nome do filho do irmao: ");
                fgets(filhoIrmao, sizeof(filhoIrmao), stdin);
                filhoIrmao[strcspn(filhoIrmao, "\n")] = '\0';
                adicionarFilhoAoIrmao(irmao, filhoIrmao);
            }
                printf("Adicinado com sucesso!\n");
                adicionarIrmao(novaPessoa, irmao, conjugeIrmao, filhoIrmao, pai, mae);
            break;

            case 3:
            printf("Digite o nome da pessoa para pesquisar o irmao: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            Pessoa *pessoaVerIrmaos = encontrarPessoa(arvore->raiz, nome);

            if (pessoaVerIrmaos != NULL) {
                mostrarIrmaos(pessoaVerIrmaos);
            }

                printf("Digite o nome do irmao: ");
                fgets(irmao, sizeof(irmao), stdin);
                irmao[strcspn(irmao, "\n")] = '\0';

                Pessoa *irmaoParaFilho = encontrarPessoa(arvore->raiz, irmao);

                if (irmaoParaFilho == NULL) {
                    printf("Irmao nao encontrado na arvore.\n");
                    break;
                }

                printf("Digite o nome do filho do irmao: ");
                fgets(filhoIrmao, sizeof(filhoIrmao), stdin);
                filhoIrmao[strcspn(filhoIrmao, "\n")] = '\0';

                adicionarFilhoAoIrmao(irmaoParaFilho, filhoIrmao);
                printf("Cadastro realizado com sucesso!\n");
                break;

            case 4:
            printf("Digite o nome da pessoa para pesquisar o irmao: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            Pessoa *pessoaVerIrmao = encontrarPessoa(arvore->raiz, nome);

            if (pessoaVerIrmao != NULL) {
                mostrarIrmaos(pessoaVerIrmao);
            }

                printf("Digite o nome do irmao: ");
                fgets(irmao, sizeof(irmao), stdin);
                irmao[strcspn(irmao, "\n")] = '\0';

                Pessoa *esposaParaIrmao = encontrarPessoa(arvore->raiz, irmao);

                if (esposaParaIrmao == NULL) {
                    printf("Irmao nao encontrado na arvore.\n");
                    break;
            }

                printf("Digite o da esposa do irmao: ");
                fgets(conjugeIrmao, sizeof(conjugeIrmao), stdin);
                conjugeIrmao[strcspn(conjugeIrmao, "\n")] = '\0';
                adicionarConjuge(esposaParaIrmao, conjugeIrmao);
                printf("Cadastro realizado com sucesso!\n");
                break;

            case 5:
                printf("\nArvore Genealogica:\n");
                mostrarArvore(arvore->raiz, 0);
                break;
            case 6:
                printf("Digiteo nome da esposa: ");
                fgets(conjuge, sizeof(conjuge), stdin);
                conjuge[strcspn(conjuge, "\n")] = '\0';
                adicionarConjuge(novaPessoa, conjuge);
                printf("Esposa adicionada com sucesso!\n");
                break;
            case 7:
                printf("Digite o nome do filho: ");
                fgets(filho, sizeof(filho), stdin);
                filho[strcspn(filho, "\n")] = '\0';
                adicionarFilho(novaPessoa, filho);
                printf("Filho adicionado com sucesso\n");
                break;
            case 8:
                printf("Digite o nome da pessoa para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                Pessoa *pessoaBuscada = encontrarPessoa(arvore->raiz, nome);

                if (pessoaBuscada != NULL) {
                    printf("Pessoa encontrada!\n");
                    printf("Nome: %s\n", pessoaBuscada->nome);

                    if (pessoaBuscada->pai != NULL) {
                        printf("Pai: %s\n", pessoaBuscada->pai->nome);
                    } else {
                        printf("Pai: Desconhecido\n");
                    }

                    if (pessoaBuscada->mae != NULL) {
                        printf("Mae: %s\n", pessoaBuscada->mae->nome);
                    } else {
                        printf("Mae: Desconhecida\n");
                    }
                    if(pessoaBuscada->conjuge != NULL){
                        printf("Esposa: %s\n", pessoaBuscada->conjuge->nome);
                    }else{
                        printf("Esposa: Desconhecida\n");
                    }
                    if(pessoaBuscada->filhos[0] != NULL){
                    for(int i = 0; i < pessoaBuscada->filhos[i] != NULL; i++){
                            printf("Filho(a): %s\n", pessoaBuscada->filhos[i]->nome);
                        }
                    }
                    if(pessoaBuscada->irmao[0] != NULL){
                        for(int i = 0; pessoaBuscada->irmao[i] != NULL; i++){
                        printf("Irmao: %s\n",pessoaBuscada->irmao[i]->nome);

                        if (pessoaBuscada->irmao[i]->conjuge != NULL) {
                            printf("Esposa do Irmao: %s\n", pessoaBuscada->irmao[i]->conjuge->nome);
                        } else {
                            printf("Esposa do Irmao: Desconhecida\n");
                            }
                    if(pessoaBuscada->irmao[i]->filhosIrmao[0] != NULL){
                        for(int j = 0; pessoaBuscada->irmao[i]->filhosIrmao[j] != NULL; j++){
                            printf("Filho do %s: %s\n",pessoaBuscada->irmao[i]->nome, pessoaBuscada->irmao[i]->filhosIrmao[j]->nome);
                        }
                    }
                }
            }
                    if(pessoaBuscada->filhosIrmao[0] != NULL){
                        for(int i = 0; i < pessoaBuscada->filhosIrmao[i] != NULL; i++){
                            printf("Filho(a): %s\n", pessoaBuscada->filhosIrmao[i]->nome);
                        }
                    }
                } else {
                    printf("Pessoa não encontrada na árvore.\n");
                }
        break;
            case 9:
                printf("Digite o nome da pessoa a ser removida: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerPessoa(arvore, nome);
                printf("Pessoa Removida com sucesso!\n");
                break;
            case 10:
                desfazerOperacao(arvore, pilhaOperacoes);
                break;
            case 11:
                refazerOperacao(arvore, pilhaOperacoes);
                break;
            case 12:
                liberarArvore(arvore);
                liberarPilhaOperacoes(pilhaOperacoes);
                printf("Programa encerrado.\n");
                break;
        default:
             printf("A opcao selecionada nao existe!\n");
        }
    } while (opcao != 12);
    return 0;
}
