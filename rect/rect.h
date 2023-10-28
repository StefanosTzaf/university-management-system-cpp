typedef void* Pointer;


class rect{
    private:
   
    static int count_of_objects;
    float platos;
    float mikos;

    public :
    
    static void print_count(void);//το στατικ μονο εδω στην δηλωση
    float get_mikos();
    float get_platos();
    void set_platos(float p);
    void set_mikos(float m);
 
    void print();
    rect();
    rect(int m,int p);
    ~rect();
    float emvadon();
    friend rect addrects(const rect &rect1,const rect &rect2);
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


