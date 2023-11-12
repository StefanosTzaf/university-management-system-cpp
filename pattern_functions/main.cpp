#include <iostream>
#include "pat.h"
#include "../rect/rect.h"
using namespace std;

int main(void){
    cout << max1(2,3)<<endl;
    cout << max1(2.4,5.4)<<endl;
    rect r1(14,2);
    rect r2(5,8);
    cout << "rect r1 is:\n"<<r1;
    cout << "rect r2 is:\n"<<r2;
    cout <<"Max of r1, r2(based in their area) is rect with :\n"<< max1(r1,r2);

    max_different_types(2.5,6);
    cout <<"\n\n";
    zevgos<rect> z1(r1,r2);
    cout << z1.add();

    return 0;
}