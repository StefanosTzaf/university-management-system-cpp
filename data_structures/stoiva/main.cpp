#include <iostream>

using namespace std;
#include "../../rect/rect.h"
#include "stoiva.h"

int main(void){

    rect r1(1,1);
    rect r2(2,2);
    rect r3(3,3);
    rect r4(4,4);
    rect r35(35,35);

    my_stack<rect> s1(r1);
    s1.push(r2);
    s1.push(r3);
    s1.push(r4);


    my_stack<rect> s3;
    s3.push(r35);

    my_stack<rect>s2(s1);

    cout << "After 3 push s1:\n";;
    s1.print();
    s1.pop();   
    cout <<"After 1 pop s1:\n";
    s1.print();
    cout <<"size of s1 is: "<<s1.get_size()<<endl<<endl;

    

    cout <<"size of copy s2 is: "<<s2.get_size()<<endl;
    cout <<"top of copy s2 is:\n" <<s2.get_top()<<endl;
    s2.pop();
    s2.pop();
    cout <<"after 2 pops s2:\n" <<s2.get_top()<<endl;
    cout <<"size of copy s2 is: "<<s2.get_size()<<endl;

   // my_stack<rect> sum;
   // sum = s3 + s2;
    return 0;
}

