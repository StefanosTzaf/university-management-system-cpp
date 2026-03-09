#include "classes.h"
#include <limits>

using namespace std;

Course::Course():courseName("empty"), ects(0), type("empty"), numberOfSemester(0), professor(nullptr){

}

Course::~Course(){
    // Since we do not allocate dynamic memory, just clear the map
    enrolledStudents.clear();
}


Course::Course(string courseName, int ECTS, string type, int numberOfSemester) : 
              courseName(courseName), ects(ECTS), type(type), numberOfSemester(numberOfSemester), professor(nullptr) {


}

// Copy constructor
Course :: Course(const Course& course){
    this->courseName = course.courseName;
    this->ects = course.ects;
    this->type = course.type;
    this->numberOfSemester = course.numberOfSemester;
    
    // If professor exists, copy it
    if(course.getProfessor() != nullptr){
        this->professor = course.getProfessor();
    }
    else{
        this->professor = nullptr;
    }
    
    
    this->enrolledStudents.clear();

     for(auto it = course.enrolledStudents.begin(); it != course.enrolledStudents.end(); ++it){
          this->enrolledStudents.insert(*it);
     } 
}


void Course::modifySemester(int numberOfSemester){
    this->numberOfSemester = numberOfSemester;
}

void Course :: setProfessor( Professor* newProfessor) {
    this->professor = newProfessor; 
}

void Course :: declareCourse(const Student &student){
    enrolledStudents.insert(pair<Student, string>(student, "not_examined"));
}

void Course::removeStudent(const Student &student){
    for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ++it) {
        if ((*it).first.getRegistrationNumber() == student.getRegistrationNumber()) {
            enrolledStudents.erase(it);
            break;
        }
    }
}

void Course::clearProfessor(const Professor *professor){
    if (this->professor == nullptr || professor == nullptr) {
        return;
    }

    if (this->professor->getRegNum() == professor->getRegNum()) {
        this->professor = nullptr;
    }
}

 // Checks whether the student is enrolled in this course
bool Course :: containsStudentByRegNum(const Student &student){

    bool contained = false;
    
     for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); it++) {
        
        if ((*it).first.getRegistrationNumber() == student.getRegistrationNumber()) {
            contained = true;
            break;
        }
     }
    return contained;
}


void Course :: registerGrade(const Student &student,const float grade){
    enrolledStudents[student] = to_string(grade);

}

string Course:: getGradeOfStudent(const Student &student){
    for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ++it) {
        if ((*it).first.getRegistrationNumber() == student.getRegistrationNumber()) {
            return (*it).second;
        }
    }

    return "not_examined";
}

bool Course::operator<(const Course &c1)const {
    return courseName < c1.courseName;
}

bool Course::operator == (const Course &c1)const {
    return courseName == c1.courseName;
}

void Course ::studentsPassedCourse(void){
  
    cout << "Students that passed Course "<<this->courseName<< " are:\n";
  
    for(auto it = enrolledStudents.begin();it != enrolledStudents.end();++it){
  
        if((*it).second != "not_examined"){
           
            if (stof( (*it).second) >= 5.0){
           
                cout << (*it).first.getFirstName()<<" "<<(*it).first.getLastName()<<" "<<
                (*it).first.getRegistrationNumber()<<" - "<<(*it).second<<endl;
            }
        }
    }

}

int Course:: countOfStudentsPassedCourse() const{

    int total = 0;

    for(auto it = enrolledStudents.begin();it != enrolledStudents.end();++it){

        if((*it).second != "not_examined"){
            if (stof( (*it).second) >= 5.0){
                total++;
            }
        }
    }
    return total;
}

int Course:: countOfStudentsNotPassedCourse() const{

    int total = 0;

    for(auto it = enrolledStudents.begin();it != enrolledStudents.end();++it){
        
        if((*it).second != "not_examined"){
        
            if (stof( (*it).second) < 5.0){
                total++;
            }
        }
    }
    return total;
}

// Read course data from user input
 istream &operator>>(istream &is, Course &course){
    cout << "Enter Courses Name: ";
    is >> course.courseName;
    
    cout << "Enter Ects: ";
    while (!(is >> course.ects)) {
        cout << "Please enter an integer: \n";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Ignore every character until Enter is pressed
    }
    
    cout << "Enter type (Compulsory - elective): ";
    is >> course.type;
    
    while(course.type != "Elective" && course.type != "elective" && course.type != "Compulsory" && course.type != "compulsory" ){
        cout <<"Please enter Valid type of Course (Elective - Compulsory)\n";
        is >> course.type;
    }
    
    cout << "Enter semester: ";
    while (!(is >> course.numberOfSemester)) {
        cout << "Please enter an integer: \n";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Ignore every character until Enter is pressed
    }
    
    return is;
 }


ostream &operator<<(ostream &os,const Course &course){
    os << "Courses Name: ";
    os << course.courseName;
    os << "\nEcts: ";
    os << course.ects;
    os << "\nType : ";
    os << course.type;
    os << "\nsemester: ";
    os << course.numberOfSemester;
    return os;
 }


void Course:: displayStatisticsOfCourse(){
    cout << "Statistics for course " << getCourseName() << " are:\n";

        int passed = countOfStudentsPassedCourse();
        int notPassed = countOfStudentsNotPassedCourse();
        int sum = passed + notPassed;
        float passedPercent;
        
        if (sum != 0) {
            passedPercent  = ((float)passed / sum) * 100 ;
            cout << passed << " students passed \n" ;
            cout << notPassed << " students did not pass \n";
            cout << passedPercent << "% percentage of success\n";
            cout << "-------------------------\n\n";
        }
        else {
            passedPercent = 0;
            cout << "no students examined yet\n\n";
        }
}
