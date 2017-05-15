/* Programa Listanator L-1000
 * Este programa de cria uma lista encadeada de inteiros e possui as funções inserir, buscar, remover e imprimir todos os elementos.
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 10/05/2017
 * Editado em: 11/05; 12/05; 15/05;
*/

/*-----Bibliotecas-----*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*-----Estruturas-----*/
typedef struct end {    /*Estrutura da lista e do endereco para a lista*/
    int num;
    struct end* prox;
} Lista;

/*-----Variaveis globais-----*/
#define MAX 10

/*-----Funcoes-----*/
void listanator(void);                                      /*Roda o programa em si*/
int teste(int var, int isso, int aquilo, int tipo);         /*Testa a validade da entrada do usuario de acordo com os parametros passados para a funcao*/
struct end *seekndestroy(struct end *p, struct end **pon, int procurado, int tipo); /*Busca elementos na lista e os destroi. Ou nao, dependendo do parametro tipo passado para a funcao...*/
void inter_ins(struct end *p, struct end **pon);            /*Interface para a funcao inserir novos elementos na lista*/
void inserir(struct end *p, struct end **pon, int pos, int valor, int tipo);        /*Insere elementos na lista*/
void remover(struct end *p, struct end **pon);              /*Remove elementos indesejados*/
void busca(struct end *p, struct end **pon);                /*Interface para a funcao de busca*/
void imprimir(struct end *p);                               /*Imprime os elementos da lista*/

int main(void) {    /*-----Funcao principal-----*/
    
    printf("Bem vindo ao programa Listanator L-1000!\nEste programa cria uma lista de numeros inteiros especialmente para voce, assim\ncomo permite a insercao "); /*Mensagem de boas vindas*/
    printf("de novos numeros inteiros por voce, a remocao de alguns\nnumeros indesejados, a busca de um dos numeros e a impressao de todos eles.\n\n");
    
    listanator();   /*Chama a funcao listanator*/
    
    printf("\nObrigado por usar o programa!\n\n");  /*Mensagem de saida*/
    
return(0); }        /*-----Fim da funcao principal-----*/

void listanator(void) { /*Funcao listanator: Serve de interface para todo o programa*/
    int i, destino = -1, flag = 0;      /*Cria a variavel de contagem i; a variavel destino, que recebe a entrada do usuario e uma flag*/
    struct end *p, *p_aux, **pon = &p;  /*Cria os ponteiros p (primeiro elemento da lista), p_aux (ponteiro auxiliar), pon (ponteiro de ponteiro para modificar o ponteiro p)*/
    
    while(destino != 0) {   /*Laco para rodar o programa*/
        printf("O que voce deseja fazer?\n    1. Inserir um numero inteiro\n    2. Remover um numero\n    3. Buscar um numero\n    4. Imprimir todos os numeros\n    0. Sair\n");
        scanf("%i", &destino);  /*Recebe a entrada do usuario com relacao ao que ele quer fazer*/
        
        destino = teste(destino, 0, 4, 2);  /* Testa a validade da entrada do usuario */
        
        if (destino != 0) {     /*Caso seja a primeira vez que o programa esta rodando*/
            if (flag == 0) {    /*E o usuario quer, efetivamente, rodar o programa*/
                flag = 1;       /*Define a flag como 1 para criar a lista apenas uma vez*/
                srand(time(NULL));  /*Gera uma seed para randomizar mais a funcao rand()*/
                
                for (i = 0; i < MAX; i++) { /*Laco para alocar o espaco para a lista*/
                    Lista *novo;
                    novo = malloc(sizeof(Lista));
                    
                    if (i > 0) {    /*Se nao for o primeiro elemento da lista*/
                        p_aux->prox = novo; /*Define a posicao do proximo elemento do elemento anterior da lista como o elemento recem criado*/
                        p_aux = novo;       /*Define o vetor auxiliar como o elemento recem criado*/
                        novo->num = rand()%32676;   /*Atribui um numero aleatorio ao membro da lista*/
                    }
                    else {          /*Caso seja o primeiro elemento da lista*/
                        p = novo;   /*Define o ponteiro p como o elemento recem criado e o primeiro elemento da lista*/
                        p_aux = p;  /*Define o ponteiro auxiliar como primeiro elemento da lista*/
                        novo->num = rand()%32767;   /*Atribui um numero aleatorio ao membro da lista*/
                    }
                }
                p_aux->prox = NULL; /*Define o atibuto prox do ultimo elemento da lista como NULL*/
            }
            
            if (destino == 1)       /*Chama a funcao inter_ins*/
                inter_ins(p, pon);
            
            else if (destino == 2)  /*Chama a funcao remover*/
                remover(p, pon);
            
            else if (destino == 3)  /*Chama a funcao busca*/
                busca(p, pon);
            
            else if (destino == 4)  /*Chama a funcao imprimir*/
                imprimir(p);
        }
    }
    while (p_aux != NULL) { /*Laco para liberar a memoria alocada*/
        p_aux = p->prox;    /*p_aux recebe o endereco do proximo elemento da lista*/
        free(p);            /*Libera a memoria alocada*/
        p = p_aux;          /*Redefine p para a proxima iteracao*/
    }
    free(p);    /*Libera a memoria alocada do ultimo delemento da lista*/
        
}   /* -----Fim da funcao listanator----- */

int teste(int var, int isso, int aquilo, int tipo) {   /*Testa a validade da entrada do usuario (var) de acordo com os parametros passados para a funcao ('isso' e 'aquilo'), permitindo correcao*/ 
                                                        /*e retorna o valor da variavel para a funcao*/
    if (tipo == 1) {    /* TIPO 1: teste para sim (1) ou nao (0). */
        while (var != isso && var != aquilo) {  /* Enquanto a entrada for diferente de 0 e 1, repete, permitindo correcao. */
            printf("Sua entrada %i eh invalida. Digite 1 para sim ou 0 para nao:\n", var);
            scanf("%i", &var); }
    }
    
    else if (tipo == 2) {   /* TIPO 2: Faz comparacoes de maior que 'isso', menor que 'aquilo'. */
        while (var < isso || var > aquilo) {    /* Enquanto a entrada nao possuir os valores aceitos repete, permitindo a correcao. */
            printf("Sua entrada %i eh invalida. Digite um valor entre %i e %i\n", var, isso, aquilo);
            scanf("%i", &var); }
    }
    
return(var); }  /* -----Fim da funcao teste----- */

struct end *seekndestroy(struct end *p, struct end **pon, int procurado, int tipo) {    /*Funcao seekndestroy: Busca um elemento e o destroi caso tipo == 2; caso tipo == 1, retorna sua posicao*/
                                                                                        /*sem maiores danos*/
    struct end *p_aux = p, *p_ant = p_aux; /*Ponteiro auxiliares para guardar o elemento atual e o anterior a esse*/
    
    while (p_aux != NULL) { /*Laco para varrer toda a lista*/
        if (p_aux->num == procurado) {  /*Se o elemento da lista atual for o elemento procurado*/
            if (tipo == 1)  /*Caso seja apenas busca, retorna seu endereco de memoria, indicando sucesso*/
                return(p_aux);
            
            else {          /*Caso seja exigida sua remocao*/
                if (p_ant != p_aux) {   /*Testa se NAO eh o primeiro elemento da lista*/
                    p_ant->prox = p_aux->prox;  /*Registra o endereco do proximo elemento da lista no campo adequado do elemento anterior (com relacao ao atual (p_aux))*/
                    free(p_aux);                /*Libera a memoria alocada*/
                    return(p_ant); }            /*Retorna 0, indicando sucesso*/
                
                else {              /*Caso seja o primeiro elemento da lista*/
                    *pon = p_aux->prox;     /*Registra a nova posicao do primeiro elemento*/
                    free(p_aux);            /*Libera a memoria alocada*/
                    return(p_ant); }        /*Retorna 0, indicando sucesso*/
            }
        }
        else {              /*Caso nao seja o elemento procurado, passa para o proximo elemento da lista, registrando a posicao do anterior*/
            p_ant = p_aux;
            p_aux = p_aux->prox; }
    }
/*Caso nao encontre o elemento procurado, retorna NULL, indicando que o elemento nao existe na lista */
return(NULL); } /* -----Fim da funcao seekndestroy----- */

void inter_ins(struct end *p, struct end **pon) {  /*Funcao inter_ins: serve de interface para a funcao inserir e permite sobrescrever um elemento*/
    
    int valor, entrada = -1;    /*valor: recebe o valor a ser inserido; entrada: recebe diversas entradas do usuario */
    struct end *p_aux;          /*Ponteiro auxiliar para receber a posicao de um elemento procurado*/
    
    printf("Sua lista atual:\n");   /*Imprime a lista no seu estado atual*/
    imprimir(p);
    
    while (entrada != 0) {  /*Laco para inserir os elementos*/
        printf("Deseja inserir ou sobrescrever um elementos?\n1. Inserir\t2. Sobrescrever\t\t0. Cancelar\n"); /*Pergunta se o usuario quer inserir ou sobrescrever um elemento*/
        scanf("%i", &entrada);
            
        entrada = teste(entrada, 0, 2, 2);  /* Testa a validade da entrada do usuario */
            
        if (entrada == 2) {         /*O usuario deseja sobrescrever um elemento*/
            printf("Qual elemento voce deseja sobrescrever? "); /*Pergunta qual elemento deve ser sobrescrito*/
            scanf("%i", &valor);
            
            p_aux = seekndestroy(p, pon, valor, 1); /*Chama a funcao de busca para achar o elemento a ser sobrescrito*/
            
            if (p_aux != NULL) {    /*Caso ele exista*/
                printf("Com qual valor voce deseja sobrescrever? (Max.: 32.767 | Min. -32.768)\n"); /*Pergunta qual o valor que sobrescrevera o elemento*/
                scanf("%i", &valor);
                
                valor = teste(valor, -32768, 32767, 2); /* Testa a validade da entrada do usuario */
                
                p_aux->num = valor; /*Sobrescreve o elemento*/
            }
            else    /*Caso o elemento nao exista, informa o usuario sobre a nao existencia*/
                printf("O elemento procurado (%5i) nao esta na lista.\n", valor);
        }
        else if (entrada == 1) {    /*O usuario deseja inserir um elemento */
            printf("Onde voce deseja posicionar o novo elemento?\n1. Inicio\t2. Apos um dos elementos\n3. Fim\t\t0. Cancelar\n");   /*Pergunta onde o usuario deseja posicionar o novo elemento*/
            scanf("%i", &entrada);
            
            entrada = teste(entrada, 0, 3, 2);  /* Testa a validade da entrada do usuario */
                
            if (entrada > 0) {  /*O usuario nao cancelou a insercao*/
                printf("Qual valor voce deseja inserir? (Max.: 32.767 | Min. -32.768)\n");  /*Pergunta qual o valor a ser inserido*/
                scanf("%i", &valor);
            
                valor = teste(valor, -32768, 32767, 2); /* Testa a validade da entrada do usuario */
                    
                if (entrada == 2) { /*Caso o usuario deseje inserir um elemento apos um outro elemento*/
                    printf("Apos qual elemento voce deseja inserir o novo?\n"); /*Pergunta apos qual elemento o usuario deseja inserir o novo*/
                    scanf("%i", &entrada);
                    
                    inserir(p, pon, entrada, valor, 1); /*Chama a funcao inserir, com tipo = 1 para inserir apos um dos elementos*/
                }
                else if (entrada == 1) {    /*Caso o usuario deseje inserir um elemento no inicio da lista*/
                    inserir(p, pon, 0, valor, 2);       /*Chama a funcao inserir, com tipo = 2 para inserir no inicio da lista*/
                    p = *pon;                           /*Atualiza a posicao do primeiro elemento da lista*/
                }
                
                else    /*Caso o usuario deseje inserir um elemento no final da lista*/
                    inserir(p, pon, 0, valor, 3);           /*Chama a funcao inserir, com tipo = 3 para inserir no fim da lista*/
            }
        }
        else    /*Sai do laco, caso o usuario tenha cancelado a insercao de um novo elemento*/
            break;
        
        printf("Deseja inserir outro numero a sua lista? (1. Sim | 0. Nao)\n"); /*Pergunta se o usuario deseja inserir um outro elemento a lista*/
        scanf("%i", &entrada);
            
        entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
        
        if (entrada == 1) { /*Caso o usuario deseje inserir um novo elemento a lista, imprime a lista na sua configuracao atual e da continuidade ao laco*/
            printf("\nSua lista atual:\n");
            imprimir(p); }
    }
}   /* -----Fim da funcao inter_ins----- */

void inserir(struct end *p, struct end **pon, int pos, int valor, int tipo) {   /*Funcao inserir: insere um elemento na lista, podendo inserir: 1. no meio; 2. no inicio; 3. no fim.*/
    struct end *p_aux;  /*Ponteiro auxiliar para lidar com insercoes entre dois elementos */
    
    if (tipo == 1) {        /*Tipo 1: Insercao apos um elemento especifico*/
        p_aux = seekndestroy(p, pon, pos, 1);   /*Chama a funcao de busca para procurar o elemento em questao*/
        
        if (p_aux != NULL) {    /*Caso ele exista, cria um novo elemento para a lista, aloca o espaco e faz as designacoes necessarias*/
            Lista *novo;
            novo = malloc(sizeof(Lista));
            
            novo->prox = p_aux->prox;   /*O novo elemento aponta para o proximo do elemento anterior ao novo elemento*/
            p_aux->prox = novo;         /*O elemento anterior aponta para o novo elemento inserido*/
            novo->num = valor;          /*Designa o valor a ser guardado na lista*/
        }
        else
            printf("O elemento procurado (%5i) nao esta na lista.\n", pos); /*Informa ao usuario que o elemento que ele procura nao existe*/
    }
    else if (tipo == 2) {   /*Tipo 2: insercao no inicio da lista*/
        Lista *novo;                    /*Cria um vetor para o novo elemento e aloca o espaco na memoria para ele*/
        novo = malloc(sizeof(Lista));
        
        novo->prox = p;     /*O novo elemento aponta para o que era o primeiro da lista*/
        *pon = novo;        /*Designa o novo elemento como o primeiro da lista*/
        novo->num = valor;  /*Guarda o valor na lista*/
    }
    else {                  /*Tipo 3: insercao no fim da lista*/
        while (p->prox != NULL) /*Laco para procurar o ultimo elemento da lista*/
            p = p->prox;
        
        Lista *novo;                    /*Cria um vetor para o novo elemento e aloca o espaco na memoria para ele*/
        novo = malloc(sizeof(Lista));
        
        p->prox = novo;     /*O antigo ultimo elemento da lista agora aponta para o novo elemento*/
        novo->prox = NULL;  /*O novo elemento nao aponta para nada, o que o caracteriza como o ultimo elemento da lista*/
        novo->num = valor;  /*Guarda o valor na lista*/
    }
}   /* -----Fim da funcao inserir----- */

void remover(struct end *p, struct end **pon) { /*Funcao remover: serve de interface para passar os dados para a funcao de busca e destruicao*/
    int metallica, lars = -1;   /*Variavel para receber o valor a ser removido e variavel auxiliar*/
    struct end *p_aux;          /*Ponteiro auxiliar para receber o retorno da funcao de busca de destruicao*/
    
    printf("Deseja remover um elemento? (1. Sim | 0. Nao)\n");
    scanf("%i", &lars);
    
    lars = teste(lars, 0, 1, 1);    /* Testa a validade da entrada do usuario */
    
    while (lars != 0) {
        printf("Deseja remover qual elemento? ");   /*Pergunta qual o elemento a ser destruido*/
        scanf("%i", &metallica);
    
        p_aux = seekndestroy(p, pon, metallica, 2); /*Chama a funcao seekndestroy com tipo dois para destruicao*/
    
        if (p_aux == NULL)  /*Caso o elemento procurado nao esteja na lista, informa o usuario*/
            printf("O elemento procurado (%i) nao existe.\n", metallica);
        
        printf("Deseja eliminar outro elemento? (1. Sim | 0. Nao)\n");  /*Pergunta se o usuario deseja remover outro elemento da lista*/
        scanf("%i", &lars);
        
        lars = teste(lars, 0, 1, 1);    /* Testa a validade da entrada do usuario */
    }
}

void busca(struct end *p, struct end **pon) {   /*Funcao busca: serve de interface para a funcao seekndestroy*/
    int aux = -1, i;    /*Variavel auxiliar multiuso e variavel de contagem*/
    struct end *p_aux;  /*Ponteiro auxiliar que recebe a posicao do elemento buscado*/
    
    while (aux != 0) {  /*Laco para fazer uma ou varias buscas*/
        printf("Qual o valor que voce busca? ");    /*Pergunta qual o valor procurado pelo usuario*/
        scanf("%i", &aux);
    
        p_aux = seekndestroy(p, pon, aux, 1);       /*Chama a funcao de busca com parametro 1 para ela buscar sem destruir nada*/
    
        if (p_aux != NULL) {    /*Caso o numero esteja na lista*/
                for(i = 1; p != p_aux; i++) /*Conta em qual posicao ele esta*/
                    p = p->prox;
                
                p = *pon;   /*Redefine o ponteiro p como o primeiro elemento da lista*/
                printf("O valor %i eh o %io elemento da lista.\n", aux, i); /*Informa em qual posicao o valor procurado esta*/
        }
        else    /*Informa ao usuario que o valor que ele busca nao esta na lista*/
            printf("O elemento procurado (%i) nao esta na lista.\n", aux);
        
        printf("Deseja procurar outro valor? (1. Sim | 0. Nao)\n"); /*Pergunta se o usuario deseja procurar por outro valor*/
        scanf("%i", &aux);
        
        aux = teste(aux, 0, 1, 1);  /* Testa a validade da entrada do usuario */
    }
}
        
void imprimir(struct end *p) {  /*Funcao imprimir: imprime os elementos da lista. Recebe o ponteiro para o 1o elemento.*/
    for(int i = 1; p != NULL; i++) {    /*Laco para impressao dos elementos*/
        printf("%2io elemento: %5i\t", i, p->num);
        p = p->prox;     /*Ajuste da posicao na lista*/
        if ( (i % 3) == 0)
            printf("\n");       /*Insere uma quebra de linha a cada tres elementos*/
        
        else if (p == NULL) {   /*Insere uma quebra de linha ao fim da lista*/
            printf("\n");
            break; }            /*Poupa uma comparacao que seria feita pelo laco*/
    }
    printf("\n");   /*Insere uma quebra de linha final*/
}   /* -----Fim da funcao imprimir----- */
