#include <fstream>
#include "../../rect/rect.h"
using namespace std;

int main(){
    rect r[3],rec;

    ofstream fout;
    fout.open("data.txt",ios::binary);

    r[0].set_platos(121);
    r[0].set_mikos(311);
    r[1].set_platos(4);
    r[1].set_mikos(5);
    r[2].set_platos(22);
    r[2].set_mikos(22);

    for(int i = 0;i <= 2;i++){
        fout.write(reinterpret_cast<char *>(&r[i]),sizeof(rect));
    }
    fout.close();
    int pos;

    fstream finout;//θελουμε και να γραψουμε και να διαβασουμε


    finout.open("data.txt",ios::in|ios::out|ios::binary);
    cout << "Which RECTANGLE do you wanna change?\n";
    cin >> pos;
    cin >> rec;

//!!!!ΤΟΠΟΘΕΤΕΙ ΤΟΝ ΔΕΙΤΗ ΑΡΧΕΙΟΥ(συγκεκριμενα τον δεικτη εγγραφης στο 2ο ρεκτ)
    finout.seekp((pos - 1 )*sizeof(rect));
    finout.write(reinterpret_cast<char*>(&rec),sizeof(rect));

    finout.seekg(0);//να αρχισει αναγλωση απο την αρχη
    for(int i = 0;i <= 2;i++){
        //αυτο το string που διαβάζεις βαλτο στην διευ΄θυνση του rec
        finout.read(reinterpret_cast<char*> (&rec),sizeof(rec));
        cout << rec;
    }
    finout.close();
    return 0;
}