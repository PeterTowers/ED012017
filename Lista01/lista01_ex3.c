/* Programa DesvPad66v2
 * 
 * Este programa calcula o desvio padrão de uma população de até 32.767 elementos vindouros de uma entrada obtida do usuário.
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 19/03/2017
 * Editado em: 21/03/17; 
 * 
*/

/* ---Bibliotecas--- */
#include <stdio.h>
#include <math.h>


/* ---Funcoes--- */

void desvpad (int tamanho, float *ponteiro);    /* Funcao desvpad: calcula o desvio padrao */

int main(void) {    /* Funcao principal */
    
    float *ponteiro;    /* Ponteiro para passar os dados do vetor para a funcao */
    int tamanho;        /* Variavel que recebe o tamanho do vetor */
    
    printf("\nBem vindo ao programa DesvPad66_v3! Este programa calcula o desvio padrão de uma\namostra de dados.\n"); /* Mensagem de boas vindas */
    printf("Qual eh o tamanho de sua amostra? (max: 32.767) "); /* Pede o numero total de dados a serem calculados */
    scanf("%i", &tamanho);
    
    while(tamanho <= 0) {   /* Checa a validade da entrada e permite correcoes */
        printf("Sua entrada eh invalida. Digite um valor estritamente maior que zero.\n");
        scanf("%i", &tamanho); }
    
    float amostra[tamanho]; /* Cria o vetor para armazenar os dados */
    
    for (int i = 0; i < tamanho; i++) { /* Laco para receber os dados do usuario */
        printf("Digite o valor do dado numero %i: ", i+1);
        scanf("%f", &amostra[i]); } /* Fim do laco */
    
    ponteiro = &amostra[0];     /* Declara o ponteiro como o endereco do primeiro elemento do vetor */
    
    desvpad(tamanho, ponteiro); /* Chama a funcao desvpad */
    
    printf("Obrigado por usar o programa!\n\n");  /* Mensagem de saida */
    
return(0); } /* Fim da funcao main */

void desvpad (int tamanho, float *ponteiro) {   /* Funcao desvpad: calcula o desvio padrao */
    
    int i;                          /* Variavel de contagem */
    float media = 0, desvio = 0;    /* Variavel para calcular a media e o desvio padrao, respectivamente */
    
    for (i = 0; i < tamanho; i++)   /* Laco para calcular o somatorio do valor de todas as amostras */
        media = media + ponteiro[i];
    
    media = media/tamanho;          /* Calculo da media */
    
    for (i = 0; i < tamanho; i++)   /* Laco para calcular o somatorio dado por (amostra - media)^2 */
        desvio = desvio + (ponteiro[i] - media)*(ponteiro[i] - media);
    
    desvio = sqrt(desvio/tamanho);  /* Calculo do desvio padrao */
    printf("\nO desvio padrao da amostra eh: %f\n", desvio);  /* Imprime o resultado do desvio padrao */
    
}