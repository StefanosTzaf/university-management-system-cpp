#include <fstream>
#include "classes.h"
#include <sstream>

void readStudentFromFile(ifstream &fin, Secretary &secretary){
    fin.open("./data/students.txt", ios::in);

    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string phoneNumber;
    std::string email;
    int currentSemester;
    std::string registrationNumber;
    std::string typeOfStudent;
    std::string courseName;
    std::string grade;

    // Read the basic characteristics of the student until the end of the file
    while (fin >> firstName >> lastName >> dateOfBirth >> phoneNumber >> email >> currentSemester >> registrationNumber >> typeOfStudent) {

        Student tempStudent(firstName, lastName, dateOfBirth, phoneNumber, email, currentSemester, registrationNumber, typeOfStudent);
        secretary.addStudent(&tempStudent);
        

        std::string restOfLine;

        // Read the rest of the line that contains the courses and grades
        std::getline(fin, restOfLine);

        // Convert the string into a stream for further processing (based on a solution found online)
        std::istringstream iss(restOfLine);

        // Process each course and its grade
        while (iss >> courseName >> grade) {
        // While loop ensures that the "stream" reads the "rest" - string
            
            Course* courseToDeclare = secretary.findCourseByName(courseName); 
            
           secretary.declareCourse(*secretary.findStudentByRegNum(registrationNumber),*courseToDeclare);

            if(grade != "not_examined"){

                float gradeValue = std::stof(grade);// Convert the grade to float for registering grades
                secretary.registerGrades(*secretary.findStudentByRegNum(registrationNumber),*courseToDeclare,gradeValue);
            }

        }
    
    }

    fin.close();
}

void writeStudentToFile(ofstream &fout, Secretary &secretary){
    secretary.displayStudentsToFile(fout);
}
 

void readProfessorFromFile(ifstream &fin, Secretary &secretary){
    fin.open("./data/professors.txt", ios::in);
        string firstName;
        string lastName;
        string dateOfBirth;
        string phoneNumber;
        string email;
        string office;
        string webPage;
        string specialization;
        string registrationNumber;

    while(fin >> firstName >> lastName >> dateOfBirth >> phoneNumber >> email >> office >> webPage >> specialization >> registrationNumber) {
        
        Professor tempProfessor(firstName, lastName, dateOfBirth, phoneNumber, email, office, webPage, specialization, registrationNumber);  
        secretary.addProfessor(&tempProfessor);
    }

    fin.close();
}

void writeProfessorToFile(ofstream &fout, Secretary &secretary){
    secretary.displayProfessorsToFile(fout);
}

void readCourseFromFile(ifstream &fin, Secretary &secretary) {
    fin.open("./data/courses.txt", ios::in);
        string courseName;
        int ects;
        string type;
        int numberOfSemester;
        string regNumOfProf;
     
    
    while(fin >> courseName >> ects >> type >> numberOfSemester >> regNumOfProf ) {
        
        Course* temporaryCourse = new Course(courseName, ects, type, numberOfSemester);  
        
        secretary.addCourse(temporaryCourse);

        if(regNumOfProf != "No_Professor_Declared"){
            Professor* foundProf = secretary.findProfessorByRegNum(regNumOfProf);
            secretary.setProfessor(foundProf, secretary.findCourseByName(courseName));
        }

        delete temporaryCourse;
    }

    

    fin.close();
}


void writeCourseToFile(ofstream &fout, Secretary &secretary){
    secretary.displayCourseToFile(fout); 
}

void writeStudentsWithDegreeToFile(ofstream &fout, Secretary &secretary){
    secretary.displayStudentsWithDegree(fout);
}