#include <fstream>
#include <iostream>

using namespace std;

int main(void){     
    ifstream fin;
    fin.open("in.txt");

    int x;
    int sum = 0;
     while(!fin.eof()){
         fin >> x;
         sum+=x;
     }
    cout << "sum is : "<<sum<<endl;

    fin.close();
    return 0;
}