typedef void* Pointer;


class rect{
    float platos;
    float mikos;
    public :
    //accessors
    float get_mikos();
    float get_platos();
    void set_platos(float p);
    void set_mikos(float m);
    
    void print();
    rect();
    rect(int m,int p);
    float emvadon();
};

class Group{
    int n;//μεγεθος πινακα με rect
    rect *group;


    public:
        Group(int x);//constructor
       // ~Group();
        void set_rect(int i,float p,float m);
        rect get_rec(int i) const;
        void print();

};