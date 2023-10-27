#include <iostream>
#include "rect.h"

using namespace std;

int main(void){
    //r1 se 0,0
    rect r1;
    r1.print();

    int mikos,platos;
    cout<<"Give high and width: ";
    cin >>mikos>>platos;
    rect r2(mikos,platos);
    r2.print();
    
    rect r3(5,6);

    rect r4;
    //kalw kanonika sa synarthsh ektos klashs
    r4 = addrects(r3,r2);
    r4.print();
    cout << r4.count_of_objects;
    return 0;

}