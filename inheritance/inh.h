#include <iostream>
#include "../rect/rect.h"

class box : public rect{
        float vathos;
        using rect::emvadon;//ginetai idiotikh !xwris ()
    public : 
        int ogkos();
        void set_vathos(int v);
        void print(){
            cout << "mikos = " <<mikos<<"\nplatos = "<<platos<<"\nvathos = "<<vathos<<endl;
        }

        box(float x,float y,float z);
        box();

};