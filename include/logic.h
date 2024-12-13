#ifndef LOGIC_H
#define LOGIC_H


//Funcoes de resolver o sudoku
void imprimir_sudoku(int mat[][9], int index);
int verificar_linha(int a, int b, int c[][9]);
int verificar_coluna(int a, int b, int c[][9]);
int verificar_bloco(int a, int b, int c, int d[][9]);
int heuristica_possibilidade(int mat[][9], int *linha, int *coluna);
int resolver_heuristica(int mat[][9]);
int resolver_forca_bruta(int mat[][9]);
void menu(char *filename);



#endif