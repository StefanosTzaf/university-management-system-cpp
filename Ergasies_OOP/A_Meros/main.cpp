#include <iostream>
#include "classes.h"
#include <string>
#include <set>

using namespace std;

int Person::count = 0;

int main(void){
    Secretary s,s_equal;

    Person stef("stef","tzaf","2/05/07","dit","student","greek","6","st@","m");
    Person eri("eri","gal","02/04/04","dit","student","bulg","6","el@","fm");

    //πρεπει να μπαινει (διαφορετικο τηλεφωνο)
    Person p_copy("stef","tzaf","02/04/04","dit","student","greek","9","st@","m");

    //δεν θα πρέπει να μπaινει δευτερη φορα
    Person p_copy2("stef","tzaf","02/04/04","dit","student","greek","9","st@","m");
    s + stef;
    s + p_copy;
    s + p_copy2;
    cin >> s;

    Person to_be_deleted("d","d","d","d","d","d","d","d","d");
    s_equal + to_be_deleted;//δεν θα πρεπει να το εκτυπωνει αφου κανουμε αναθεση(διαγραφει τα παλια περιεχομενα)
    //Θα πρέπει να είναι τα ίδια 
    s_equal = s;
    Secretary s_copy = s; //copy constructor

    s + eri;//δεν θα πρεπει να αντανακλα η αλλαγη στο s3,s2 κανουμε
    //deep copy οχι shallow μεσω pointer
    cout <<"------------Original Secretary s :\n\n" <<s;
    cout << "-----------Secretary with '=' --------------\n\n"<<s_equal;
    cout << "-----------Secretary made from copy constructor---------\n\n" << s_copy;
    return 0;
}