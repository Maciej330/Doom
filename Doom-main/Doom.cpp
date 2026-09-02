#include<iostream>
#include<thread>
#include<windows.h>
#include<cmath>
#include<mmsystem.h>
#include<cstdlib>
#include<ctime>
using namespace std;

constexpr int rozmiart = 2000;
int t[rozmiart][rozmiart];
int g1wiersz=15, g1kolumna=15;
double dg1wiersz=15, dg1kolumna=15;
int pz=100;
int lwrogow=0;
int pokonani=0, pozostalo;
int wprzeciwnik[20], kprzeciwnik[20], pzprzeciwnik[20];
int nrprzeciwnik[72];
int nr;
int kierunek=18, prawo, lewo, myszkierunek=900;
char obraz[10][72];
bool w, a, s, d, spacja, pr, lw, ml, wolne, omysz=false, start=false;
int q=2;
int x, y;
double radiany, odleglosc, stopnie;
double sodl[72], podl[72];
int styp[72], ptyp[72];
int pkol, pkat;
int wiersz, kolumna;
int wiersz2, kolumna2;
constexpr int zasieg = 131;
constexpr int pwg = (zasieg-1) / 2;
int kat[zasieg][zasieg];
double odl[zasieg][zasieg];
POINT kursor;
int eszerokosc;
int ewysokosc;
int srszerokosc;
int srwysokosc;

int gw=25, gk=25;
int wpok, kpok;
int lszer, lwys;
int ostszer, ostwys;
bool pusto;
int kier;
int los, typ;
constexpr int grozmiar=50;
int gt[grozmiar][grozmiar];
int skala = 32;
int wstart, kstart;

void sterowanie()
{
    this_thread::sleep_for(std::chrono::seconds(1));
    while(true){
        if(GetAsyncKeyState('W') & 0x8000) w=true;
        else w=false;
        if(GetAsyncKeyState('S') & 0x8000) s=true;
        else s=false;
        if(GetAsyncKeyState('A') & 0x8000) a=true;
        else a=false;
        if(GetAsyncKeyState('D') & 0x8000) d=true;
        else d=false;
        if(GetAsyncKeyState('E') & 0x8000) pr=true;
        else pr=false;
        if(GetAsyncKeyState('Q') & 0x8000) lw=true;
        else lw=false;
        if(GetAsyncKeyState(VK_LBUTTON) & 0x8000) ml=true;
        else ml=false;
        if(GetAsyncKeyState('P') & 0x8000) system("cls");
        if(GetAsyncKeyState('O') & 0x8000) omysz=!omysz;
        GetCursorPos(&kursor);
        if(omysz==true){
            myszkierunek=myszkierunek+(kursor.x-srszerokosc);
            kierunek=myszkierunek/50;
            if(kierunek>71) kierunek=kierunek-72;
            if(kierunek<0) kierunek=kierunek+72;
            SetCursorPos(srszerokosc,srwysokosc);
        }
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ekran()
{
    while(true){

        prawo=kierunek+8;
        lewo=kierunek-8;
        if(lewo<0) lewo=lewo+72;
        if(prawo>71) prawo=prawo-72;
        for(int w=0;w<10;w++){
            for(int k=lewo;k!=prawo;k++){
                cout<<obraz[w][k];
                if(k==71) k=-1;
            }
            cout<<"\n";
        }
        cout<<"pozostalo: "<<pozostalo;

        cout<<"\n"<<kierunek<<" ";

/*
        cout<<"\n"<<"\n";


        for(int i=0;i<72;i++){
            cout<<styp[i]<<" ";
        }
        cout<<"\n";
        for(int i=0;i<72;i++){
            cout<<sodl[i]<<" ";
        }
        cout<<"\n";

        for(int i=0;i<50;i++){
            for(int j=0;j<200;j++){
                cout<<t[i][j];
            }
            cout<<"\n";
        }

        cout<<"\n";

        cout<<"\n"<<kierunek<<"\n";

        for(int i=0;i<72;i++){
                cout<< nrprzeciwnik[i]<<" ";
            }
        cout<<"\n";
        for(int i=0;i<72;i++){
                cout<< pzprzeciwnik[i]<<" ";
            }
        cout<<"\n";
        for(int j=1;j<=lwrogow;j++){
        cout<<wprzeciwnik[j]<<" "<<kprzeciwnik[j]<<"\n";
        }

        cout<<"\n"<<lwrogow;

        cout<<"\n";
        if(spacja==true) cout<< "xxxxx";

        cout<<kierunek<<"  "<<"\n"<<dg1wiersz<<"  "<<"\n"<<dg1kolumna<<"  ";



        cout<<kursor.x<<"              "<<"\n"<<kursor.y<<"                  ";
*/
        cout<<"\033[H";
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void gracz1()
{
    while(true){
        /*
        if(pr==true) kierunek++;
        if(kierunek>71) kierunek=kierunek-72;
        if(lw==true) kierunek--;
        if(kierunek<0) kierunek=kierunek+72;
        */

        if(w==true){
            dg1wiersz=dg1wiersz-cos(kierunek*M_PI/36);
            dg1kolumna=dg1kolumna+sin(kierunek*M_PI/36);
        }
        if(s==true){
            dg1wiersz=dg1wiersz+cos(kierunek*M_PI/36);
            dg1kolumna=dg1kolumna-sin(kierunek*M_PI/36);
        }
        if(d==true){
            if(kierunek+18<72){
                dg1wiersz=dg1wiersz-cos((kierunek+18)*M_PI/36);
                dg1kolumna=dg1kolumna+sin((kierunek+18)*M_PI/36);
            }
            else{
                dg1wiersz=dg1wiersz-cos((kierunek-54)*M_PI/36);
                dg1kolumna=dg1kolumna+sin((kierunek-54)*M_PI/36);
            }
        }
        if(a==true){
            if(kierunek+54<72){
                dg1wiersz=dg1wiersz-cos((kierunek+54)*M_PI/36);
                dg1kolumna=dg1kolumna+sin((kierunek+54)*M_PI/36);
            }
            else{
                dg1wiersz=dg1wiersz-cos((kierunek-18)*M_PI/36);
                dg1kolumna=dg1kolumna+sin((kierunek-18)*M_PI/36);
            }
        }
        wolne=true;
        for(int w=51;w<=79;w++){
            wiersz2=round(dg1wiersz)-pwg+w;
            if(wiersz2>=0 && wiersz2<rozmiart){
                for(int k=51;k<=79;k++){
                    kolumna2=round(dg1kolumna)-pwg+k;
                    if(kolumna2>=0 && kolumna2<rozmiart){
                        if(odl[w][k]<14){
                            if(t[wiersz2][kolumna2]==0 || t[wiersz2][kolumna2]==3){
                                ;
                            }
                            else{
                                wolne=false;
                            }
                        }
                    }
                }
            }
        }
        if(wolne==true){
            t[g1wiersz][g1kolumna]=0;
            g1wiersz=round(dg1wiersz);
            g1kolumna=round(dg1kolumna);
            t[g1wiersz][g1kolumna]=3;
        }
        else{
            dg1wiersz=g1wiersz;
            dg1kolumna=g1kolumna;
        }


        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void render()
{
    while(true)
    {
    for(int i=0;i<72;i++){
        sodl[i]=99;
        podl[i]=99;
        styp[i]=0;
        ptyp[i]=0;
        nrprzeciwnik[i]=0;
        nrprzeciwnik[i]=0;
    }
    for(int w=0;w<zasieg;w++){
        for(int k=0;k<zasieg;k++){
            wiersz = g1wiersz - pwg + w;
            kolumna = g1kolumna - pwg + k;
            if(wiersz>=0 && kolumna>=0 && wiersz<rozmiart && kolumna<rozmiart){
                if(t[wiersz][kolumna]==1 && odl[w][k] < sodl[kat[w][k]]){
                        styp[kat[w][k]]=1;
                        sodl[kat[w][k]]=odl[w][k];
                }
            }
        }
    }
    for(int w=0;w<zasieg;w++){
        for(int k=0;k<zasieg;k++){
            wiersz = g1wiersz - pwg + w;
            kolumna = g1kolumna - pwg + k;
            if(wiersz>=0 && kolumna>=0 && wiersz<rozmiart && kolumna<rozmiart){
                if(t[wiersz][kolumna]==2 && odl[w][k] < sodl[kat[w][k]]+10){
                    styp[kat[w][k]]=2;
                    sodl[kat[w][k]]=odl[w][k];
                }
                if(t[wiersz][kolumna]==5){
                    for(int j=1;j<=lwrogow;j++){
                        if(wprzeciwnik[j]==wiersz && kprzeciwnik[j]==kolumna){
                            nr=j;
                        }
                    }
                    if(odl[w][k]<20){
                        for(int i=-4;i<=4;i++){
                            pkat=kat[w][k]+i;
                            if(pkat<0) pkat=pkat+72;
                            if(pkat>71) pkat=pkat-72;
                            if(odl[w][k] < podl[pkat]){
                                ptyp[pkat]=35+i;
                                podl[pkat]=odl[w][k];
                                nrprzeciwnik[pkat]=nr;
                            }
                        }
                    }
                    else if(odl[w][k]<32){
                        for(int i=-3;i<=3;i++){
                            pkat=kat[w][k]+i;
                            if(pkat<0) pkat=pkat+72;
                            if(pkat>71) pkat=pkat-72;
                            if(odl[w][k] < podl[pkat]){
                                ptyp[pkat]=24+i;
                                podl[pkat]=odl[w][k];
                                nrprzeciwnik[pkat]=nr;
                            }
                        }
                    }
                    else if(odl[w][k]<44){
                        for(int i=-2;i<=2;i++){
                            pkat=kat[w][k]+i;
                            if(pkat<0) pkat=pkat+72;
                            if(pkat>71) pkat=pkat-72;
                            if(odl[w][k] < podl[pkat]){
                                ptyp[pkat]=13+i;
                                podl[pkat]=odl[w][k];
                                nrprzeciwnik[pkat]=nr;
                            }
                        }
                    }
                    else if(odl[w][k]<65){
                        for(int i=-1;i<=1;i++){
                            pkat=kat[w][k]+i;
                            if(pkat<0) pkat=pkat+72;
                            if(pkat>71) pkat=pkat-72;
                            if(odl[w][k] < podl[pkat]){
                                ptyp[pkat]=2+i;
                                podl[pkat]=odl[w][k];
                                nrprzeciwnik[pkat]=nr;
                            }
                        }
                    }
                }
            }
        }
    }

    for(int k=0;k<72;k++){
        if(styp[k]==0){
            obraz[0][k]=' ';
            obraz[1][k]=' ';
            obraz[2][k]=' ';
            obraz[3][k]=' ';
            obraz[4][k]=' ';
            obraz[5][k]=' ';
            obraz[6][k]=' ';
            obraz[7][k]=' ';
            obraz[8][k]=' ';
            obraz[9][k]=' ';
        }
        else if(styp[k]==1){
            if(sodl[k]<16){
                obraz[0][k]='#';
                obraz[1][k]=' ';
                obraz[2][k]=' ';
                obraz[3][k]=' ';
                obraz[4][k]=' ';
                obraz[5][k]=' ';
                obraz[6][k]=' ';
                obraz[7][k]=' ';
                obraz[8][k]=' ';
                obraz[9][k]='#';
            }
            else if(sodl[k]<21){
                obraz[0][k]=' ';
                obraz[1][k]='#';
                obraz[2][k]=' ';
                obraz[3][k]=' ';
                obraz[4][k]=' ';
                obraz[5][k]=' ';
                obraz[6][k]=' ';
                obraz[7][k]=' ';
                obraz[8][k]='#';
                obraz[9][k]=' ';
            }
            else if(sodl[k]<29){
                obraz[0][k]=' ';
                obraz[1][k]=' ';
                obraz[2][k]='#';
                obraz[3][k]=' ';
                obraz[4][k]=' ';
                obraz[5][k]=' ';
                obraz[6][k]=' ';
                obraz[7][k]='#';
                obraz[8][k]=' ';
                obraz[9][k]=' ';
            }
            else if(sodl[k]<46){
                obraz[0][k]=' ';
                obraz[1][k]=' ';
                obraz[2][k]=' ';
                obraz[3][k]='#';
                obraz[4][k]=' ';
                obraz[5][k]=' ';
                obraz[6][k]='#';
                obraz[7][k]=' ';
                obraz[8][k]=' ';
                obraz[9][k]=' ';
            }
            else if(sodl[k]<=64){
                obraz[0][k]=' ';
                obraz[1][k]=' ';
                obraz[2][k]=' ';
                obraz[3][k]=' ';
                obraz[4][k]='#';
                obraz[5][k]='#';
                obraz[6][k]=' ';
                obraz[7][k]=' ';
                obraz[8][k]=' ';
                obraz[9][k]=' ';
            }
        }
        else if(styp[k]==2){
            if(sodl[k]<16){
                obraz[0][k]='#';
                obraz[1][k]='#';
                obraz[2][k]='#';
                obraz[3][k]='#';
                obraz[4][k]='#';
                obraz[5][k]='#';
                obraz[6][k]='#';
                obraz[7][k]='#';
                obraz[8][k]='#';
                obraz[9][k]='#';
            }
            else if(sodl[k]<21){
                obraz[0][k]=' ';
                obraz[1][k]='#';
                obraz[2][k]='#';
                obraz[3][k]='#';
                obraz[4][k]='#';
                obraz[5][k]='#';
                obraz[6][k]='#';
                obraz[7][k]='#';
                obraz[8][k]='#';
                obraz[9][k]=' ';
            }
            else if(sodl[k]<29){
                obraz[0][k]=' ';
                obraz[1][k]=' ';
                obraz[2][k]='#';
                obraz[3][k]='#';
                obraz[4][k]='#';
                obraz[5][k]='#';
                obraz[6][k]='#';
                obraz[7][k]='#';
                obraz[8][k]=' ';
                obraz[9][k]=' ';
            }
            else if(sodl[k]<47){
                obraz[0][k]=' ';
                obraz[1][k]=' ';
                obraz[2][k]=' ';
                obraz[3][k]='#';
                obraz[4][k]='#';
                obraz[5][k]='#';
                obraz[6][k]='#';
                obraz[7][k]=' ';
                obraz[8][k]=' ';
                obraz[9][k]=' ';
            }
            else if(sodl[k]<=64){
                obraz[0][k]=' ';
                obraz[1][k]=' ';
                obraz[2][k]=' ';
                obraz[3][k]=' ';
                obraz[4][k]='#';
                obraz[5][k]='#';
                obraz[6][k]=' ';
                obraz[7][k]=' ';
                obraz[8][k]=' ';
                obraz[9][k]=' ';
            }
        }
        if(ptyp[k]==31 && podl[k]<sodl[k]){
            obraz[2][k]='<';
            obraz[5][k]='/';
            obraz[6][k]='@';
            obraz[9][k]='|';
        }
        else if(ptyp[k]==32 && podl[k]<sodl[k]){
            obraz[2][k]='(';
            obraz[3][k]=' ';
            obraz[4][k]='/';
            obraz[5][k]=' ';
            obraz[6][k]=' ';
            obraz[7][k]=' ';
            obraz[8][k]='/';
            obraz[9][k]='|';
        }
        else if(ptyp[k]==33 && podl[k]<sodl[k]){
            obraz[1][k]='_';
            obraz[2][k]=' ';
            obraz[3][k]='\\';
            obraz[4][k]='|';
            obraz[5][k]='|';
            obraz[6][k]='|';
            obraz[7][k]='/';
            obraz[8][k]='/';
        }
        else if(ptyp[k]==34 && podl[k]<sodl[k]){
            obraz[1][k]='\\';
            obraz[2][k]='o';
            obraz[3][k]=' ';
            obraz[4][k]='\\';
            obraz[5][k]=' ';
            obraz[6][k]='_';
            obraz[7][k]='/';
        }
        else if(ptyp[k]==35 && podl[k]<sodl[k]){
            obraz[1][k]='-';
            obraz[2][k]=' ';
            obraz[3][k]=' ';
            obraz[4][k]='^';
            obraz[5][k]=' ';
            obraz[6][k]='_';
        }
        else if(ptyp[k]==36 && podl[k]<sodl[k]){
            obraz[1][k]='/';
            obraz[2][k]='o';
            obraz[3][k]=' ';
            obraz[4][k]='/';
            obraz[5][k]=' ';
            obraz[6][k]='_';
            obraz[7][k]='\\';
        }
        else if(ptyp[k]==37 && podl[k]<sodl[k]){
            obraz[1][k]='_';
            obraz[2][k]=' ';
            obraz[3][k]='/';
            obraz[4][k]='|';
            obraz[5][k]='|';
            obraz[6][k]='|';
            obraz[7][k]='\\';
            obraz[8][k]='\\';
        }
        else if(ptyp[k]==38 && podl[k]<sodl[k]){
            obraz[2][k]=')';
            obraz[3][k]=' ';
            obraz[4][k]='\\';
            obraz[5][k]=' ';
            obraz[6][k]=' ';
            obraz[7][k]=' ';
            obraz[8][k]='\\';
            obraz[9][k]='|';
        }
        else if(ptyp[k]==39 && podl[k]<sodl[k]){
            obraz[2][k]='>';
            obraz[3][k]=' ';
            obraz[4][k]=' ';
            obraz[5][k]='\\';
            obraz[6][k]='@';
            obraz[7][k]=' ';
            obraz[8][k]=' ';
            obraz[9][k]='|';
        }
        else if(ptyp[k]==21 && podl[k]<sodl[k]){
            obraz[3][k]='<';
            obraz[6][k]='@';
            obraz[8][k]='/';
        }
        else if(ptyp[k]==22 && podl[k]<sodl[k]){
            obraz[3][k]='(';
            obraz[5][k]='/';
            obraz[7][k]='/';
            obraz[8][k]='/';
        }
        else if(ptyp[k]==23 && podl[k]<sodl[k]){
            obraz[2][k]='\\';
            obraz[3][k]='o';
            obraz[4][k]='\\';
            obraz[5][k]='|';
            obraz[6][k]='|';
            obraz[7][k]='/';
        }
        else if(ptyp[k]==24 && podl[k]<sodl[k]){
            obraz[2][k]='_';
            obraz[3][k]=' ';
            obraz[4][k]='^';
            obraz[5][k]=' ';
            obraz[6][k]='_';
        }
        else if(ptyp[k]==25 && podl[k]<sodl[k]){
            obraz[2][k]='/';
            obraz[3][k]='o';
            obraz[4][k]='/';
            obraz[5][k]='|';
            obraz[6][k]='|';
            obraz[7][k]='\\';
        }
        else if(ptyp[k]==26 && podl[k]<sodl[k]){
            obraz[3][k]=')';
            obraz[5][k]='\\';
            obraz[7][k]='\\';
            obraz[8][k]='\\';
        }
        else if(ptyp[k]==27 && podl[k]<sodl[k]){
            obraz[3][k]='>';
            obraz[6][k]='@';
            obraz[8][k]='\\';
        }
        else if(ptyp[k]==11 && podl[k]<sodl[k]){
            obraz[4][k]='/';
            obraz[7][k]='/';
        }
        else if(ptyp[k]==12 && podl[k]<sodl[k]){
            obraz[3][k]='(';
            obraz[4][k]='|';
            obraz[5][k]='|';
            obraz[6][k]='/';
        }
        else if(ptyp[k]==13 && podl[k]<sodl[k]){
            obraz[3][k]='"';
            obraz[4][k]=' ';
            obraz[5][k]='_';
        }
        else if(ptyp[k]==14 && podl[k]<sodl[k]){
            obraz[3][k]=')';
            obraz[4][k]='|';
            obraz[5][k]='|';
            obraz[6][k]='\\';
        }
        else if(ptyp[k]==15 && podl[k]<sodl[k]){
            obraz[4][k]='\\';
            obraz[7][k]='\\';
        }
        else if(ptyp[k]==1 && podl[k]<sodl[k]){
            obraz[5][k]='/';
            obraz[6][k]='/';
        }
        else if(ptyp[k]==2 && podl[k]<sodl[k]){
            obraz[4][k]='o';
            obraz[5][k]='|';
        }
        else if(ptyp[k]==3 && podl[k]<sodl[k]){
            obraz[5][k]='\\';
            obraz[6][k]='\\';
        }
    }

    if(kierunek-3>=0){
        obraz[8][kierunek-3]='/';
    }
    else{
        obraz[8][kierunek-3+72]='/';
    }
    if(kierunek-2>=0){
        obraz[7][kierunek-2]='/';
        obraz[8][kierunek-2]='|';
    }
    else{
        obraz[7][kierunek-2+72]='/';
        obraz[8][kierunek-2+72]='|';
    }
    if(kierunek-1>=0){
        obraz[6][kierunek-1]='/';
        obraz[7][kierunek-1]='_';
        obraz[8][kierunek-1]=' ';
    }
    else{
        obraz[6][kierunek-1+72]='/';
        obraz[7][kierunek-1+72]='_';
        obraz[8][kierunek-1+72]=' ';
    }
    obraz[5][kierunek]='+';
    obraz[6][kierunek]='^';
    obraz[7][kierunek]='_';
    obraz[8][kierunek]=' ';
    if(kierunek+1<72){
        obraz[6][kierunek+1]='\\';
        obraz[7][kierunek+1]='_';
        obraz[8][kierunek+1]=' ';
    }
    else{
        obraz[6][kierunek+1-72]='\\';
        obraz[7][kierunek+1-72]='_';
        obraz[8][kierunek+1-72]=' ';
    }
    if(kierunek+2<72){
        obraz[7][kierunek+2]='\\';
        obraz[8][kierunek+2]='|';
    }
    else{
        obraz[7][kierunek+2-72]='\\';
        obraz[8][kierunek+2-72]='|';
    }
    if(kierunek+3<72){
        obraz[8][kierunek+3]='\\';
    }
    else{
        obraz[8][kierunek+3-72]='\\';
    }

    this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void bron()
{
    mciSendStringA("open \"shotgun.wav\" type waveaudio alias strzal", NULL, 0, NULL);
    mciSendStringA("open \"smiercwroga1.wav\" type waveaudio alias smiercwroga", NULL, 0, NULL);
    while(true){
        if(ml==true){
            if(nrprzeciwnik[kierunek]!=0 && podl[kierunek]<sodl[kierunek]){
                pzprzeciwnik[nrprzeciwnik[kierunek]]=pzprzeciwnik[nrprzeciwnik[kierunek]]-110;
                if(pzprzeciwnik[nrprzeciwnik[kierunek]]<=0){
                    t[wprzeciwnik[nrprzeciwnik[kierunek]]][kprzeciwnik[nrprzeciwnik[kierunek]]]=0;
                    pokonani++;
                    pozostalo--;
                    mciSendStringA("seek smiercwroga to start", NULL, 0, NULL);
                    mciSendStringA("play smiercwroga", NULL, 0, NULL);
                }
            }
            mciSendStringA("seek strzal to start", NULL, 0, NULL);
            mciSendStringA("play strzal", NULL, 0, NULL);
            this_thread::sleep_for(std::chrono::milliseconds(800));
            ml=false;
        }
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void muzyka()
{
    while(true){
        PlaySoundA("DOOMmuzyka.wav", NULL, SND_FILENAME | SND_SYNC | SND_NODEFAULT);
    }
}

int main()
{
/*
    ios_base::sync_with_stdio(false);
*/
    eszerokosc = GetSystemMetrics(SM_CXSCREEN);
    ewysokosc = GetSystemMetrics(SM_CYSCREEN);
    srszerokosc = eszerokosc/2;
    srwysokosc = ewysokosc/2;
    for(int w=0;w<zasieg;w++){
        for(int k=0;k<zasieg;k++){
            x=k-pwg;
            y=pwg-w;
            radiany=atan2(x, y);
            stopnie=radiany*180.0/M_PI;
            if(stopnie<0) stopnie=stopnie+360;
            stopnie=round(stopnie/5);
            if(stopnie==72) stopnie=0;
            kat[w][k]=stopnie;
        }
    }
    for(int w=0;w<zasieg;w++){
        for(int k=0;k<zasieg;k++){
            x=k-pwg;
            y=pwg-w;
            if(x!=0){
                radiany=atan2(x, y);
                odleglosc=x/sin(radiany);
            }
            else{
                odleglosc=abs(y);

            }
            odleglosc = round(odleglosc);
            odl[w][k]=odleglosc;
        }
    }

    cout<<"\e[?25l";
    cout<<"          __    __   __           ____ __            "<<"\n";
    cout<<"          | \\  |  | |  | \\    /      | | \\           "<<"\n";
    cout<<"          |  | |  | |  | |\\  /|   ---| |  |          "<<"\n";
    cout<<"          |_/  |__| |__| | \\/ |   ___| |_/           "<<"\n";
    cout<<"                       -------                       "<<"\n";
    cout<<"                      | START |                      "<<"\n";
    cout<<"                       -------                       "<<"\n";
    cout<<"                  przybli¿ konsole                   "<<"\n";
    cout<<"                   nacisnij start                    "<<"\n";
    cout<<"                 gdy bedziesz gotowy                 ";
    while(start==false){
        GetCursorPos(&kursor);
        if(GetAsyncKeyState(VK_LBUTTON) & 0x8000){
            if(kursor.x>=1000 && kursor.x<=1450 && kursor.y>=410 && kursor.y<=660){
                start=true;
            }
        }
        if(GetAsyncKeyState('P') & 0x8000) system("cls");
    }

    srand(time(NULL));
    los = rand()%2;

    wpok=(rand()%(grozmiar-8))+4;
    kpok=(rand()%(grozmiar-8))+4;
    lwys=3-rand()%3;
    lszer=3-rand()%3;
    for(int w=lwys*(-1);w<=lwys;w++){
        for(int k=lszer*(-1);k<=lszer;k++){
            gt[wpok+w][kpok+k]=1;
        }
    }
    gw=wpok;
    gk=kpok;
    wstart=wpok;
    kstart=kpok;

    for(int i=0;i<100;i++){
        wpok=(rand()%(grozmiar-8))+4;
        kpok=(rand()%(grozmiar-8))+4;
        lwys=3-rand()%3;
        lszer=3-rand()%3;
        pusto=true;
        for(int w=lwys*(-1);w<=lwys;w++){
            for(int k=lszer*(-1);k<=lszer;k++){
                if(gt[wpok+w][kpok+k]==1) pusto=false;
            }
        }
        if(pusto==true){
        for(int w=lwys*(-1);w<=lwys;w++){
            for(int k=lszer*(-1);k<=lszer;k++){
                gt[wpok+w][kpok+k]=1;
            }
        }
        if(rand()%2==0){
            while(gw<wpok){
                gw++;
                gt[gw][gk]=1;
            }
            while(gw>wpok){
                gw--;
                gt[gw][gk]=1;
            }
            while(gk<kpok){
                gk++;
                gt[gw][gk]=1;
            }
            while(gk>kpok){
                gk--;
                gt[gw][gk]=1;
            }
        }
        else{
            while(gk<kpok){
                gk++;
                gt[gw][gk]=1;
            }
            while(gk>kpok){
                gk--;
                gt[gw][gk]=1;
            }
            while(gw<wpok){
                gw++;
                gt[gw][gk]=1;
            }
            while(gw>wpok){
                gw--;
                gt[gw][gk]=1;
            }
        }
        gw=wpok;
        gk=kpok;
        }
    }
    for(int w=1;w<grozmiar-1;w++){
        for(int k=1;k<grozmiar-1;k++){
            if(rand()%12==0 && gt[w][k]==1     && gt[w-1][k-1]!=5 && gt[w-1][k]!=5 && gt[w-1][k+1]!=5      && gt[w][k-1]!=5 && gt[w][k]!=5 && gt[w][k+1]!=5     && gt[w+1][k-1]!=5 && gt[w+1][k]!=5 && gt[w+1][k+1]!=5){
                gt[w][k]=5;
            }
        }
    }

/*
            for(int w=0;w<grozmiar;w++){
                for(int k=0;k<grozmiar;k++){
                    if(gt[w][k]==0) cout<<"  ";
                    else if(gt[w][k]==5) cout<<"@ ";
                    else cout<<gt[w][k]<<" ";
                }
                cout<<"\n";
            }
*/

    for(int gw=0;gw<grozmiar;gw++){                               //gw generator wiersz
        for(int gk=0;gk<grozmiar;gk++){                           //gk renerator kolumna
            if(gt[gw][gk]==0){                                    //gt na t
                for(int w=gw*skala;w<gw*skala+skala;w++){
                    for(int k=gk*skala;k<gk*skala+skala;k++){
                        t[w][k]=1;
                    }
                }
            }
            else if(gt[gw][gk]==1){
                for(int w=gw*skala;w<gw*skala+skala;w++){
                    for(int k=gk*skala;k<gk*skala+skala;k++){
                        t[w][k]=0;
                    }
                }
            }
            else if(gt[gw][gk]==5 || gt[gw][gk]==3){
                for(int w=gw*skala;w<gw*skala+skala;w++){
                    for(int k=gk*skala;k<gk*skala+skala;k++){
                        if(w%skala!=skala/2-1 || k%skala!=skala/2-1){
                            t[w][k]=0;
                        }
                        else{
                            if(gt[gw][gk]==5){
                                t[w][k]=5;
                            }
                            else{
                                t[w][k]=3;

                            }
                        }
                    }
                }
            }
        }
    }
/*
    for(int i=0;i<1000;i++){
        for(int j=0;j<1000;j++){
            cout<<t[i][j]<<" ";
        }
        cout<<"\n";
    }
*/
    for(int w=skala;w<rozmiart-skala;w++){
        for(int k=skala;k<rozmiart-skala;k++){
            if(t[w][k]==5){
                lwrogow++;
                wprzeciwnik[lwrogow]=w;
                kprzeciwnik[lwrogow]=k;
                pzprzeciwnik[lwrogow]=100;
            }
            if(t[w][k]==1){
                if(t[w-1][k]==0 && t[w][k+1]==0 && t[w+1][k]==1 && t[w][k-1]==1){
                    t[w][k]=2;
                }
                else if(t[w-1][k]==1 && t[w][k+1]==0 && t[w+1][k]==0 && t[w][k-1]==1){
                    t[w][k]=2;
                }
                else if(t[w-1][k]==1 && t[w][k+1]==1 && t[w+1][k]==0 && t[w][k-1]==0){
                    t[w][k]=2;
                }
                else if(t[w-1][k]==0 && t[w][k+1]==1 && t[w+1][k]==1 && t[w][k-1]==0){
                    t[w][k]=2;
                }
                else if(t[w-1][k]==1 && t[w][k+1]==1 && t[w+1][k]==1 && t[w][k-1]==1){
                    if(t[w-1][k-1]==0 || t[w-1][k+1]==0 || t[w+1][k-1]==0 || t[w+1][k+1]==0){
                        t[w][k]=2;
                    }
                }
            }
        }
    }
    g1wiersz=wstart*skala+skala/2-1;
    g1kolumna=kstart*skala+skala/2-1;
    t[g1wiersz][g1kolumna]=3;
    pozostalo=lwrogow;
    thread f1(sterowanie);
    thread f2(ekran);
    thread f3(gracz1);
    thread f4(render);
    thread f5(bron);
    thread f6(muzyka);

    f1.join();
    f2.join();
    f3.join();
    f4.join();
    f5.join();
    f6.join();

}
