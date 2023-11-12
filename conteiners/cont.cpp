#include <iostream>
#include "../rect/rect.h"
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

bool kata_emvadon(rect r1,rect r2){
    return r1.emvadon() < r2.emvadon();
}

void display(rect r){
    cout << r;
}

void display_map(pair<string,int> x){//αν το βαζα μεσα στην msin ηθελε ->
    cout << x.first<<" ," << x.second<<endl;
}

int main(){
    cout<<"------VECTOR-----\n\n";
    vector <rect> v;
    vector <rect>::iterator it;
    v.push_back(rect(1,44));
    v.push_back(rect(2,3));
    v.push_back(rect(20,10));

    sort(v.begin(),v.end(),kata_emvadon);

    for_each(v.begin(),v.end(),display );
    cout<<"------SET-----\n\n";
    set <rect> s;
    s.insert(rect(1,2));
    s.insert(rect(10,62));
    s.insert(rect(5,2));
    s.insert(rect(8,3));
    //DEN TO VAZEI
    s.insert(rect(1,2));
    //!!!!!!!!!!!!!!!  ΤΑ ΙΣΕΜΒΑΔΙΚΑ ΔΕΝ ΜΠΑΙΝΟΥΝ ΓΙΑΤΙ ΜΠΑΙΝΟΥΝ ΒΑΣΗ ΤΟΥ < OPERATOR OXI TOU ==!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //In other words, two elements are considered equal if !(a < b) && !(b < a) and neither compares less than the other.

    set<rect>::iterator it_s;
    for_each(s.begin(),s.end(),display );


    cout << "-------MAP-------\n\n";
    map<string,int> student;
    map<string,int>::iterator it_m;
    
    //Κρατάει διαταξη βαση κλειδιων αρα εδω αλφαβητικα

    student["Maria"] = 5;
    student.insert(pair<string,int>("Erikos",21));
    student["Stef"] = 14;

    // for(it_m = student.begin();it_m != student.end();it_m ++){
    //     cout << it_m->first<<" ," << it_m->second<<endl;
    // }
    for_each(student.begin(),student.end(),display_map);

    return 0;
}