#include <iostream>

using namespace std;


int main(void){
    int count = 0;
    int number[10];
    while(cin >> number[count]){
       count++;
    }


    cout << "combinations([";
    int product = 1;
    for(int i = 0;i < count;i++){
        if(number[i] != 0){

            
            //οι συνδυασμοι προκυπτουν αν παρουμε τον πρωτο αριθμο πχ 5 ανα 1 κλπ και τους πολλ/σουμε αρα
            product *=number[i]; 
        }

        //Για να μην τυπώνει εξτρα κενό και κόμα
        cout << number[i];
        if(i != count - 1){
                cout << ", ";
        }
        
    }
    cout << "]) -->";
    cout << " " << product;



    cout <<endl;
    return 0;
}