#include <fstream>
#include <map>
#include <iostream>

using namespace std;

int main(void){


    map <char,int> freq;

    ifstream fin;
    fin.open("syxnothta.txt",ios::binary);
    char ch;
    while(fin.get(ch)){//οσο δεν ειναι eof
        if(ch <= '9' && ch >= '0'){
//when you use the [] operator with a key in a std::map, if the key doesn't exist,
//a new key-value pair is inserted into the map with the default-initialized value 
//for the mapped type (in this case, int, which is 0).
//So, in your code, when you do freq[ch]++ and ch is not already in the map, it will be
// inserted with a default-initialized value of 0, and then the count will be incremented.
            freq[ch]++;
        }
    }

    map<char,int>::iterator it;
    cout << "Frequency of numbers in TXT is:\n";
    for(it = freq.begin();it != freq.end();it++){
        cout << it->first <<" : "<<it->second <<endl;

    }
    return 0;
}