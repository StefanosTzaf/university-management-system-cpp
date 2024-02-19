#include <iostream>
#include "classes.h"
#include <string>

using namespace std;


//constructors
Person::Person(const string &firstname, const string &lastname, const string &date_of_birth, const string &faculty,
               const string &status, const string &nationality, const string &phone, const string &email, const string &gender)
                : FirstName(firstname), LastName(lastname), Date_of_Birth(date_of_birth), Faculty(faculty),
                Status(status), Nationality(nationality), Gender(gender), Phone_Number(phone), Email(email){

    count ++;
}

Person::Person()
    : FirstName("empty"), LastName("empty"), Date_of_Birth("empty"), Faculty("empty"),
      Status("empty"), Nationality("empty"), Gender("empty"), Phone_Number("empty"), Email("email") {
    
    
    count++;
}

//decοnstructor
Person::~Person(){
    count --;
}

//copy constructor
Person::Person(Person const &P){
    FirstName = P.FirstName;
    LastName = P.LastName;
    Date_of_Birth = P.Date_of_Birth;
    Faculty = P.Faculty;
    Gender = P.Gender;
    Nationality = P.Nationality;
    Status = P.Status;
    Phone_Number = P.Phone_Number;
    Email = P.Email;

    count++;
}

int Person::count_of_people() const{
    return count;
}

ostream &operator<<(ostream &os,const Person &p1){
    os <<"Person 's characteristics :\n";
    os <<"FIRST NAME : " <<p1.FirstName<<"\n";
    os <<"LAST NAME : "<<p1.LastName<<"\n";
    os <<"DATE OF BIRTH  : "<<p1.Date_of_Birth<<"\n";
    os <<"FACULTY : "<<p1.Faculty<<"\n";
    os <<"STATUS : "<<p1.Status<<"\n";
    os <<"NATIONALITY : "<<p1.Nationality<<"\n";
    os <<"PHONE NUMBER: "<<p1.Phone_Number<<"\n";
    os << "EMAIL : " << p1.Email<<"\n";
    os <<"GENDER : "<<p1.Gender<<"\n\n";
    
    return os;
   
} 

istream &operator>>(istream &str,Person &p1){
    cout << "Give Person 's First name :\n";
    cin >> p1.FirstName;
    cout << "Give Person 's Last name :\n";
    cin >> p1.LastName;
    cout << "Give Person 's Date of birth :\n";
    cin >> p1.Date_of_Birth;
    cout << "Give Person 's Faculty :\n";
    cin >> p1.Faculty;
    cout << "Give Person 's Status\n";
    cin >> p1.Status;
    cout << "Give Person 's Nationality :\n";
    cin >> p1.Nationality;
    cout << "Give Person 's Phone number :\n";
    cin >> p1.Phone_Number;
    cout << "Give Person 's Email :\n";
    cin >> p1.Email;
    cout << "Give Person 's Gender :\n";
    cin >> p1.Gender;
    cout <<endl;
    return str;
}


//θα χρειαστει για το secretary (set)
bool Person::operator<(const Person &p)const{
    if(LastName < p.LastName){
        return true;
    }
    else if(LastName > p.LastName){
        return false;
    }
    else{//αν εχουν ιδια επιθετα συγκριση ονοματων
        if(FirstName < p.FirstName){
            return true;
        }
        else if(FirstName > p.FirstName){
            return false;
        }
        else{
        //σε περιπτωση ιδιου ονοματος και ιδιου επιθετου (σπανιο αλλα μπορει να συμβει)
        //δε θελουμε το set να τους θεωρει ιδιους και να μη βαζει εναν ,καταταξη μεσω αριθμου τηλεφώνου(μοναδικος σιγουρα)
            if(Phone_Number < p.Phone_Number){
                return true;
            }
            else{
                return false;
            }
        }
    } 
}