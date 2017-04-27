/* Programa TheMatrixCriatividade0
 * 
 * Este programa gera uma matriz de tamanho MxN definido pelo usuário e a preenche com números aleatórios.
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
#include <stdlib.h>
#include <time.h>

/* ---Funcoes--- */
void arquiteto (int m, int n, int *ponteiro);   /* Recebe as dimensoes da matriz e o ponteiro para vetor e o preenche com numeros aleatorios */

int main(void) { /* Funcao principal */
    
    int m, n;       /* Dimensoes da matriz */
    int *ponteiro;  /* Ponteiro para o vetor que sera criado */
    
    printf("\nBem vindo ao programa TheMatrixCriatividade0!\nEste programa cria uma matriz de dimensoes definidas por voce e preenche ela com\n");	/* Mensagem de boas vindas e explicacao do */
    printf("numeros aleatorios. Recomendo o maximo de 10x10 para melhor leitura e formatacao\nno terminal.\n");						/* programa */
    
    printf("Digite o numero de colunas:\t");    /* Recebe o numero de colunas da matriz e registra na variavel 'm' */
    scanf("%i", &m);
    while(m <= 0) {  /* Garante que o valor entrado nao seja negativo ou zero e permite correcao*/
        printf("Sua entrada eh invalida. Digite um valor estritamente maior que zero.\n");
        scanf("%i", &m); }
    
    printf("Digite o numero de linhas:\t");     /* Recebe o numero de linhas da matriz e registra na variavel 'n' */
    scanf("%i", &n);
    while(n <= 0) {  /* Garante que o valor entrado nao seja negativo ou zero e permite correcao*/
        printf("Sua entrada eh invalida. Digite um valor estritamente maior que zero.\n");
        scanf("%i", &n); }
    
    int matrix[m*n];        /* Cria um vetor de dimensao m*n que simulara a matriz */
    ponteiro = &matrix[0];  /* Atribui ao ponteiro o valor do endereco do primeiro elemento do vetor */
    srand(time(NULL));      /* Gera uma nova "seed" para a funcao rand() */
    
    arquiteto(m, n, ponteiro);  /* Chama a funcao arquiteto */
    
    printf("\n\nObrigado por usar o programa!\n\n");    /* Mensagem de agradecimento */
    
return(0); }    /* Fim da funcao principal */

void arquiteto (int m, int n, int *ponteiro) {  /* Recebe as dimensoes da matriz e o ponteiro para vetor e o preenche com numeros aleatorios */
    int i;  /* Variavel de contagem */
    
    for(i = 0; i < m*n; i++)    /* Laco que preenche o vetor com numeros aleatorios (com valores de ate 32767)*/
            ponteiro[i] = rand()%32767;
    
    printf("\nSua matriz preenchida com numeros aleatorios eh a seguinte:\n\n");
    
    for(i = 0; i < m*n; i++) {  /* Laco que imprime e formata a saida */
        if( ((i % n) == 0) && (i != 0) ) {  /* Imprime uma quebra de linha para formatar o texto no estilo de uma matriz a cada n elementos impressos na tela */
                printf("\n");
        }
        printf("%5i\t", ponteiro[i]);
        }

} /* Fim da funcao arquiteto */
