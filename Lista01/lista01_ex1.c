/* Programa DesvPad66
 * 
 * Este programa calcula o desvio padrão de uma população de 10 elementos vindouros de uma entrada obtida do usuário.
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 17/03/2017
 * Editado em: 19/03/17
 * 
*/

/* ---Bibliotecas--- */
#include <stdio.h>
#include <math.h>

/* ---Variaveis globais--- */
#define POPULAC     10      /* Tamanho da populacao */

/* ---Funcoes--- */

void desvpad (float amostra[]);    /* Funcao desvpad: calcula o desvio padrao */

int main(void) {    /* Funcao principal */
    
    float amostra[POPULAC]; /* Vetor para armazenar os dados */
    
    printf("\nBem vindo ao programa DesvPad66! Este programa calcula o desvio padrão de uma\namostra de %i dados.\n", POPULAC); /* Mensagem de boas vindas */
    
    for (int i = 0; i < POPULAC; i++) { /* Laco para receber os dados do usuario */
        printf("Digite o valor do dado numero %i: ", i+1);
        scanf("%f", &amostra[i]); } /* Fim do laco */
    
    desvpad(amostra);  /* Chama a funcao desvpad */
    
    printf("Obrigado por usar o programa!\n");  /* Mensagem de saida */
    
return(0); } /* Fim da funcao main */

void desvpad (float amostra[]) {   /* Funcao desvpad: calcula o desvio padrao */
    
    int i;  /* Variavel de contagem */
    float media = 0, desvio = 0;    /* Variavel para calcular a media e o desvio padrao, respectivamente */
    
    for (i = 0; i < POPULAC; i++)   /* Laco para calcular o somatorio do valor de todas as amostras */
        media = media + amostra[i];
    
    media = media/POPULAC; /* Calculo da media */
    
    for (i = 0; i < POPULAC; i++)   /* Laco para calcular o somatorio dado por (amostra - media)^2 */
        desvio = desvio + (amostra[i] - media)*(amostra[i] - media);
    
    desvio = sqrt(desvio/POPULAC);  /* Calculo do desvio padrao */
    printf("\nO desvio padrao da amostra eh: %f\n", desvio);  /* Imprime o resultado do desvio padrao */
    
}