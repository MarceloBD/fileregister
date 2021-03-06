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

void main( )
{
    interface();
}

void interface()
{
    char optionMain;
    int rgtNumber , i;

    printf("\n1- Want to make a registration?\n2- Want to take a register?\n3- Want to see the registers?\n\n>>");

    scanf("%s", &optionMain);

    if(optionMain == '1')
    {
        system("cls");
        newRegister();
        interface();
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

    struct registerFields newRgt;

    if(!exists(FILENAME)){
        FILE *create = fopen(FILENAME , "wb" );
        fclose(create);
    }

    FILE *fp = fopen( FILENAME ,"rb+" );

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);

    RRN = length/rgtLength_t;

    int j;
    printf("\nName (10): ");
    scanf("%10s", &newRgt.name);
    int c;
    while ((c = getchar()) != EOF && c != '\n') ;

    fseek ( fp , 0 + rgtLength_t * RRN , SEEK_SET );
    fwrite(newRgt.name , 1 , 10, fp);

    printf("Brand (10): ");
    scanf("%10s" , &newRgt.brand);
    while ((c = getchar()) != EOF && c != '\n') ;
    fseek ( fp , 10+rgtLength_t * RRN , SEEK_SET );
    fwrite(newRgt.brand , 1 , sizeof(newRgt.brand), fp);


    printf("Ean13 (13): ");
    scanf("%13s" , &newRgt.ean13);
   while ((c = getchar()) != EOF && c != '\n') ;
    fseek ( fp , 20 + rgtLength_t * RRN , SEEK_SET );
    fwrite(newRgt.ean13 , 1 , sizeof(newRgt.ean13), fp);


    printf("Price (4): ");
    scanf("%4s" , &newRgt.price);
    while ((c = getchar()) != EOF && c != '\n') ;
    fseek ( fp , 33 + rgtLength_t * RRN , SEEK_SET );

    fwrite(newRgt.price , 1 , sizeof(newRgt.price), fp);

    fseek ( fp , rgtLength_t * (RRN+1) , SEEK_SET );
    fprintf(fp, "%c", '0');
    fclose(fp);

    system("cls");
    printf("\nYour register has been realized with RRN = %d\n",RRN);


}

void readRegister(int RRN){

    struct registerFields rgtFound;
    int i;

    FILE *fp = fopen( FILENAME, "rb+" );
    fseek(fp , 0 , SEEK_END);
    int length = ftell(fp);
    length = (length / rgtLength_t) - 1;

    if(RRN > length){
        printf("\nInvalid register \n");
        interface();
        return;
    }

    printf("----------------\n");

    fseek(fp , 0 + RRN * rgtLength_t , SEEK_SET);
    printf("Name: ");
    fread(rgtFound.name , 1 , 10, fp);
    rgtFound.name[10]=0;
    printf("%s" , rgtFound.name);


    fseek(fp , 10 + RRN * rgtLength_t , SEEK_SET);
    printf("\nBrand: ");
    fread(rgtFound.brand , 1 , sizeof(rgtFound.brand), fp);
    rgtFound.brand[10]=0;
    printf("%s" , rgtFound.brand);


    printf("\nEan13: ");
    fseek(fp, 20 + RRN * rgtLength_t, SEEK_SET);

    fread(rgtFound.ean13 , 1 , sizeof(rgtFound.ean13), fp);
    rgtFound.ean13[13]=0;
    printf("%s" , rgtFound.ean13);


    fseek(fp,33 + RRN * rgtLength_t , SEEK_SET);
    printf("\nPrice: ");

    fread(rgtFound.price , 1 , sizeof(rgtFound.price), fp);
    rgtFound.price[4]=0;
    printf("%s" , rgtFound.price);

    printf("\n----------------");

    fclose(fp);
  }

int fileLength()
{
        FILE *fp = fopen( FILENAME, "r+" );
        fseek(fp , 0 , SEEK_END);
        int length = ftell(fp);
        length = (length / rgtLength_t) - 1;
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
