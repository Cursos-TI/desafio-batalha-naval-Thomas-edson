#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define NUM_NAVIOS 3

int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

// Estrutura para representar um navio
typedef struct {
    int linha;
    int coluna;
    char orientacao; // 'H' para horizontal, 'V' para vertical
} Navio;

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro() {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se é possível posicionar o navio (dentro dos limites e sem sobreposição)
int podePosicionar(Navio n) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int linha = n.linha + (n.orientacao == 'V' ? i : 0);
        int coluna = n.coluna + (n.orientacao == 'H' ? i : 0);

        // Verifica se está fora dos limites
        if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO)
            return 0;

        // Verifica se já há um navio nessa posição
        if (tabuleiro[linha][coluna] == 3)
            return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(Navio n) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int linha = n.linha + (n.orientacao == 'V' ? i : 0);
        int coluna = n.coluna + (n.orientacao == 'H' ? i : 0);
        tabuleiro[linha][coluna] = 3;
    }
}

// Exibe o tabuleiro no console
void exibirTabuleiro() {
    printf("\nTabuleiro final:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Navio navios[NUM_NAVIOS];
    inicializarTabuleiro();

    printf("Posicione %d navios de tamanho %d (em um tabuleiro %dx%d):\n", NUM_NAVIOS, TAM_NAVIO, TAM_TABULEIRO, TAM_TABULEIRO);

    for (int i = 0; i < NUM_NAVIOS; i++) {
        int valido = 0;

        while (!valido) {
            printf("\nNavio %d:\n", i + 1);
            printf("Digite a linha inicial (0 a %d): ", TAM_TABULEIRO - 1);
            scanf("%d", &navios[i].linha);

            printf("Digite a coluna inicial (0 a %d): ", TAM_TABULEIRO - 1);
            scanf("%d", &navios[i].coluna);

            printf("Digite a orientação (H para horizontal, V para vertical): ");
            scanf(" %c", &navios[i].orientacao);

            if (navios[i].orientacao != 'H' && navios[i].orientacao != 'V') {
                printf("Orientação inválida! Use H ou V.\n");
                continue;
            }

            if (podePosicionar(navios[i])) {
                posicionarNavio(navios[i]);
                valido = 1;
            } else {
                printf("Posição inválida ou navio sobreposto. Tente novamente.\n");
            }
        }
    }

    exibirTabuleiro();
    return 0;
}