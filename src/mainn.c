#include "../include/input.h"
#include "../include/logic.h"

int main(int argc, char *argv[]) {
    
    char *filename = processar_entrada(argc, argv);
    menu(filename);


    return 0;
}