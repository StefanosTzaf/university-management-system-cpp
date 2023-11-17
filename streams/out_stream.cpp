#include <fstream>

using namespace std;

int main(void){
    //αντικειμενο κλασης ofstream(τυπου αρχειου εξοδου),πρεπει να το συσχετίσω με ένα αρχείο

    ofstream fout;//out file stream
    //If you just use ios::app without ios::out, it will still work in most cases because ios::app implies ios::out.
    //However, it's a good practice to be explicit about your intentions and include both flags when you want to open the file
    // for both output and append operations.
    fout.open("out.txt",ios::out|ios::app);//αν δεν υπάρχει το φτιάχνει
    int x = 4;
    fout <<x;
    fout.close();


    return 0;
}