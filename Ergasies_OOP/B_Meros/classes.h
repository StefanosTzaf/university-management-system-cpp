#include <string>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class invalidInput{}; // για exception 

class Person{

    //ωστε να έχουμε πρόσβαση στις παράγωγες κλάσεις
    protected:
        string firstName;
        string lastName;
        string dateOfBirth;
        string phoneNumber;
        string email;

        static int count;

    public:
        
        Person();

        Person(Person const &P);

        Person(string const &firstName,string const &lastName,string const &dateOfBirth,string const &phone,string const &email);

        //για να καλείται ο αντιστοιχος deconstructor της παράγωγης
        virtual ~Person();


        string getLastName() const{
            return lastName;    
        }

        string getFirstName() const{
            return firstName;
        }

        string getPhone() const{
            return phoneNumber;    
        }

        void setPhone(const string &phoneNumber){
            this->phoneNumber = phoneNumber ;
            cout << "Phone changed to : "<< phoneNumber <<endl;
        }

        void setEmail(string const &email){
            this->email = email;
            cout << "Email changed to : "<< email <<endl;
        }

        string getEmail() const{
            return email;    
        }

        string getDateOfBirth() const{
            return dateOfBirth;
        }



        int countOfPeople() const;

        //τυπώνει μόνο τα βασικά χαρακτηριστικά ενός Person
        friend ostream &operator<<(ostream &os,const Person &p1);

        //τυπώνει εξ' ολοκλήρου τις παράγωγες κλάσεις
        virtual void display(void) const = 0;

        friend istream &operator>>(istream &is, Person &p1);

        bool operator<(const Person &p)const; //υπερφορτωση τελεστη < που θα χρειαστει στην συναρτηση compare των set απο student,professor της γραμματείας

};

//forward declaration για κλάσεις που χρειάζονται
class Course;
class Semester;


class Student : public Person{
    private:
        int currentSemester;
        string registrationNumber;
        string typeOfStudent;//bachelor-erasmus

    public:
        Student();

        Student(string const &firstName, string const &lastName, string const &dateOfBirth,  string const &phone, string const &email,
        int const &semester, string const &registrationNumber, string const &type);
        ~Student();
        
        Student(const Student& student);

        //################# GETTERS AND SETTERS #####################//

        int getCurrentSemester() const {
            return currentSemester;
        }
        void setCurrentSemester(int semester) {
            currentSemester = semester;
            cout << "Current semester changed to : "<< currentSemester <<endl;
        }

        string getRegistrationNumber() const {
            return registrationNumber;
        }

        string getTypeOfStudent() const {
            return typeOfStudent;
        }

        //η pure virtual συνάρτηση για να κάνει την κλάση Person abstract
        void display(void) const;


        friend istream &operator>>(istream &str, Student &student);   
            
};



class Professor : public Person{
    private:
        string office;
        string webPage;
        string specialization;
        string registrationNumber;
        
        class invalidGrade{}; //exception class για τη συναρτηση registerGrades
    
    public:        

        Professor();

        Professor(string const &firstName, string const &lastName, string const &dateOfBirth, string const &phone, string const &email,
        string const &office, string const &webpage, string const &specialization, string const &registrationNumber);
        Professor(const Professor& professor);
        ~Professor();

        //################# GETTERS AND SETTERS #####################//
        string getRegNum() const{
            return registrationNumber;
        }

        void setRegNum(string registrationNumber){
            this->registrationNumber = registrationNumber;
            cout << "Registration number changed to : "<< registrationNumber <<endl;

        }
        
        string getOffice() const{
            return office;
        }

         void setOffice(string office) {
            this->office = office;
            cout << "Office changed to : "<< office <<endl;
        }

        string getWebpage() const{
            return webPage;
        }

         void setWebpage(string webpage) {
            webPage = webpage;
            cout << "Webpage changed to : "<< webPage <<endl;
        }

        string getSpecialization() const{
            return specialization;
        }


        void display(void) const ;

        friend istream &operator>>(istream &is, Professor &professor);

};




class Course{
    private:
        string courseName;
        int ects;
        string type;//compulsory - elective
        int numberOfSemester;

        Professor* professor; //διδασκων
        
        //αντιστοιχιση εγγεγραμμένων μαθητών με βαθμούς αν έχουν περαστεί απο
        //τους καθηγητές αλλι΄ως not examined
        //οι βαθμοι ως string έτσι ώστε όταν δεν έχει εξεταστεί το μάθημα να μπορούμε να καταχωρούμε ένα μήνυμα.
        map <Student, string> enrolledStudents; 

    public:
                
        Course();

        //Τον διδασκοντα τον οριζει η γραμματεια
        Course(string courseName, int ECTS, string type, int numberOfSemester);

        Course(const Course& course);
        
        ~Course();
       
        //################# GETTERS AND SETTERS #####################//
        string getCourseName() const {
            return courseName;
        }

        int getEcts() const {
            return ects;
        }

        Professor* getProfessor() const {
            return professor;
        }

        string getType() const {
            return type;
        }
        
        int getSem() const {
            return numberOfSemester;
        }

        void setCourseName(const string& courseName) {
            this->courseName = courseName;
            cout << "Course name changed to " << courseName << endl;
        }

        void setEcts(int ects) {
            this->ects = ects;
            cout << "Ects of course changed to " << ects << endl;
        }

        void setProfessor( Professor *   newProfessor);

        void setType(const string& type) {
            this->type = type;
            cout << "Type of course changed to " << type << endl;
        }

        void setSem(int sem) {
            this->numberOfSemester = numberOfSemester;
            cout << "Semester of course changed to " << numberOfSemester << endl;
        }

        
        bool operator<(const Course &c1)const;
        bool operator ==(const Course &c1)const;

        //μετακίνηση μεταξύ semester 
        void modifySemester(int numberOfSemester);

        //εγγραφή μαθητή στο μάθημα
        void declareCourse(const Student &student);

        //μας λεει αν εχει εγγεγραφει ο μαθητης σαυτο το μαθημα
        bool containsStudentByRegNum(const Student &student);

        //καταχώρηση βαθμού μαθητή
        void registerGrade(const Student &student,const float grade);

        string getGradeOfStudent(const Student &student);

        //εκτυπώνει όλους τους μαθητές που πέρασαν το μάθημα
        void studentsPassedCourse(void);

        //εκτυπώνει το πλ΄ήθος των μαθητών που πέρασαν το μάθημα
        int countOfStudentsPassedCourse() const;

        //εκτυπώνει το πλ΄ήθος των μαθητών που κόπηκαν στο μάθημα
        int countOfStudentsNotPassedCourse() const;

        friend istream &operator>>(istream &is, Course &course);
        friend ostream &operator<<(ostream &os,const Course &course);

        //εκτυπώνει τα σταστιστικά του μαθήματος 
        void displayStatisticsOfCourse();
};


class Semester{
    
    private:
        int number;
        vector <Course*> courses;

    public:
        
        Semester();
        Semester(int number);
        Semester(Semester &semester);
        ~Semester();

        //καλεί την setProfessor του course για το συγκεκριμένο μάθημα
        void setProfessor(Professor* professor, Course* course);

        int getNumberOfSemester() const {
            return number;
        }

        //προσθέτει ένα μάθημα στο εξάμηνο
        void addCourse(Course* course);

        void removeCourse(Course *course);

        //επιστρέφει ενα μαπ με όλα τα δηλωμένα μαθήματα ενός μαθητή και τους περασμένους βαθμούς τους.
        const map<Course, string> findCoursesOfStudent(const Student &student);

        //επιστρέφει εναν iterator στο δοθεν course ή courses.end() αν δεν βρέθηκε
        vector<Course*>::iterator findCourse(Course *course);
        
        //επιστρέφει το course με το δοθέν όνομα ή NULL αν δεν βρεθεί
        Course* findCourseByName(string &name)const;
        
        void statisticsOfProfessor(Professor* prof);

        //καλείται από τη secretary για να τυπώσει όλα τα μαθήματα του εξαμήνου στο αρχείο
        void displayCoursesOfSemester(ofstream &fout);
};


//κλάση που συμπεριλαμβάνει τις απαραίτητες προυποθέσεις για αποφοίτηση
class GraduationDetails{
    private : 
        int totalYears;
        int totalEcts;
    
        //υποχρεωτικά μαθήματα για ολοκλήρωση σπουδών
        vector <Course*> obligatoryCourses;
    
    public:
        //μονο default constructor - κάνει set η γραμματεία
        GraduationDetails() : totalYears(0), totalEcts(0) {}
        
        ~GraduationDetails(){
            for(auto it = obligatoryCourses.begin();it != obligatoryCourses.end(); it++){
                delete(*it);
            }
            obligatoryCourses.clear();
        }
        
        int getTotalYears() const {
            return totalYears;
        }

        void setTotalYears(int totalYears) {
            this->totalYears = totalYears;
        }

        //const vector για να μην μπορεί να τροποποιηθεί
        const vector<Course*>& getObligatoryCourses() const {
            return obligatoryCourses;
        }

        void addObligatoryCourse(Course* obligatoryCourse) {
            obligatoryCourses.push_back(obligatoryCourse);
        }

        void removeObligatoryCourse(Course *course){
            for(auto it = obligatoryCourses.begin();it != obligatoryCourses.end();it++){
                if((*it)->getCourseName() == course->getCourseName()){
                    delete (*it);
                    obligatoryCourses.erase(it);
                    break;
                }
            }

        }
        // Getter for totalEcts
        int getTotalEcts() const {
            return totalEcts;
        }

        // Setter for totalEcts
        void setTotalEcts(int totalEcts) {
            this->totalEcts = totalEcts;
        }
};



class Secretary{
    private:

    //βρήκαμε πως μπορούμε να ορ΄ίσουμε συνάρτηση
    //συγκρισης για τα στοιχεία του σετ εφόσον είναι pointers και δεν καλειται ο τελεστης < 
    //οπως για τα πέρσον αυτόματα.
        struct StudentCompare {
            bool operator()(const Student *s1, const  Student *s2) const {
                if(*s1 < *s2){
                    return true;
                }
            return false;
            }
        };

        struct ProfessorCompare {
            bool operator()(const Professor *p1, const  Professor *p2) const {
                if(*p1 < *p2) {
                    return true;
                }
            return false;
            }
        };

         set<Student*, StudentCompare> students;
         set<Professor*, ProfessorCompare> professors;
         vector<Semester*> semesters;
         
        //επιστρέφει ενα μαπ με όλα τα δηλωμένα μαθήματα ενός μαθητή και τους βαθμούς, αλλα καλείται μόνο απο συναρτ΄ήσεις της γραμματείας
        //για την εύρεση των συνολικών ECTS, για εκτύπωση βαθμών κ.α
        const map<Course, string> findCourses(const Student &student); 

        GraduationDetails graduationDetails;
         
    public:
        
        Secretary();
        ~Secretary();

        void setTotalYears(int totalYears) {
            graduationDetails.setTotalYears(totalYears);
        }

        void setTotalEcts(int totalECTS) {
            graduationDetails.setTotalEcts(totalECTS);
        }

        //στην περίπτωση προσθήκης ενός μαθήματος, αν ειναι υποχρεωτικό προστιθεται και σε αυτό το βεκτορ
        void addObligatoryCourse(Course* obligatoryCourse) {
            graduationDetails.addObligatoryCourse(obligatoryCourse);
        }

        friend ostream &operator<<(ostream &os, const Secretary &s1);


        //βρίσκει εαν υπάρχει ένας μαθη΄τής ΄ή καθηγητ΄ής στο αντίστοιχο σετ
        bool containStudent(const Student* const  s1)const ;
        bool containProfessor(const Professor* const  p1)const ;
        

        //επιστρέφει δείκτη στον καθηγητ΄η/μαθητή εαν βρεθεί με βάση τον αριθμό μητρώου 
        Professor* findProfessorByRegNum(const string &regNum)const ;
        Student* findStudentByRegNum(const string &regNum)const;

        
        //επιστρέφει το συγκεκριμένο εξάμηνο εαν βρεθεί με βάση τον αριθμό του
        Semester* findSemesterByNum(const int num) ;     
        

        int getEcts(const Student &student); //επιστρέφει τα συνολικά ECTS ενός μαθη΄τή
        string getDegree(const Student &student); //βρίσκει εαν ένας μαθητής μπορεί να πάρει πτυχίο και επιστρέφει το κατάλληλο μήνυμα


        Course* findCourse( Course *course) ; //επιστρέφει δείκτη στο δοθεν course εαν υπάρχει σε κάποιο από τα εξάμηνα 
        Course* findCourseByName(string name)const; //επιστρέφει δείκτη σε ένα course εαν βρεθέι με βάση το όνομα
        
        void addSemester(Semester *sem) {
            Semester* newSemester = new Semester;
            *newSemester = *sem;
            semesters.push_back(newSemester);
        }
        
        void displayDeclaredCoursesOfStudent(const Student &student);
        
        //#############   ΛΕΙΤΟΥΡΓΙΕΣ MENU  ##############//

        void addProfessor(Professor* professor);
        void removeProfessor(Professor* professor);
        void modifyProfessor(Professor* professor);

        void addStudent(Student* student);
        void removeStudent(Student* student);
        void modifyStudent(Student* student);

        void addCourse(Course* course);
        void removeCourse(Course* course);
        void modifyCourse(Course* course);

        void setProfessor(Professor* professor, Course *course);
        
        void declareCourse(const Student &student, Course &course); //δήλωση μαθήματος για έναν μαθητή
        
        void studentsPassedCourse(Course* course); //εκτυπώνει όλους τους μαθη΄τές που πέρασαν το μάθημα
        
        void statisticsOfProfessor(Professor *prof); //εκτυπώνει τα στατιστικά των μαθημάτων του καθηγητή
        
        void displayGradesOfStudent(Student* student); //εκτυπώνει την αναλυτική βαθμολογία του μαθητή για όλα τα έτη ή του τωρινού εξάμηνου
        
        void displayStudentsWithDegree();  //εκτυπώνει όλους τους μαθητές που μπορούν να πάρουν πτυχίο
        
        void registerGrades(Student &student, Course &course, const float &grade); //καταχώρηση βαθμού σε ένα μάθημα για έναν μαθητή
      

        //#############    FILES    ###############//
        void displayStudentsToFile(ofstream &fout); //τυπώνει σε αρχείο τα χαρακτηριστικά ενός μαθητή και τα δηλωμένα μαθήματα με τους βαθμούς
        void displayProfessorsToFile(ofstream &fout); //τυπω΄νει τα χαρακτηριστικά ενός καθηγητή
        void displayCourseToFile(ofstream &fout); //τυπώνει τα χαρακτηριστικά ενός μαθήματος
        void displayStudentsWithDegree(ofstream &fout);

        //############## ΚΛΑΣΕΙΣ ΓΙΑ EXCEPTIONS #############//
        class CourseNotExists{}; //για exception στην findCourse 
        class invalidGrade{}; //exception για τη συναρτηση registerGrades
        class studentNotFound{};
   
   };


//#########################    FILES   ########################//

//διαβάζουν και γράφουν στα αρχεία βάση ενος συγκεκριμένου format(data data data...)

void readStudentFromFile(ifstream &fin, Secretary &secretary);
void writeStudentToFile(ofstream &fout, Secretary &secretary);

void readProfessorFromFile(ifstream &fin, Secretary &secretary);
void writeProfessorToFile(ofstream &fout, Secretary &secretary);

void readCourseFromFile(ifstream &fin, Secretary &secretary);
void writeCourseToFile(ofstream &fout, Secretary &secretary);

void writeStudentsWithDegreeToFile(ofstream &fout, Secretary &secretary);