#include <iostream>
#include "rect.h"

using namespace std;

int main(void){
    Group g(3);
    g.set_rect(0,3,3);
    g.set_rect(1,2,2);
    g.set_rect(2,5,5);
    g.print();
    return 0;
}