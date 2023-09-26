#include <stdio.h>
#include <string.h>

#define MAX_STRING 100
#define MAX_FILMES 10

typedef struct
{
    char titulo[MAX_STRING];
    char diretor[MAX_STRING];
    int anoLancamento;
    float classificacao;
    int quantidade;
} Filme;

void mostrarFilmes();
Filme cadastrarFilme();
void exibirFilme(int i);

Filme filmes[MAX_FILMES];
int totalFilmes = 0;

void imprimirFilme(Filme filme) {
    printf("Título: %s\n", filme.titulo);
    printf("Diretor: %s\n", filme.diretor);
    printf("Ano de Lançamento: %d\n", filme.anoLancamento);
    printf("Classificação: %.1f\n", filme.classificacao);
    printf("Quantidade em estoque: %d\n", filme.quantidade);
}

int buscarFilmePorNomeEDiretor(Filme filmes[], int numFilmes, char nome[], char diretor[]) {
    for (int i = 0; i < numFilmes; i++) {
        if (strcmp(filmes[i].titulo, nome) == 0 && strcmp(filmes[i].diretor, diretor) == 0) {
            return i;
        }
    }
    return -1; // Filme não encontrado
}

void alugarFilme(Filme filmes[], int index) {
    if (index >= 0) {
        if (filmes[index].quantidade > 0) {
            filmes[index].quantidade--;
            printf("Filme \"%s\" alugado com sucesso!\n", filmes[index].titulo);
        } else {
            printf("Desculpe, este filme está fora de estoque.\n");
        }
    } else {
        printf("Filme não encontrado.\n");
    }
}

void devolverFilme(Filme filmes[], int index, int dias) {
    if (index >= 0) {
        float valorTotal = filmes[index].classificacao * dias;
        filmes[index].quantidade++;
        printf("Filme \"%s\" devolvido com sucesso!\n", filmes[index].titulo);
        printf("Valor a ser pago: R$ %.2f\n", valorTotal);
    } else {
        printf("Filme não encontrado.\n");
    }
}

int main()
{
    int opcao, index;

    do
    {
        printf("\nLocadora de Filmes\n");
        printf("1. Cadastrar Filme\n");
        printf("2. Ver Filmes Cadastrados\n");
        printf("3. Ver Dados de um filme\n");
        printf("4. Buscar filme por nome e/ou diretor\n");
        printf("5. Alugar filme\n");
        printf("6. Devolver filme\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (totalFilmes < MAX_FILMES)
            {
                filmes[totalFilmes] = cadastrarFilme();
                totalFilmes++;
            }
            else
            {
                printf("Quantidade máxima de filmes cadastrada\n");
            }
            break;
        case 2:
            mostrarFilmes();
            break;
        case 3:
            printf("Informe o índice do filme que você deseja: ");
            scanf("%d", &index);
            exibirFilme(index);
            break;
        case 4:
            char nome[50];
            char diretor[50];
            printf("Digite o nome do filme: ");
            scanf(" %[^\n]s", nome);
            printf("Digite o nome do diretor: ");
            scanf(" %[^\n]s", diretor);
            index = buscarFilmePorNomeEDiretor(filmes, totalFilmes, nome, diretor);
            if (index >= 0) {
                imprimirFilme(filmes[index]);
            } else {
                printf("Filme não encontrado.\n");
            }
            break;
        case 5:
            char nomeAluguel[50];
            char diretorAluguel[50];
            printf("Digite o nome do filme que deseja alugar: ");
            scanf(" %[^\n]s", nomeAluguel);
            printf("Digite o nome do diretor do filme: ");
            scanf(" %[^\n]s", diretorAluguel);
            index = buscarFilmePorNomeEDiretor(filmes, totalFilmes, nomeAluguel, diretorAluguel);
            alugarFilme(filmes, index);
            break;
        case 6:
            char nomeDevolucao[50];
            char diretorDevolucao[50];
            int dias;
            printf("Digite o nome do filme que deseja devolver: ");
            scanf(" %[^\n]s", nomeDevolucao);
            printf("Digite o nome do diretor do filme: ");
            scanf(" %[^\n]s", diretorDevolucao);
            index = buscarFilmePorNomeEDiretor(filmes, totalFilmes, nomeDevolucao, diretorDevolucao);
            if (index >= 0) {
                printf("Quantos dias você manteve o filme alugado: ");
                scanf("%d", &dias);
                devolverFilme(filmes, index, dias);
            } else {
                printf("Filme não encontrado.\n");
            }
            break;
        case 7:
            printf("Obrigado por usar a Locadora de Filmes! Volte sempre.\n");
            break;
        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 7);

    return 0;
}

Filme cadastrarFilme()
{
    Filme f;
    getchar();

    printf("\n--- Cadastro de Filme ---\n");
    printf("Informe o título do filme: ");
    fgets(f.titulo, MAX_STRING, stdin);
    f.titulo[strcspn(f.titulo, "\n")] = '\0';

    printf("Informe o diretor do filme: ");
    fgets(f.diretor, MAX_STRING, stdin);
    f.diretor[strcspn(f.diretor, "\n")] = '\0';

    printf("Informe o ano de lançamento do filme: ");
    scanf("%d", &f.anoLancamento);

    printf("Informe a classificação do filme (0.0 a 10.0): ");
    scanf("%f", &f.classificacao);

    printf("Informe a quantidade de cópias em estoque: ");
    scanf("%d", &f.quantidade);

    return f;
}

void exibirFilme(int i)
{
    if (i >= 0 && i < totalFilmes) {
        imprimirFilme(filmes[i]);
    } else {
        printf("Filme não encontrado.\n");
    }
}

void mostrarFilmes()
{
    printf("\n--- Lista de Filmes ---\n");

    if (totalFilmes == 0)
    {
        printf("Nenhum filme foi cadastrado ainda!\n");
    }
    else
    {
        for (int i = 0; i < totalFilmes; i++)
        {
            printf("Filme %d:\n", i + 1);
            imprimirFilme(filmes[i]);
            printf("\n");
        }
    }
}
