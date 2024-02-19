#include <string>
#include <set>
using namespace std;


class Person{
    private:
        string FirstName;
        string LastName;
        string Date_of_Birth;
        string Faculty;
        string Status;
        string Nationality;
        string Phone_Number;
        string Email;
        string Gender;

        static int count;
    public:

        string getLastName() const{
            return LastName;    
        }

        string getFirstName() const{
            return FirstName;
        }

        string getPhone() const{
            return Phone_Number;    
        }

        string getGender(){
            return Gender;
        }//για περιπ΄τωσεις στατιστικών ερευνών 

        //αλλαγη στοιχειων επικοινωνιας
        void setPhone(string const &new_phone){
            Phone_Number = new_phone;
        }

        void setEmail(string const &new_email){
            Email = new_email;
        }

        Person(string const &firstname,string const &lastname,string const &date_of_birth,string const &faculty,
        string const &status ,string const &nationality,string const &phone,string const &email,string const &gender);

        Person();

        Person(Person const &P);

        ~Person();
        
        int count_of_people() const;

        friend ostream &operator<<(ostream &os,const Person &p1);

        friend istream &operator>>(istream &is, Person &p1);

        bool operator<(const Person &p)const; //υπερφορτωση τελεστη < που θα χρειαστει στην συναρτηση  compare του set

};



class Secretary{
    private:

    //βρήκαμε πως μπορούμε να ορ΄ίσουμε συνάρτηση
    //συγκρισης για τα στοιχεία του σετ εφόσον είναι pointers και δεν καλειται ο τελεστης < 
    //οπως για τα πέρσον αυτόματα.
        struct PersonCompare {
            bool operator()(const Person *p1, const Person *p2) const {
                if(*p1 < *p2){
                    return true;
                }
            return false;
            }
        };

        set<Person*, PersonCompare> people;
    public:
        Secretary();
        Secretary(const Person &p);
        ~Secretary();

        bool operator+(const Person &p); 

        friend ostream &operator<<(ostream &os,const Secretary &s1);
        friend istream &operator>>(istream &is, Secretary &s1);

        bool find_person(const Person* const  p1)const ;

        Secretary(const Secretary &s);

        Secretary& operator = (const Secretary &s); 

};