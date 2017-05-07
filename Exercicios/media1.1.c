/* Programa alocDin
 * 
 * Este programa recebe um número de elementos definido pelo usuário, e calcula a média deles.
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 22/03/2017
 * Editado em: 07/05;
 * 
*/

/* ---Bibliotecas--- */
#include <stdio.h>
#include <stdlib.h>

/* ---Funcoes--- */
void media (int num, int *ponteiro); /* Funcao media: recebe o numero de valores e o ponteiro para onde os valores serao armazenados e calcula a media dos valores. */

int main(void) {    /* Funcao principal */
    
    int num;    /* Recebe o numero total de dados */
    
    printf("\nBem vindo ao programa alocDin!\nEste programa calcula a media de uma amostra de dados.\n\n"); /* Mensagem de boas vindas */
    
    printf("Qual eh o tamanho de sua amostra?\t");  /* Recebe o tamanho da amostra */
    scanf("%i", &num);
    
    while(num < 1) {    /* Confere o valor e permite correcoes */
        printf("Sua entrada eh invalida. Digite um valor estritamente maior que zero.\n");
        scanf("%i", &num);
    }
    
    float *ponteiro = (float*) malloc(num*sizeof(float)); /* Aloca a memoria para receber um numero 'num' de dados */
    
    media (num, ponteiro);  /* Chama a funcao media */
    
    free(ponteiro); /* Libera a memoria alocada anteriormente */
    
    printf("\nObrigado por usar o programa!\n");    /* Mensagem de saida */
    
return(0); }        /* Fim da funcao principal */

void media (int num, int *ponteiro) { /* Funcao media: recebe o numero de valores e o ponteiro para onde os valores serao armazenados e calcula a media dos valores. */
    
    int i;          /* Variavel de contagem */
    float avg = 0;  /* Variavel para armazenar a media */
    
    for(i = 0; i < num; i++) {  /* Laco para receber o valor de cada dado da amostra */
        printf("Digite o valor do dado de numero %i:\t", i+1);
        scanf("%f", &ponteiro[i]); }
    
    for(i = 0; i < num; i++)    /* Laco que faz o somatorio de todos os dados da amostra */
        avg = avg + ponteiro[i];
    
    avg = avg / num;    /* Divide o valor do somatorio anterior pelo numero de amostras para calcular a media */
    
    printf("\nA media dos %i valores apresentados eh: %.4f\n", num, avg); /* Imprime a media na tela */

} /* Fim da funcao media */
