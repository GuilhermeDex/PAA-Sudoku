#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic.h"
#include "input.h"
#include "timer.h"

void imprimir_sudoku(int mat[][9], int index) {
    printf("Sudoku %d:\n", index + 1);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int verificar_linha(int a, int b, int c[][9]) {
    for (int i = 0; i < 9; i++) {
        if (c[a][i] == b) {
            return 0;
        }
    }
    return 1;
}

int verificar_coluna(int a, int b, int c[][9]) {
    for (int i = 0; i < 9; i++) {
        if (c[i][a] == b) {
            return 0;
        }
    }
    return 1;
}

int verificar_bloco(int a, int b, int c, int d[][9]) {
    int start_row = (a / 3) * 3;
    int start_col = (b / 3) * 3;

    for (int i = start_row; i < start_row + 3; i++) {
        for (int j = start_col; j < start_col + 3; j++) {
            if (d[i][j] == c) {
                return 0;
            }
        }
    }
    return 1;
}
// tenta encontrar a celula com menos possibilidade de ser enccaixada
int heuristica_possibilidade(int mat[][9], int *linha, int *coluna) {
    int min_possibilidades = 10;
    int possibilidades, num;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (mat[i][j] == 0) {
                possibilidades = 0;
                for (num = 1; num <= 9; num++) {
                    if (verificar_linha(i, num, mat) && verificar_coluna(j, num, mat) && verificar_bloco(i, j, num, mat)) {
                        possibilidades++;
                    }
                }
                if (possibilidades < min_possibilidades) {
                    min_possibilidades = possibilidades;
                    *linha = i;
                    *coluna = j;
                }
            }
        }
    }

    return (min_possibilidades != 10); // retorna 0 se nao encontrar nenhuma celula
}

int resolver_heuristica(int mat[][9]) {
    int linha, coluna;

    if (!heuristica_possibilidade(mat, &linha, &coluna)) {
        return 1; // sudoku resolvido
    }

    for (int num = 1; num <= 9; num++) {
        if (verificar_linha(linha, num, mat) && verificar_coluna(coluna, num, mat) && verificar_bloco(linha, coluna, num, mat)) {
            mat[linha][coluna] = num;
            if (resolver_heuristica(mat)) {
                return 1;
            }
            mat[linha][coluna] = 0;
        }
    }

    return 0;
}

int resolver_forca_bruta(int mat[][9]) {
    for (int linha = 0; linha < 9; linha++) {
        for (int coluna = 0; coluna < 9; coluna++) {
            if (mat[linha][coluna] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (verificar_linha(linha, num, mat) && verificar_coluna(coluna, num, mat) && verificar_bloco(linha, coluna, num, mat)) {
                        mat[linha][coluna] = num;
                        if (resolver_forca_bruta(mat)) {
                            return 1;
                        }
                        mat[linha][coluna] = 0; // Backtracking
                    }
                }
                return 0; // Falha
            }
        }
    }
    return 1; // Sudoku resolvido
}



int validar_sudoku(int mat[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (mat[i][j] != 0) {
                int num = mat[i][j];
                mat[i][j] = 0; // remove temporariamente para validacao
                if (!verificar_linha(i, num, mat) || !verificar_coluna(j, num, mat) || !verificar_bloco(i, j, num, mat)) {
                    mat[i][j] = num; // restaura o numero
                    return 0; // sudoku invalido
                }
                mat[i][j] = num; // voltam os numeros
            }
        }
    }
    return 1; // sudoku valido
}


void menu(char *filename) {
    int choice;
    printf("Escolha o metodo de resolucao:\n");
    printf("1. Forca Bruta\n");
    printf("2. Heuristica\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);

    int mat[10][9][9]; // armazena ate quantas quantidades querer basta alterar o valor do primeiro vetor( que nesse caso esta como 10)
    int working_mat[9][9]; // matriz para resolver o sudoku atual
    int sudoku_count = 0;

    le_arquivo(filename, mat, &sudoku_count); // carrega os sudokus originais

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s_resolvido.txt", filename);

    FILE *arquivo_saida = fopen(output_filename, "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao criar o arquivo de saida: %s\n", output_filename);
        exit(1);
    }

    for (int k = 0; k < sudoku_count; k++) {
        printf("Sudoku %d lido:\n", k + 1);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d ", mat[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");

        // valida e resolve o Sudoku
        int resolvido = 0;
        if (!validar_sudoku(mat[k])) {
            printf("Sudoku %d eh invalido. Ignorando.\n", k + 1);
            continue;
        }

        memcpy(working_mat, mat[k], sizeof(working_mat)); // Copia apenas o Sudoku atual
        printf("Resolvendo sudoku %d...\n", k + 1);

        start_timer();
        if (choice == 1) {
            resolvido = resolver_forca_bruta(working_mat);
        } else if (choice == 2) {
            resolvido = resolver_heuristica(working_mat);
        } else {
            printf("Escolha invalida. Encerrando programa.\n");
            fclose(arquivo_saida);
            exit(1);
        }
        stop_timer();

        if (resolvido) {
            imprimir_sudoku(working_mat, k);
            salvar_sudoku(working_mat, k, arquivo_saida);
        } else {
            printf("Nao foi possivel resolver o Sudoku %d.\n", k + 1);
        }
        print_timer();
    }

    fclose(arquivo_saida);
    printf("As solucoes foram salvas no arquivo: %s\n", output_filename);
}
