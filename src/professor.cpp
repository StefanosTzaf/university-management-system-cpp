#include "classes.h"

using namespace std;


Professor:: Professor():Person(), office("empty"),
                            webPage("empty"), specialization("empty"), registrationNumber("empty"){
}

Professor::Professor(string const &firstName, string const &lastName, string const &dateOfBirth, string const &phone, string const &email, 
        string const &office, string const &webpage, string const &specialization, string const &registrationNumber)

        : Person(firstName, lastName, dateOfBirth, phone, email),
         office(office), webPage(webpage), specialization(specialization), registrationNumber(registrationNumber) {

}

Professor ::~Professor(){
    
}

void Professor::display(void) const{
    cout << "Professor 's characteristics :\n";
    cout << *this;//overloaded << for person
    cout << "REGISTRATION NUMBER :"<<registrationNumber<<endl;
    cout << "OFFICE : " << office << endl;
    cout << "WEB PAGE : " << webPage << endl;
    cout << "SPECIALIZATION : " << specialization  << endl <<endl;
}


istream &operator>>(istream &str, Professor &professor){
    // To call the overloaded >> of person
    Person& person = professor;  
    str >> person; 

    cout << "Registration number: ";
    str >> professor.registrationNumber;
    cout << "Office: ";
    str >> professor.office;
    cout << "Webpage: ";
    str >> professor.webPage;
    cout << "Specialization: ";
    str >> professor.specialization;
 
    return str;

}

//copy constructor
Professor :: Professor(const Professor& professor) : Person(professor) {
    this->office = professor.office;
    this->webPage = professor.webPage;
    this->specialization = professor.specialization;
    this->registrationNumber = professor.registrationNumber;
}