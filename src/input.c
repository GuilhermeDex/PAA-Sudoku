#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/input.h"


void le_arquivo(char *nome, int mat[][9][9], int *sudoku_count) {
    FILE *arq = fopen(nome, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nome);
        exit(1);
    }

    int i, j;
    char valor;
    *sudoku_count = 0;

    while (1) {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                if (fscanf(arq, " %c", &valor) != 1) {
                    if (i == 0 && j == 0 && *sudoku_count == 0) {
                        fclose(arq);
                        return; // fim do arquivo
                    } else {
                        fclose(arq);
                        return; // fim do ultimo sudoku
                    }
                }
                if (valor == 'v') {
                    mat[*sudoku_count][i][j] = 0; // substitui 'v' por 0
                } else if (valor >= '1' && valor <= '9') {
                    mat[*sudoku_count][i][j] = valor - '0'; // converte caractere para numero inteiro
                } else {
                    printf("Arquivo de entrada contem valores invalidos no Sudoku %d.\n", *sudoku_count + 1);
                    fclose(arq);
                    exit(1);
                }
            }
        }

        (*sudoku_count)++;

        // verifica se ha mais sudokus no arquivo (linhas em branco)
        int c = fgetc(arq);
        if (c == EOF) {
            fclose(arq);
            return;
        } else if (c != '\n' && c != '\r') {
            ungetc(c, arq); // retorna caractere lido ao buffer
        }
    }
}



char *processar_entrada(int argc, char *argv[]) {
    char *filename = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
        case 'f':
            filename = optarg;
            break;
        default:
            fprintf(stderr, "Uso: %s -f <arquivo>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (filename == NULL) {
        fprintf(stderr, "Erro: Nome do arquivo de entrada nao especificado.\n");
        fprintf(stderr, "Uso: %s -f <arquivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return filename;
}


void salvar_sudoku(int mat[][9], int index, FILE *arquivo_saida) {
    fprintf(arquivo_saida, "Sudoku %d resolvido:\n", index + 1);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(arquivo_saida, "%d ", mat[i][j]);
        }
        fprintf(arquivo_saida, "\n");
    }
    fprintf(arquivo_saida, "\n");
}
