#include <iostream>
#include "classes.h"
#include <string>
#include <set>
#include <algorithm>

//constructors
Secretary::Secretary(){

}

Secretary::Secretary(const Person &p){
    Person* new_person = new Person(p);
    people.insert(new_person);
}


Secretary::~Secretary(){
    set <Person*>::iterator it;
    for(it = people.begin();it != people.end();it++){
        delete *it;
    }
    people.clear();
}

bool Secretary::operator+(const Person &p){
    //αν υπαρχει ηδη
    if(find_person(&p) ){
        //Αν υπαρχει ήδη στο set της secretary προφανως δεν θέλουμε
        //να τον ξαναβαλει (το set δεν θα το επετρεπε ετσι κιαλλιως 
        //αλλα θα υπήρχε ένα θέμα με memory leak, εφοσον θα έκανε το memory
        //allocation αλλα οχι το insert).
        return false;
    }
    else{
        Person* new_person = new Person(p);
        if(new_person != NULL){
            people.insert(new_person);
            return true;
        }
        return false;
    }
}

ostream &operator<<(ostream &os,const Secretary &s1){
    set <Person*>::iterator it;
    os << "People of this secretary are\n\n";
    os << "            |\n";
    os << "            V\n\n";
    for(it = s1.people.begin();it != s1.people.end();it++){
        cout << **it ;
    }
    return os;
}

istream &operator>>(istream &is, Secretary &s1){

    do{
        cout << "For 'New' Person Press 'N' for 'Exit' Press 'E' :\n";

        char ch;
        cin >>ch;
        while(ch != 'N' && ch != 'n' && ch != 'E' &&ch != 'e'){
            cout << "Give a Valid letter please ";
            cin >> ch;
        }
        if(ch == 'N' || ch == 'n'){

            Person* new_person = new Person;
            cin >> *new_person;
            if(s1.find_person(new_person) == 0){
                s1.people.insert(new_person);
            }
            else{
                cout <<"This person exists!\n";
                delete new_person;
            }
        }
        else{//αν εινα e η E
            break;
        }
    }
    while(1);
    return is;
}


bool Secretary::find_person(const Person* const p)const{
    set<Person*>::iterator it;
    bool found = false;
    for(it = people.begin();it!= people.end();it++){
        //αν εχει αυτα τα τρια ιδια θα ειναι αυτος
        if((*it)->getFirstName() == p->getFirstName() &&
           (*it)->getLastName() == p->getLastName() &&
           (*it)->getPhone() == p->getPhone() ){
                found = true;
                break;
           }
    }
    if(found == false){
        return false;
    }
    else{
        return true;
    }
}


//copy constructor
Secretary::Secretary(const Secretary &s){
    set<Person*>::iterator it;
    for(it = s.people.begin();it != s.people.end();it++){
        (*this) + (**it);
    }
}


Secretary& Secretary:: operator = (const Secretary &s){
    set<Person*>::iterator it;
    
    //διαγραφη δεδομενων που υπηρχαν πριν στο set

    for(it = people.begin();it != people.end();it++){
       
        delete *it;
    }
    people.clear();//αφαιρει και τους null pointers για να μην υπαρχει θεμα στο dereference

    for(it = s.people.begin();it != s.people.end();it++){
        
        (*this) + (**it);
    }   
    return *this;
}
