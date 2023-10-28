#include <iostream>
using namespace std;

class rect{
    private:
   
        static int count_of_objects;
        float platos;
        float mikos;

    public :
    
        rect();
        rect(int m,int p);
        ~rect();

        //-----------------overloaded operators--------------------------
        //ο πρωτος τελεστης ειναι το αντικειμενο που την καλει
        rect operator+(const rect &op2);
        bool operator>(const rect &op2);
        //προθεματικο ++
        rect operator++();
        rect operator++(int);
        //αν αλλαξει το αντικειμενο που ανατειθεται δεν αλλαζει το ανατιθεμενο
        rect operator=(const rect &op2);

        friend ostream &operator<<(ostream &str, rect &r1);
    
        friend istream &operator>>(istream &str, rect &r1);

        
        float get_mikos();
        float get_platos();
        void set_platos(float p);
        void set_mikos(float m);
        float emvadon() const;
        static void print_count(void);//το στατικ μονο εδω στην δηλωση
        



        //φιλη για να φανει η διαφορα με την συναρτηση κλασης
        friend float emvadon(const rect &rect1);


};

class Group{
    int n;//μεγεθος πινακα με rect
    rect *group;


    public:
        Group(int x);//constructor
        ~Group();
        void set_rect(int i,float p,float m);
        rect get_rec(int i) const;
        void print();
        //copy constructor
        Group(const Group &g);
};


