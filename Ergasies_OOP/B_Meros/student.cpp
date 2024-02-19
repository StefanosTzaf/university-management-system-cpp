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
    //αφου έχουμε κάνει υπερφορτωση του <<  θα πάει να εκτυπώσει τα χαρακτηριστικα του Person κομματιου
    cout << "Student 's characteristics :\n";
    cout << *this;
    cout << "CURRENT SEMESTER : " << currentSemester << endl;
    cout << "REGISTRATION NUMBER : " << registrationNumber << endl;
    cout << "TYPE OF STUDENT : " << typeOfStudent << endl << endl;
}


//για ανάγνωση μαθητή απ΄ό τον χρήστη
istream &operator>>(istream &str, Student &student){

    //διαβάζει τα χαρακτηριστικά του Person πρώτα
    Person& person = student;  
    str >> person; 
    cout <<"Current semester: ";

    //σε περίπτωση που δεν δοθεί ακέραιος(βρήκαμε στο internet την λούπα αυτή για να το διαχειρίζεται σωστά)
    while (!(str >> student.currentSemester)) {
        cout << "Please enter an integer: \n";
        str.clear();
        str.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//αγνοει κάθε χαρακτήρα μεχρι το enter
    }

    cout << "Registration number: ";
    str >> student.registrationNumber;
    cout << "Type of student: ";
    str >> student.typeOfStudent;

    return str;
}