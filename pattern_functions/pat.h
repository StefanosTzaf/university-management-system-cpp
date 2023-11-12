#include <iostream>

using namespace std;

//και η υλοποιηση εδω λόγω template
template <class T>
T max1(T a,T b){
    return a > b?a:b;
}

template <class T1,class T2>
void max_different_types(T1 a,T2 b){
    cout << "Max is "<< (a > b?a:b) <<endl;
}

template <class T>
class zevgos{
    T a;
    T b;
    public:
    zevgos(T a,T b){
        this->a = a;
        this->b = b;
    }
    T add(){
        return a+b;
    } 
};