/* Programa Agendanator A-1000
 * 
 * Este programa permite a criação de uma agenda eletrônica contendo os seguintes dados: nome do contato, e-mail e telefone. O programa permite a inserção de tais dados pelo usuario e coloca-os
 * em ordem alfabética de acordo com seus nomes, também permite a edição dos dados do contato (mantento a ordenação, caso o nome seja trocado) e a remoção de um contato da agenda; assim como lista
 * todos os contatos, ou busca por um contato específico e o mostra na tela.
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 21/05/2017
 * Editado em: 22/05, 23/05;
 * 
*/

/* ---Bibliotecas--- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---Variaveis globais---*/
#define MAX_N 51
#define MAX_E 31
#define MAX_F 21

/* ---Registros--- */
typedef struct end {
    char nome[MAX_N];
    char email[MAX_E];
    char fone[MAX_F];
    
    struct end* prox;
} Contato;

/* ---Funcoes--- */
int teste(int var, int isso, int aquilo, int tipo);         /*Testa a validade da entrada do usuario de acordo com os parametros passados para a funcao*/

void interface(void);
void imprimir(struct end *p, int tipo);
void buscar(struct end *p);

struct end *inserir(struct end *p);
struct end *ordenaEntrada(struct end *p, struct end *novo);
struct end *seekndestroy(struct end *p, char *p_nom, int tipo); /*Busca elementos na lista e os destroi. Ou nao, dependendo do parametro tipo passado para a funcao...*/
struct end *editar(struct end *p);
struct end *remover(struct end *p);

int main(void) {
    
    printf("\nBem vindo ao programa Agendanator A-1000!\nEste programa funciona como a sua agenda eletronica pessoal, permitindo que voce\nguarde o nome, e-mail e telefone de seus contatos ");
    printf("e os resgate com facilidade\nquando precisar. Caso prefira, tambem podera remover algum contato indesejado de\nsua agenda.\n");
    
    interface();
    
    printf("\nObrigado por usar o Agendanator A-1000!\n");
    
return(0); }

int teste(int var, int isso, int aquilo, int tipo) {   /*Testa a validade da entrada do usuario (var) de acordo com os parametros passados para a funcao ('isso' e 'aquilo'), permitindo correcao*/ 
                                                        /*e retorna o valor da variavel para a funcao*/
    if (tipo == 1) {    /* TIPO 1: teste para sim (1) ou nao (0). */
        while (var != isso && var != aquilo) {  /* Enquanto a entrada for diferente de nao (isso) e sim (aquilo), repete, permitindo correcao. */
            printf("Sua entrada %i eh invalida. Digite %i para sim ou %i para nao:\n", var, aquilo, isso);
            scanf("%i", &var); }
    }
    
    else if (tipo == 2) {   /* TIPO 2: Faz comparacoes de maior que 'isso', menor que 'aquilo'. */
        while (var < isso || var > aquilo) {    /* Enquanto a entrada nao possuir os valores aceitos repete, permitindo a correcao. */
            printf("Sua entrada %i eh invalida. Digite um valor entre %i e %i\n", var, isso, aquilo);
            scanf("%i", &var); }
    }
    
return(var); }  /* -----Fim da funcao teste----- */

void interface(void) {  /*Funcao interface: */
    int entrada = -1;
    struct end *p = NULL;
    
    while (entrada != 0) {
        printf("\nO que deseja fazer?\n1. Inserir um contato\t2. Listar todos os contatos\n3. Buscar um contato\t4. Editar um contato\n5. Remover um contato\n\n0. Sair\n");
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 5, 2);
        
        if (entrada == 1)
            p = inserir(p);
        else if (entrada == 2)
            imprimir(p, 1);
        else if (entrada == 3)
            buscar(p);
        else if (entrada == 4)
            p = editar(p);
        else if (entrada == 5)
            p = remover(p);
        else {
            printf("Deseja realmente sair? (1. Sim | 0. Nao)\n");
            scanf("%i", &entrada);
            
            teste(entrada, 0, 1, 1);
            
            if (entrada == 1)
                break;
            else
                entrada = -1;
        }
    }
} /* -----Fim da funcao interface----- */

struct end *inserir(struct end *p) {    /*Funcao inserir: */
    int entrada, destino, c;
    
    for (entrada = 0; entrada < 100; entrada++)
        printf("\n");
    
    printf("Deseja inserir um novo contato? (1. Sim | 0. Nao)\n");
    scanf("%i", &entrada);
    
    entrada = teste(entrada, 0, 1, 1);
    
    while (entrada != 0) {
        Contato *novo;
        novo = malloc(sizeof(Contato));
        novo->prox = NULL;
        destino = -1;
        
        while (entrada != 0) {
            int i;
            if (destino == -1 || destino == 1) {
                entrada = 0;
                
                while (entrada != 1) {
                    printf("Qual eh o nome do contato? (Max.: %i caracteres)\n", MAX_N-1);
                    c = getchar();
                    fgets(novo->nome, MAX_N, stdin);
                    
                    for (i = 0; (novo->nome[i] != '\n') && (novo->nome[i] != '\0'); i++)
                        ;
                    novo->nome[i] = '\0';
            
                    printf("\nO nome: '%s' esta correto?\n(1. Sim | 0. Nao)\n", novo->nome);
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 1, 1);
                }
                if (destino < 0)
                    destino--;
            }
            else if (destino == -2 || destino == 2) {
                entrada = 0;
                
                while (entrada != 1) {
                    printf("Qual eh o e-mail do contato? (Max.: %i caracteres)\n", MAX_E-1);
                    c = getchar();
                    fgets(novo->email, MAX_E, stdin);
                    
                    for (i = 0; (novo->email[i] != '\n') && (novo->email[i] != '\0'); i++ )
                            ;
                    novo->email[i] = '\0';
                    
                    printf("\nO e-mail: '%s' esta correto? (1. Sim | 0. Nao)\n", novo->email);
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 1, 1);
                }
                if (destino < 0)
                    destino--;
            }
            else if (destino == -3 || destino == 3) {
                entrada = 0;
                
                while (entrada != 1) {
                    printf("Qual eh o numero de telefone do contato? (Max.: %i caracteres)\n", MAX_F-1);
                    c = getchar();
                    fgets(novo->fone, MAX_E, stdin);
                    
                    for (i = 0; (novo->fone[i] != '\n') && (novo->fone[i] != '\0'); i++)
                            ;
                    novo->fone[i] = '\0';
            
                    printf("\nO numero: '%s' esta correto? (1. Sim | 0. Nao)\n", novo->fone);
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 1, 1);
                }
                if (destino < 0)
                    destino = 4;
            }
            if (destino > 0) {
                printf("\n-----------------------------Novo contato-----------------------------\n");
                printf("Nome:\t%s\nE-mail:\t%s\nTelefone: %s", novo->nome, novo->email, novo->fone);
                printf("\n----------------------------------------------------------------------\n");
                
                printf("\nOs dados do contato estao corretos? (1. Sim | 0. Nao)\n");
                scanf("%i", &entrada);
                
                entrada = teste(entrada, 0, 1, 1);
                
                if (entrada == 1)
                    break;
                
                else {
                    entrada = -1;
                    
                    printf("O que deseja corrigir? (1. Nome | 2. E-mail | 3. Telefone)\n");
                    scanf("%i", &destino);
                    
                    destino = teste(destino, 1, 3, 2); }
            }
        }
        p = ordenaEntrada(p, novo);
    
        printf("\nDeseja inserir outro contato? (1. Sim | 0. Nao)\n");
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);
    }
    
return(p); }

struct end *ordenaEntrada(struct end *p, struct end *novo) {    /*Funcao ordenaEntrada: coloca os elementos da lista em ordem alfabetica. Recebe p: 1o elemento; novo: elemento a ser ordenado*/
    
    if (p != NULL) {    /*Se existir um primeiro elemento da lista*/
        int i, flag = 0;            /*Declara a variavel de contagem i, e uma flag que sera condicao de saida dos lacos utilizados*/
        struct end *p_aux, *p_ant;  /*Declara dois ponteiros para elementos da lista: p_aux eh o elemento atual e p_ant eh o anterior ao p_aux*/
        
        if ( (p == novo) && (p->prox != NULL) )
            p = p->prox;
        
        p_aux = p;
        
        while (flag == 0) { /*Laco para a ordenacao*/
            if (novo->nome[0] > p_aux->nome[0]) {   /*Se o primeiro caractere do nome do novo for "maior" que o do elemento atual*/
                if (p_aux->prox != NULL) {  /*Se o elemento atual NAO eh o ultimo da lista, passa para o proximo elemento, registrando o elemento anterior*/
                    p_ant = p_aux;
                    p_aux = p_aux->prox;
                }
                else {                      /*Caso o elemento atual seja o ultimo da lista, posiciona o novo elemento no final da lista*/
                    novo->prox = NULL;
                    p_aux->prox = novo;
                    flag = 1;               /*Aciona a flag para registrar a condicao de saida*/
                }
            }
            else if (novo->nome[0] == p_aux->nome[0]) { /*Se o primeiro caractere de ambos nomes forem iguais*/
                for (i = 1; p_aux->nome[i] == novo->nome[i]; i++) /*Laco para comparar os caracteres de ambos nomes ate que sejam diferentes*/
                    ;
                
                if (novo->nome[i] > p_aux->nome[i]) {   /*Se o caractere diferente do novo for "maior" que o do elemento atual*/
                    if (p_aux->prox != NULL) {  /*Se o elemento atual NAO eh o ultimo da lista, passa para o proximo elemento, registrando o elemento anterior*/
                        p_ant = p_aux;
                        p_aux = p_aux->prox;
                    }
                    else {                      /*Caso o elemento atual seja o ultimo da lista, posiciona o novo elemento no final da lista*/
                        novo->prox = NULL;
                        p_aux->prox = novo;
                        flag = 1;               /*Aciona a flag para registrar a condicao de saida*/
                    }
                }
                else {                                  /*Se o caractere diferente do novo for "menor" que o do elemento atual*/
                    p_ant->prox = novo;                 /*Posiciona o novo elemento entre o anterior e o atual*/
                    novo->prox = p_aux;
                    flag = 1;                           /*Aciona a flag para registrar a condicao de saida*/
                }
            }
            else {                                      /*Se o primeiro caractere do nome do novo elemento for "menor" que o do atual*/
                if (p_aux != p) {   /*Se o elemento atual NAO eh o primeiro da lista*/
                    p_ant->prox = novo; /*Posiciona o novo elemento entre o anterior e o atual*/
                    novo->prox = p_aux;
                    flag = 1;           /*Aciona a flag para registrar a condicao de saida*/
                }
                else {              /*Caso o elemento atual seja o primeiro da lista*/
                    p = novo;           /*Define o novo elemento como o primeiro elemento da lista*/
                    novo->prox = p_aux; /*Registra o proximo elemento da lista na posicao adequada*/
                    flag = 1;           /*Aciona a flag para registrar a condicao de saida*/
                }
            }
        }   /*Fim do laco de ordenacao*/
    }
    else    /*Se nao existir um primeiro elemento da lista*/
        p = novo;   /*Registra o novo elemento como o primeiro*/
    
return(p);  /*Retorna a posicao do primeiro elemento da lista*/} /* -----Fim da funcao ordenaEntrada----- */

void imprimir(struct end *p, int tipo) {  /*Funcao imprimir: imprime (tipo == 1) todos os elementos da lista (p eh o 1o elemento da lista); ou o elemento p recebido. */
    if (p != NULL) {
        if (tipo == 1) {
            for(int i = 1; p != NULL; i++) {    /*Laco para impressao dos elementos*/
                printf("\n-------------------------Contato %2i-------------------------\n", i);
                printf("Nome:\t%s\nE-mail:\t%s\nTelefone: %s\n", p->nome, p->email, p->fone);
            
                p = p->prox;     /*Ajuste da posicao na lista*/
            }
            printf("------------------------------------------------------------\n");
            printf("Aperte 'Enter' para voltar ao menu anterior.\n");
            tipo = getchar();
        }
        else {
            printf("------------------------------------------------------------\n");
            printf("Nome: %s\nE-mail: %s\nTelefone: %s\n", p->nome, p->email, p->fone);
            printf("------------------------------------------------------------\n");
        }
    }
    else
        printf("Voce nao possui contatos na sua agenda.\n");
}   /* -----Fim da funcao imprimir----- */

void buscar(struct end *p) {
    int entrada;
    
    if (p != NULL) {
        int i;
        char c, procurado[MAX_N], *p_nom = &procurado[0];
        struct end *p_aux;
        
        printf("\nDeseja buscar um contato? (1. Sim | 0. Nao)\n");
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);
        
        while (entrada != 0) {
            entrada = 0;
            while (entrada != 1) {
                printf("Qual eh o nome do contato que voce busca? (Max.: %i caracteres)\n", MAX_N-1);
                c = getchar();
                fgets(procurado, MAX_N, stdin);
            
                for (i = 0; (procurado[i] != '\n') && (procurado[i] != '\0'); i++)
                    ;
                procurado[i] = '\0';
            
                printf("O nome '%s' esta correto? (1. Sim | 0. Nao)\n", procurado);
                scanf("%i", &entrada);
            
                entrada = teste(entrada, 0, 1, 1);
            }
            
            p_aux = seekndestroy(p, p_nom, 1);
            
            if (p_aux != NULL)
                imprimir(p_aux, 2);
            
            else
                printf("O contato buscado nao esta na agenda.\n");
            
            printf("Deseja buscar outro contato? (1. Sim | 0. Nao)\n");
            scanf("%i", &entrada);
            
            entrada = teste(entrada, 0, 1, 1);
        }
        
    }
    else
        printf("Voce nao possui contatos na sua agenda.\n");
    
    printf("Aperte 'Enter' para voltar ao menu principal.\n");
    entrada = getchar();
    entrada = getchar();
}   /* -----Fim da funcao buscar----- */

struct end *seekndestroy(struct end *p, char *p_nom, int tipo) {    /*Funcao seekndestroy: Busca um elemento e o destroi caso tipo == 2; caso tipo == 1, retorna sua posicao sem maiores danos*/
    struct end *p_aux = p, *p_ant = p_aux; /*Ponteiro auxiliares para guardar o elemento atual e o anterior a esse*/
    
    while (p_aux != NULL) { /*Laco para varrer toda a lista*/
        if (strcmp(p_aux->nome, p_nom) == 0) {  /*Se o elemento da lista atual for o elemento procurado*/
            
            if (tipo == 1)          /*Caso seja apenas busca, retorna seu endereco de memoria, indicando sucesso*/
                return(p_aux);
            
            else if (tipo == 2) {   /*Caso seja exigida sua remocao*/
                if (p_ant != p_aux) {   /*Testa se NAO eh o primeiro elemento da lista*/
                    p_ant->prox = p_aux->prox;  /*Registra o endereco do proximo elemento da lista no campo adequado do elemento anterior (com relacao ao atual (p_aux))*/
                    free(p_aux);                /*Libera a memoria alocada*/
                    return(p); }                /*Retorna o endereco do primeiro elemento da lista, indicando sucesso*/
                
                else {              /*Caso seja o primeiro elemento da lista*/
                    p = p_aux->prox;    /*Registra a nova posicao do primeiro elemento*/
                    free(p_aux);        /*Libera a memoria alocada*/
                    return(p); }        /*Retorna o novo endereco do primeiro elemento da lista, indicando sucesso*/
            }
        }
        else {              /*Caso nao seja o elemento procurado, passa para o proximo elemento da lista, registrando a posicao do anterior*/
            p_ant = p_aux;
            p_aux = p_aux->prox; }
    }
/*Caso nao encontre o elemento procurado, retorna NULL, indicando que o elemento nao existe na lista */
return(NULL); } /* -----Fim da funcao seekndestroy----- */

struct end *editar (struct end *p) {
    int entrada;
    
    if (p != NULL) {
        int i;
        char c, procurado[MAX_N], *p_nom = &procurado[0];
        struct end *p_aux;
        
        printf("\nDeseja editar um contato? (1. Sim | 0. Nao)\n");
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);
        
        while (entrada != 0) {
            printf("Qual o nome do contato que voce deseja editar? (Max.: %i caracteres)\n", MAX_N-1);
            c = getchar();
            fgets(procurado, MAX_N, stdin);
            
            for (i = 0; (procurado[i] != '\n') && (procurado[i] != '\0'); i++)
                ;
            procurado[i] = '\0';
            
            p_aux = seekndestroy(p, p_nom, 1);
            
            if (p_aux != NULL) {
                while (entrada != 0) {
                    imprimir(p_aux, 2);
                    
                    printf("O que voce deseja editar?\n1. Nome\t    2. E-mail\t  3. Telefone\t0. Nada\n");
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 3, 2);
                    
                    if (entrada == 1) {
                        printf("Qual o novo nome do contato? (Max.: %i caracteres)\n", MAX_N-1);
                        c = getchar();
                        fgets(p_aux->nome, MAX_N, stdin);
                        
                        for (i = 0; (p_aux->nome[i] != '\n') && (p_aux->nome[i] != '\0'); i++)
                            ;
                        p_aux->nome[i] = '\0';
                        
                        p = ordenaEntrada(p, p_aux);
                    }
                    else if (entrada == 2) {
                        printf("Qual o novo e-mail do contato? (Max.: %i caracteres)\n", MAX_E-1);
                        c = getchar();
                        fgets(p_aux->email, MAX_E, stdin);
                        
                        for (i = 0; (p_aux->email[i] != '\n') && (p_aux->email[i] != '\0'); i++)
                            ;
                        p_aux->email[i] = '\0';
                    }
                    else if (entrada == 3) {
                        printf("Qual o novo telefone do contato? (Max.: %i caracteres)\n", MAX_F-1);
                        c = getchar();
                        fgets(p_aux->fone, MAX_F, stdin);
                        
                        for (i = 0; (p_aux->fone[i] != '\n') && (p_aux->fone[i] != '\0'); i++)
                            ;
                        p_aux->fone[i] = '\0';
                    }
                }
            }
            else 
                printf("O contato procurado nao esta na agenda.\n");
            
            printf("Deseja editar outro contato? (1. Sim | 0. Nao)\n");
            scanf("%i", &entrada);
            
            entrada = teste(entrada, 0, 1, 1);
        }
    }
    else
        printf("Voce nao possui contatos na sua agenda.\n");
    
    printf("Aperte 'Enter' para voltar ao menu principal.\n");
    entrada = getchar();
    entrada = getchar();
return(p); }   /* -----Fim da funcao editar----- */

struct end *remover(struct end *p) {
    int entrada;
    
    if (p != NULL) {
        int i;
        char c, procurado[MAX_N], *p_nom = &procurado[0];
        struct end *p_aux;
        
        printf("Deseja remover um contato? (1. Sim | 0. Nao)\n");
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);
        
        while (entrada != 0) {
            entrada = 0;
            
            while (entrada != 1) {
                printf("Qual o nome do contato que voce deseja remover? (Max.: %i caracteres)\n", MAX_N-1);
                c = getchar();
                fgets(procurado, MAX_N, stdin);
                
                for (i = 0; (procurado[i] != '\n') && (procurado[i] != '\0'); i++)
                    ;
                procurado[i] = '\0';
            
                printf("O nome '%s' esta correto? (1. Sim | 0. Nao)\n", procurado);
                scanf("%i", &entrada);
                
                entrada = teste(entrada, 0, 1, 1);
            }
            p_aux = seekndestroy(p, p_nom, 1);
            
            if (p_aux != NULL) {
                imprimir(p_aux, 2);
                
                printf("Deseja REALMENTE excluir o contato em questao? Esse processo nao pode ser\nrevertido. (1. Sim | 0. Nao)\n");
                scanf("%i", &entrada);
            
                entrada = teste(entrada, 0, 1, 1);
                
                if (entrada == 1) {
                    p = seekndestroy(p, p_nom, 2);
                    printf("\nO contato '%s' foi removido da agenda.\n", procurado);
                }
            }
            else
                printf("O contato buscado nao esta na agenda.\n");
            
            if (p == NULL) {
                printf("Voce nao possui mais contatos em sua agenda.\n");
                break;
            }
            else {
                printf("Deseja remover outro contato? (1. Sim | 0. Nao)\n");
                scanf("%i", &entrada);
            
                entrada = teste(entrada, 0, 1, 1);
            }
        }
    }
    else
        printf("Voce nao possui contatos na sua agenda.\n");
    
    printf("Aperte 'Enter' para voltar ao menu principal.\n");
    entrada = getchar();
    entrada = getchar();
    
return(p); }    /* -----Fim da funcao remover----- */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
