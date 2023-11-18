#include <fstream>
#include "../../rect/rect.h"

using namespace std;

int main(){
    rect r[3],rec;

    ofstream fout;
    fout.open("data.txt",ios::binary);

    r[0].set_platos(2.5);
    r[0].set_mikos(3.5);
    r[1].set_platos(4.5);
    r[1].set_mikos(5.5);
    r[2].set_platos(11.5);
    r[2].set_mikos(11.5);
//γράφω ένα block από bytes (στο συγκεκριμένο παράδειγμα rect)
//σε αρχειο
    for(int i = 0;i <= 2;i++){
        //δεχεται το array apo chars και το μεγεθος του
        fout.write(reinterpret_cast<char *>(&r[i]),sizeof(rect));
        //to reintepret μετατρεπει τη διευθυνση του r[i] σε char*
    }


    fout.close();

//διαβάζω ένα block δέδομένων
    ifstream fin;
    fin.open("data.txt",ios::binary);
    for(int i = 0;i <= 2;i++){
        //αυτο το string που διαβάζεις βαλτο στην διευ΄θυνση του rec
        fin.read(reinterpret_cast<char*> (&rec),sizeof(rec));
        cout << rec;
    }
    fin.close();
    return 0;
}