#include <fstream>
#include "classes.h"
#include <sstream>

void readStudentFromFile(ifstream &fin, Secretary &secretary){
    fin.open("students.txt", ios::in);

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

    //διαβάζουμε τα βασικά χαρακτηριστικά του φοιτητή μέχρι το τέλος του αρχείου
    while (fin >> firstName >> lastName >> dateOfBirth >> phoneNumber >> email >> currentSemester >> registrationNumber >> typeOfStudent) {

        Student tempStudent(firstName, lastName, dateOfBirth, phoneNumber, email, currentSemester, registrationNumber, typeOfStudent);
        secretary.addStudent(&tempStudent);
        

        std::string restOfLine;

        //διαβάζει την υπόλοιπη σειρά που απέμεινε απο εκεί που είναι τώρα ο δείκτης ανάγνωσης
        // (δηλαδή ονόματα μαθημάτων και βαθμούς και την αποθηκεύει στο string restOfline)
        std::getline(fin, restOfLine);

        //συμπεροφερόμαστε στο string σαν να ήταν stream διαβάζοντας μία μία λέξη(βρήκαμε αυτη τη λειτουργία της βιβλιοθήκης sstream sto internet)
        std::istringstream iss(restOfLine);

        //έχουμε ένα ρεύμα που έχει τους βαθμούς και τα μαθήματα του μαθητή εναλλάξ
        while (iss >> courseName >> grade) {
        //άρα επαναλαμβάνουμε την ίδια διαδικασία (while) μεχρι να τελειώσει το "ρευμα" - string
            
            Course* courseToDeclare = secretary.findCourseByName(courseName); 
            
           secretary.declareCourse(*secretary.findStudentByRegNum(registrationNumber),*courseToDeclare);

            if(grade != "not_examined"){

                float gradeValue = std::stof(grade);//μετατροπή του βαθμου σε float για να καλέσουμε την συνάρτηση register grades
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
    fin.open("professors.txt", ios::in);
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
    fin.open("courses.txt", ios::in);
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
    
        if(temporaryCourse->getType() == "elective" || temporaryCourse->getType() == "Elective"){
            delete temporaryCourse;
            //αν είναι elective θέλουμε να το διαγραφουμε το temporary course που μόλις ορίσαμε γιατί στην add course δημιουργείται καινούριο βάση του 
            //copy constructor του course.Αν όμως είναι Compulsory μπαίνει στο vector των obligatory Courses,ομως μπαίνει ο δείκτης οπότε η αποδέσμευση 
            //γίνεται στον destructor του Graduation details
        }
    }

    

    fin.close();
}


void writeCourseToFile(ofstream &fout, Secretary &secretary){
    secretary.displayCourseToFile(fout); 
}

void writeStudentsWithDegreeToFile(ofstream &fout, Secretary &secretary){
    secretary.displayStudentsWithDegree(fout);
}