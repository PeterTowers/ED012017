/* Programa Batalha Náutica
 * 
 * Este programa simula o jogo Batalha Naval, com um tabuleiro de tamanho variável e a opção de preenchê-lo automaticamente, de forma aleatória.
 * 
 * Aluno: Pedro Lucas S. H. Torres
 * Matrícula: 16/0141575
 * Matéria: Estrutura de Dados, turma B
 * Data de criação do código: 02/04/2017
 * Editado em: 05/04/17, 06/04/17, 07/04/17; 
 * 
*/

/* ---Bibliotecas--- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/* ---Estruturas--- */
struct Navio{
    char classe[17];    /* Nome da embarcacao */
    char desig;         /* Primeira letra (exceto no caso do contratorpedeiro) que sera impressa no tabuleiro */
    int qtd;            /* Numero de embarcacoes disponiveis para posicionar */
    int tam;            /* Quantidade de embarcacoes da classe disponiveis */
};

struct Navio Embarc[] = {           /* Atribuicao dos valores para a estrutura */
    {"Porta-avioes", 'P', 1, 5},
    {"Encouracado", 'E', 2, 4},
    {"Cruzador", 'C', 3, 3},
    {"Submarino", 'S', 4, 3},
    {"Contratorpedeiro", 'T', 5, 2}
};                                  /* Fim da atribuicao */

/* ---Funcoes--- */
int teste       (int var, int isso, int aquilo, int tipo);                                          /* Testa a validade da entrada do usuario de acordo com os parametros passados para a funcao */
void batalha    (void);                                                                                         /* Executa o jogo */
void almirante  (int colunas, int linhas, int ***player);                                                       /* Permite o jogador posicionar suas embarcacoes no tabuleiro manualmente */
void marinheiro (int colunas, int linhas, int ***player);                                                       /* Posiciona as embarcacoes do jogador aleatoriamente */
int brief1      (int ***player1, int ***player2, int *lastx, int *lasty, int *pontlife, int linhas, int colunas, int lifepl);  /* Roda o jogo do player 1 */
int brief2      (int ***player1, int ***player2, int *lastx, int *lasty, int *pontlife, int linhas, int colunas, int lifepl);  /* Roda o jogo do player 2 */

int main(void) {    /* Funcao principal */
    int continuar;  /* Recebe uma entrada do usuario, relativa ao desejo de jogar */
    
    printf("\nBem vindo ao programa Batalha Nautica!\nEste programa simula o jogo Batalha Naval, com um tabuleiro de tamanho definido\npor voce e a opcao de preenche-lo automaticamente.\n");   /* Mensagem de boas vindas */
    printf("Deseja jogar? (Sim: 1 | Nao: 0)\n");    /* Pergunta se o usuario deseja jogar o jogo */
    scanf("%i", &continuar);
    
    continuar = teste(continuar, 1, 0, 1);          /* Testa a validade da entrada do usuario */
    
    while (continuar == 1) {    /* Laco que executa o jogo enquanto o usuario desejar */
        batalha();                                              /* Executa a funcao do jogo */
        
        printf("Deseja jogar novamente? (Sim: 1 | Nao: 0)\n");  /* Pergunta se o jogador deseja jogar novamente, apos o fim da partida */
        scanf("%i", &continuar);
        
        continuar = teste(continuar, 1, 0, 1);                  /* Testa a validade da entrada do usuario */
        
        if (continuar == 0) {                                   /* Caso o usuario nao queira mais jogar */
            printf("\nObrigado por jogar e volte sempre!\n\n"); /* Imprime uma mensagem de agradecimento e termina o programa */
            return(0); }
    }
    
    printf("Obrigado por usar o programa!\n");  /* Mensagem de agradecimento, caso o jogador decida nao jogar */

return(0); }        /* -----Fim da funcao principal----- */

int teste (int var, int isso, int aquilo, int tipo) {   /* Testa a validade da entrada do usuario (var) de acordo com os parametros passados para a funcao ('isso' e 'aquilo'), permitindo correcao. E retorna o valor da variavel para a funcao */
    
    if (tipo == 1) {    /* TIPO 1: teste para sim (1) ou nao (0). */
        while (var != isso && var != aquilo) {  /* Enquanto a entrada for diferente de 0 e 1, repete, permitindo correcao. */
            printf("Sua entrada %i eh invalida. Digite um valor entre %i e %i\n", var, isso, aquilo);
            scanf("%i", &var); }
    }
    
    else if (tipo == 2) {   /* TIPO 2: Faz comparacoes de maior que 'isso', menor que 'aquilo'. */
        while (var < isso || var > aquilo) {    /* Enquanto a entrada nao possuir os valores aceitos repete, permitindo a correcao. */
            printf("Sua entrada %i eh invalida. Digite um valor entre %i e %i\n", var, isso, aquilo);
            scanf("%i", &var); }
    }
    
return(var); }  /* -----Fim da funcao teste----- */

void batalha (void) {   /* Funcao batalha: executa todos os passos do jogo */
    
    int linhas, colunas, bool, i, j;                                                        /* Variaveis que receberao valores e nao precisam ser inicializadas */
    int lifepl1 = 0, lifepl2, lastx[2] = {0, 0}, lasty[2] = {0, 0};                         /* Variaveis e vetores que precisam ser inicializadas */
    int *pontx1 = &lastx[0], *pontx2 = &lastx[1], *ponty1 = &lasty[0], *ponty2 = &lasty[1]; /* Ponteiros para os vetores */
    int *pontlife1 = &lifepl1, *pontlife2 = &lifepl2;                                       /* Ponteiros para a vida dos jogadores */
    
    printf("Quantas linhas voce deseja em seu tabuleiro? (Min: 10 | Max: 16)\n");   /* Pergunta e recebe a quantidade de linhas do tabuleiro de acordo com os criterios descritos */
    scanf("%i", &linhas);
    
    linhas = teste(linhas, 10, 16, 2);  /* Testa a validade da entrada do usuario */
    
    printf("Quantas colunas voce deseja em seu tabuleiro? (Min: 10 | Max: 16)\n");  /* Pergunta e recebe a quantidade de colunas do tabuleiro de acordo com os criterios descritos */
    scanf("%i", &colunas);
    
    colunas = teste(colunas, 10, 16, 2);    /* Testa a validade da entrada do usuario */
    
    int ***player1 = (int***) malloc(linhas*(sizeof(int**)));   /* Alocacao de memoria para os tabuleiros dos jogadores */
    
    for (i = 0; i < colunas; i++) {
        player1[i] = (int**) malloc(colunas*(sizeof(int**)));
        for (j = 0; j < linhas; j++)
            player1[i][j] = (int*) malloc(3*(sizeof(int*)));
    }
        
    int ***player2 = (int***) malloc(linhas*(sizeof(int**)));
    
    for (i = 0; i < colunas; i++) {
        player2[i] = (int**) malloc(colunas*(sizeof(int**)));
        
        for (j = 0; j < linhas; j++)
            player2[i][j] = (int*) malloc(3*(sizeof(int*)));
    }                                                           /* Fim do processo de alocacao de memoria */
    
    
    printf("Player 1, deseja posicionar suas embarcacoes aleatoriamente? (Sim: 1 | Nao: 0)\n"); /* Questiona se o jogador 1 deseja posicionar suas embarcacoes aleatoriamente e recebe sua entrada*/
    scanf("%i", &bool);
    
    bool = teste(bool, 1, 0, 1);    /* Testa a validade da entrada do usuario */
    
    srand(time(NULL));  /* Inicializa uma seed para a funcao rand() que sera utilizada caso um dos jogadores deseje posicionar suas embarcacoes aleatoriamente */
    
    if (bool == 0)      /* Caso bool == 0, chama a funcao que permite o jogador 1 posicionar suas embarcacoes manualmente no tabuleiro */
        almirante(colunas, linhas, player1);
    else                /* Caso contrario, chama a funcao que posiciona as embarcacoes aleatoriamente */
        marinheiro(colunas, linhas, player1);
    
    printf("Player 2, deseja posicionar suas embarcacoes aleatoriamente? (Sim: 1 | Nao: 0)\n"); /* Questiona se o jogador 2 deseja posicionar suas embarcacoes aleatoriamente e recebe sua entrada*/
    scanf("%i", &bool);
    
    bool = teste(bool, 1, 0, 1);    /* Testa a validade da entrada do usuario */
    
    if (bool == 0)      /* Caso bool == 0, chama a funcao que permite o jogador 1 posicionar suas embarcacoes manualmente no tabuleiro */
        almirante(colunas, linhas, player2);
    else                /* Caso contrario, chama a funcao que posiciona as embarcacoes aleatoriamente */
        marinheiro(colunas, linhas, player2);
    
    for (i = 0; i < 5; i++) /* Inicializa a vida dos jogadores (lifepl1 e 2) que servira de criterio de parada para o jogo */
        lifepl1 = lifepl1 + (Embarc[i].tam * Embarc[i].qtd);
    
    lifepl2 = lifepl1;      /* Fim da inicializacao das vidas */
    
    bool = 0;   /* Define a variavel bool = 0 para garantir a entrada no laco a seguir */
        
    while (bool != 1) { /* Laco para evitar que um jogador veja o tabuleiro do outro */
        printf("Voce eh o player 1? (Sim: 1| Nao: 0)\n");
        scanf("%i", &bool);
            
        teste(bool, 0, 1, 1); } /* Testa a validade da entrada do usuario */
    
    while (lifepl1 > 0 && lifepl2 > 0) {                                                /* Laco que roda o jogo, em si */
        lifepl2 = brief1(player1, player2, pontx1, ponty1, pontlife1, linhas, colunas, lifepl2);   /* Chama a funcao brief1 para que o jogador 1 faca sua jogada */
        
        if (lifepl2 == 0)                                                               /* Teste para evitar que o jogador 2 jogue uma rodada com todas suas embarcacoes afundadas */
            break;
        
        bool = 0;                                                                       /* Define a variavel bool = 0 para garantir a entrada no laco a seguir */
        
        while (bool != 1) {                                                             /* Laco para evitar que um jogador veja o tabuleiro do outro */
            printf("Voce eh o player 2? (Sim: 1| Nao: 0)\n");
            scanf("%i", &bool);
            
            teste(bool, 0, 1, 1); }                                                     /* Testa a validade da entrada do usuario */
        
        for(i = 1; i < 120; i++)                                                        /* Abre um espaco para garantir que um jogador nao veja o tabuleiro do outro */
            printf("\n");
            
        lifepl1 = brief2(player1, player2, pontx2, ponty2, pontlife2, linhas, colunas, lifepl1);   /* Chama a funcao brief1 para que o jogador 2 faca sua jogada */
        
        bool = 0;                                                                       /* Define a variavel bool = 0 para garantir a entrada no laco a seguir */
        
        while (bool != 1) {
            printf("Voce eh o player 1? (Sim: 1| Nao: 0)\n");                           /* Laco para evitar que um jogador veja o tabuleiro do outro */
            scanf("%i", &bool);
            teste(bool, 0, 1, 1); }                                                     /* Testa a validade da entrada do usuario */
        
        for(i = 1; i < 120; i++)                                                        /* Abre um espaco para garantir que um jogador nao veja o tabuleiro do outro */
            printf("\n");
            
    }
    
    free(player1);  /* Processo para liberar a memoria alocada */
    free(player2);
    
    for (i = 0; i < colunas; i++) {
        for (j = 0; j < linhas; j++) {
            free(player1[i][j]);
            free(player2[i][j]); }
        
        free(player1[i]);
        free(player2[i]);
    }               /* Fim do processo de liberacao de memoria */
    
    if (lifepl1 > lifepl2)                                  /* Testa qual jogador venceu e imprime uma mensagem de vitoria */
        printf("\n\nParabens Player 1! Voce venceu!\n");
    else
        printf("\n\nParabens Player 2! Voce venceu!\n");
    
} /* -----Fim da funcao batalha----- */

void almirante (int colunas, int linhas, int ***player) {   /* Funcao almirante: Permite que o jogador posicione suas embarcacoes manualmente */
    
    int i, j, k, direcao, qtd, x, y;    /* i, j, k sao variaveis de contagem; 'direcao' recebe valores 0 (horizontal) ou 1 (vertical); 'qtd' recebe a quantidade de cada uma das embarcacoes; x, y recebe a entrada de coluna e linha, respectivamente */
    int flag = 1;                       /* flag para uma serie de testes de validez */
    
    for (i = 0; i < colunas; i++)       /* Inicializa o tabuleiro */
        for (j = 0; j < linhas; j++) {
            player[j][i][0] = '~';
            player[j][i][1] = 0;
        }                               /* Fim da inicializacao do tabuleiro */
    
    i = 0;                  /* Reinicializa a variavel de contagem para o laco a seguir */
    qtd = Embarc[i].qtd;    /* Inicializa a variavel com o valor da quantidade de porta-avioes */
    
    while (i < 5) {         /* Inicializa o laco para posicionar cada uma das embarcacoes */
        printf("  ");                       /* Impressao do tabuleiro */
        
        for (j = 1; j <= colunas; j++)
            printf("|%2i", j);
        printf("|\n");
        
        for (j = 0; j < linhas; j++) {
            printf("%2i", j+1);
            
            for (k = 0; k < colunas; k++)
                printf("|%2c", player[k][j][0]);
            
            printf("|\n");
        }                                   /* Fim da impressao do tabuleiro */
        
        printf("\nDeseja posicionar seu %s na horizontal (0) ou vertical (1)? ", Embarc[i].classe); /* Pergunta e recebe a direcao de posicionamento da embarcacao em questao */
        scanf("%i", &direcao);
        
        teste(direcao, 0, 1, 1);    /* Testa a validade da entrada do usuario */
        
        printf("O %s ocupa %i quadrantes. Em quais coordenadas voce deseja\nposiciona-lo? (O navio sera posicionado nas coordenadas desejadas e ocupara as\ncoordenadas subsequentes de ", Embarc[i].classe, Embarc[i].tam);
        printf("acordo com a sua escolha de direcao)\n");   /* Imprime intrucoes relativas ao posicionamento da embarcacao */
        
        while (flag != 0) {
            printf("Em qual linha deseja posicionar sua embarcacao? ");     /* Pergunta e recebe a linha onde a embarcacao sera posicionada */
            scanf("%i", &y);
            printf("Em qual coluna deseja posicionar sua embarcacao? ");    /* Pergunta e recebe a coluna onde a embarcacao sera posicionada */
            scanf("%i", &x);
        
            teste(y, 1, linhas, 2);         /* Verifica a validez da variavel y */
        
            teste(x, 1, colunas, 2);        /* Verifica a validez da variavel x */
        
            x = x-1;    /* Ajustes para adequar a matriz */
            y = y-1;
            flag = 1;   /* Levanta a flag caso ela tenha sido mudada numa iteracao anterior */
        
            if (direcao == 0) {                     /* Caso a direcao seja horizontal */
                if (x+Embarc[i].tam > colunas) {    /* Testa se a embarcacao ficaria parcialmente fora do tabuleiro ao ser posicionada */
                    printf("Sua entrada eh invalida, porque parte de seu navio ficaria fora do tabuleiro.\nEscolha outras coordenadas para ele. (Os mesmos criterios se aplicam.)\n");
                    flag = 2; }
                else {                              /* Testa se a embarcacao ficaria em um espaco ja ocupado por outra e evita chamar uma regiao da memoria nao alocada */
                    for(j = x; j < x+Embarc[i].tam; j++)
                        if (player[j][y][0] != '~') {
                            printf("Sua entrada eh invalida, porque seu navio ficaria numa posicao ja ocupada por\noutro. Escolha outras coordenadas para ele. (Os mesmos criterios se aplicam.)\n");
                            flag = 2;
                            break; }
                }
                
                if (flag != 2) {    /* Caso a flag nao tenha sido levantada pelos testes anteriores */
                    flag = 0;       /* Define a flag como 0 para sair do laco */
                    
                    for(j = x; j < x+Embarc[i].tam; j++) {  /* Posiciona a embarcacao de acordo com o desejado */
                        player[j][y][0] = Embarc[i].desig;
                        player[j][y][2] = direcao;
                    }
                    
                    qtd--;          /* Diminui em uma unidade o numero de embarcacoes */
                }                   /* Fim do posicionamento da embarcacao */
            }
            else {                                  /* Caso a direcao seja vertical */
                if (y+Embarc[i].tam > linhas) {     /* Testa se a embarcacao ficaria parcialmente fora do tabuleiro ao ser posicionada */
                    printf("Sua entrada eh invalida, porque seu navio ficaria fora do tabuleiro. Escolha\noutras coordenadas para ele. (Os mesmos criterios se aplicam.)\n");
                    flag = 2; }
                else {                              /* Testa se a embarcacao ficaria em um espaco ja ocupado por outra e evita chamar uma regiao da memoria nao alocada */
                    for(j = y; j < y+Embarc[i].tam; j++)
                        if (player[x][j][0] != '~') {
                            printf("Sua entrada eh invalida, porque seu navio ficaria numa posicao ja ocupada por\noutro. Escolha outras coordenadas para ele. (Os mesmos criterios se aplicam.)\n");
                            flag = 2;
                            break; }
                }
                
                if (flag != 2) {    /* Caso a flag nao tenha sido levantada pelos testes anteriores */
                    flag = 0;       /* Define a flag como 0 para sair do laco */
                    
                    for(j = y; j < y+Embarc[i].tam; j++)    /* Posiciona a embarcacao de acordo com o desejado */
                        player[x][j][0] = Embarc[i].desig;
                    
                    qtd--;          /* Diminui em uma unidade o numero de embarcacoes */
                }                   /* Fim do posicionamento da embarcacao */
            }
        }
    flag = 1;       /* Reseta a flag */
    if (qtd == 0) {             /* Caso a quantidade de embarcacoes chegue a zero */
        i++;                    /* Acrescenta uma unidade ao contador */
        qtd = Embarc[i].qtd; }  /* Muda a quantidade de acordo com a classe da embarcacao */
    }
    
    for(i = 1; i < 120; i++)    /* Abre um espaco para garantir que um jogador nao veja o tabuleiro do outro */
        printf("\n");

}   /* -----Fim da funcao almirante----- */

void marinheiro (int colunas, int linhas, int ***player) {  /* Funcao marinheiro: posiciona as embarcacoes de forma aleatoria no tabuleiro */
    
    int i, j, x, y, qtd;    /* i, j sao variaveis de contagem; x, y recebem as coordenadas de linhas e colunas; qtd recebe a quantidade numerica de cada embarcacao */
    int  flag = 0;          /* flag eh utilizada nos testes de poscionamento */
    
    for (i = 0; i < colunas; i++)       /* Inicializa o tabuleiro */
        for (j = 0; j < linhas; j++) {
            player[j][i][0] = '~';
            player[j][i][1] = 0;
        }                               /* Fim da incializacao do tabuleiro */
    
    i = 0;                  /* Define a variavel i como 0 para o laco a seguir */
    qtd = Embarc[i].qtd;    /* Define a variavel qtd como a quantidade de porta-avioes */
    
    while (i < 5) {     /* Inicia o laco para posicionar cada uma das embarcacoes */
        
        x = rand() % colunas;   /* Define a variavel x de acordo com o numero de colunas */
        y = rand() % linhas;    /* Define a variavel y de acordo com o numero de linhas */
        flag = 0;
        
        if ((x%2) == 0)         /* Caso x seja par, a embarcacao sera posicionada na horizontal */
            if(x + Embarc[i].tam < colunas) {           /* Testa se a embarcacao ficaria parcialmente fora do tabuleiro ao ser posicionada e evita chamar uma regiao da memoria nao alocada */
                for(j = x; j < x+Embarc[i].tam; j++)    /* Testa se a embarcacao ficaria em um espaco ja ocupado por outra */
                        if (player[j][y][0] != '~')
                            flag = 1;                   /* Levanta a flag caso a embarcacao fique em um espaco ja ocupado por outra */
                
                if (flag == 0) {                            /* Caso a flag nao tenha sido levantada pelo teste anterior, posiciona a embarcacao utilizando o laco for */
                    for(j = x; j < x+Embarc[i].tam; j++)
                        player[j][y][0] = Embarc[i].desig;
                    qtd--;                                  /* Reduz em uma unidade a variavel qtd */
                }                                           /* Fim do posicionamento da embarcacao em questao */
            }                                           /* Fim do primeiro teste de posicionamento */
        
        else                    /* Caso x seja impar, a embarcacao sera posicionada na vertical */
            if(y + Embarc[i].tam < linhas) {            /* Testa se a embarcacao ficaria parcialmente fora do tabuleiro ao ser posicionada e evita chamar uma regiao da memoria nao alocada */
                for(j = y; j < y+Embarc[i].tam; j++)    /* Testa se a embarcacao ficaria em um espaco ja ocupado por outra */
                        if (player[x][j][0] != '~')
                            flag = 1;                   /* Levanta a flag caso a embarcacao fique em um espaco ja ocupado por outra */
                
                if (flag == 0) {                            /* Caso a flag nao tenha sido levantada pelo teste anterior, posiciona a embarcacao utilizando o laco for */
                    for(j = y; j < y+Embarc[i].tam; j++)
                        player[x][j][0] = Embarc[i].desig;
                    
                    qtd--;                                  /* Reduz em uma unidade a variavel qtd */
                }                                           /* Fim do posicionamento da embarcacao em questao */
            }                                           /* Fim do primeiro teste de posicionamento */
        
        if (qtd == 0) {             /* Caso a quantidade de embarcacoes chegue a zero */
            i++;                    /* Acrescenta uma unidade ao contador */
            qtd = Embarc[i].qtd; }  /* Muda a quantidade de acordo com a classe da embarcacao */
    }                   /* Fim do laco para posicionar as embarcacoes */
    
}   /* -----Fim da funcao marinheiro----- */

int brief1 (int ***player1, int ***player2, int *lastx, int *lasty, int *pontlife, int linhas, int colunas, int lifepl) {  /* Funcao brief1: Executa o jogo em si para o jogador 1 */
    
    int i, j;       /* Variaveis de contagem */
    int bool = 0;   /* Variavel para evitar que um jogador veja o tabuleiro do outro */
    
    while (bool != 1) { /* Laco para evitar que um jogador veja o tabuleiro do outro */
        printf("Mesmo? (Sim: 1| Nao: 0)\n");
        scanf("%i", &bool);
            
        teste(bool, 0, 1, 1); } /* Fim do laco com um teste da validade da entrada do usuario */
            
    printf("  ");                       /* Impressao do tabuleiro do jogador 1*/
    for (j = 1; j <= colunas; j++)
        printf("|%2i", j);
        
    printf("|\n");
        
    for (j = 0; j < linhas; j++) {
        printf("%2i", j+1);
            
        for (int k = 0; k < colunas; k++) {
            if (player1[j][k][0] != '~' && player1[j][k][1] == 1)   /* Caso o quadrante em questao possua uma embarcacao e ja tenha sido atirado, imprime o caractere '*' */
                printf("| *");
            else                                                    /* Caso contrario, imprime a propria designacao */    
            printf("|%2c", player1[j][k][0]); }
        
        if (j == 1)
            printf("|\t Ultima jogada (L): %2i\n", *lasty+1);   /* Imprime a ultima jogada do player ao lado de seu tabuleiro */
        
        else if (j == 2)
            printf("|\t Ultima jogada (C): %2i\n", *lastx+1);   /* Imprime a ultima jogada do player ao lado de seu tabuleiro */
        
        else if (j == 3)
            printf("|\t Seu life: %2i\n", *pontlife);       /* Imprime o life do player ao lado de seu tabuleiro */
        
        else if (j == 4)
            printf("|\t Life do adversario: %2i\n", lifepl);/* Imprime o life do adversario ao lado do tabuleiro  do player*/
        
        else                                                /* Imprime o caractere '|' e a quebra de linha nas linhas seguintes */
            printf("|\n");
    }                                           /* Fim da impressao */
    printf("\nSeu tabuleiro eh o de cima\n\n"); /* Impressao de uma pequena informacao pertinente */
        
    printf("  ");                       /* Impressao do tabuleiro do jogador adversario*/
        
    for (j = 1; j <= colunas; j++)
        printf("|%2i", j);
        
    printf("|\n");
        
    for (j = 0; j < linhas; j++) {
        printf("%2i", j+1);
            
        for (int k = 0; k < colunas; k++) {
            if (player2[j][k][1] == 0)  /* Caso o jogador nao tenha atirado no quadrante em questao, ele vera um caractere '?' */
                printf("| ?");
            else                        /* Caso contrario, ele vera o elemento guardado no quadrante em questao */
                printf("|%2c", player2[j][k][0]);
        }
        printf("|\n");
    }                                   /* Fim da impressao do tabuleiro do jogador adversario */
        
    printf("\n Proxima jogada: (linha)\t");     /* Pergunta e recebe a proxima linha a ser atirada */
    scanf("%i", lasty);
    
    printf("\n Proxima jogada: (coluna)\t");    /* Pergunta e recebe a proxima coluna a ser atirada */
    scanf("%i", lastx);
    
        teste(*lasty, 1, linhas, 2);    /* Testa a validade da entrada do usuario */
        teste(*lastx, 1, colunas, 2);   /* Testa a validade da entrada do usuario */
        
    *lasty = *lasty - 1;    /* Ajusta a entrada do usuario para caber na matriz */
    *lastx = *lastx - 1;    /* Ajusta a entrada do usuario para caber na matriz */
        
    while(player2[*lasty][*lastx][1] == 1) {    /* Laco para garantir que o jogador nao atire duas vezes no mesmo quadrante */
        printf("Voce ja atirou nesse quadrante. Escolha outro:\n");
        printf("\n Proxima jogada: (linha)\t");     /* Pergunta e recebe a proxima linha a ser atirada */
        scanf("%i", lasty);
    
        printf("\n Proxima jogada: (coluna)\t");    /* Pergunta e recebe a proxima coluna a ser atirada */
        scanf("%i", lastx);
            
        teste(*lasty, 1, linhas, 2);            /* Testa a validade da entrada do usuario */
        teste(*lastx, 1, colunas, 2);           /* Testa a validade da entrada do usuario */
            
        *lasty = *lasty - 1;                    /* Ajuste das entradas do usuario para seu uso na matriz */
        *lastx = *lastx - 1; }                  /* Fim do laco */
            
    player2[*lasty][*lastx][1] = 1;             /* Define o quadrante como "atirado" */
    
    for (j = 1; j < 20; j++)
        printf("\n");   /* Quebra de linha tatica */
    
    printf("  ");                       /* Impressao do tabuleiro do jogador adversario*/
        
    for (j = 1; j <= colunas; j++)
        printf("|%2i", j);
        
    printf("|\n");
        
    for (j = 0; j < linhas; j++) {
        printf("%2i", j+1);
            
        for (int k = 0; k < colunas; k++) {
            if (player2[j][k][1] == 0)  /* Caso o jogador nao tenha atirado no quadrante em questao, ele vera um caractere '?' */
                printf("| ?");
            else                        /* Caso contrario, ele vera o elemento guardado no quadrante em questao */
                printf("|%2c", player2[j][k][0]);
        }
        printf("|\n");
    }                                   /* Fim da impressao do tabuleiro do jogador adversario */
        
    if (player2[*lasty][*lastx][0] == '~')  /* Imprime o resultado do tiro (agua) */
        printf("Voce acertou a agua, marujo! Mire melhor a proxima!\n");
        
    else {                                  /* Imprime o resultado do tiro (embarcacao) */
        printf("Ahoy! Voce acertou alguma coisa ali!\n");
        lifepl--; }                         /* Reduz a vida do jogador que levou o tiro */

return(lifepl); }   /* Retorna o valor da vida do jogador */ /* ----Fim da funcao brief1----- */
    
int brief2 (int ***player1, int ***player2, int *lastx, int *lasty, int *pontlife, int linhas, int colunas, int lifepl) {  /* Funcao brief1: Executa o jogo em si para o jogador 1 */
    
    int i, j;       /* Variaveis de contagem */
    int bool = 0;   /* Variavel para evitar que um jogador veja o tabuleiro do outro */
    
    while (bool != 1) { /* Laco para evitar que um jogador veja o tabuleiro do outro */
        printf("Mesmo? (Sim: 1| Nao: 0)\n");
        scanf("%i", &bool);
            
        teste(bool, 0, 1, 1); } /* Fim do laco com um teste da validade da entrada do usuario */
            
    printf("  ");                       /* Impressao do tabuleiro do jogador atual*/
    for (j = 1; j <= colunas; j++)
        printf("|%2i", j);
        
    printf("|\n");
        
    for (j = 0; j < linhas; j++) {
        printf("%2i", j+1);
            
        for (int k = 0; k < colunas; k++) {
            if (player2[j][k][0] != '~' && player2[j][k][1] == 1)   /* Caso o quadrante em questao possua uma embarcacao e ja tenha sido atirado, imprime o caractere '*' */
                printf("| *");
            else                                                    /* Caso contrario, imprime a propria designacao */
            printf("|%2c", player2[j][k][0]); }
        
        if (j == 1)
            printf("|\t Ultima jogada (L): %2i\n", *lasty+1);   /* Imprime a ultima jogada do player ao lado de seu tabuleiro */
        
        else if (j == 2)
            printf("|\t Ultima jogada (C): %2i\n", *lastx+1);   /* Imprime a ultima jogada do player ao lado de seu tabuleiro */
            
        else if (j == 3)
            printf("|\t Seu life: %2i\n", *pontlife);       /* Imprime o life do player ao lado de seu tabuleiro */
        
        else if (j == 4)
            printf("|\t Life do adversario: %2i\n", lifepl);/* Imprime o life do adversario ao lado do tabuleiro  do player*/
        
        else
            printf("|\n");                                  /* Imprime o caractere '|' e a quebra de linha nas linhas seguintes */
    }                                           /* Fim da impressao */
    printf("\nSeu tabuleiro eh o de cima\n\n"); /* Impressao de uma pequena informacao pertinente */
        
    printf("  ");                       /* Impressao do tabuleiro do jogador adversario*/
        
    for (j = 1; j <= colunas; j++)
        printf("|%2i", j);
        
    printf("|\n");
        
    for (j = 0; j < linhas; j++) {
        printf("%2i", j+1);
            
        for (int k = 0; k < colunas; k++) {
            if (player1[j][k][1] == 0)              /* Caso o jogador nao tenha atirado no quadrante em questao, ele vera um caractere '?' */
                printf("| ?");
            else                                    /* Caso contrario, ele vera o elemento guardado no quadrante em questao */
                printf("|%2c", player1[j][k][0]);
        }
        printf("|\n");
    }                               /* Fim da impressao do tabuleiro do jogador adversario */
    
    printf("\n Proxima jogada: (linha)\t");     /* Pergunta e recebe a proxima linha a ser atirada */
    scanf("%i", lasty);
    
    printf("\n Proxima jogada: (coluna)\t");    /* Pergunta e recebe a proxima linha a ser atirada */
    scanf("%i", lastx);
        
        teste(*lasty, 1, linhas, 2);    /* Testa a validade da entrada do usuario */
        teste(*lastx, 1, colunas, 2);   /* Testa a validade da entrada do usuario */
        
    *lasty = *lasty - 1;    /* Ajuste da entrada do usuario para o uso na matriz */
    *lastx = *lastx - 1;    /* Ajuste da entrada do usuario para o uso na matriz */
        
    while(player1[*lasty][*lastx][1] == 1) {
        printf("Voce ja atirou nesse quadrante. Escolha outro:\n");
        printf("\n Proxima jogada: (linha)\t");     /* Pergunta e recebe a proxima linha a ser atirada */
        scanf("%i", lasty);
    
        printf("\n Proxima jogada: (coluna)\t");    /* Pergunta e recebe a proxima linha a ser atirada */
        scanf("%i", lastx);
            
        teste(*lasty, 1, linhas, 2);    /* Testa a validade da entrada do usuario */
        teste(*lastx, 1, colunas, 2);   /* Testa a validade da entrada do usuario */
            
        *lasty = *lasty - 1;            /* Ajuste das entradas do usuario para o uso na matriz */
        *lastx = *lastx - 1; }          /* Fim do laco */
            
    player1[*lasty][*lastx][1] = 1;     /* Define o quadrante como "atirado" */
    
    for (j = 1; j < 20; j++)
        printf("\n");   /* Quebra de linha tatica */
    
    printf("  ");                       /* Impressao do tabuleiro do jogador adversario*/
        
    for (j = 1; j <= colunas; j++)
        printf("|%2i", j);
        
    printf("|\n");
        
    for (j = 0; j < linhas; j++) {
        printf("%2i", j+1);
            
        for (int k = 0; k < colunas; k++) {
            if (player1[j][k][1] == 0)              /* Caso o jogador nao tenha atirado no quadrante em questao, ele vera um caractere '?' */
                printf("| ?");
            else                                    /* Caso contrario, ele vera o elemento guardado no quadrante em questao */
                printf("|%2c", player1[j][k][0]);
        }
        printf("|\n");
    }                               /* Fim da impressao do tabuleiro do jogador adversario */
        
    if (player1[*lasty][*lastx][0] == '~')  /* Imprime o resultado do tiro (agua) */
        printf("Voce acertou a agua, marujo! Mire melhor a proxima!\n");
        
    else {                                  /* Imprime o resultado do tiro (embarcacao) */
        printf("Ahoy! Voce acertou alguma coisa ali!\n");
        lifepl--; }                         /* Reduz a vida do jogador que levou o tiro */

return(lifepl); }   /* Retorna o valor da vida do jogador */ /* ----Fim da funcao brief2----- */
