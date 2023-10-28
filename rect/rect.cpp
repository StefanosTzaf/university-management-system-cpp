#include <iostream>
#include "rect.h"

using namespace std;


//getters - accesors
float rect::get_mikos(){
    return mikos;
}
float rect::get_platos(){
    return platos;
}


//setters -- mutators
void rect::set_mikos(float m){
    mikos = m ;
}
void rect::set_platos(float p){
    platos = p ;
}



//--------------------------------CONSTRUCTORS------------------------------------
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

rect rect:: operator+(const rect &op2){
    rect t;
    t.mikos =  mikos +op2.mikos;
    t.platos =  platos +op2.platos;
    return t;
}

//ΔΕΝ χρειαζεται το : ΟΥΤΕ ΤΟ friend στην υλοποιηση ΣΑΝ μια απλη συναρτηση
float emvadon(const rect &rect1){
    return rect1.mikos*rect1.platos;
}
//-----------------------------PRINTS---------------------------------

//λογω της private μεταβλητης 
void rect::print_count(void){
     cout << "There are "<<count_of_objects<<" objects  now.\n";
}
void rect::print(){
    cout <<"Mikos is: " << mikos <<", Platos is: " <<platos << endl ;
}

//--------------------------------------------CLASS GROUP----------------------------------------

Group::Group(int x):n(x){
    group = new rect[n];
}

Group::~Group(){
    delete []group;
}


Group::Group(const Group &g){
    //delete[] group;
    n = g.n;
   
    group = new rect[n];
    
    for(int i = 0;i < n;i++){
        group[i] = g.group[i]; 
    }
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

