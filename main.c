#include <stdio.h>
#include <stdlib.h>

int filtroMedia();
int melhorarQualidade();

int main(){
    int op;
    while(1){
        printf("Como deseja tratar a imagem?\n1 - Filto da media\n2 - Melhorar qualidade\n");
        scanf(" %d", &op);
        if(op == 1){
            filtroMedia();
            break;
        } else if(op == 2){
            melhorarQualidade();
            break;
        } else {
            printf("Opção nao existe ,_,\n");
            continue;
        }
    }
    
    return 0;
}

int filtroMedia(){
    FILE *fp;
    
    int op;
    while(1){
        printf("Qual animal deseja ver sem oculos?\n1 - Dog\n2 - Cat\n");
        scanf(" %d", &op);
        if(op == 1){
            fp = fopen("dog.pgm", "r");
            break;
        } else if(op == 2){
            fp = fopen("cat.pgm", "r");
            break;
        } else {
            printf("Opção nao existe ,_,\n");
            continue;
        }
    }
    
    if(fp == NULL){ printf("Arquivo nao existe!"); return 0;}
    
    char mn[3];
    int larg, altu, mg;
    
    while(!feof(fp)){
        fscanf(fp, "%s %d %d %d", mn, &larg, &altu, &mg);
        break;
    }
    altu+=2;
    larg+=2;
    int imagem[altu][larg];
    for(int i = 1; i < altu-1; i++){
        for(int j = 1; j < larg-1; j++){
            fscanf(fp, " %d", &imagem[i][j]);
        }
    }
    fclose(fp);
    
    for(int i = 1; i < altu-1; i++){
        imagem[i][0] = imagem[i][2];
        imagem[i][larg-1] = imagem[i][larg-1-2];
    }
    for(int i = 1; i < larg-1; i++){
        imagem[0][i] = imagem[2][i];
        imagem[altu-1][i] = imagem[altu-1-2][i];
    }
    imagem[0][0] = imagem[0+2][0+2];    imagem[0][larg-1] = imagem[0+2][larg-1-2];
    
    imagem[altu-1][0] = imagem[altu-1-2][0+2];  imagem[altu-1][larg-1] = imagem[altu-1-2][larg-1-2];
    
    fp = fopen("Animal_miope", "w");
    
    fprintf(fp, "%s\n#animal miope se olhando no espelho\n%d %d\n%d\n", mn, larg-2, altu-2, mg);
    for(int i = 1; i < altu-1; i++){
        for(int j = 1; j < larg-1; j++){
            fprintf(fp, "%d ", (imagem[i-1][j-1] + imagem[i-1][j]*2 + imagem[i-1][j+1] + 
                                imagem[i][j-1]*2 + imagem[i][j]*4 + imagem[i][j+1]*2 + 
                                imagem[i+1][j-1] + imagem[i+1][j]*2 + imagem[i+1][j+1])/16);
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    
    printf("foi criando um arquivo para o animal miope!");
    return 1;
}

int melhorarQualidade(){
    FILE *fp;
    
    int op;
    while(1){
        printf("Qual animal deseja ver com oculos?\n1 - Dog\n2 - Cat\n");
        scanf(" %d", &op);
        if(op == 1){
            fp = fopen("dog.pgm", "r");
            break;
        } else if(op == 2){
            fp = fopen("cat.pgm", "r");
            break;
        } else {
            printf("Opção nao existe ,_,\n");
            continue;
        }
    }
    
    char mn[3];
    int larg, altu, mg;
    
    fscanf(fp, "%s %d %d %d", mn, &larg, &altu, &mg);
    
    altu*=3; altu+=2;
    larg*=3; larg+=2;
    int imagem[altu][larg];
    
    for(int i = 1; i < altu-1-2; i+=3){
        for(int j = 1; j < larg-1-2; j+=3){
            fscanf(fp, " %d", &imagem[i][j]);
            imagem[i][j+1] = imagem[i][j+2] = imagem[i+1][j] = imagem[i+1][j+1] = imagem[i+1][j+2] = imagem[i+2][j] = imagem[i+2][j+1] = imagem[i+2][j+2] = imagem[i][j];
        }
    }
    fclose(fp);
    
    for(int i = 1; i < altu-1; i++){
        imagem[i][0] = imagem[i][4];
        imagem[i][larg-1] = imagem[i][larg-1-4];
    }
    for(int i = 1; i < larg-1; i++){
        imagem[0][i] = imagem[4][i];
        imagem[altu-1][i] = imagem[altu-1-4][i];
    }
    imagem[0][0] = imagem[0+4][0+4];    imagem[0][larg-1] = imagem[0+4][larg-1-4];
    
    imagem[altu-1][0] = imagem[altu-1-4][0+4];  imagem[altu-1][larg-1] = imagem[altu-1-4][larg-1-4];
    
    fp = fopen("Animal_de_oculos.pgm", "w");
    
    fprintf(fp, "%s\n#animal de oculos se olhando no espelho\n%d %d\n%d\n", mn, larg-2, altu-2, mg);
    
    for(int i = 1; i < altu-1; i++){
        for(int j = 1; j < larg-1; j++){
            fprintf(fp, "%d ", (imagem[i-1][j-1] + imagem[i-1][j] + imagem[i-1][j+1] + 
                                imagem[i][j-1] + imagem[i][j] + imagem[i][j+1] + 
                                imagem[i+1][j-1] + imagem[i+1][j] + imagem[i+1][j+1])/9);
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    return 1;
}