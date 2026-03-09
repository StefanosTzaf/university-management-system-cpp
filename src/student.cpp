#include "classes.h"
#include <limits>

using namespace std;

Student::Student(): Person(),currentSemester(0), registrationNumber("empty"), typeOfStudent("empty"){
}


Student::Student(string const &firstName,string const &lastName,string const &dateOfBirth,string const &phone,string const &email,
        int const &semester,string const &registrationNumber,string const &type)

        : Person(firstName, lastName, dateOfBirth, phone, email) ,
         currentSemester(semester),registrationNumber(registrationNumber), typeOfStudent(type){
}

Student::~Student() {

}

Student:: Student(const Student& student)
    : Person(student),  
        currentSemester(student.currentSemester),
        registrationNumber(student.registrationNumber),
        typeOfStudent(student.typeOfStudent) {
}


void Student::display(void) const{
    // Since we are using the overloaded << operator, it will display the characteristics of Person
    cout << "Student 's characteristics :\n";
    cout << *this;
    cout << "CURRENT SEMESTER : " << currentSemester << endl;
    cout << "REGISTRATION NUMBER : " << registrationNumber << endl;
    cout << "TYPE OF STUDENT : " << typeOfStudent << endl << endl;
}


// For reading student data from input
istream &operator>>(istream &str, Student &student){

    // Read the characteristics of Person first
    Person& person = student;  
    str >> person; 
    cout <<"Current semester: ";

    // Ensure the input is valid (based on a solution found online)
    while (!(str >> student.currentSemester)) {
        cout << "Please enter an integer: \n";
        str.clear();
        str.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Ignore every character until Enter is pressed
    }

    cout << "Registration number: ";
    str >> student.registrationNumber;
    cout << "Type of student: ";
    str >> student.typeOfStudent;

    return str;
}