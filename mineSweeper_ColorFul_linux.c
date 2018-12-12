#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 14    //y jadval
#define N 30    //x jadval
#define Mine 40 //tedad min ha

// code haye ANSI baraye chap rangi
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//Functions :
void cls(); //pak kardan safhe
void winner();  //tabei ke baad az bord payami chap mikonad
void loser(); //tabei ke payam bakht ra print mikonad va bomb hara moshakhas mikonad
int winCheck(char table[M][N]); //tabei ke check mikonad aya be mogheiate bord reside ast
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

    while(winCheck(table)>40){   //loopi ke bazi dar an anjam mishavad ta ya bebazad ya bebarad
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
                cls();                           //safhe pak mishavad
                defineMines(table,mines,Mine);   //bombha bar roye arraye neshan dade mishavad
                printTable(table);               // payam bakht neshan dade mishavad
                loser(); //etmame bazi ra elam mikonad 
                return 0;
            }else{
                sweeper(table,tableCheck,mines,Mine,x,y);//agar ham khane mine nabood biayad An khane ra be sweeper pass dahad
                                                         //ta amaliate bazi anjam shavad :D
            }
            defineTable(tableCheck); 
            //har taghirati ke dar sweeper bar roye array tableCheck anjam shode bood be halate defult barmigardad '#'
            cls();  //agar nabakhte bood safhera pak karde va dar door baad safhe jadid print shavad
            break;  //va break mikhorad va az switch case kharej mishavad ta cmd jadid ra az vorodi begirad

            case 'f': //Set Flag
            fgets(xY, sizeof(xY)*5, stdin); //x,y be sorate "x,y" gerefte mishavad
            x = inputX(xY); //reshte be inputX dade mishavad ta x input dar x zakhire shavad
            y = inputY(xY); //reshte be inputY dade mishavad ta y input dar y zakhire shavad
            cls();  
            setFlag(table,x,y); //mokhtasate x , y besorate int be setFlag pass dade mishavad ta az # be P tabdil konad
            break;  //va break mikhorad va az switch case kharej mishavad ta cmd jadid ra az vorodi begirad

            case 'u': //UnFlag
            fgets(xY, sizeof(xY)*5, stdin); //x,y be sorate "x,y" gerefte mishavad
            x = inputX(xY); //reshte be inputX dade mishavad ta x input dar x zakhire shavad
            y = inputY(xY); //reshte be inputY dade mishavad ta y input dar y zakhire shavad
            cls();
            unflag(table,x,y);  //mokhtasate x , y besorate int be unFlag pass dade mishavad ta az P be # tabdil konad
            break;  //va break mikhorad va az switch case kharej mishavad ta cmd jadid ra az vorodi begirad
        }
    }

    winner();   //agar az while biron biayad yani 40 khane mande ke bomb hastand pas barande shode!
    
    return 0;
}


//Functions:
void cls(){
    system("clear");    //table ghabli ra pak mikonad
}

int winCheck(char table[M][N]){ //tabei ke check mikonad khane haye baghi mande tedadash che ghad ast.
    int count =0;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(table[i][j]=='P'||table[i][j]=='#'){ //kane haye baghimande ya # hastand ya flag shode and.
                count++;
            }
        }
    }
    return count;
}

void winner(){  //payam bordan bazi ra print mikonad
    puts(ANSI_COLOR_GREEN);
    puts("__   __            _    _ _        ");
    puts("\\ \\ / /           | |  | (_)       ");
    puts(" \\ V /___  _   _  | |  | |_ _ ___ ");
    puts("  \\ // _ \\| | | | | |/\\| | | '_  \\");
    puts("  | | (_) | |_| | \\  /\\  / | | | | ");
    puts("  \\_/\\___/ \\__,_|  \\/  \\/|_|_| |_| ");
    puts(ANSI_COLOR_RESET);
}

void loser(){   //agar bomb entekhab shavad :
    puts(ANSI_COLOR_RED);                   //color print be RED taghir mikonad
    puts("  ______                       ______              ");
    puts(" /  ____|                     / ___  |               ");
    puts(" | |  __  __ _ _ __ ___ ____  | |  | |_   ______ ___ ");
    puts(" | | |_ |/ _` | '_ ` _|/ _  | | |  | | \\ / / _ |' __|");
    puts(" | |__| | (_| | | | | ||  __/ | |__| |\\ V /| __| |   ");
    puts(" |______|_,_|_| |_| |_||___/  |______| \\_/ \\___|_|");
    puts(ANSI_COLOR_RESET);                 //pas az print payam color RESET mishavad
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
    printf("   ");  //ebteda 3 _ space dade mishavad
    for(int i =0;i<N;i++)   printf(ANSI_COLOR_GREEN "%3d"ANSI_COLOR_RESET,i);   //baad adad mokhtasat x dar line aval chap mishavad
    puts("");
    for(int i=0;i<M;i++){
        printf(ANSI_COLOR_GREEN "%3d" ANSI_COLOR_RESET,i);  //dar ebtedaye har line shomare satr 
        for(int j=0;j<N;j++){
            if(table[i][j]=='#')    printf("%3c",table[i][j]);  //baad az An on satr chap mishavad # WHITE
            else if(table[i][j]=='*')    printf(ANSI_COLOR_RED "%3c" ANSI_COLOR_RESET,table[i][j]);// * RED
            else if(table[i][j]=='P')    printf(ANSI_COLOR_BLUE "%3c" ANSI_COLOR_RESET,table[i][j]);// P BLUE
            else    printf(ANSI_COLOR_MAGENTA "%3c" ANSI_COLOR_RESET,table[i][j]);  //khane haye daray addad ba MAGENTA
        }
        puts("");
    }
}

void setFlag(char table[M][N] ,int x ,int y){//mokhtasate x , y besorate int be setFlag pass dade mishavad ta az # be P tabdil konad
    if(table[y][x] =='#')   table[y][x] ='P';
    else    puts(ANSI_COLOR_RED "-- You Cannot Change it to Flag ! -----------------"ANSI_COLOR_RESET);
    //agar khane # nabahsad warning midahad va warning ra be rang RED print mikonad
}

void unflag(char table[M][N] ,int x ,int y){//mokhtasate x , y besorate int be unFlag pass dade mishavad ta az P be # tabdil konad
    if(table[y][x] =='P')   table[y][x] ='#';
    else    puts(ANSI_COLOR_RED "-- There is No Flag to UnFlag ! -------------------"ANSI_COLOR_RESET);
    //agar khane P nabahsad warning midahad va warning ra be rang RED print mikonad
}


void sweeper(char table[M][N],char tableCheck[M][N],int mines[],int size,int x,int y){   //Function Asli bazi :D
    int count =0;                                                   //count ke barabare tedad khane haye atraf x,y ast ra aval 0 migirm
    if(tableCheck[y][x]=='#'){                                      //check mikonim ke aya khane # ra karbar entekhab karde
        for(int i=-1;i<2;i++){                                      //sepas tamam khane yahe atrafe x,y ra check mikonim
            if(x+i < 0 || x+i>=N) continue;                         //x E khane atraf agar dar kadr bazi nabod az An sarf nazar mikonim
            for(int j=-1;j<2;j++){                                  
                if(y+j < 0 || y+j>=M) continue;                     //x E khane atraf agar dar kadr bazi nabod az An sarf nazar mikonim
                if(checker(mines,size,x+i,y+j) == 1)    count++;    //sepas age bomb bood count ra ++ mokonim
            }                                                       
        }                                                           
                                                                        
        if(count > 0){                                              //baad agar dar khane atraf x,y bomb bood (count>0)
            table[y][x] = count+'0';                                //count ra besorate char dar jadval save mikonim
        }else{                                                      //agar count = 0 bood
            table[y][x]=' ';                                        //an khane ra be ' ' tabdil konad
            tableCheck[y][x]='0';                                   //va chon khane check shode tableCheck ro az # be 0 tabdil mikonim
            for(int i=-1;i<2;i++){                                  //ke dafhe baadi on khane ra check nakonad
                if(x+i < 0 || x+i>=N) continue;                     
                for(int j=-1;j<2;j++){                              
                    if(y+j < 0 || y+j>=M) continue;                 
                    sweeper(table,tableCheck,mines,size,x+i,y+j);   //baad roye tamam khane haye atraf x,y sweeper ra anjam dahad
                }                                                   //ta jai ke az kadr bazi kharej shavad ya be bomb beresad edame midahad
            }                                                       //va tableCheck khane haye check shode ra be 0 tabdil mikonad
        }                                                           //pas az ejra tabe sweeper bayad tableCheck ra dobare define konim
    }                                                               //ta dar dor haye baad dochare moshkel nashavad
    
}

