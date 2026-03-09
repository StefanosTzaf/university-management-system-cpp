#include "classes.h"


using namespace std;

Semester::Semester(){

}

Semester::Semester(int number): number(number) {

}

Semester::~Semester(){
// If there are pointers, delete the courses
    for(auto it = courses.begin(); it != courses.end(); ++it){
        delete (*it);
    }
    courses.clear();
}


Semester :: Semester (Semester &semester){
    this->number = semester.number;

    vector <Course*> :: iterator it;
    for(it = courses.begin();it != courses.end(); it++ ){
        this->courses.push_back(*it);
    }
}

void Semester :: addCourse(Course* course){
    Course* newCourse = new Course( *course);
    
    courses.push_back(newCourse);
}

void Semester::addExistingCourse(Course* course){
    courses.push_back(course);
}


void Semester::setProfessor( Professor* professor, Course *course){

    vector <Course*> :: iterator it;
    
    for(it = courses.begin();it != courses.end(); ++it ){
        if((*it)->getCourseName() == course->getCourseName()){
            // If the course matches, call its setProfessor
            (*it)->setProfessor(professor);
        }
    }
}

vector<Course*>::iterator Semester:: findCourse(Course *course){
      
    for(auto it = courses.begin(); it != courses.end(); ++it){
        if((*it)->getCourseName() == course->getCourseName()){
            return it;
        }
    }
    return courses.end();
}

const map<Course, string> Semester ::  findCoursesOfStudent(const Student &student){
    
    map <Course, string> studentCourses;
    
    for(auto it = courses.begin(); it != courses.end(); it++){

        // If the student is enrolled in this course
        if( (*it)->containsStudentByRegNum(student)) {
            
            studentCourses.insert(pair<Course, string>((**it), (**it).getGradeOfStudent(student)));
        }
    }

    return studentCourses;
}

void Semester :: removeCourse(Course *course){
    vector<Course*> :: iterator it = findCourse(course);
   
    if(it == courses.end()){
        cout << "No course "<<course->getCourseName()<<" found in semester "<<this->getNumberOfSemester()<<endl ;
    }
    else{
        delete (*it);
        courses.erase(it);
    }
}

Course* Semester::extractCourse(Course *course){
    vector<Course*>::iterator it = findCourse(course);

    if (it == courses.end()) {
        return nullptr;
    }

    Course* extractedCourse = *it;
    courses.erase(it);
    return extractedCourse;
}

void Semester::removeStudent(const Student &student){
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        (*it)->removeStudent(student);
    }
}

void Semester::clearProfessorAssignments(const Professor *professor){
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        (*it)->clearProfessor(professor);
    }
}


Course* Semester:: findCourseByName(string &name)const{
    
    for (auto it = courses.begin(); it != courses.end(); it++) {
        if ((*it)->getCourseName() == name){

            return (*it);
        }
    }
    return NULL;
}


void Semester:: statisticsOfProfessor(Professor* prof){
    for (auto it = courses.begin(); it != courses.end(); it++) {
         Professor* courseProfessor = (*it)->getProfessor();

         if (courseProfessor != nullptr && courseProfessor->getRegNum() == prof->getRegNum()) {
         
            // If the professor has courses in this semester, call the displayStatisticsOfCourse
            (*it)->displayStatisticsOfCourse();
         }
    }
}


// Output courses of the semester to a file
void Semester:: displayCoursesOfSemester(ofstream &fout){
    for (auto it = courses.begin(); it != courses.end(); it++){
      
        if((*it)->getProfessor() != nullptr){
            fout << (*it)->getCourseName() << " " << (*it)->getEcts() << " " << (*it)->getType() << " " <<(*it)->getSem() << " " <<(*it)->getProfessor()->getRegNum() ;
        }
        else{
            fout << (*it)->getCourseName() << " " << (*it)->getEcts() << " " << (*it)->getType() << " " <<(*it)->getSem() << " " <<"No_Professor_Declared";
        }

       fout << "\n";
    }
}
