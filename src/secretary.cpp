#include "classes.h"
#include <algorithm>

using namespace std;

//constructors
Secretary::Secretary() : graduationDetails(){

}

// Destructor to free dynamically allocated memory for students, professors, and semesters
Secretary::~Secretary(){
    for(auto it = students.begin();it != students.end();++it){
        delete (*it);
    }
    students.clear();


    for(auto it = professors.begin();it != professors.end();++it){
        delete (*it);
    }
    professors.clear();


    for(auto it = semesters.begin();it != semesters.end(); ++it){
        delete (*it);
    }
    semesters.clear();    

}

// Outputs professors, students, or all based on user input
ostream &operator<<(ostream &os,const Secretary &s1) {

    string ch;

    cout << "What would you like to view?\nFor professors press 'P', for students press 'S' and for all press 'A' \n ";
    cin >>ch;
    while(ch != "P" && ch != "p" && ch != "S" &&ch != "s" && ch != "A" && ch != "a") {
        cout << "Give a Valid letter please ";
        cin >> ch;
    }  
    

    if (ch == "s" || ch == "S") {

        set <Student*>::iterator it;
        if (s1.students.size() == 0) {
            os << "There are no students yet!\n\n";
        }
        else{
            os << "Students of this secretary are\n\n";
            os << "            |\n";
            os << "            V\n\n";
            for(it = s1.students.begin();it != s1.students.end();it++){
                (**it).display();
            }
        }
        return os;
    }

    else if(ch == "P" || ch == "p") {
        set <Professor*>::iterator it;
        if (s1.professors.size() == 0) {
            os << "There are no professors yet!\n\n";
        }
        else{
            os << "Professors of this secretary are\n\n";
            os << "            |\n";
            os << "            V\n\n";
            for(it = s1.professors.begin();it != s1.professors.end();it++){
                (**it).display();
            }
        }
        return os;
    }

    else if(ch == "a" || ch == "A") {
        if (s1.students.size() == 0) {
            os << "There are no students yet!\n\n";
        }
        else{

            set <Student*>::iterator it;
            os << "Students of this secretary are\n\n";
            os << "            |\n";
            os << "            V\n\n";
            for(it = s1.students.begin();it != s1.students.end();it++){
                (**it).display();
            }
        }
        
        if (s1.professors.size() == 0) {
            os << "There are no professors yet!\n\n";
        }
        else{

            set <Professor*>::iterator it2;
            os << "Professors of this secretary are\n\n";
            os << "            |\n";
            os << "            V\n\n";
            for(it2 = s1.professors.begin(); it2 != s1.professors.end(); it2++){
                (**it2).display();
            }
        }
    }
    return os;

}



bool Secretary::containStudent(const Student* const s)const{
    
    set<Student*>::iterator it;
    bool found = false;

    for(it = students.begin(); it!= students.end(); it++){
    
        // If these three fields match, this is the same student
        if((*it)->getFirstName() == s->getFirstName() &&
           (*it)->getLastName() == s->getLastName() &&
           (*it)->getPhone() == s->getPhone() ){
                found = true;
                break;
           }
    }
    if(found == false){
        return false;
    }
    else{
        return true;
    }
}

bool Secretary::containProfessor(const Professor* const p)const{
   
    set<Professor*>::iterator it;
    bool found = false;
   
    for(it = professors.begin(); it != professors.end(); it++){
        // If these three fields match, this is the same professor
        if((*it)->getFirstName() == p->getFirstName() &&
           (*it)->getLastName() == p->getLastName() &&
           (*it)->getPhone() == p->getPhone() ){
                found = true;
                break;
           }
    }
    if(found == false){
        return false;
    }
    else{
        return true;
    }
}



void Secretary::setProfessor(Professor*  professor, Course *course){
    vector <Semester*>::iterator it;

    int semesterNumber = course->getSem();

    for(it = semesters.begin(); it != semesters.end(); ++it ){
        if((*it)->getNumberOfSemester() == semesterNumber){
           
            (*it)->setProfessor(professor, course);
        }
    }

}


void Secretary:: declareCourse(const Student &student, Course &course){
    
    if (course.getSem() <= student.getCurrentSemester()){
        course.declareCourse(student);
    }
    else{
        cout << "Course from later Semester was requested\n";
    }
} 


void Secretary:: registerGrades(Student &student, Course &course, const float &grade) {
    bool valid_grade = false;
    float newGrade = grade;
    string RegNum;
      
    while (valid_grade == false) {
        try{
            // If an invalid grade is given
            if (newGrade > 10 || newGrade < 0) {
                throw invalidGrade();
            }
            valid_grade = true;
            
            if (course.containsStudentByRegNum(student) == false) {
                throw studentNotFound();
            }

            else{
                course.registerGrade(student,newGrade);
            }
        }
    
        catch(invalidGrade) {
            cout << "Please enter a valid grade between 1 and 10\n";
            cin >> newGrade;
        }
        catch(studentNotFound){
            cout << "Student " <<student.getFirstName()<<" "<<student.getLastName()<<
            " with reg. Num : "<< student.getRegistrationNumber() <<"has not declared course '" <<course.getCourseName()<<"'\n" ;
        }
        catch(...) {
            cout << "unknown exception\n";
        }
    }

}



Course* Secretary:: findCourse(Course* course) {
    try{
        vector <Semester*> :: iterator it;
        vector<Course*> :: iterator it2;
       
        Semester* semesterOfCourse = findSemesterByNum(course->getSem()); 
       
        // In the course semester, first check whether the course exists
        if (semesterOfCourse != NULL){   
            it2 =  semesterOfCourse->findCourse(course);
            return (*it2);
        }
        else{
            throw CourseNotExists();
        }
    }
    catch(CourseNotExists()){
        cout << "Course "<< course->getCourseName() <<" does not exists in semester "<< course->getSem()<< endl;
        return nullptr;
    }
}

Semester* Secretary:: findSemesterByNum(const int num)  {
     vector<Semester*>:: iterator it;
    
    for (it = semesters.begin(); it != semesters.end(); it++) {
      
        if ((*it)->getNumberOfSemester() == num) {
            return (*it); 
        }
    }
    return NULL;
}

const map<Course, string> Secretary:: findCourses(const Student &student){
   
    vector<Semester*>::iterator it;
    map<Course, string> coursesOfStudent;

    for (it = semesters.begin(); it != semesters.end(); it++){
   
        // For each semester, find the student's courses and grades in that semester
        map <Course, string> tempCourses = ((*it)->findCoursesOfStudent(student));
       
        map<Course, string>:: iterator it2;

        // Add them to the overall map
        for(it2 = tempCourses.begin(); it2 != tempCourses.end(); ++it2 ){
            coursesOfStudent.insert(*it2);
        }
    }
    return coursesOfStudent;
} 


int Secretary:: getEcts(const Student &student){

    map<Course, string> coursesOfStudent = findCourses(student);
    map<Course, string>:: iterator it;

    int total = 0;

    for (it = coursesOfStudent.begin(); it != coursesOfStudent.end(); it++) {
        float grade = stof((*it).second);
        if (grade >= 5) {
            total += (*it).first.getEcts();
        }
    }

    return total;
    
}


string Secretary:: getDegree(const Student &student) {

    string messageToreturn = "empty";

    // If the student has completed all required years
    if (student.getCurrentSemester() >= (graduationDetails.getTotalYears() * 2) ) {

        // If the student has the required ECTS
        if(getEcts(student) >= graduationDetails.getTotalEcts()) {
            
            
            vector<string> obligatoryCourses = graduationDetails.getObligatoryCourses();

            for(auto it = obligatoryCourses.begin(); it != obligatoryCourses.end(); ++it){    
                string courseName = *it;
                Course* requiredCourse = findCourseByName(courseName);

                if (requiredCourse == NULL) {
                    messageToreturn = "No Course " + courseName + " found";
                    return messageToreturn;
                }

                // If the student is enrolled in the course
                if (requiredCourse->containsStudentByRegNum(student)) {
                
                    string grade = requiredCourse->getGradeOfStudent(student);

                    // If a required course has not been examined, stop here
                    if(grade == "not_examined"){
                        messageToreturn =  "not_examined" ;
                        return messageToreturn;
                    }
                    
                    // If the student failed a required course, stop here
                    if(stof(grade) < 5){
                        messageToreturn =  "Cut in Course" + courseName + " with grade " + grade ;
                        return messageToreturn;
                    }
                }

                else{ // If the student has not enrolled in a required course, stop here
                    messageToreturn = "No Course " + courseName + " found";
                    return messageToreturn;
                }
            }
            
        }
        // If the student does not have the required ECTS, stop here
        else{
             messageToreturn = "Not enough ects to get the degree";
             return messageToreturn;   
        }
    }

    // If the required years have not passed, stop here
    else{
        messageToreturn = "Not all years completed! You cannot get a degree yet";
        return messageToreturn;   
    }

    // If none of the above conditions stopped the function, the student gets the degree
    messageToreturn = "Got the Degree";
    return messageToreturn;   
}


void Secretary::addProfessor(Professor* professor){
    Professor* newProfessor = new Professor(*professor);
    professors.insert(newProfessor);
}


void Secretary::removeProfessor( Professor* professor){
    
    // If the professor exists in the secretary
    if (containProfessor(professor) ) {
        
        set<Professor*>::iterator it;

        for(it = professors.begin(); it != professors.end(); ++it){

            if((*it)->getFirstName() == professor->getFirstName() &&
            (*it)->getLastName() == professor->getLastName() &&
            (*it)->getPhone() == professor->getPhone() ){
                for (auto semIt = semesters.begin(); semIt != semesters.end(); ++semIt) {
                    (*semIt)->clearProfessorAssignments(*it);
                }
             
                delete (*it);
                professors.erase(it);
                break;
            }
        }
     }

    else{
        cout << "Professor '" << professor->getFirstName() << " " << professor->getLastName() << "' was not found.\n";
    }
}

// Only the most essential fields can be changed, not name and similar fixed data
void Secretary::modifyProfessor( Professor* professor){

    cout << "\nWhat would you like to change for Professor "<< professor->getFirstName() << " "<< professor->getLastName();
    cout << "\n\nFor Phone press '1'\nFor E-mail press '2'\nFor office press '3'\nFor WebPage Press '4'\n" ;
    string input;
    cin >> input;
    
    while(input !="1" && input != "2" && input !="3" && input != "4" ){
        cout << "Please enter a valid number from 1 - 4! \n";
        cin >> input;
    }

    string newData;

    if (input == "1") {
        cout << "Enter your new phone number: ";
        cin >> newData;
        professor->setPhone(newData);
        
    }
     else if(input == "2") {
        cout << "Enter your new Email: ";
        cin >> newData;
        professor->setEmail(newData);
    }
    else if(input == "3") {
        cout << "Enter your new office: ";
        cin >> newData;
        professor->setOffice(newData);
    }
    else if(input == "4") {
        cout << "Enter your new Webpage: ";
        cin >> newData;
        professor->setWebpage(newData);

    }  
}


Professor* Secretary:: findProfessorByRegNum(const string &regNum)const{
    
    set<Professor*>:: iterator it;
    
    for (it = professors.begin(); it != professors.end(); it++) {
        if ( (*it)->getRegNum() == regNum) {
            return (*it);
        }
    }
    return NULL;
}

Student* Secretary:: findStudentByRegNum(const string &regNum)const{
    
    set<Student*>:: iterator it;
    
    for (it = students.begin(); it != students.end(); it++) {
        if ( (*it)->getRegistrationNumber() == regNum) {
            return (*it);
        }
    }
    return NULL;
}


void Secretary::addStudent(Student *student){
    Student* newStudent = new Student;
    (*newStudent) = *student;
  
   students.insert(newStudent);
}

void Secretary::removeStudent(Student* student){
       
        if (containStudent(student) ) {
       
        set<Student*>::iterator it;

        for(it = students.begin(); it != students.end(); ++it){
            
            if((*it)->getFirstName() == student->getFirstName() &&
            (*it)->getLastName() == student->getLastName() &&
            (*it)->getPhone() == student->getPhone() ){
                for (auto semIt = semesters.begin(); semIt != semesters.end(); ++semIt) {
                    (*semIt)->removeStudent(**it);
                }
            
                delete (*it);
                students.erase(it);
                break;
            }
        }
     }
    else{
        cout << "Student '" << student->getFirstName() << " " << student->getLastName() << "' was not found.\n";

    }
}

// The student can change only phone number and email. The secretary is responsible for everything else.
void Secretary::modifyStudent( Student* student){
    cout << "What would you like to change?\nFor Phone press '1'\n"
    "For E-mail press '2' \n" ;
    string input;
    cin >> input;
    
    while(input !="1" && input != "2"){
        cout << "Please enter a valid number from 1 - 2! \n";
        cin >> input;
    }

    string newData;

    if (input == "1") {
        cout << "Enter your new phone number: ";
        cin >> newData;
        student->setPhone(newData);
        
    }
     else if(input == "2") {
        cout << "Enter your new Email: ";
        cin >> newData;
        student->setEmail(newData);
    }
}




void Secretary:: addCourse( Course* course) {

    int semesterNumber = course->getSem();

    bool added = false;

    for(auto it = semesters.begin();it != semesters.end();it++){
  
        if( (*it)->getNumberOfSemester() == semesterNumber){
            
            (*it)->addCourse(course);
            added = true;
            // Also add it to obligatory courses
            if(course->getType() == "Compulsory" || course->getType() == "compulsory"){
                graduationDetails.addObligatoryCourse(course->getCourseName());
            }
        }
    }


    if(!added){
        cout << "No semester "<<semesterNumber<<" found in Secretary\n";
    }
}

void Secretary:: removeCourse(Course* course) {

    int semesterNumber = course->getSem();

    bool removed = false;

    for(auto it = semesters.begin();it != semesters.end();it++){

        if( (*it)->getNumberOfSemester() == semesterNumber){
            if(course->getType() == "elective" ||course->getType() == "Elective" ){
                (*it)->removeCourse(course);
            }
            else{
                // Remove it from this vector as well if needed (obligatory)
                graduationDetails.removeObligatoryCourse(course->getCourseName());
                (*it)->removeCourse(course);
            }

            removed = true;
        }

    }

    if(!removed){
        cout << "No "<<semesterNumber<<" semester found in Secretary\n";
    }

}

void Secretary::modifyCourse(Course* course){

    cout << "What would you like to change?\nFor course Name press '1'\n"
    "For ECTS press '2' \nFor Professor of Course press '3' \nFor Semester of Course press '4' \n""For Type press '5' \n" ;
    
    string input;
    cin >> input;
    
    while(input != "1" && input != "2" && input != "3" && input != "4" && input != "5"){
        cout << "Please enter a valid number from 1 - 5! \n";
        cin >> input;
    }

    string newData;

    if (input == "1") {
        cout << "Enter Course's new name: ";
        cin >> newData;
        string oldName = course->getCourseName();
        course->setCourseName(newData);

        if (containsObligatoryCourse(oldName)) {
            renameObligatoryCourse(oldName, newData);
        }
    }

     else if(input == "2") {
        cout << "Enter ECTS for this Course: ";
        cin >> newData;
        course->setEcts(stoi(newData));
    }

    else if(input == "3") {
        cout << "Enter the Registration Number of new Professor to teach this Course: ";
        cin >> newData;
        
        Professor* newProf = findProfessorByRegNum(newData);
        
        if (newProf == NULL) {
            cout << "No professor with registration number '" << newData << "' found.\n"; 
        }
        else {
            course->setProfessor(newProf);
        }
        

    }

    else if(input == "4") {
        cout << "Enter the new semester that the course will be taught: ";
        cin >> newData;

        int newSemesterNumber = stoi(newData);
        Semester* newSem = findSemesterByNum(newSemesterNumber);

        if (newSem == NULL) {
            cout << "No semester '" << newData << "' found.\n";
        }
        else{
            Semester* oldSem = findSemesterByNum(course->getSem());

            if (oldSem == NULL) {
                cout << "Current semester of course was not found.\n";
            }
            else if (oldSem == newSem) {
                course->setSem(newSem->getNumberOfSemester());
            }
            else{
                Course* movedCourse = oldSem->extractCourse(course);

                if (movedCourse == NULL) {
                    cout << "Course could not be moved to semester '" << newData << "'.\n";
                }
                else{
                    movedCourse->setSem(newSemesterNumber);
                    newSem->addExistingCourse(movedCourse);
                }
            }
        }

    }

    else if(input == "5") {
        cout << "Enter new Type of the Course: ";
        cin >> newData;
        string oldType = course->getType();
        course->setType(newData);

        bool wasCompulsory = (oldType == "Compulsory" || oldType == "compulsory");
        bool isCompulsory = (newData == "Compulsory" || newData == "compulsory");

        if (!wasCompulsory && isCompulsory) {
            addObligatoryCourse(course->getCourseName());
        }
        else if (wasCompulsory && !isCompulsory) {
            removeObligatoryCourse(course->getCourseName());
        }
    }
}

// Print students who passed the course
void Secretary :: studentsPassedCourse(Course* course){
    
    Course* courseOfSecretary = findCourse(course);// Check whether it exists in the container iterator
    
    if (courseOfSecretary == nullptr){
        return;
    }
    
    courseOfSecretary->studentsPassedCourse();


}


void  Secretary:: statisticsOfProfessor(Professor* prof){
   
    for (auto it = semesters.begin(); it != semesters.end(); it++) {
        (*it)->statisticsOfProfessor(prof);
    }
}


void Secretary:: displayGradesOfStudent(Student* student){
    
    map<Course, string> courses = findCourses(*student);
    map<Course, string>:: iterator it;

    cout << "For viewing this semester's grades press 'S'\nFor viewing all of your grades press 'A':\n ";
    char input;
    cin >> input;

    bool validInput = false;

    while (validInput == false ) {
        try{

            if(input != 's' && input != 'S' && input != 'A' && input != 'a') {
                throw invalidInput();
            }

            validInput = true;

            // Only print courses and corresponding grades for the current semester
            if(input == 'S' || input == 's') {
                cout << "Your grades for the current semester are: \n";

                  for (it = courses.begin(); it != courses.end(); it++ ) {

                    string grade = (*it).second;
                    
                    if (grade != "not_examined") {

                        if ((*it).first.getSem() == student->getCurrentSemester() && (stof(grade) >= 5)) {

                            cout << (*it).first.getCourseName() << " -> " << stof(grade) << endl;

                        }
                    }
                }

            }

             else if(input == 'a' || input == 'A') {
                cout << "Your grades for all of your passed courses are: \n";

                for (it = courses.begin(); it != courses.end(); it++) {
                    string grade = (*it).second;

                    if (grade != "not_examined") {
                        if(stof(grade) >= 5) {
                            cout << (*it).first.getCourseName() << " of semester " << (*it).first.getSem() << " -> " << stof(grade) << endl;
                        }
                    }
                }

            } 

         }
    

        catch(invalidInput) {
            cout << "Please enter a valid input! Press 'Y' for all grades or 'S' for current semester's grades:\n"; 
            cin >> input;
        }

        catch(...) {
          cout << "unknown exception\n";
        }
    }
}


void Secretary :: displayStudentsWithDegree(){
   
    string messageFromGetDegree;
   
    cout << "Students that are able to get their Degrees are :\n";
   
    for(auto it = students.begin(); it!= students.end(); ++it ){
        messageFromGetDegree = getDegree((**it));
        
        if (messageFromGetDegree == "Got the Degree"){
            cout <<(*it)->getFirstName() <<" "<<(*it)->getLastName()<<" - "<<(*it)->getRegistrationNumber()<<endl;
        }
    }
    cout << "\n\n";
}



void Secretary:: displayDeclaredCoursesOfStudent(const Student &student){

    map<Course, string> courses = findCourses(student);

    if (courses.size() > 0) {
        cout << "Declared courses of student " << student.getFirstName() << " " << student.getLastName() << " are:\n";
    
        for (auto it = courses.begin(); it != courses.end(); it++){
            cout << (*it).first.getCourseName() << " - " << (*it).second << endl; 
        }
    }
    else {
        cout << "Student " << student.getFirstName() << " " << student.getLastName() << " has no declared courses!\n";
    }
    
    
}

Course* Secretary:: findCourseByName(string name) const{

    Course* course = NULL;
    
    for(auto it = semesters.begin(); it != semesters.end(); it++) {
        course = (*it)->findCourseByName(name);
        if(course != nullptr){
            return course;
        }
    }

    return course;
    
}

// Write students, professors, and courses to the file using a SPECIFIC FORMAT

void Secretary:: displayStudentsToFile(ofstream &fout){
   
    fout.open("./data/students.txt",ios::out);
   
    for (auto it = students.begin(); it != students.end(); it++) {
   
        fout << (*it)->getFirstName() << " " << (*it)->getLastName() << " " << (*it)->getDateOfBirth() <<" " <<(*it)->getPhone() << " " << (*it)->getEmail() << " " << (*it)->getCurrentSemester();
        fout << " " << (*it)->getRegistrationNumber() << " " << (*it)->getTypeOfStudent()<<" ";
   
        map <Course,string> studentCourses = this->findCourses(**it);

        for(auto it2 = studentCourses.begin(); it2 != studentCourses.end(); ++it2){
            fout << (it2)->first.getCourseName() << " " <<it2->second<< " ";
        }

        fout << "\n";
    }
    fout.close();
}


void Secretary:: displayProfessorsToFile(ofstream &fout){
    fout.open("./data/professors.txt",ios::out);
    
    for (auto it = professors.begin(); it != professors.end(); it++) {
    
        fout << (*it)->getFirstName() << " " << (*it)->getLastName() << " " << (*it)->getDateOfBirth() <<" " <<(*it)->getPhone() << " " << (*it)->getEmail() << " " << (*it)->getOffice();
        fout << " " << (*it)->getWebpage() << " " << (*it)->getSpecialization() << " " << (*it)->getRegNum();
        fout << "\n";
    }
    fout.close();
}



void  Secretary:: displayCourseToFile(ofstream &fout){
    fout.open("./data/courses.txt", ios::out);
  
    for (auto it = semesters.begin(); it != semesters.end(); it++) {
        (*it)->displayCoursesOfSemester(fout);
    }
    fout.close();
}


void Secretary:: displayStudentsWithDegree(ofstream &fout) {
    fout.open("./data/degree.txt", ios::out);

    string messageFromGetDegree;
   
    fout << "Students that are able to get their Degrees are :\n";
   
    for(auto it = students.begin(); it!= students.end(); ++it ){
        messageFromGetDegree = getDegree((**it));
        
        if (messageFromGetDegree == "Got the Degree"){
            fout <<(*it)->getFirstName() <<" "<<(*it)->getLastName()<<" - "<<(*it)->getRegistrationNumber()<<endl;
        }
    }
    cout << "\n\n";
}