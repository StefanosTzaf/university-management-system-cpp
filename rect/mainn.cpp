#include <iostream>
#include "rect.h"

using namespace std;

//Πρεπει να υπαρχει η αρχικοποιηση της εδω
int rect::count_of_objects = 0;

int main(void){
    //r1 se 0,0
    rect r1(1,2),r2(3,4),r4(5,6);
    rect r5;
    r5 = r4;
    r5.print();
    r4.set_mikos(0);
    r5.print();
    return 0;
}