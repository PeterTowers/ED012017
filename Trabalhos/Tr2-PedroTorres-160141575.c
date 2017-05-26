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
#define MAX_N 51    /*Tamanho da string que armazena o nome dos contatos*/
#define MAX_E 31    /*Tamanho da string que armazena o e-mail dos contatos*/
#define MAX_F 21    /*Tamanho da string que armazena o telefone dos contatos*/

/* ---Registros--- */
typedef struct end {    /*Registro da lista para armazenar os contatos*/
    char nome[MAX_N];   /*String para armazenar o nome dos contatos*/
    char email[MAX_E];  /*String para armazenar o e-mail dos contatos*/
    char fone[MAX_F];   /*String para armazenar o telefone dos contatos*/
    
    struct end* prox;   /*Ponteiro que aponta para o proximo elemento da lista*/
} Contato;              /*Fim do tipo de variavel 'Contato'*/

/* ---Funcoes--- */
int teste(int var, int isso, int aquilo, int tipo);         /*Testa a validade da entrada do usuario de acordo com os parametros passados para a funcao*/

void interface(void);                       /*Recebe uma entrada do usuario e o direciona para as demais funcoes*/
void imprimir(struct end *p, int tipo);     /*Imprime todos os contatos ou um contato especifico, de acordo com o parametro 'tipo'*/
void buscar(struct end *p);                 /*Imprime na tela um contato especifico*/

struct end *inserir(struct end *p);                                         /*Insere novos contatos na agenda*/
struct end *ordenaEntrada(struct end *p, struct end *novo, int tipo);       /*Coloca os elementos da lista em ordem alfabetica*/
struct end *seekndestroy(struct end *p, char *p_nom, int tipo);             /*Busca elementos na lista e os destroi. Ou nao, dependendo do parametro tipo passado para a funcao...*/
struct end *editar(struct end *p);                                          /*Permite a edicao de um contato*/
struct end *remover(struct end *p);                                         /*Remove um contato da lista*/

/* ---Funcao principal--- */
int main(void) {
    
    printf("\nBem vindo ao programa Agendanator A-1000!\nEste programa funciona como a sua agenda eletronica pessoal, permitindo que voce\nguarde o nome, e-mail e telefone de seus contatos ");
    printf("e os resgate com facilidade\nquando precisar. Caso prefira, tambem podera remover algum contato indesejado de\nsua agenda.\n"); /*Mensagem de boas vindas*/
    
    interface();    /*Chama a funcao interface*/
    
    printf("\nObrigado por usar o Agendanator A-1000!\n"); /*Mensagem de saida*/
    
return(0); }    /* -----Fim da funcao principal----- */

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
    
return(var);    /*Retorna um valor aceitavel para a variavel*/ }    /* -----Fim da funcao teste----- */

void interface(void) {  /*Funcao interface: recebe a entrada do usuario e o direciona para as demais funcoes*/
    int entrada = -1;       /*Variavel para receber a entrada do usuario*/
    struct end *p = NULL;   /*Ponteiro para armazenar o endereco do primeiro elemento da lista*/
    
    while (entrada != 0) {  /*Laco de repeticao da funcao*/
        printf("\nO que deseja fazer?\n1. Inserir um contato\t2. Listar todos os contatos\n3. Buscar um contato\t4. Editar um contato\n5. Remover um contato\n\n0. Sair\n");
        scanf("%i", &entrada);  /*Pergunta ao usuario o que ele deseja fazer*/
        
        entrada = teste(entrada, 0, 5, 2);  /* Testa a validade da entrada do usuario */
        
        if (entrada == 1)       /*O usuario deseja inserir um novo contato a agenda*/
            p = inserir(p);         /*Chamada da funcao inserir, registrando a posicao do primeiro elemento da lista*/
        
        else if (entrada == 2)  /*O usuario deseja listar todos os contatos*/
            imprimir(p, 1);         /*Chamada da funcao imprimir*/
        
        else if (entrada == 3)  /*O usuario deseja listar um contato especifico*/
            buscar(p);              /*Chamada da funcao buscar*/
        
        else if (entrada == 4)  /*O usuario deseja editar um contato*/
            p = editar(p);          /*Chamada da funcao editar, registrando a posicao do primeiro elemento da lista*/
        
        else if (entrada == 5)  /*O usuario deseja remover um contato*/
            p = remover(p);         /*Chamada da funcao remover, registrando a posicao do primeiro elemento da lista*/
        
        else {                  /*O usuario deseja sair do programa*/
            printf("Deseja realmente sair? (1. Sim | 0. Nao)\n");   /*Confirma se o usuario quer mesmo sair do programa*/
            scanf("%i", &entrada);
            
            teste(entrada, 0, 1, 1);    /* Testa a validade da entrada do usuario */
            
            if (entrada == 1)   /*Se desejar sair, quebra o laco*/
                break;
            else                /*Caso contrario, define 'entrada' como -1 para se manter no laco*/
                entrada = -1;
        }

        if (entrada != 2)
            for (entrada = 0; entrada < 80; entrada++) /*Laco para inserir uma serie de quebras de linha e "limpar" a tela*/
                putchar('\n');
    }                       /*Fim do laco de repeticao*/
}   /* -----Fim da funcao interface----- */

struct end *inserir(struct end *p) {    /*Funcao inserir: insere novos contatos na agenda e retorna a posicao do primeiro elemento da lista*/
    int entrada, destino;    /*Declara as variaveis entrada (recebe a entrada do usuario), destino (roda o laco para inserir os dados do contato)*/
    
    for (entrada = 0; entrada < 80; entrada++) /*Laco para inserir uma serie de quebras de linha e "limpar" a tela*/
        putchar('\n');
    
    printf("Deseja inserir um novo contato? (1. Sim | 0. Nao)\n");  /*Confirma a opcao do usuario*/
    scanf("%i", &entrada);
    
    entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
    
    while (entrada != 0) {  /*Laco para a insercao de novos contatos*/
        Contato *novo;                  /*Cria um ponteiro para o novo contato*/
        novo = malloc(sizeof(Contato)); /*Aloca a memoria para o novo contato criado*/
        novo->prox = NULL;              /*Define o endereco do proximo elemento da lista como NULL, por padrao*/
        destino = -1;                   /*Atribui o valor -1 a variavel para efeitos do proximo laco*/
        
        while (entrada != 0) {  /*Laco para a atribuicao de dados do registro*/
            int i;  /*Variavel de contagem*/
            
            if (destino == -1 || destino == 1) {    /*O valor -1 faz com que o laco passe, pelo menos, uma vez nessa condicional, permitindo ao usuario inserir o nome do contato ou voltar aqui...*/
                entrada = 0;                        /*... para corrigi-lo. O valor de entrada e redefinido para 0 para permitir a entrada no laco a seguir*/
                
                while (entrada != 1) {  /*Laco que recebe o nome do novo contato e permite correcao*/
                    printf("Qual eh o nome do contato? (Max.: %i caracteres)\n", MAX_N-1);
                    novo->nome[0] = getchar();          /*Recebe o caractere de quebra de linha que fica na heap*/
                    fgets(novo->nome, MAX_N, stdin);    /*Recebe o nome do novo contato, sobrescrevendo o caractere quebra de linha que foi recebido na linha anterior*/
                    
                    for (i = 0; (novo->nome[i] != '\n') && (novo->nome[i] != '\0'); i++)    /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na string.*/
                        ;                                                                   /*A condicao envolvendo '\0' eh por seguranca*/
                    novo->nome[i] = '\0';   /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
            
                    printf("\nO nome: '%s' esta correto?\n(1. Sim | 0. Nao)\n", novo->nome);    /*Confirma a entrada do usuario, permitindo correcao*/
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
                }
                if (destino < 0)    /*Ajusta a variavel destino, caso ela seja < 0, para a proxima iteracao do laco de repeticao*/
                    destino--;
            }
            else if (destino == -2 || destino == 2) {   /*Gracas ao ajuste anterior, o valor -2 faz com que o laco passe, pelo menos, uma vez nessa condicional, permitindo ao usuario inserir o...*/
                entrada = 0;                            /*...e-mail do contato ou voltar aqui para corrigi-lo. O valor de entrada e redefinido para 0 para permitir a entrada no laco a seguir*/
                
                while (entrada != 1) {  /*Laco que recebe o e-mail do novo contato e permite correcao*/
                    printf("Qual eh o e-mail do contato? (Max.: %i caracteres)\n", MAX_E-1);
                    novo->email[0] = getchar();         /*Recebe o caractere de quebra de linha que fica na heap*/
                    fgets(novo->email, MAX_E, stdin);   /*Recebe o e-mail do novo contato, sobrescrevendo o caractere quebra de linha que foi recebido na linha anterior*/
                    
                    for (i = 0; (novo->email[i] != '\n') && (novo->email[i] != '\0'); i++ ) /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na string.*/
                        ;                                                                   /*A condicao envolvendo '\0' eh por seguranca*/
                    novo->email[i] = '\0';  /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
                    
                    printf("\nO e-mail: '%s' esta correto? (1. Sim | 0. Nao)\n", novo->email);  /*Confirma a entrada do usuario, permitindo correcao*/
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
                }
                if (destino < 0)    /*Ajusta a variavel destino, caso ela seja < 0, para a proxima iteracao do laco de repeticao*/
                    destino--;
            }
            else if (destino == -3 || destino == 3) {   /*Novamente, o ajuste faz com que o laco passe, pelo menos, uma vez nessa condicional, permitindo ao usuario inserir o telefone do contato*/
                entrada = 0;                            /*...ou voltar aqui para corrigi-lo. O valor de entrada e redefinido para 0 para permitir a entrada no laco a seguir*/
                
                while (entrada != 1) {  /*Laco que recebe o telefone do novo contato e permite correcao*/
                    printf("Qual eh o numero de telefone do contato? (Max.: %i caracteres)\n", MAX_F-1);
                    novo->fone[0] = getchar();          /*Recebe o caractere de quebra de linha que fica na heap*/
                    fgets(novo->fone, MAX_E, stdin);    /*Recebe o e-mail do novo contato, sobrescrevendo o caractere quebra de linha que foi recebido na linha anterior*/
                    
                    for (i = 0; (novo->fone[i] != '\n') && (novo->fone[i] != '\0'); i++)    /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na string.*/
                        ;                                                                   /*A condicao envolvendo '\0' eh por seguranca*/
                    novo->fone[i] = '\0';   /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
            
                    printf("\nO numero: '%s' esta correto? (1. Sim | 0. Nao)\n", novo->fone);   /*Confirma a entrada do usuario, permitindo correcao*/
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
                }
                if (destino < 0)    /*Ajusta a variavel destino, caso ela seja < 0, para a proxima iteracao do laco de repeticao, que agora caira em apenas um dos campos, caso necessario, a...*/
                    destino = 4;    /*...pedido do usuario*/
            }
            if (destino > 0) {  /*Imprime os dados do novo contato na tela, apenas depois de ja ter recebido todos eles*/
                printf("\n-----------------------------Novo contato-----------------------------\n");
                printf("Nome:\t%s\nE-mail:\t%s\nTelefone: %s", novo->nome, novo->email, novo->fone);
                printf("\n----------------------------------------------------------------------\n");
                
                printf("\nOs dados do contato estao corretos? (1. Sim | 0. Nao)\n");    /*Confirma a corretude dos dados*/
                scanf("%i", &entrada);
                
                entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
                
                if (entrada == 1)   /*Caso os dados estejam corretos, sai do laco*/
                    break;
                
                else {              /*Caso contrario, pergunta o que deseja corrigir e manda para a condicional correspondente*/
                    entrada = -1;   /*Atribuicao para manter-se no laco*/
                    
                    printf("O que deseja corrigir? (1. Nome | 2. E-mail | 3. Telefone)\n");
                    scanf("%i", &destino);
                    
                    destino = teste(destino, 1, 3, 2);  /* Testa a validade da entrada do usuario */
                }
            }
        }   /*Fim do laco para a atribuicao de dados do registro*/
        p = ordenaEntrada(p, novo, 1); /*Chama a funcao ordenaEntrada para colocar a lista em ordem alfabetica, atualizando o vetor do primeiro elemento*/
    
        printf("\nDeseja inserir outro contato? (1. Sim | 0. Nao)\n");  /*Pergunta se o usuario deseja inserir outro contato*/
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
    }   /*Fim do laco para a insercao de novos contatos*/
    
return(p);  /*Retorna o vetor para o primeiro elemento*/ }  /* -----Fim da funcao inserir-----*/

struct end *ordenaEntrada(struct end *p, struct end *novo, int tipo) {  /*Funcao ordenaEntrada: coloca os elementos da lista em ordem alfabetica. Recebe p: 1o elemento; novo: elemento a ser...*/
                                                                        /*...ordenado. Caso tipo == 2, o elemento ja existe na lista e precisa, ou nao, ser realocado.*/
    int flag = 0;   /*Declara uma flag que sera condicao de saida dos lacos utilizados*/
    
    if (p == novo) {    /*Se o elemento a ser ordenado (novo) eh o primeiro elemento da lista, define o elemento seguinte ao 'novo' como o primeiro da lista*/
        p = p->prox;
        flag = 1;       /*Atribui o valor 1 a flag para que o procedimento relativo ao tipo 2 nao seja executado*/
    }
    
    if (p != NULL) {    /*Testa se a lista possui ou nao elementos e, se possui:*/
        int i;                          /*Declara a variavel de contagem i*/
        struct end *p_aux = p, *p_ant;  /*Declara dois ponteiros para elementos da lista: p_aux eh o elemento atual e p_ant eh o anterior ao p_aux*/
        
        if (tipo == 2 && flag == 0) {   /*TIPO 2: caso a chamada seja feita pela funcao editar, "remove" o elemento 'novo' da lista para fazer as proximas comparacoes novamente*/
            while (p_aux->prox != novo) /*Laco para encontrar o elemento que aponta para o elemento 'novo'*/
                p_aux = p_aux->prox;
            
            p_aux->prox = novo->prox;   /*Define que o o elemento que apontava para 'novo' agora aponta para o elemento seguinte ao 'novo'*/
            p_aux = p;                  /*Reatribui o valor do ponteiro p para o ponteiro auxiliar*/
        }
        flag = 0;   /*Atribui o novo valor a flag para garantir a entrada no proximo laco*/
        
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
    else    /*Se a lista nao possui elementos*/
        p = novo;   /*Registra o novo elemento como o primeiro*/
    
return(p);  /*Retorna a posicao do primeiro elemento da lista*/ }   /* -----Fim da funcao ordenaEntrada----- */

void imprimir(struct end *p, int tipo) {  /*Funcao imprimir: imprime (tipo == 1) todos os elementos da lista (p eh o 1o elemento da lista); ou o elemento p recebido. */
    if (p != NULL) {
        if (tipo == 1) {
            for(int i = 1; p != NULL; i++) {    /*Laco para impressao dos elementos*/
                printf("\n-------------------------Contato %2i-------------------------\n", i);
                printf("Nome:\t%s\nE-mail:\t%s\nTelefone: %s\n", p->nome, p->email, p->fone);
            
                p = p->prox;     /*Ajuste da posicao na lista*/
            }
            printf("------------------------------------------------------------\n");
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

void buscar(struct end *p) {    /*Funcao buscar: busca um contato pelo nome e imprime seus dados na tela, se ele existir*/
    int entrada;    /*Variavel para receber a entrada do usuario*/
    
    if (p != NULL) {    /*Caso a lista nao esteja vazia*/
        int i;              /*Variavel de contagem*/
        char procurado[MAX_N], *p_nom = &procurado[0]; /*Declara um vetor de char para armazenar o nome do contato procurado e um ponteiro para seu primeiro elemento*/
        struct end *p_aux;  /*Declara um ponteiro auxiliar para a lista*/
        
        for (entrada = 0; entrada < 80; entrada++) /*Laco para inserir uma serie de quebras de linha e "limpar" a tela*/
            putchar('\n');
        
        printf("\nDeseja buscar um contato? (1. Sim | 0. Nao)\n");  /* Confirma a opcao do usuario*/
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
        
        while (entrada != 0) {  /*Laco para executar as buscas*/
            entrada = 0;    /*Atribuicao de valor para entrar na clausula seguinte*/
            
            while (entrada != 1) {  /*Laco para receber o nome do contato procurado*/
                printf("Qual eh o nome do contato que voce busca? (Max.: %i caracteres)\n", MAX_N-1);
                procurado[0] = getchar();       /*Recebe o caractere de quebra de linha que fica na heap*/
                fgets(procurado, MAX_N, stdin); /*Recebe o nome do contato procurado, sobrescrevendo o caractere anterior*/
            
                for (i = 0; (procurado[i] != '\n') && (procurado[i] != '\0'); i++)  /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na string.*/
                    ;                                                               /*A condicao envolvendo '\0' eh por seguranca*/
                procurado[i] = '\0';    /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
            
                printf("O nome '%s' esta correto? (1. Sim | 0. Nao)\n", procurado); /*Confirma o nome procurado e permite correcao*/
                scanf("%i", &entrada);
            
                entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
            }
            
            p_aux = seekndestroy(p, p_nom, 1);  /*Chama a funcao seekndestroy em modo de busca para procurar o contato em questao*/
            
            if (p_aux != NULL)  /*Se o contato estiver na lista*/
                imprimir(p_aux, 2); /*Chama a funcao de impressao para imprimi-lo*/
            
            else                /*Caso o contato nao esteja na lista, informa o usuario*/
                printf("O contato buscado nao esta na agenda.\n");
            
            printf("Deseja buscar outro contato? (1. Sim | 0. Nao)\n"); /*Pergunta se o usuario deseja buscar outro contato*/
            scanf("%i", &entrada);
            
            entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
        }   /*Fim do laco de buscas*/
    }
    else    /*Caso a lista esteja vazia, informa o usuario*/
        printf("Voce nao possui contatos na sua agenda.\n");
    
    printf("Aperte 'Enter' para voltar ao menu principal.\n");  /*Permite o usuario controlar o momento que ele deseja sair da funcao*/
    entrada = getchar();    /*Recebe a quebra de linha armazenada na heap*/
    entrada = getchar();
}   /* -----Fim da funcao buscar----- */

struct end *seekndestroy(struct end *p, char *p_nom, int tipo) {    /*Funcao seekndestroy: Busca um elemento e o destroi caso tipo == 2; caso tipo == 1, retorna sua posicao sem maiores danos*/
    struct end *p_aux = p, *p_ant = p_aux; /*Ponteiros auxiliares para guardar o elemento atual e o anterior a esse*/
    
    while (p_aux != NULL) { /*Laco para varrer toda a lista*/
        if (strcmp(p_aux->nome, p_nom) == 0) {  /*Se o elemento da lista atual for o elemento procurado*/
            
            if (tipo == 1)          /*TIPO 1: Apenas busca, retorna seu endereco de memoria, indicando sucesso*/
                return(p_aux);
            
            else if (tipo == 2) {   /*TIPO 2: Remocao*/
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

struct end *editar (struct end *p) {    /*Funcao editar: permite a edicao de um ou mais contatos, retornando o ponteiro para o primeiro elemento da lista*/
    int entrada;    /*Variavel para armazenar a entrada do usuario*/
    
    if (p != NULL) {    /*Caso a lista nao esteja vazia*/
        int i;              /*Variavel de contagem*/
        char procurado[MAX_N], *p_nom = &procurado[0];  /*Declara um vetor de char para armazenar o nome do contato a ser editado e um ponteiro para o seu primeiro elemento*/
        struct end *p_aux;  /*Declara um ponteiro auxliar para a lista*/
        
        for (entrada = 0; entrada < 80; entrada++) /*Laco para inserir uma serie de quebras de linha e "limpar" a tela*/
            putchar('\n');
        
        printf("\nDeseja editar um contato? (1. Sim | 0. Nao)\n");  /*Confirma a opcao do usuario*/
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
        
        while (entrada != 0) {  /*Laco para a edicao de contatos*/
            printf("Qual o nome do contato que voce deseja editar? (Max.: %i caracteres)\n", MAX_N-1); /*Pergunta o nome do contato a ser editado*/
            procurado[0] = getchar();       /*Recebe o caractere de quebra de linha que fica na heap*/
            fgets(procurado, MAX_N, stdin); /*Recebe o nome do contato a ser editado, sobrescrevendo o caractere acima*/
            
            for (i = 0; (procurado[i] != '\n') && (procurado[i] != '\0'); i++)  /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na string.*/
                ;                                                               /*A condicao envolvendo '\0' eh por seguranca*/
            procurado[i] = '\0';    /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
            
            p_aux = seekndestroy(p, p_nom, 1);  /*Chama a funcao seekndestroy em modo de busca e armazena o ponteiro retornado no auxiliar*/
            
            if (p_aux != NULL) {    /*Se o contato buscado existir*/
                while (entrada != 0) {  /*Laco para a edicao dos dados do contato*/
                    imprimir(p_aux, 2); /*Chama a funcao 'imprimir' para imprimir os dados do contato em questao*/
                    
                    printf("O que voce deseja editar?\n1. Nome\t    2. E-mail\t  3. Telefone\t0. Nada\n");  /*Pergunta qual campo o usuario deseja editar*/
                    scanf("%i", &entrada);
                    
                    entrada = teste(entrada, 0, 3, 2);  /* Testa a validade da entrada do usuario */
                    
                    if (entrada == 1) {         /* ----Edicao do nome---- */
                        printf("Qual o novo nome do contato? (Max.: %i caracteres)\n", MAX_N-1);
                        p_aux->nome[0] = getchar();         /*Recebe o caractere de quebra de linha que fica na heap*/
                        fgets(p_aux->nome, MAX_N, stdin);   /*Recebe o novo nome do contato, sobrescrevendo o caractere acima*/
                        
                        for (i = 0; (p_aux->nome[i] != '\n') && (p_aux->nome[i] != '\0'); i++)  /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na...*/
                            ;                                                                   /*...string. A condicao envolvendo '\0' eh por seguranca*/
                        p_aux->nome[i] = '\0';  /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
                        
                        p = ordenaEntrada(p, p_aux, 2);    /*Chama a funcao ordenaEntrada para colocar o elemento de volta na lista em ordem alfabetica, recebendo o vetor para o primeiro elemento*/
                    }
                    else if (entrada == 2) {    /* ----Edicao de e-mail---- */
                        printf("Qual o novo e-mail do contato? (Max.: %i caracteres)\n", MAX_E-1);
                        p_aux->email[0] = getchar();        /*Recebe o caractere de quebra de linha que fica na heap*/
                        fgets(p_aux->email, MAX_E, stdin);  /*Recebe o novo e-mail do contato, sobrescrevendo o caractere acima*/
                        
                        for (i = 0; (p_aux->email[i] != '\n') && (p_aux->email[i] != '\0'); i++)
                            ;
                        p_aux->email[i] = '\0';
                    }
                    else if (entrada == 3) {
                        printf("Qual o novo telefone do contato? (Max.: %i caracteres)\n", MAX_F-1);
                        p_aux->fone[0] = getchar();         /*Recebe o caractere de quebra de linha que fica na heap*/
                        fgets(p_aux->fone, MAX_F, stdin);   /*Recebe o novo telefone do contato, sobrescrevendo o caractere acima*/
                        
                        for (i = 0; (p_aux->fone[i] != '\n') && (p_aux->fone[i] != '\0'); i++)  /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na...*/
                            ;                                                                   /*...string. A condicao envolvendo '\0' eh por seguranca*/
                        p_aux->fone[i] = '\0';  /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
                    }
                }   /*Fim do laco para edicao dos dados*/
            }
            else                    /*Caso o contato nao esteja na lista, informa o usuario*/
                printf("O contato procurado nao esta na agenda.\n");
            
            printf("Deseja editar outro contato? (1. Sim | 0. Nao)\n"); /*Pergunta se o usuario deseja editar outro contato*/
            scanf("%i", &entrada);
            
            entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
        }
    }
    else    /*Caso a lista esteja vazia, informa o usuario*/
        printf("Voce nao possui contatos na sua agenda.\n");
    
    printf("Aperte 'Enter' para voltar ao menu principal.\n");  /*Permite o usuario controlar o momento que ele deseja sair da funcao*/
    entrada = getchar();    /*Recebe a quebra de linha armazenada na heap*/
    entrada = getchar();
return(p);  /*Retorna o ponteiro para o primeiro elemento da lista*/ }  /* -----Fim da funcao editar----- */

struct end *remover(struct end *p) {    /*Funcao remover: Procura um usuario e o remove caso necessario. Retorna o ponteiro para o primeiro elemento da lista*/
    int entrada;    /*Variavel para receber entradas do usuario*/
    
    if (p != NULL) {    /*Caso a lista nao esteja vazia*/
        int i;              /*Variavel de contagem*/
        char procurado[MAX_N], *p_nom = &procurado[0];  /*Declara um vetor de caracteres e um ponteiro para o primeiro elemento do vetor*/
        struct end *p_aux;  /*Ponteiro auxiliar para lista*/
        
        for (entrada = 0; entrada < 80; entrada++) /*Laco para inserir uma serie de quebras de linha e "limpar" a tela*/
            putchar('\n');
        
        printf("Deseja remover um contato? (1. Sim | 0. Nao)\n");   /*Confirma a opcao do usuario*/
        scanf("%i", &entrada);
        
        entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
        
        while (entrada != 0) {  /*Laco para busca e remocao de contato*/
            entrada = 0;    /*Atribuicao para entrar na proxima condicao*/
            
            while (entrada != 1) {  /*Laco para receber nome do contato a ser removido*/
                printf("Qual o nome do contato que voce deseja remover? (Max.: %i caracteres)\n", MAX_N-1);
                procurado[0] = getchar();       /*Recebe o caractere de quebra de linha que fica na heap*/
                fgets(procurado, MAX_N, stdin); /*Recebe o nome do contato a ser removido, sobrescrevendo o caractere acima*/
                
                for (i = 0; (procurado[i] != '\n') && (procurado[i] != '\0'); i++)  /*Laco para remover a entrada de uma quebra de linha que a funcao fgets() recebe e armazena na string.*/
                    ;                                                               /*A condicao envolvendo '\0' eh por seguranca*/
                procurado[i] = '\0';    /*Atribui o valor de "fim de string" no lugar da quebra de linha*/
            
                printf("O nome '%s' esta correto? (1. Sim | 0. Nao)\n", procurado); /*Confirma se o nome entrado esta correto*/
                scanf("%i", &entrada);
                
                entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
            }
            p_aux = seekndestroy(p, p_nom, 1);  /*Chama a funcao seekndestroy em modo de busca e armazena o ponteiro retornado no auxiliar*/
            
            if (p_aux != NULL) {    /*Se o contato procurado existir*/
                imprimir(p_aux, 2); /*Chama a funcao 'imprimir' para imprimir seus dados na tela*/
                
                printf("Deseja REALMENTE excluir o contato em questao? Esse processo nao pode ser\nrevertido. (1. Sim | 0. Nao)\n");    /*Confirma a opcao do usuario*/
                scanf("%i", &entrada);
            
                entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
                
                if (entrada == 1) { /*Se o usuario desejar, remove o contato em questao da agenda e informa o usuario do sucesso da operacao*/
                    p = seekndestroy(p, p_nom, 2);
                    printf("\nO contato '%s' foi removido da agenda.\n", procurado);
                }
            }
            else                    /*Caso o contato procurado nao esteja na lista, informa o usuario*/
                printf("O contato buscado nao esta na agenda.\n");
            
            if (p == NULL) {    /*Caso todos os contatos sejam excluidos da agenda*/
                printf("Voce nao possui mais contatos em sua agenda.\n");   /*Informa a situacao para o usuario*/
                break;  /*Sai do laco para evitar erros de leitura de memoria*/
            }
            else {              /*Caso ainda hajam contatos, sugere a exclusao de mais alguns*/
                printf("Deseja remover outro contato? (1. Sim | 0. Nao)\n");
                scanf("%i", &entrada);
            
                entrada = teste(entrada, 0, 1, 1);  /* Testa a validade da entrada do usuario */
            }
        }   /*Fim do laco para busca e remocao*/
    }
    else                /*Caso a lista esteja vazia, informa o usuario*/
        printf("Voce nao possui contatos na sua agenda.\n");
    
    printf("Aperte 'Enter' para voltar ao menu principal.\n");  /*Dá ao usuario a ilusão de que ele controla a máquina*/
    entrada = getchar();    /*Recebe a quebra de linha armazenada na heap*/
    entrada = getchar();
    
return(p);  /*Retorna o ponteiro para o primeiro elemento da lista*/ }  /* -----Fim da funcao remover----- */
