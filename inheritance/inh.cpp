#include <iostream>
#include "inh.h"
// #include "../rect/rect.h"

using namespace std;

int box ::ogkos(){
    return vathos*platos*mikos; //εχουν οριστει ως protected
}

void box :: set_vathos(int v){
    vathos = v;
}

box::box(){

}

box::box(float x,float y,float z):rect( x, y){
     vathos = z;
}