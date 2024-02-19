#include <iostream>
#include <fstream>
#include "classes.h"
#include <string>
#include <set>
#include <limits>


int Person::count = 0;


//συνάρτηση για να διαβάζει και να βρίσκει τον μαθητή βάση του αριθμού μητρώου 

string readValidStudent(const Secretary &secretary){
    string input;
    std::cout<< "Enter registration number of Student(or 'M' to return to Main Menu): ";
    cin >> input;

    if(input == "M" || input == "m") {
        return input;
    }
    
    while (secretary.findStudentByRegNum(input) == nullptr) {
        
        if(input == "M" || input == "m") {
            return input;
        }
    
        std::cout<< "No student with registration number '" << input << "' found!\n";
        std::cout<< "Enter a different registration number(or 'M' to return to Main Menu): ";
        cin >> input;
    }
    return input;
}


string readValidCourse(const Secretary &secretary){
    string input;
    std::cout<< "Enter name of Course(or 'M' to return to Main Menu): ";
    cin >> input;

     
    
    while (secretary.findCourseByName(input) == nullptr) {

        
        if(input == "M" || input == "m") {
             return input;
        }  

        std::cout<< "No Course '" << input << "' found!\n";
        std::cout<< "Enter a different Course (or 'M' to return to Main Menu): ";
        cin >> input;
    }
    return input;
}

//συνάρτηση για να διαβάζει και να βρίσκει τον καθηγητή βάση του αριθμού μητρώου 
string readValidProfessor(const Secretary &secretary){
    string input;
    std::cout<< "Enter Registration Number of Professor(or 'M' to return to Main Menu): ";
    cin >> input;

   
   
    while (secretary.findProfessorByRegNum(input) == nullptr) {

         if(input == "M" || input == "m") {
            return input;
        }
        std::cout<< "No Professor '" << input << "' found!\n";
        std::cout<< "Enter a different Professor(or 'M' to return to Main Menu): ";
        cin >> input;
    }
    return input;
}



int main(void){
    Secretary secretary;
    //Γραμματέας - ορισμος λεπτομερειων αποφοίτησης
    secretary.setTotalEcts(40);
    secretary.setTotalYears(4);

    //ορισμος ακαδημαικων εξαμηνων
    Semester sem1(1);
    Semester sem2(2);
    Semester sem3(3);
    Semester sem4(4);
    Semester sem5(5);
    Semester sem6(6);
    Semester sem7(7);
    Semester sem8(8);

    //προσθήκη στη γραμματεια
    secretary.addSemester(&sem1);
    secretary.addSemester(&sem2);
    secretary.addSemester(&sem3);
    secretary.addSemester(&sem4);
    secretary.addSemester(&sem5);
    secretary.addSemester(&sem6);
    secretary.addSemester(&sem7);
    secretary.addSemester(&sem8);
    
    //για την add πιο μετά
    Professor newProf;
    Course newCourse;
    Student newStudent;
    string inputToExit;


    std::ifstream fin, fin2, fin3;
    
    //διαβάζει τα δεδομένα απο τα αντίστοιχα αρχεία και τα φορτώνει στη γραμματεία
    readProfessorFromFile(fin2, secretary);
    readCourseFromFile(fin3, secretary);
    readStudentFromFile(fin, secretary);
    
    
    do{
        //############# ΜΕΝΟΥ ############//
        std::cout<<"\n\n\n";
        std::cout<< "                   MENU\n";
        std::cout<< "To add/modify/remove a Professor press '1'\n";
        std::cout<< "To add/modify/remove a Student press '2'\n";
        std::cout<< "To add/modify/remove a Course press '3'\n";
        std::cout<< "To set a Professor of a Course press '4' \n";
        std::cout<< "To enroll a Student in a Course press '5'\n";
        std::cout<< "To print all succesfully examined Students of a Course press '6'\n";
        std::cout<< "To print the statistics of the Courses of a specific Professor press '7'\n";
        std::cout<< "To print the general transcript or the current semester's press '8'\n";
        std::cout<< "To print all students eligible for degree press '9'\n";
        std::cout<< "To register a grade for a student press '10'\n";
        std::cout<< "For exit press 'E'\n\n\n\n";

        cin >> inputToExit;

        string input;
        bool validInput = false;
        
        while(!validInput){
            try{
                if(inputToExit !="1" && inputToExit != "2" && inputToExit !="3" && inputToExit != "4" && inputToExit !="5" && inputToExit !="6" && inputToExit !="7" && inputToExit !="8" && inputToExit !="9" && inputToExit !="10" && inputToExit !="E" && inputToExit !="e"){
                    throw invalidInput();
                }

                validInput = true;

                //επεξεργασία καθηγητών
                if (inputToExit == "1") {
                    std::cout<< "To add Professor press '1'\n";
                    std::cout<< "To modify Professor press '2'\n";
                    std::cout<< "To remove Professor press '3'\n";
                    std::cout<< "To return to Main Menu press 'M'\n";
                    cin >> input;
                    while(input != "1" && input != "2" && input != "3" && input != "m" && input != "M" ){
                        std::cout<< "Enter a valid number from 1 - 3 or 'M' To return to Main Menu!\n";
                        cin >> input;
                    }

                    if(input == "1"){
                        cin >> newProf;
                        secretary.addProfessor(&newProf);
                    }

                    else if(input == "2"){
                        input = readValidProfessor(secretary);
                       
                        if(input == "M" || input == "m") {
                            cout << "\nReturned to main menu!\n\n";
                            continue;
                        }

                        secretary.modifyProfessor(secretary.findProfessorByRegNum(input));


                    }

                    else if(input == "3"){
                        input = readValidProfessor(secretary);
                        if(input == "M" || input == "m") {
                            cout << "\nReturned to main menu!\n\n";
                            continue;
                        }
                        secretary.removeProfessor(secretary.findProfessorByRegNum(input));

                    }
                    else{
                        continue;
                    }
                }

                //επεξεργασία φοιτητών
                else if(inputToExit == "2") {
                    std::cout<< "To add Student press '1'\n";
                    std::cout<< "To modify Student press '2'\n";
                    std::cout<< "To remove Student press '3'\n";
                    std::cout<< "To return to Main Menu press 'M'\n";

                    cin >> input;
                    while(input != "1" && input != "2" && input != "3" && input != "m" && input != "M"){
                        std::cout<< "Enter a valid number from 1 - 3 or 'M' To return to Main Menu!\n";
                        cin >> input;
                    }

                    if(input == "1"){
                        cin >> newStudent;
                        secretary.addStudent(&newStudent);

                    }

                    else if(input == "2"){
                        input = readValidStudent(secretary);
                        if(input == "M" || input == "m") {
                            cout << "\nReturned to main menu!\n\n";
                            continue;
                        }
                        secretary.modifyStudent(secretary.findStudentByRegNum(input));

                    }

                    else if(input == "3"){
                        input = readValidStudent(secretary);
                        if(input == "M" || input == "m") {
                            cout << "\nReturned to main menu!\n\n";
                            continue;
                        }
                        secretary.removeStudent(secretary.findStudentByRegNum(input));

                    }
                    else{
                        continue;
                    }
           
                }

                //επεξεργασία μαθημάτων
                else if (inputToExit == "3") {
                    std::cout<< "To add Course press '1'\n";
                    std::cout<< "To modify Course press '2'\n";
                    std::cout<< "To remove Course press '3'\n";
                    std::cout<< "To return to Main Menu press 'M'\n";

                    cin >> input;
                    while(input != "1" && input != "2" && input != "3"&& input != "m" && input != "M"){
                        std::cout<< "Enter a valid number from 1 - 3 or 'R' To return to Main Menu!\n";
                        cin >> input;
                    }

                    if(input == "1"){
                        cin >> newCourse;
                        Course* tempCourse = new Course(newCourse);
                        secretary.addCourse(tempCourse);
                    }

                    else if(input == "2"){
                        input = readValidCourse(secretary);
                        if(input == "M" || input == "m") {
                            cout << "\nReturned to main menu!\n\n";
                            continue;
                        }
                        secretary.modifyCourse(secretary.findCourseByName(input));      

                    }

                    else if(input == "3"){
                        input = readValidCourse(secretary);
                        if(input == "M" || input == "m") {
                            cout << "\nReturned to main menu!\n\n";
                            continue;
                        }
                        secretary.removeCourse(secretary.findCourseByName(input));
                            if(secretary.findCourseByName(input) == NULL){
                                std::cout<< "Course removed successfully!\n\n";
                            }
                            else{
                                std::cout<< "Course "<< input <<  " was not removed!\n\n";
                            }
                    }
                    else {
                        continue;
                    }
                   
                }

                // ορισμός καθηγητή
                else if(inputToExit == "4") {
                    input = readValidProfessor(secretary);
                    
                    if(input == "M" || input == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }
                    
                    Professor* foundProfessor = secretary.findProfessorByRegNum(input);

                    string courseNameInput;
                    courseNameInput = readValidCourse(secretary);
                    if(courseNameInput == "M" || courseNameInput == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }
                    Course* foundCourse = secretary.findCourseByName(courseNameInput);

                    secretary.setProfessor(foundProfessor,foundCourse);
                    std::cout<< "Professor '" << foundProfessor->getFirstName() << " " << foundProfessor->getLastName() << " was set to Course '" << courseNameInput << "' successfully!\n\n\n";
                    
                }


                //δήλωση μαθ΄ήματος από φοιτητ΄ή
                else if(inputToExit == "5") {
                    input  = readValidCourse(secretary);
                    
                    if(input == "M" || input == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }

                    Course* foundCourse = secretary.findCourseByName(input);

                    string RegNum;
                    RegNum  = readValidStudent(secretary);
                    if(RegNum == "M" || RegNum == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }
            
                    Student* foundStudent = secretary.findStudentByRegNum(RegNum);

                    secretary.declareCourse(*foundStudent, *foundCourse);
 

                }  

                //εκτ΄ύπωση επιτυχόντων ενός μαθήματος
                else if(inputToExit == "6") {
                    input = readValidCourse(secretary);
                    
                    if(input == "M" || input == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }
                    
                    Course* foundCourse = secretary.findCourseByName(input);
                    secretary.studentsPassedCourse(foundCourse);
                }  

                //εκτύπωση στατιστικών μαθημάτων ενός καθηγητ΄ή 
                else if(inputToExit == "7") {
                    input = readValidProfessor(secretary);

                    if(input == "M" || input == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }
                    
                    Professor* foundProfessor = secretary.findProfessorByRegNum(input);

                    secretary.statisticsOfProfessor(foundProfessor);


                }  

                //εκτύπωση αναλυτικής βαθμολογίας ενός μαθητή
                else if(inputToExit == "8") {
                    input = readValidStudent(secretary);

                    if(input == "M" || input == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }

                    Student* foundStudent = secretary.findStudentByRegNum(input);

                    secretary.displayGradesOfStudent(foundStudent);
                }  

                //εκτύπωση φοιτητών που μπορούν να πάρουν πτυχίο
                else if(inputToExit == "9") {
                    
                    secretary.displayStudentsWithDegree();
                    
                }  

                //καταχώρηση βαθμού από καθηγητή
                else if(inputToExit == "10") {
                    input = readValidStudent(secretary);
                    
                    if(input == "M" || input == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }
                    
                    Student* foundStudent = secretary.findStudentByRegNum(input);

                    string courseNameInput;
                    courseNameInput = readValidCourse(secretary);
                    if(input == "M" || input == "m") {
                        cout << "\nReturned to main menu!\n\n";
                        continue;
                    }
                    Course* foundCourse = secretary.findCourseByName(courseNameInput);

                    string grade;
                    std::cout<< "Enter grade of Student: ";
                    cin >> grade;

                    secretary.registerGrades(*foundStudent, *foundCourse, stof(grade));
                    
                }  


            }
            catch(invalidInput){
                std::cout<< "Please enter a valid number from 1 - 9 or press 'E' for exit! \n";
                cin >> inputToExit;
            }
        }


    }while(inputToExit != "e" && inputToExit != "E");



    std::ofstream fout, fout2, fout3, fout4;

    //ενημέρωση αρχείων 
    writeCourseToFile(fout3, secretary);
    writeProfessorToFile(fout2, secretary);
    writeStudentToFile(fout, secretary);
    writeStudentsWithDegreeToFile(fout4, secretary);


    return 0;
}