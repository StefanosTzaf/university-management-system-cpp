#include <iostream>
#include "rect.h"

using namespace std;

//Πρεπει να υπαρχει η αρχικοποιηση της εδω Ή  στο object file(rect.cpp)

int main(void){
    //r1 se 0,0
    rect r1(1,2),r2(3,4);
    rect r5;
    r1.print_count();
    r5 = r1;
    cout << r5;
    rect ours;
    cin >> ours;
    cout << ours;
    return 0;
}