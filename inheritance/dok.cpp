#include <iostream>

using namespace std;

class one{
    public:
        virtual void f1(){
            cout << "1 ";
            f2();
        }
        void f2(){
            cout << "2\n ";
        }
};

class two : public one{
    public:
        void f1(){
            cout << "3 ";
            f2();
        }
         void f2(){
            cout << "4\n";
        }
};

class three : public two{
    public:
        void f1(){
            cout << "5 ";
            f2();
        }
         void f2(){
            cout << "6\n";
        }
};

int main(){
    one* p1 = new two;
    p1->f1();
    p1 = new three;
    p1->f1();
    two* p2 = new three;
    p2->f1();//θα κληθει η f2 της three αφου υπάρχει η  f2  και εχει γινει override
    p2->f2();//θα κληθει η 4 αφου δεν ειναι  virtual  η f2


    p1 = new two;
    if(typeid(*p1) == typeid(one) ){
        cout << "TYPE ONE\n";
    }
    else if(typeid(*p1) == typeid(two)){
        cout << "TYPE TWO\n";
    }
    else{
        cout << "TYPE THREE\n";
    }


    p1 = new three;
    if(typeid(*p1) == typeid(one) ){
        cout << "TYPE ONE\n";
    }
    else if(typeid(*p1) == typeid(two)){
        cout << "TYPE TWO\n";
    }
    else{
        cout << "TYPE THREE\n";
    }
    return 0;
}