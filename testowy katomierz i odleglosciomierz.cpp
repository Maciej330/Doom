#include<iostream>
#include<cmath>
using namespace std;
int sciany[72];
int main() {
    int x, y, kierunek;
    double radiany, odleglosc, stopnie;
    int obraz[9][27];
    double sciany[72];
    int wiersz=65, kolumna=65;
    int kat[131][131];
    double odl[131][131];

/*
    for(int w=0;w<102;w++){
        for(int k=0;k<102;k++){
            x=k-kolumna;
            y=wiersz-w;
            cout<<x<<"_"<<y<<"  ";
        }
        cout<< endl;
    }

    cout<<endl;
*/
    for(int w=0;w<131;w++){
        for(int k=0;k<131;k++){
            x=k-kolumna;
            y=wiersz-w;
            radiany=atan2(x, y);
            stopnie=radiany*180.0/M_PI;
            if(stopnie<0) stopnie=stopnie+360;
            stopnie=round(stopnie/5);
            if(stopnie==72) stopnie=0;
            cout<<stopnie<<" ";
            if(stopnie<10) cout<<" ";
            kat[w][k]=stopnie;
        }
        cout<< endl;
    }

    cout<<endl;

    for(int w=0;w<131;w++){
        for(int k=0;k<131;k++){
            x=k-kolumna;
            y=wiersz-w;
            if(x!=0){
                radiany=atan2(x, y);
                odleglosc=x/sin(radiany);
            }
            else{
                odleglosc=abs(y);

            }
            odleglosc = round(odleglosc);
            cout<<odleglosc<<" ";
            if(odleglosc<10) cout<< " ";
            odl[w][k]=odleglosc;
        }
        cout<< endl;
    }
    cout<<endl<<endl<<endl;


    for(int w=0;w<102;w++){
        for(int k=0;k<102;k++){
            if(odl[w][k]==14){
                x=k-kolumna;
                y=wiersz-w;
                radiany=atan2(x, y);
                stopnie=radiany*180.0/M_PI;
                if(stopnie<0) stopnie=stopnie+360;
                stopnie=round(stopnie/5);
                cout<<stopnie;
            }
            else cout<<" ";
        }
        cout<<endl;
    }



/*
    int najblizej=100000;
    for(int w=0;w<102;w++){
        for(int k=0;k<102;k++){
            if(kat[w][k]==0 && odl[w][k]>14{
                x=k-kolumna;
                y=wiersz-w;
                sciany[kat[x][y]]=
            }
        }
    }
*/

    }
