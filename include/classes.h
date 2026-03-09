#include <string>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class invalidInput{}; // Exception class

class Person{

    // So derived classes can access these members
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

        // So the corresponding derived destructor is called
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

        // Prints only the basic characteristics of a Person
        friend ostream &operator<<(ostream &os,const Person &p1);

        // Prints the derived classes in full
        virtual void display(void) const = 0;

        friend istream &operator>>(istream &is, Person &p1);

        bool operator<(const Person &p)const; // Overloaded < operator used by the set compare function for secretary students and professors

};

// Forward declarations for dependent classes
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

        // Pure virtual function to make Person an abstract class
        void display(void) const;


        friend istream &operator>>(istream &str, Student &student);   
            
};



class Professor : public Person{
    private:
        string office;
        string webPage;
        string specialization;
        string registrationNumber;
        
        class invalidGrade{}; // Exception class for registerGrades
    
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

        Professor* professor; // Instructor
        
        // Maps enrolled students to grades if professors have entered them,
        // otherwise to not_examined
        // Grades are stored as strings so we can keep a message when the
        // course has not been examined yet.
        map <Student, string> enrolledStudents; 

    public:
                
        Course();

        // The instructor is assigned by the secretary
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
            this->numberOfSemester = sem;
            cout << "Semester of course changed to " << sem << endl;
        }

        
        bool operator<(const Course &c1)const;
        bool operator ==(const Course &c1)const;

        // Move between semesters
        void modifySemester(int numberOfSemester);

        // Enroll student in the course
        void declareCourse(const Student &student);

        void removeStudent(const Student &student);

        void clearProfessor(const Professor *professor);

        // Checks whether the student is enrolled in this course
        bool containsStudentByRegNum(const Student &student);

        // Register a student's grade
        void registerGrade(const Student &student,const float grade);

        string getGradeOfStudent(const Student &student);

        // Prints all students who passed the course
        void studentsPassedCourse(void);

        // Prints the number of students who passed the course
        int countOfStudentsPassedCourse() const;

        // Prints the number of students who failed the course
        int countOfStudentsNotPassedCourse() const;

        friend istream &operator>>(istream &is, Course &course);
        friend ostream &operator<<(ostream &os,const Course &course);

        // Prints course statistics
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

        // Calls the course setProfessor for the specific course
        void setProfessor(Professor* professor, Course* course);

        int getNumberOfSemester() const {
            return number;
        }

        // Adds a course to the semester
        void addCourse(Course* course);

        void addExistingCourse(Course* course);

        void removeCourse(Course *course);

        Course* extractCourse(Course *course);

        void removeStudent(const Student &student);

        void clearProfessorAssignments(const Professor *professor);

        // Returns a map with all declared courses of a student and their recorded grades.
        const map<Course, string> findCoursesOfStudent(const Student &student);

        // Returns an iterator to the given course or courses.end() if not found
        vector<Course*>::iterator findCourse(Course *course);
        
        // Returns the course with the given name or NULL if not found
        Course* findCourseByName(string &name)const;
        
        void statisticsOfProfessor(Professor* prof);

        // Called by secretary to print all semester courses to the file
        void displayCoursesOfSemester(ofstream &fout);
};


// Class that includes the necessary graduation requirements
class GraduationDetails{
    private : 
        int totalYears;
        int totalEcts;
    
        // Required course names for graduation
        vector<string> obligatoryCourses;
    
    public:
        // Only default constructor; values are set by the secretary
        GraduationDetails() : totalYears(0), totalEcts(0) {}
        
        ~GraduationDetails(){
            obligatoryCourses.clear();
        }
        
        int getTotalYears() const {
            return totalYears;
        }

        void setTotalYears(int totalYears) {
            this->totalYears = totalYears;
        }

        // const vector so it cannot be modified directly
        const vector<string>& getObligatoryCourses() const {
            return obligatoryCourses;
        }

        void addObligatoryCourse(const string &obligatoryCourse) {
            for (auto it = obligatoryCourses.begin(); it != obligatoryCourses.end(); ++it) {
                if (*it == obligatoryCourse) {
                    return;
                }
            }

            obligatoryCourses.push_back(obligatoryCourse);
        }

        void removeObligatoryCourse(const string &courseName){
            for(auto it = obligatoryCourses.begin();it != obligatoryCourses.end();it++){
                if(*it == courseName){
                    obligatoryCourses.erase(it);
                    break;
                }
            }

        }

        void renameObligatoryCourse(const string &oldName, const string &newName) {
            for (auto it = obligatoryCourses.begin(); it != obligatoryCourses.end(); ++it) {
                if (*it == oldName) {
                    *it = newName;
                    break;
                }
            }
        }

        bool containsObligatoryCourse(const string &courseName) const {
            for (auto it = obligatoryCourses.begin(); it != obligatoryCourses.end(); ++it) {
                if (*it == courseName) {
                    return true;
                }
            }

            return false;
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

    // We define a comparison function for set elements because they are
    // pointers and the < operator is not called automatically as it is for
    // Person objects.
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
         
        // Returns a map with all declared courses of a student and their
        // grades, but is only called by secretary functions for finding total
        // ECTS, printing grades, and similar operations
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

        // When a course is added, if it is compulsory it is also added to this vector
        void addObligatoryCourse(const string &obligatoryCourse) {
            graduationDetails.addObligatoryCourse(obligatoryCourse);
        }

        void removeObligatoryCourse(const string &courseName) {
            graduationDetails.removeObligatoryCourse(courseName);
        }

        void renameObligatoryCourse(const string &oldName, const string &newName) {
            graduationDetails.renameObligatoryCourse(oldName, newName);
        }

        bool containsObligatoryCourse(const string &courseName) const {
            return graduationDetails.containsObligatoryCourse(courseName);
        }

        friend ostream &operator<<(ostream &os, const Secretary &s1);


        // Checks whether a student or professor exists in the corresponding set
        bool containStudent(const Student* const  s1)const ;
        bool containProfessor(const Professor* const  p1)const ;
        

        // Returns a pointer to the professor or student if found by registration number
        Professor* findProfessorByRegNum(const string &regNum)const ;
        Student* findStudentByRegNum(const string &regNum)const;

        
        // Returns the specific semester if found by its number
        Semester* findSemesterByNum(const int num) ;     
        

        int getEcts(const Student &student); // Returns the total ECTS of a student
        string getDegree(const Student &student); // Checks whether a student can graduate and returns the appropriate message


        Course* findCourse( Course *course) ; // Returns a pointer to the given course if it exists in one of the semesters
        Course* findCourseByName(string name)const; // Returns a pointer to a course if found by name
        
        void addSemester(Semester *sem) {
            Semester* newSemester = new Semester;
            *newSemester = *sem;
            semesters.push_back(newSemester);
        }
        
        void displayDeclaredCoursesOfStudent(const Student &student);
        
        //#############   MENU FUNCTIONS   ##############//

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
        
        void declareCourse(const Student &student, Course &course); // Course declaration for a student
        
        void studentsPassedCourse(Course* course); // Prints all students who passed the course
        
        void statisticsOfProfessor(Professor *prof); // Prints statistics for the professor's courses
        
        void displayGradesOfStudent(Student* student); // Prints the student's transcript for all years or the current semester
        
        void displayStudentsWithDegree();  // Prints all students eligible for graduation
        
        void registerGrades(Student &student, Course &course, const float &grade); // Registers a grade in a course for a student
      

        //#############    FILES    ###############//
        void displayStudentsToFile(ofstream &fout); // Writes a student's details and declared courses with grades to a file
        void displayProfessorsToFile(ofstream &fout); // Writes a professor's details to a file
        void displayCourseToFile(ofstream &fout); // Writes a course's details to a file
        void displayStudentsWithDegree(ofstream &fout);

        //############## EXCEPTION CLASSES #############//
        class CourseNotExists{}; // Exception for findCourse
        class invalidGrade{}; // Exception for registerGrades
        class studentNotFound{};
   
   };


//#########################    FILES   ########################//

// Read from and write to files based on a specific format (data data data...)

void readStudentFromFile(ifstream &fin, Secretary &secretary);
void writeStudentToFile(ofstream &fout, Secretary &secretary);

void readProfessorFromFile(ifstream &fin, Secretary &secretary);
void writeProfessorToFile(ofstream &fout, Secretary &secretary);

void readCourseFromFile(ifstream &fin, Secretary &secretary);
void writeCourseToFile(ofstream &fout, Secretary &secretary);

void writeStudentsWithDegreeToFile(ofstream &fout, Secretary &secretary);