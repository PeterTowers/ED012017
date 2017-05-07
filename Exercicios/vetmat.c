/* Programa Armazenador
 * Este programa armazena dados em um vetor para depois imprimi-lo. E depois faz o mesmo com uma matriz.
 *
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: Circa 03/2017
 * Editado em: 07/05;
 */

#include <stdio.h>

int main(void) {
  
  int vetor[10] = {0}, matriz[3][4] = {0}, i = 0, j = 0;	/* Cria e inicializa as variaveis */
  
  printf("Bem vindo ao armazenador de dados em um vetor!\nEste programa armazena dez números inteiros em um vetor e depois os imprime.\n");	/* Mensagem de boas vindas */
  
  for(i = 0; i < 10; i++) {	/* Laco que recebe dados para armazenar no vetor */
    printf("Entre com o numero de posicao %i:\t", i+1);
    scanf("%i", &vetor[i]);
  }
  
  printf("| ");
  for(i = 0; i < 10; i++) {	/* Laco para imprimir os dados contidos no vetor */
    printf("%i | ", vetor[i]);
  }
  
  printf("\n\nAgora vamos fazer uma matriz 3x4!\n");	/* Mensagem de contexto */
  
  for(i = 0; i < 3; i++) {	/* Laco que recebe dados para armazenar na matriz */
    for(j = 0; j < 4; j++) {
    	printf("Entre com o numero que ficara na posicao (%i, %i): ", i, j);
    	scanf("%i", &matriz[i][j]); 
    }
  }
  
  printf("\n");
  for(i = 0; i < 3; i++) {	/* Laco para imprimir os dados contidos na matriz */
    for(j = 0; j < 4; j++) {
      printf("%i ", matriz[i][j]);
    
      if (j == 3)
        printf("\n");
    }
  }
  
  printf("\nObrigado por usar o programa!\n");	/* Mensagem de agradecimento */
  
return(0); }
