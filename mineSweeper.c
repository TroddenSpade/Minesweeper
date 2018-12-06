#include <stdio.h>
#include <stdlib.h>
#define M 14
#define N 30

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

int main(){

    char table[M][N];
    defineTable(table);

    char cmd[3];
    char xY[3];
    while(1){
        fgets(cmd, sizeof(cmd)*3, stdin);
        
        switch(cmd[0]) {
            case 'e': return 0;
            break;
            case 'c': printf("%d", 1);
            break;
            case 'f': printf("%d", 2);
            break;
            case 'u': printf("%d", 3);
        }



    }
    
  
    
    return 0;
}