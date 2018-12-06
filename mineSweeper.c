#include <stdio.h>
#include <stdlib.h>
#define M 14
#define N 30
#define mine 40

void cls();
void defineTable(char table[M][N]);
void randMine(int mines[mine][2]);
void printTable(char table[M][N]);
void setFlag(char table[M][N] ,int ,int);
void unflag(char table[M][N] ,int ,int );


int main(){
    char table[M][N];
    defineTable(table);

    char cmd[3];
    char xY[3];

    while(1){
        

        fgets(cmd, sizeof(cmd)*3, stdin);
        int y , x;
        
        switch(cmd[0]) {
            case 'e': return 0; //exit

            case 'c': //choose x and y
            fgets(xY, sizeof(xY)*3, stdin);
            x = xY[0] - 48;
            y = xY[2] - 48;
            break;

            case 'f': //Set Flag
            fgets(xY, sizeof(xY)*3, stdin);
            x = xY[0] - 48;
            y = xY[2] - 48;
            setFlag(table,x,y);
            break;

            case 'u': //UnFlag
            fgets(xY, sizeof(xY)*3, stdin);
            x= xY[0] - 48;
            y= xY[2] - 48;
            break;
        }

        printTable(table);
        
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
            printf("%c",table[i][j]);
        }
        puts("");
    }
}

void setFlag(char table[M][N] ,int x ,int y){
    table[x][y] ='P';
    
}

void unflag(char table[M][N] ,int x ,int y){
    table[x][y] = '#';
}