#include "classes.h"

using namespace std;


//constructors
Person::Person(const string &firstName, const string &lastname, const string &dateOfBirth, 
               const string &phone, const string &email)
                : firstName(firstName), lastName(lastname), dateOfBirth(dateOfBirth), phoneNumber(phone), email(email){

    count ++;
}

Person::Person()
    : firstName("empty"), lastName("empty"), dateOfBirth("empty"),
     phoneNumber("empty"), email("empty"){
    
    
    count++;
}

//decοnstructor
Person::~Person(){
    count --;
}

//copy constructor
Person::Person(Person const &P){
    firstName = P.firstName;
    lastName = P.lastName;
    dateOfBirth = P.dateOfBirth;
    phoneNumber = P.phoneNumber;
    email = P.email;

    count++;
}

int Person::countOfPeople() const{
    return count;
}

ostream &operator<<(ostream &os,const Person &p1){
    os <<"FIRST NAME : " <<p1.firstName<<"\n";
    os <<"LAST NAME : "<<p1.lastName<<"\n";
    os <<"DATE OF BIRTH  : "<<p1.dateOfBirth<<"\n";
    os <<"PHONE NUMBER: "<<p1.phoneNumber<<"\n";
    os << "EMAIL : " << p1.email<<"\n";
    
    return os;
   
} 

istream &operator>>(istream &str,Person &p1){
    cout <<"First name: ";
    str >> p1.firstName;
    cout << "Last name: ";
    str >> p1.lastName;
    cout << "Date of birth: ";
    str >> p1.dateOfBirth;
    cout << "Phone number: ";
    str >> p1.phoneNumber;
    cout << "Email: ";
    str >> p1.email;
    cout <<endl;
    return str;
}


//θα χρειαστει για το secretary (set)
bool Person::operator<(const Person &p)const{
    if(lastName < p.lastName){
        return true;
    }
    else if(lastName > p.lastName){
        return false;
    }
    else{//αν εχουν ιδια επιθετα συγκριση ονοματων
        if(firstName < p.firstName){
            return true;
        }
        else if(firstName > p.firstName){
            return false;
        }
        else{
        //σε περιπτωση ιδιου ονοματος και ιδιου επιθετου (σπανιο αλλα μπορει να συμβει)
        //δε θελουμε το set να τους θεωρει ιδιους και να μη βαζει εναν ,καταταξη μεσω αριθμου τηλεφώνου(μοναδικος σιγουρα)
            if(phoneNumber < p.phoneNumber){
                return true;
            }
            else{
                return false;
            }
        }
    } 
}