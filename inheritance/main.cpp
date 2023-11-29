#include <iostream>
#include "inh.h"
// #include "../rect/rect.h"
using namespace std;

int main(){
    box x(1,2,3);
    cout <<"PRINT TOU BOX\n";
    x.print();
    cout << "PRINT TOU RECT\n";
    x.rect::print();

    return 0;
}