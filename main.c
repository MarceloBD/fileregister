/**
    @author Marcelo Bertoldi Diani
    @version 1.0
**/


/*
*
NAME    (Name of the product)
BRAND   (The company of the product)
EAN13   (Bar code with 13 digits)
PRICE   (Price of the product)
*
*/

#include "main.h"

void main()
{
    interface();
}

void interface()
{
    char optionMain;
    int rgtNumber , i;

    printf("\n1- Want to make a registration?\n2- Want to take a register?\n3- Want to see the registers?\n\n>>");

    scanf("%s" , &optionMain);

    if(optionMain == '1')
    {
        system("cls");
        newRegister();
    }

    else if (optionMain == '2')
    {
        printf("\nType the number of register: ");
        scanf("%d" , &rgtNumber);
        system("cls");
        readRegister(rgtNumber);

        interface();
    }

    else if (optionMain == '3')
    {
        system("cls");
        for(i = 0 ; i < fileLength() + 1 ; i++){
            printf("\nRRN= %d\n" , i);
            readRegister(i);}
        interface();
    }
    else
        return;

}

void newRegister()
{
    int length, RRN;
    char resposta[30];
    struct registerFields novo;

    if(!exists(fileName)){
        FILE *create=fopen(fileName, "w+" );
        fclose(create);
    }

    FILE *fp=fopen( fileName,"r+" );

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);

    RRN= length/tamRegistro;

    printf("\nName (10): ");
    scanf("%s",&novo.name);
    fseek ( fp , 0+tamRegistro*RRN , SEEK_SET );
    fprintf(fp, "%s", novo.name);

    printf("Brand (10): ");
    scanf("%s",&novo.brand);
    fseek ( fp , 10+37*RRN , SEEK_SET );
    fprintf(fp, "%s", novo.brand);

    printf("Ean13 (13): ");
    scanf("%s",&novo.ean13);
    fseek ( fp , 20+tamRegistro*RRN, SEEK_SET );
    fprintf(fp, "%s", novo.ean13);

    printf("Price (4): ");
    scanf("%s",&novo.price);
    fseek ( fp , 33+tamRegistro*RRN, SEEK_SET );
    fprintf(fp, "%s", novo.price);

    fseek ( fp , tamRegistro*(RRN+1), SEEK_SET );
    fprintf(fp, "%c", '0');
    fclose(fp);

    system("cls");
    printf("\nYour register has been realized with RRN = %d\n",RRN);

    interface();
}

void readRegister(int RRN){

    struct registerFields rgtFound;
    int i;

    FILE *fp=fopen( fileName, "r+" );
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    length=(length/tamRegistro)-1;

    if(RRN>length){
        printf("\nInvalid register \n");
        interface();
        return;
    }

    printf("----------------\n");

    fseek(fp,0+RRN*tamRegistro,SEEK_SET);
    printf("Nome: ");
    for(i=0;i<10;i++){
        fscanf(fp,"%c", &rgtFound.name[i]);
        printf("%c",rgtFound.name[i]);
    }

    fseek(fp,10+RRN*tamRegistro,SEEK_SET);
    printf("\nMarca: ");
    for(i=0;i<10;i++){
            fscanf(fp,"%c", &rgtFound.brand[i]);
            printf("%c",rgtFound.brand[i]);
    }

    printf("\nEan13: ");
    fseek(fp,20+RRN*tamRegistro,SEEK_SET);
    for(i=0;i<13;i++){
            fscanf(fp,"%c", &rgtFound.ean13[i]);
            printf("%c",rgtFound.ean13[i]);

    }
    fseek(fp,33+RRN*tamRegistro,SEEK_SET);
    printf("\nValor: ");
    for(i=0;i<4;i++){
            fscanf(fp,"%c", &rgtFound.price[i]);
            if(rgtFound.price[i]!=' ')
                printf("%c",rgtFound.price[i]);
    }
    printf("\n----------------");

    fclose(fp);
  }


int fileLength(){
        FILE *fp=fopen( fileName, "r+" );
        fseek(fp, 0, SEEK_END);
        int length = ftell(fp);
        length=(length/tamRegistro)-1;
        return length;
}

int exists(const char *fileN)
{
    FILE *file;
    if (file = fopen(fileN, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
