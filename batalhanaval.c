#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TAMANHO 10
#define NAVIOS 8
#define AGUA '~'
#define PORTA_AVIOES 'P'
#define NAVIO_TANQUE 'T'
#define CONTRATORPEDEIRO 'C'
#define SUBMARINO 'S'
#define ERRO 'E'
#define ACERTO 'A'

void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
    printf("   ");
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%d  ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAMANHO; j++)
        {
            printf("%c  ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            tabuleiro[i][j] = AGUA;
        }
    }
}

int posicionarNavio(char tabuleiro[TAMANHO][TAMANHO], char tipo, int tamanho)
{
    int x, y, direcao;
    do
    {
        x = rand() % TAMANHO;
        y = rand() % TAMANHO;
        direcao = rand() % 2; // 0 para horizontal, 1 para vertical
    } while (!verificarPosicao(tabuleiro, x, y, direcao, tamanho));

    if (direcao == 0)
    {
        for (int i = 0; i < tamanho; i++)
        {
            tabuleiro[x][y + i] = tipo;
        }
    }
    else
    {
        for (int i = 0; i < tamanho; i++)
        {
            tabuleiro[x + i][y] = tipo;
        }
    }

    return 1;
}

int verificarPosicao(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int direcao, int tamanho)
{
    if (direcao == 0)
    {
        if (y + tamanho > TAMANHO)
        {
            return 0;
        }
        for (int i = 0; i < tamanho; i++)
        {
            if (tabuleiro[x][y + i] != AGUA)
            {
                return 0;
            }
        }
    }
    else
    {
        if (x + tamanho > TAMANHO)
        {
            return 0;
        }
        for (int i = 0; i < tamanho; i++)
        {
            if (tabuleiro[x + i][y] != AGUA)
            {
                return 0;
            }
        }
    }
    return 1;
}

/// @brief 
/// @param tabuleiro 
/// @return 
int ataqueHumano(char tabuleiro[TAMANHO][TAMANHO])
{
    int linha, coluna;

    printf("Informe a coordenada do ataque (ex: A1): ");
    scanf(" %c%d", &linha, &coluna);
    linha = toupper(linha);

    if (linha < 'A' || linha >= 'A' + TAMANHO || coluna < 1 || coluna > TAMANHO)
    {
        printf("Coordenadas inválidas!\n");
        return 0;
    }

    if (tabuleiro[linha - 'A'][coluna - 1] == AGUA)
    {
        printf("Você errou!\n");
        tabuleiro[linha - 'A'][coluna - 1] = ERRO;
    }
    else if (tabuleiro[linha - 'A'][coluna - 1] == ACERTO)
    {
        printf("Você já atacou essa posição!\n");
    }
    else
    {
        printf("Você acertou um navio!\n");
        tabuleiro[linha - 'A'][coluna - 1] = ACERTO;
    }

    return 1;
}

int ataqueComputador(char tabuleiro[TAMANHO][TAMANHO], int acertos)
{
    int linha, coluna;

    do
    {
        linha = 'A' + rand() % TAMANHO;
        coluna = rand() % TAMANHO;
    } while (tabuleiro[linha - 'A'][coluna] == ERRO || tabuleiro[linha - 'A'][coluna] == ACERTO);

    if (tabuleiro[linha - 'A'][coluna] == AGUA)
    {
        printf("O computador errou em %c %d!\n", linha, coluna + 1);
        tabuleiro[linha - 'A'][coluna] = ERRO;
    }
    else
    {
        printf("O computador acertou em %c %d!\n", linha, coluna + 1);
        tabuleiro[linha - 'A'][coluna] = ACERTO;
        acertos++;
    }

    return acertos;
}

int main()
{
    char tabuleiroHumano[TAMANHO][TAMANHO];
    char tabuleiroComputador[TAMANHO][TAMANHO];
    int acertosHumano = 0, acertosComputador = 0;
    srand(time(NULL));

    inicializarTabuleiro(tabuleiroHumano);
    inicializarTabuleiro(tabuleiroComputador);

    // Posicione os navios do jogador humano manualmente
    printf("Posicione seus navios:\n");
    for (int i = 0; i < NAVIOS; i++)
    {
        printf("Posicione o navio %d/%d\n", i + 1, NAVIOS);
        imprimirTabuleiro(tabuleiroHumano);
        char tipo;
        int tamanho;

        if (i == 0)
        {
            tipo = PORTA_AVIOES;
            tamanho = 5;
        }
        else if (i < 3)
        {
            tipo = NAVIO_TANQUE;
            tamanho = 4;
        }
        else if (i < 5)
        {
            tipo = CONTRATORPEDEIRO;
            tamanho = 3;
        }
        else
        {
            tipo = SUBMARINO;
            tamanho = 2;
        }

        if (!posicionarNavio(tabuleiroHumano, tipo, tamanho))
        {
            printf("Posição inválida! Tente novamente.\n");
            i--;
        }
    }

    // Posicione os navios do computador aleatoriamente
    for (int i = 0; i < NAVIOS; i++)
    {
        char tipo;
        int tamanho;

        if (i == 0)
        {
            tipo = PORTA_AVIOES;
            tamanho = 5;
        }
        else if (i < 3)
        {
            tipo = NAVIO_TANQUE;
            tamanho = 4;
        }
        else if (i < 5)
        {
            tipo = CONTRATORPEDEIRO;
            tamanho = 3;
        }
        else
        {
            tipo = SUBMARINO;
            tamanho = 2;
        }

        posicionarNavio(tabuleiroComputador, tipo, tamanho);
    }

    while (1)
    {
        printf("Seu tabuleiro:\n");
        imprimirTabuleiro(tabuleiroHumano);
        printf("\nTabuleiro do Computador:\n");
        imprimirTabuleiro(tabuleiroComputador);

        if (!ataqueHumano(tabuleiroComputador))
        {
            continue;
        }

        if (acertosHumano == NAVIOS)
        {
            printf("Você venceu! 🎆\n");
            imprimirTabuleiro(tabuleiroComputador);
            break;
        }

        acertosComputador = ataqueComputador(tabuleiroHumano, acertosComputador);

        if (acertosComputador == NAVIOS)
        {
            printf("O Computador venceu! 🎆\n");
            imprimirTabuleiro(tabuleiroComputador);
            break;
        }
    }

    return 0;
}
