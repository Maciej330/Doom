#include<iostream>
#include<cmath>
#include <chrono>
using namespace std;
constexpr int rozmiart = 802;
int t[rozmiart][rozmiart];
int main()
{
    cout<< "{1";
    for(int a=1;a<rozmiart;a++){
        cout<< ",1";
    }
    cout<< "},";
    for(int w=0;w<rozmiart-2;w++){
        cout<< "{1,";
        for(int k=1;k<rozmiart-1;k++){
            cout<< "0,";
        }
        cout<< "1}," << endl;
    }
    cout<< "{1";
    for(int a=1;a<rozmiart;a++){
        cout<< ",1";
    }
    cout<< "}";
}
