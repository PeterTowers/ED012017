/* Programa pilha
 * Este programa faz uma pilha simples, utilizando um vetor de 10 argumentos, com a entrada do usuario e imprime a pilha de acordo com seu funcionamento (LIFO)
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 31/03/2017
 * Editado em: 09/05; 
*/

#include <stdio.h>
#include <stdlib.h>

/* -----Variaveis globais----- */
#define MAX 10              /* Tamanho do vetor a ser utilizado */
int topo = 0, status = 1;   /* topo salva a posicao do topo da pilha, status eh uma variavel de controle (status == 1, tudo ok; status == 0, ha algo errado) */

void push (int stack[], int item);  /* Funcao push */
int pop (int stack[]);              /* Funcao pop */

int main (void) {   /* Funcao principal */
    int numero;   /* Recebe a entrada do usuario */
    int* vetor = (int*)malloc(MAX*sizeof(int));   /* Aloca o espaco para o vetor que guardara as entradas do usuario */
  
    printf("\nBem vindo ao programa pilha!\nEste programa recebe %i valores, os guarda em uma estrutura de dados chamada\npilha ", MAX);   /* Mensagem de boas vindas */
    printf("e retorna os valores armazenados de acordo com o sistema LIFO.\n\n");
  
    for(int i = 0; i < MAX; i++) {    /* Laco para empilhar os valores */
        printf("Digite o %2io numero: ", i+1);
        scanf("%i", &numero);
        push(vetor, numero);    /* Chamada da funcao push */
    }
    
    printf("\n");
    for(int i = 0; i < MAX; i++)  /* Laco para desempilhar os valores e imprimi-los */
        printf("%2io numero %i\n", topo+1, pop(vetor));
    
    free(vetor);    /* Libera o espaco ocupado pelo vetor na memoria */

    printf("\nObrigado por usar o programa!\n");    /* Mensagem de saida */
    
return(0); }    /* -----Fim da funcao principal----- */

void push (int vetor[], int item) { /* Funcao push: empilha um valor na ultima posicao de um vetor de entrada */
    
    if (topo == MAX)    /* Testa se a pilha esta cheia e, caso esteja, define a variavel de controle status = 0 */
        status = 0;
    else {              /* Caso contrario, empilha o valor */
        status = 1;
        ++topo;     /* Ajusta o topo da pilha */
        vetor[topo] = item; }

}   /* -----Fim da funcao push----- */

int pop (int vetor[]) { /* Funcao pop: retorna o ultimo valor inserido no vetor */
  
  int ret;  /* Variavel de retorno */
  
  if (topo == -1) { /* Testa se a pilha esta vazia e, caso esteja, define a variavel de controle status = 0 e retorna o valor 0*/
    status = 0;
    return(0); }
  
  else {            /* Caso contrario, desempilha o ultimo numero empilhado */
    status = 1;
    ret = vetor[topo];
    --topo; }   /* Ajusta onde esta o topo da pilha */

return ret; }   /* -----Fim da funcao pop----- */
