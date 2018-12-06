#include <stdio.h>
#include <stdlib.h>
#define M 14
#define N 30

void cls();
void defineTable(char table[][]);
void printTable(char table[][]);
void setFlag(char table[][] ,int ,int);
void Unflag(char table[][] ,int ,int);


int main(){

    char table[M][N];
    defineTable(table);

    char cmd[3];
    char xY[3];
    
    while(1){
        fgets(cmd, sizeof(cmd)*3, stdin);
        
        switch(cmd[0]) {
            case 'e': return 0; //exit
            break;

            case 'c': //choose x and y
            ;
            break;

            case 'f': //Set Flag
            printf("%d", 2);
            break;

            case 'u': //UnFlag
            printf("%d", 3);
            break;
        }
    }
    
    return 0;
}



void cls(){
    system("cls");
}

void defineTable(char table[M][N]){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            table[i][j]='#';
        }
    }
}

void printTable(char table[M][N]){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            putchar(table[i][j]);
        }
        puts("");
    }
}

void setFlag(char table[M][N] ,int x ,int y){

}

void Unflag(char table[M][N] ,int x ,int y){

}