#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 14    //y jadval
#define N 30    //x jadval
#define Mine 40 //tedad min ha

//Functions :
void cls(); //pak kardan safhe
void winner(char table[M][N],int mines[]);
void loser(char table[M][N],int mines[]);
int inputX(char xY[]);  //x varedshode dar cmd ra peyda mikonad
int inputY(char xY[]);  //y varedshode dar cmd ra peyda mikonad
int checker(int mines[],int ,int,int);  //check mikonad ke mokhtasate x,y daray bomb ast ya na
void defineTable(char table[M][N]); //jadvale dade shode ra bo # tabdil mikonad
void randMine(int mines[],int size);//be sorate random adadi tolid mikonad ke majmoe x,y khane bomb be sorate yekta mibashad
void printTable(char table[M][N]);  //arraye 2d ra printf mikonad
void setFlag(char table[M][N] ,int ,int);   //mokhtasati migirad va an ra az # be P tabdil mikonad
void unflag(char table[M][N] ,int ,int );   //mokhtasati migirad va an ra az P be # tabdil mikonad
void sweeper(char table[M][N],char tableCheck[M][N],int mines[],int,int ,int ); //amaliate asli ra anjam midhad ;D
void defineMines(char table[M][N],int mines[],int size); 
//arraye i migirad va bedone avaz kardan khane haye digar
//khane hai ke bomb dar anan bode moshakhas mikonad


int main(){
    char tableCheck[M][N];  //arraye 2d ke baadan bedardeman mikhorad ;D
    defineTable(tableCheck);//tableCheck ra be # tabdil mikonim
    char table[M][N];   //arraye 2d ke shamele halat safhe bazi dar har marhale ast
    defineTable(table); //table ra be # tabdil mikonim
    int mines[Mine];    //arraye shamele Mine ta min  
    randMine(mines,Mine);   //besorate random Mine ta min ra dar mines[] gharar midahim

    char cmd[3];    //char cmd baraye zakhire dastor avalie karbar cho,flg,ufl,ext,...
    char xY[5];     //char xY baraye zakhire mokhtasate vared shode be sorate reshte

    while(1){   //loopi ke bazi dar an anjam mishavad ta ya bebazad ya bebarad
        printTable(table);// har bar dar aval table[][] print mishavad
        
        fgets(cmd, sizeof(cmd)*3, stdin);// dastor avalie gerefte mishavad
        int y , x;  //motaghayere x , y baraye zakhire X,Y input az karbar be sorate int

        switch(cmd[0]) {    //dastorat avalie bar asas char avale cmd be e,c,f,u tabdil mishavand

            case 'e': return 0; //exit

            case 'c': //choose x and y
            fgets(xY, sizeof(xY)*5, stdin); //x,y be sorate "x,y" gerefte mishavad
            x = inputX(xY); //reshte be inputX dade mishavad ta x input dar x zakhire shavad
            y = inputY(xY); //reshte be inputY dade mishavad ta y input dar y zakhire shavad
            if(checker(mines,Mine,x,y) == 1){   //check mikonad bebinad mine dar an khane ast ya na
                loser(table,mines); //etmame bazi ra elam mikonad va min hara print mikonad
                return 0;
            }else{
                sweeper(table,tableCheck,mines,Mine,x,y);//agar ham khane mine nabood biayad An khane ra be sweeper pass dahad
                                                         //ta amaliate bazi anjam shavad :D
            }
            defineTable(tableCheck); 
            //har taghirati ke dar sweeper bar roye array tableCheck anjam shode bood be halate defult barmigardad '#'
            break;  //va break mikhorad va az switch case kharej mishavad ta cmd jadid ra az vorodi begirad

            case 'f': //Set Flag
            fgets(xY, sizeof(xY)*5, stdin); //x,y be sorate "x,y" gerefte mishavad
            x = inputX(xY); //reshte be inputX dade mishavad ta x input dar x zakhire shavad
            y = inputY(xY); //reshte be inputY dade mishavad ta y input dar y zakhire shavad
            setFlag(table,x,y); //mokhtasate x , y besorate int be setFlag pass dade mishavad ta az # be P tabdil konad
            break;  //va break mikhorad va az switch case kharej mishavad ta cmd jadid ra az vorodi begirad

            case 'u': //UnFlag
            fgets(xY, sizeof(xY)*5, stdin); //x,y be sorate "x,y" gerefte mishavad
            x = inputX(xY); //reshte be inputX dade mishavad ta x input dar x zakhire shavad
            y = inputY(xY); //reshte be inputY dade mishavad ta y input dar y zakhire shavad
            unflag(table,x,y);  //mokhtasate x , y besorate int be unFlag pass dade mishavad ta az P be # tabdil konad
            break;  //va break mikhorad va az switch case kharej mishavad ta cmd jadid ra az vorodi begirad
        }

        cls();  //pas az taghirat roye table[][] , table ghabli pak mishavad ta dar dor baadi loop table jadid print shavad
    
    }
    
    return 0;
}



void cls(){
    system("clear");    //table ghabli ra pak mikonad
}

void winner(char table[M][N],int mines[]){
    cls();
    defineMines(table,mines,Mine);
    printTable(table);
}

void loser(char table[M][N],int mines[]){   //agar bomb entekhab shavad safhe pak mishavad va bomb hara print mikonad
    cls();
    defineMines(table,mines,Mine);
    printTable(table);
    puts("   _____                       ______              ");
    puts("  / ____|                     / ___  |               ");
    puts(" | |  __  __ _ _ __ ___  ___  | |  | |_   ______ ___ ");
    puts(" | | |_ |/ _` | '_ ` _|/ _  | | |  | | \\ / / _ |' __|");
    puts(" | |__| | (_| | | | | ||  __/ | |__| |\\ V |  __| |   ");
    puts(" |______|_,_|_| |_| |_||___/  |______| \\_/ \\___|_|");
}

int inputX(char xY[]){  //xY[] ra migirad va x ra be sorat int return midahad
    int length;
    for(length=0 ;;length++)
        if(xY[length]==',')  break; //meghdar char haye ghabl "," andaze giri mishavad ke char haye x hastand
    
    if(length == 1) return (xY[0]-48) ; //agar length 1 bood char x ra ke code assci An ast az kode assci 0 kam mikonim 
                                        //va be sorate int return midahim
    
    return (xY[0]-48)*10 + (xY[1]-48);  //agar length 2 bood char aval ra dar 10 zarb karde va ba adade char dovom jam mikonim 
}

int inputY(char xY[]){
    int length;                                 //be sorate moshabehe bala y ra peyda mikonim 
    int n1;                                     //faghat ! char haye y baad az "," gharar darand
    for(length =0 ;;length++){                  //agar 2 ya 1 raghami bood halat bandi mishavand
        if(xY[length]==',')  n1 = length;       //va manande function inputX return dade mishavand.
        if (xY[length]=='\0')    break; 
    }
    if(length-n1==3)  return (xY[n1+1] - 48);

    return  (xY[n1+1]-48)*10 + (xY[2+n1]-48);
}

void randMine(int mines[],int size){    //khane haye jadval ra az samte chap bala namgozari (az 0) mikonim ke M*N khane ast
    int randomNum =0; 
    int count=0;    
    srand(time(NULL));                  //banabar in 40 ta random kochektar az M*N mikhahim ke har kodam neshan dahande yek min bashad
    while(count<size){                  //sepas adad ra bedast avardi va dar mines[] zakhire mikonim
        randomNum = rand()%(M*N);       // va har bar check mikonim ke aya adadi ke rand ast ghablan ham amade ya na  
        for(int j=0;j<count;j++){       // adad ra mod M*N migirim ta az 0 ta M*N-1 bema dahand ke neshan dahande khane hast 
            if(mines[j]==randomNum){
                randomNum =-1;
                break;
            }
        }
        if(randomNum != -1) {
            mines[count]= randomNum;
            count++;
        }
    }
}


int checker(int mines[],int n ,int x,int y){  //mokhtasati migirad va motabeghe raveshe bala shomare khane an mokhtasat ra bedast miavarad
    int num = y*30 + x;                       //ke be in sorat ast. num = y*30 + x
    for(int i=0;i<n;i++){                     // baad check mikonad ke bebinad aya dar mines[] ham shomare khanei be haman adad hast yana
        if(num == mines[i])   return 1;       // va 0 ya 1 ra return mikonad
    }
    return 0;
}

//Err?!//
void defineMines(char table[M][N],int mines[],int size){ //jadvale An marhale ra migirad va shomare mine haye mines[] ra 
                                               //motabeghe maakos ravesh haye bala be mokhtasat tabdil mikonad
    for(int i=0;i<size;i++){                            //sepas an mokhtasat ra be '*' tabdil mikonad
        table[mines[i]/N][mines[i]%N]='*';
    }
}

void defineTable(char table[M][N]){     //arraye 2d ke pass midahim ta be # tabdil mikonad
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            table[i][j]='#';
        }
    }
}


void printTable(char table[M][N]){      //arraye pass dade shode ra print mikonad
    printf("   ");
    for(int i =0;i<N;i++)   printf("%3d",i);
    puts("");
    for(int i=0;i<M;i++){
        printf("%3d",i);
        for(int j=0;j<N;j++){
            printf("%3c",table[i][j]);
        }
        puts("");
    }
}

void setFlag(char table[M][N] ,int x ,int y){//mokhtasate x , y besorate int be setFlag pass dade mishavad ta az # be P tabdil konad
    table[y][x] ='P';
    
}

void unflag(char table[M][N] ,int x ,int y){//mokhtasate x , y besorate int be unFlag pass dade mishavad ta az P be # tabdil konad
    table[y][x] = '#';
}


void sweeper(char table[M][N],char tableCheck[M][N],int mines[],int size,int x,int y){   //Function Asli bazi :D
    int count =0;                                                   //
    if(tableCheck[y][x]=='#'){                                      //
        for(int i=-1;i<2;i++){                                      //
            if(x+i < 0 || x+i>=N) continue;                         //
            for(int j=-1;j<2;j++){                                  //
                if(y+j < 0 || y+j>=M) continue;                     //
                if(checker(mines,size,x+i,y+j) == 1)    count++;    //
            }                                                       //
        }                                                           //
                                                                        
        if(count > 0){                                              //
            table[y][x] = count+'0';                                //
        }else{                                                      //
            table[y][x]=' ';                                        //
            tableCheck[y][x]='0';                                   //
            for(int i=-1;i<2;i++){                                  //
                if(x+i < 0 || x+i>=N) continue;                     //
                for(int j=-1;j<2;j++){                              //
                    if(y+j < 0 || y+j>=M) continue;                 //
                    sweeper(table,tableCheck,mines,size,x+i,y+j);   //
                }                                                   //
            }                                                       //
        }                                                           //
    }
    
}

