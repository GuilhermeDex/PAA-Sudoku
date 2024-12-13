#ifndef INPUT_H
#define INPUT_H


//funcoes para ler e saida dos arquivos
void le_arquivo(char *nome, int mat[][9][9], int *sudoku_count);
char *processar_entrada(int argc, char *argv[]);
void salvar_sudoku(int mat[][9], int index, FILE *arquivo_saida);


#endif