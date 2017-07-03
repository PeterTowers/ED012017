/* Programa realocacao
 * Este programa faz uma pilha simples, utilizando um vetor de 10 argumentos, podendo aumentar conforme a necessidade, e imprime a pilha de acordo com seu funcionamento (LIFO)
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 03/07/2017
 * Editado em: 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -----Variaveis globais----- */
int topo = -1, max = 10;    /* topo salva a posicao do topo da pilha, max eh o tamanho do vetor */

int *push (int *pilha, int item);   /* Funcao push */
int pop (int *pilha);               /* Funcao pop */

int main (void) {   /* Funcao principal */
    int numero = -1;   /* Recebe a entrada do usuario */
    int *pilha = (int*)malloc(max*sizeof(int)); /* Aloca o espaco para o vetor que guardara as entradas do usuario */
  
    printf("\nBem vindo ao programa pilha!\nEste programa recebe %i valores, os guarda em uma estrutura de dados chamada\npilha ", max);   /* Mensagem de boas vindas */
    printf("e retorna os valores armazenados de acordo com o sistema LIFO.\n");
    
    while (numero != 0) {
        printf("\nO que deseja fazer?\n1. Inserir um dado na pilha\n2. Imprimir um dado da pilha\n3. Imprimir toda a pilha\n0. Sair\n");
        scanf("%i", &numero);
        
        if (numero == 1) {
            printf("Diga-me o numero a ser inserido (max. 32.767):\t");
            scanf("%i", &numero);
            
            pilha = push(pilha, numero);
        }
        else if (numero == 2) {
            numero = pop(pilha);
            printf("Ultimo numero da pilha: %i\n", numero);
        }
        else if (numero == 3)
            while (topo >= 0) {
                numero = pop(pilha);
                printf("Elemento numero %2i: %5i\n", topo+1, numero);
            }
        
        else if (numero == 0)
            break;
        
        else
            printf("Entrada invalida. Tente novamente.\n");
        
        numero = -1;
    }
    free(pilha);
    
    printf("\nObrigado por usar o programa!\n");    /* Mensagem de saida */
    
return(0); }    /* -----Fim da funcao principal----- */

int *push (int *pilha, int item) { /* Funcao push: empilha um valor na ultima posicao de um vetor de entrada */
    
    if (topo == max) {  /* Testa se a pilha esta cheia e, caso esteja, cria um novo vetor maior, copia os dados do antigo para o novo e libera o espaco alocado pelo vetor antigo */
        max = max + 5;
        
        int *aux = (int*)malloc(max*sizeof(int));   /* Criacao do novo vetor maior */
        
        memcpy(aux, pilha, topo*sizeof(int));       /* Copia o vetor antigo para o novo */
        free(pilha);    /* Libera o espaco alocado */
        
        topo++;             /* Ajusta o topo da pilha */
        aux[topo] = item;   /* Empilha o novo item */
        
        return(aux);    /* Retorna o endereco do novo vetor */
    }
    else {              /* Caso contrario, empilha o valor */
        ++topo;     /* Ajusta o topo da pilha */
        pilha[topo] = item;
        
        return(pilha);
    }

}   /* -----Fim da funcao push----- */

int pop (int *pilha) { /* Funcao pop: retorna o ultimo valor inserido no vetor */
  
  int ret;  /* Variavel de retorno */
  
  if (topo == -1)   /* Testa se a pilha esta vazia e, caso esteja, retorna o valor 0*/
    return(0);
  
  else {            /* Caso contrario, desempilha o ultimo numero empilhado */
    ret = pilha[topo];
    --topo; }   /* Ajusta onde esta o topo da pilha */

return ret; }   /* -----Fim da funcao pop----- */
