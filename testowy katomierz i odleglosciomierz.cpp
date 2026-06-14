#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int x, y, stopnie;
    float radiany, odleglosc;

    int wiersz=3, kolumna=3;
    int t[7][7]=
    {
        {1,1,1,1,1,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,3,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,1,1,1,1,1,1},
    };

    for(int w=0;w<7;w++){
        for(int k=0;k<7;k++){
            x=k-kolumna;
            y=wiersz-w;
            cout<<x<<"_"<<y<<"  ";
        }
        cout<< endl;
    }

    cout<<endl;

    for(int w=0;w<7;w++){
        for(int k=0;k<7;k++){
            x=k-kolumna;
            y=wiersz-w;
            radiany=atan2(x, y);
            stopnie=radiany*180.0/M_PI;
            if(stopnie<0) stopnie=stopnie+360;
            cout<<stopnie<<" ";
        }
        cout<< endl;
    }

    cout<<endl;

    for(int w=0;w<7;w++){
        for(int k=0;k<7;k++){
            x=k-kolumna;
            y=wiersz-w;
            if(x!=0){
                radiany=atan2(x, y);
                odleglosc=x/sin(radiany);
                cout<<odleglosc<<" ";
            }
            else{
                odleglosc=abs(y);
                cout<<odleglosc<<" ";
            }

        }
        cout<< endl;
    }
}
