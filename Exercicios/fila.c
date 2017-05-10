/* Programa feela
 * Este programa faz uma fila simples, utilizando um vetor de 10 argumentos, com a entrada do usuario e imprime a fila de acordo com seu funcionamento (FIFO)
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
#define MAX 10                          /* Tamanho do vetor a ser utilizado */
int inicio = 0, fim = -1, status = 1;    /* (inicio) salva a posicao primeiro da fila e (fim) do final, (status) eh uma variavel de controle (status == 1, tudo ok; status == 0, ha algo errado) */

void pushfila (int stack[], int item);  /* Funcao push */
int popfila (int stack[]);              /* Funcao pop */

int main (void) {   /* Funcao principal */
    int numero;                                 /* Variavel para receber a entrada do usuario */
    int* vetor = (int*)malloc(MAX*sizeof(int)); /* Aloca o espaco para o vetor que guardara as entradas do usuario */
  
    printf("\nBem vindo ao programa feela!\nEste programa recebe %i valores, os guarda em uma estrutura de dados chamada\nfila ", MAX);   /* Mensagem de boas vindas */
    printf("e retorna os valores armazenados de acordo com o sistema FIFO.\n\n");
  
    for(int i = 0; i < MAX; i++) {    /* Laco para colocar os valores em fila */
        printf("Digite o %2io numero: ", i+1);
        scanf("%i", &numero);
        pushfila(vetor, numero);    /* Chamada da funcao push */
    }
    
    printf("\n");
    for(int i = 0; i < MAX; i++)  /* Laco para remover os valores da fila e imprimi-los */
        printf("%2io numero: %i\n", inicio, popfila(vetor));
    
    free(vetor);    /* Libera o espaco ocupado pelo vetor na memoria */

    printf("\nObrigado por usar o programa!\n");    /* Mensagem de saida */
    
return(0); }    /* -----Fim da funcao principal----- */

void pushfila (int vetor[], int item) { /* Funcao push: coloca um valor na ultima posicao da fila */
    
    if (fim == MAX)    /* Testa se a fila esta cheia e, caso esteja, atribui valor 0 a variavel de controle status */
        status = 0;
    else {              /* Caso contrario, coloca o valor na fila */
        status = 1;
        ++fim;          /* Ajusta o topo da fila */
        vetor[fim] = item; }

}   /* -----Fim da funcao push----- */

int popfila (int vetor[]) { /* Funcao pop: retorna o ultimo valor inserido no vetor */
  
  int ret;  /* Variavel de retorno */
  
  if (inicio == -1) { /* Testa se a fila esta vazia e, caso esteja, define a variavel de controle status = 0 e retorna o valor 0*/
    status = 0;
    return(0); }
  
  else {            /* Caso contrario, remove o primeiro valor da fila */
    status = 1;
    ret = vetor[inicio];
    ++inicio; }   /* Ajusta onde esta o topo da fila */

return ret; }   /* -----Fim da funcao pop----- */
