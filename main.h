#ifndef MAIN
#define MAIN

    #include <stdio.h>

    #define rgtLength_t 37

    struct registerFields {
            char name[10];
            char brand[10];
            char ean13[13];
            char price[4];
    };

    const char FILENAME[] = "Registers.txt";

    void newRegister(void);
    void readRegister(int);
    void action(void);
    int getTamanho(void);
    int exists(const char*);
#endif
