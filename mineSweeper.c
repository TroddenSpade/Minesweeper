#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 14    //tool jadval
#define N 30    //arz jadval
#define Mine 40 //tedad min ha

//Functions :
void cls(); //pak kardan safhe
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
                defineMines(table,mines,Mine);   //agar bood mine hara print konad va bazi tamam shavad

                ////////////////////////////////////////////////////////////////////////////////////////////////////

                // baad az entekhabe khane mine che mishavad ?????!!!!!!!

                ////////////////////////////////////////////////////////////////////////////////////////////////////


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

void randMine(int mines[],int size){        //khane haye jadval ra az samte chap bala namgozari (az 0) mikonim ke M*N khane ast
    int randomNum;                          //banabar in 40 ta random kochektar az M*N mikhahim ke har kodam neshan dahande yek min bashad
    srand(time(NULL));                      //sepas adad ra bedast avardi va dar mines[] zakhire mikonim
    for (int i =0;i<size ;i++){             // va har bar check mikonim ke aya adadi ke rand ast ghablan ham amade ya na
        randomNum = rand()%(M*N);           // adad ra mod M*N migirim ta az 0 ta M*N-1 bema dahand ke neshan dahande khane hast 
        for(int j=0;j<i;j++){
            if(mines[j]==randomNum) randomNum =-1;
        }
        if(randomNum != -1) mines[i]= randomNum;
    }
}


int checker(int mines[],int n ,int a,int b){  //mokhtasati migirad va motabeghe raveshe bala shomare khane an mokhtasat ra bedast miavarad
    int num = b*30 + a;                       //ke be in sorat ast. num = b*30 + a
    for(int i=0;i<n;i++){                     // baad check mikonad ke bebinad aya dar mines[] ham shomare khanei be haman adad hast yana
        if(num == mines[i])   return 1;       // va 0 ya 1 ra return mikonad
    }
    return 0;
}


void defineMines(char table[M][N],int mines[],int size){ //jadvale An marhale ra migirad va shomare mine haye mines[] ra 
    int x,y;                                            //motabeghe maakos ravesh haye bala be mokhtasat tabdil mikonad
    for(int i=0;i<size;i++){                            //sepas an mokhtasat ra be '*' tabdil mikonad
        x = mines[i]%M;
        y = mines[i]/14;
        table[x][y]='*';
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
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            printf("%c",table[i][j]);
        }
        puts("");
    }
}

void setFlag(char table[M][N] ,int x ,int y){//mokhtasate x , y besorate int be setFlag pass dade mishavad ta az # be P tabdil konad
    table[x][y] ='P';
    
}

void unflag(char table[M][N] ,int x ,int y){//mokhtasate x , y besorate int be unFlag pass dade mishavad ta az P be # tabdil konad
    table[x][y] = '#';
}


void sweeper(char table[M][N],char tableCheck[M][N],int mines[],int size,int x,int y){   //Function Asli bazi :D
    int count =0;                                                   //
    if(tableCheck[x][y]=='#'){                                      //
        for(int i=-1;i<2;i++){                                      //
            if(x+i < 0 || x+i >M) continue;                         //
            for(int j=-1;j<2;j++){                                  //
                if(y+j < 0 || y+j >N) continue;                     //
                if(checker(mines,size,x+i,y+j) == 1)    count++;    //
            }                                                       //
        }                                                           //
                                                                        
        if(count > 0){                                              //
            table[x][y] = count+'0';                                //
        }else{                                                      //
            table[x][y]=' ';                                        //
            tableCheck[x][y]='0';                                   //
            for(int i=-1;i<2;i++){                                  //
                if(x+i < 0 || x+i >M) continue;                     //
                for(int j=-1;j<2;j++){                              //
                    if(y+j < 0 || y+j >N) continue;                 //
                    sweeper(table,tableCheck,mines,size,x+i,y+j);   //
                }                                                   //
            }                                                       //
        }                                                           //
    }
    
}

