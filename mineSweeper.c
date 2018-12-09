#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 14
#define N 30
#define Mine 40

void cls();
int inputX(char xY[]);
int inputY(char xY[]);
int checker(int mines[],int ,int,int);
void defineTable(char table[M][N]);
void randMine(int mines[],int size);
void printTable(char table[M][N]);
void setFlag(char table[M][N] ,int ,int);
void unflag(char table[M][N] ,int ,int );
void sweeper(char table[M][N],char tableCheck[M][N],int mines[],int,int ,int );
void printMines(char table[M][N],int mines[],int size);


int main(){
    char tableCheck[M][N];
    defineTable(tableCheck);
    char table[M][N];
    defineTable(table);
    int mines[Mine];
    randMine(mines,Mine);

    char cmd[3];
    char xY[5];

    while(1){
        printTable(table);
        
        fgets(cmd, sizeof(cmd)*3, stdin);
        int y , x;

        switch(cmd[0]) {
            case 'e': return 0; //exit

            case 'c': //choose x and y
            fgets(xY, sizeof(xY)*5, stdin);
            x = inputX(xY);
            y = inputY(xY);
            
            if(checker(mines,Mine,x,y) == 1){
                printMines(table,mines,Mine);
            }else{
                sweeper(table,tableCheck,mines,Mine,x,y);
            }
            defineTable(tableCheck);
            break;

            case 'f': //Set Flag
            fgets(xY, sizeof(xY)*5, stdin);
            x = inputX(xY);
            y = inputY(xY);
            setFlag(table,x,y);
            break;

            case 'u': //UnFlag
            fgets(xY, sizeof(xY)*5, stdin);
            x = inputX(xY);
            y = inputY(xY);
            unflag(table,x,y);
            break;
        }

        cls();
    
    }
    
    return 0;
}

int inputX(char xY[]){
    int length;
    for(length=0 ;;length++)
        if(xY[length]==',')  break;
    
    if(length == 1) return (xY[0]-48) ;
    
    return (xY[0]-48)*10 + (xY[1]-48);
}

int inputY(char xY[]){
    int length;
    int n1;
    for(length =0 ;;length++){
        if(xY[length]==',')  n1 = length;
        if (xY[length]=='\0')    break; 
    }
    if(length-n1==3)  return (xY[n1+1] - 48);

    return  (xY[n1+1]-48)*10 + (xY[2+n1]-48);
}

void randMine(int mines[],int size){
    int randomNum;
    srand(time(NULL));
    for (int i =0;i<size ;i++){
        randomNum = rand()%(M*N);
        for(int j=0;j<i;j++){
            if(mines[j]==randomNum) randomNum =-1;
        }
        if(randomNum != -1) mines[i]= randomNum;
    }
}


int checker(int mines[],int n ,int a,int b){
    int num = b*30 + a;
    for(int i=0;i<n;i++){
        if(num == mines[i])   return 1;
    }
    return 0;
}


void printMines(char table[M][N],int mines[],int size){
    int x,y;
    for(int i=0;i<size;i++){
        x = mines[i]%M;
        y = mines[i]/14;
        table[x][y]='*';
    }
}


void cls(){
    system("clear");
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

//Err?//
void sweeper(char table[M][N],char tableCheck[M][N],int mines[],int size,int x,int y){
    int count =0;
    if(tableCheck[x][y]=='#'){
        if(checker(mines,size,x,y) == 0){
            for(int i=-1;i<2;i++){
                if(x+i < 0) continue;
                for(int j=-1;j<2;j++){
                    if(y+j < 0) continue;
                    if(checker(mines,size,x+i,y+j) == 1)    count++;
                }
            }

            if(count > 0){
                table[x][y] = count+'0';
            }else{
                table[x][y]=' ';
                tableCheck[x][y]='0';
                for(int i=-1;i<2;i++){
                    if(x+i < 0) continue;
                    for(int j=-1;j<2;j++){
                    if(y+j < 0) continue;
                    sweeper(table,tableCheck,mines,size,x+i,y+j);
                    }  
                }
            }
        }
    }
    
}