#include <iostream>
#include "rect.h"

using namespace std;

//Πρεπει να υπαρχει η αρχικοποιηση της εδω
int rect::count_of_objects = 0;

int main(void){
    //r1 se 0,0
    rect r1;
    r1.print();
    int x,y;
    x=4;
    y=6;
    rect r2(x,y);
    r2.print();
    
    rect r3(5,6);

    //kalw kanonika sa synarthsh ektos klashs
    cout << "Emvadon is: "<< emvadon(r3)<<endl;
    rect r4 ;
    r4 = r3 + r2;
    r4.print();
    rect::print_count();
    return 0;
}