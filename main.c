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

#include <stdio.h>

#define fileName "Registros.txt"
#define tamRegistro 37

void newRegister(void); //Cria novo cadastro
void readRegister(int); //Busca o cadastro
void action(void); // Gerencia açoes de cadastro e de busca
int getTamanho(void); // Procura tamanho do arquivo
int exists(const char*); //Verifica se o arquivo existe

struct registerFields {
        char name[10];
        char brand[10];
        char ean13[13];
        char price[4];
};

void main(){
    action();
}


void newRegister(){
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

    printf("\nNome (10): ");
    scanf("%s",&novo.name);
    fseek ( fp , 0+tamRegistro*RRN , SEEK_SET );
    fprintf(fp, "%s", novo.name);

    printf("Marca (10): ");
    scanf("%s",&novo.brand);
    fseek ( fp , 10+37*RRN , SEEK_SET );
    fprintf(fp, "%s", novo.brand);

    printf("Ean13 (13): ");
    scanf("%s",&novo.ean13);
    fseek ( fp , 20+tamRegistro*RRN, SEEK_SET );
    fprintf(fp, "%s", novo.ean13);

    printf("Valor (4): ");
    scanf("%s",&novo.price);
    fseek ( fp , 33+tamRegistro*RRN, SEEK_SET );
    fprintf(fp, "%s", novo.price);

    fseek ( fp , tamRegistro*(RRN+1), SEEK_SET );
    fprintf(fp, "%c", '0');
    fclose(fp);

    system("cls");
    printf("\nSeu cadastro foi realizado com RRN = %d\n",RRN);

    action();
}

void readRegister(int RRN){

    struct registerFields achado;
    int i;

    FILE *fp=fopen( fileName, "r+" );
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    length=(length/tamRegistro)-1;

    if(RRN>length){
        printf("\nCadastro invalido \n");
        action();
        return;
    }

    printf("----------------\n");

    fseek(fp,0+RRN*tamRegistro,SEEK_SET);
    printf("Nome: ");
    for(i=0;i<10;i++){
        fscanf(fp,"%c", &achado.name[i]);
        printf("%c",achado.name[i]);
    }

    fseek(fp,10+RRN*tamRegistro,SEEK_SET);
    printf("\nMarca: ");
    for(i=0;i<10;i++){
            fscanf(fp,"%c", &achado.brand[i]);
            printf("%c",achado.brand[i]);
    }

    printf("\nEan13: ");
    fseek(fp,20+RRN*tamRegistro,SEEK_SET);
    for(i=0;i<13;i++){
            fscanf(fp,"%c", &achado.ean13[i]);
            printf("%c",achado.ean13[i]);

    }
    fseek(fp,33+RRN*tamRegistro,SEEK_SET);
    printf("\nValor: ");
    for(i=0;i<4;i++){
            fscanf(fp,"%c", &achado.price[i]);
            if(achado.price[i]!=' ')
                printf("%c",achado.price[i]);
    }
    printf("\n----------------");

    fclose(fp);
  }

void action(){
    char r;
    int numero,i;
    printf("\n1- Want to make a registration?\n2- Want to take a register?\n3- Want to see the registers?\n\n>>");
    scanf("%s",&r);
    if(r=='1'){
        system("cls");
        newRegister();
    }
    else if (r=='2'){
        printf("\nDigite o numero do cadastro: ");
        scanf("%d",&numero);
        system("cls");
        readRegister(numero);
        action();
        }
    else if (r=='3'){
        system("cls");
        for(i=0;i<getTamanho()+1;i++){
            printf("\nRRN= %d\n",i);
            readRegister(i);}
        action();
    }
    else
        return;

}

int getTamanho(){
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
