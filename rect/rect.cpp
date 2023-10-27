#include <iostream>
#include "rect.h"

using namespace std;


float rect::emvadon(){
    return mikos*platos;
}

float rect::get_mikos(){
    return mikos;
}
float rect::get_platos(){
    return platos;
}

void rect::set_mikos(float m){
    mikos = m ;
}

void rect::set_platos(float p){
    platos = p ;
}
//constructor με αρχικοποιηση στο 0 με initializer list (sto headerfile δεν χρειαζεται)
rect::rect():mikos(0),platos(0){
    count_of_objects++;
}

rect::~rect(){
    count_of_objects--;
}
rect::rect(int m,int p):mikos(m),platos(p){
    if ((m < 0) ||(p < 0)){
        cout << "Sorry no negative values permitted (the corresponding side became 0)\n";
        if(m < 0){
            m = 0;
        }
        else{
            p = 0;
        }
    }
    mikos = m;
    platos = p;
    count_of_objects++;
}
void rect::print_count(void){
     cout << "There are "<<count_of_objects<<"objects  now.";
}
void rect::print(){
    cout <<"Mikos is: " << mikos <<", Platos is: " <<platos << endl ;
}


//ΔΕΝ χρειαζεται το : ΟΥΤΕ ΤΟ friend στην υλοποιηση ΣΑΝ μια απλη συναρτηση
rect addrects(const rect &rect1,const rect &rect2){
    rect r;
    r.platos = rect1.platos+rect2.platos;
    r.mikos = rect1.mikos+rect2.mikos;
    return r;
}


Group::Group(int x):n(x){
    group = new rect[n];
}

Group::~Group(){
    delete []group;
}

void Group::set_rect(int i,float p,float m){
    group[i].set_mikos(m);
    group[i].set_platos(p);
}

rect Group::get_rec(int i) const{
    return group[i];
}

void Group::print(){
    for(int i = 0;i < n;i++){
        group[i].print();
    }
}

Group::Group(const Group &g){
    //delete[] group;
    n = g.n;
   
    group = new rect[n];
    
    for(int i = 0;i < n;i++){
        group[i] = g.group[i]; 
    }
}
