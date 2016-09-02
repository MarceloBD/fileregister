#ifndef MAIN
#define MAIN

    #include <stdio.h>

    #define fileName "Registros.txt"
    #define tamRegistro 37

    struct registerFields {
            char name[10];
            char brand[10];
            char ean13[13];
            char price[4];
    };


    void newRegister(void); //Cria novo cadastro
    void readRegister(int); //Busca o cadastro
    void action(void); // Gerencia açoes de cadastro e de busca
    int getTamanho(void); // Procura tamanho do arquivo
    int exists(const char*); //Verifica se o arquivo existe
#endif
