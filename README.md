# 🎓 University Management System

A comprehensive CLI-based **Academic Information System** designed to manage students, faculty, and course enrollments.
Built with a focus on **Object-Oriented Design patterns**, the system automates administrative workflows
like graduation eligibility checks, grading, and course assignments.
The project emphasizes low-level memory safety and efficient data handling, featuring custom persistence 
logic and a modular architecture.

## ✨ Key Features

* **Role Management:** Full CRUD operations for Students and Professors.
* **Course Administration:** Manage mandatory and elective courses, ECTS credits,
  and semester assignments.
* **Enrollment & Grading:** Enroll students in courses based on their academic year.
  Includes an extended feature (Menu Option 10) for professors to easily register
  and update grades.
* **Academic Analytics:** Generate academic transcripts for students and teaching
  statistics for professors.
* **Graduation Checking:** Automatically evaluate if a student meets the
  department's graduation criteria.
* **Data Persistence:** Automatically loads and saves all system data (users,
  courses, grades) to local files on startup and when the application exits.

## 🛠️ Technologies & Concepts Used

* **Language:** C++
* **OOP Principles:** Encapsulation, Inheritance, Polymorphism, Abstract Classes.
* **Memory Management:** Dynamic allocation, Pointers, Destructors, Copy
  Constructors, Operator Overloading (Rule of Three), and memory leak prevention
  via Valgrind.
* **Build System:** GNU Make

## 🏗️ Architecture & Design Notes

* **Abstract Base Class:** The `Person` class was designed as an abstract class,
  meaning no direct instances of it are created. Instead, the system maintains two
  separate sets/containers for `Student` and `Professor` objects.
* **Encapsulation & Orchestration:** The `Secretary` class acts as the main
  orchestrator. It directs the objects within its containers to execute specific
  actions (e.g., `declare`, `register`, `enroll`), eliminating the need for
  `friend` classes and keeping the architecture cleanly decoupled.
* **Memory Management:** Memory for every student, professor, course, and semester
  is allocated dynamically upon creation (or reading from a file) in the
  `Secretary` and is strictly deallocated in their respective destructors. The
  same applies to `GraduationDetails` and `Semester` classes. The memory integrity
  has been successfully verified using Valgrind.
* **Extended Functionality:** While Phase A requirements included certain operator
  overloads (like `+` in `Secretary`), these were refactored and removed in the
  final version as their logic was cleanly replaced and expanded by the
  interactive CLI menu.

## 📂 Project Structure

```text
University-Management-System/
├── src/            # Source files (.cpp)
├── include/        # Header files (.h)
├── build/          # Compiled object files (.o) - Ignored by Git
├── data/           # Text files for data persistence
├── Makefile        # Build instructions
└── README.md       # Project documentation
```

## 🚀 How to Build and Run

### Prerequisites
* A C++ compiler (e.g., `g++`)
* `make` utility installed
* `valgrind` (optional, for memory leak testing)

### Instructions
1. **Compile the project:**
   ```bash
   make
   ```
2. **Run the application:**
   ```bash
   make run
   ```
3. **Run with Memory Check (Valgrind):**
   ```bash
   make valgrind
   ```
   *(This verifies that all dynamically allocated memory is properly deallocated).*
4. **Clean compiled files:**
   ```bash
   make clean
   ```

   ## 💻 Usage & CLI Menu

Once the application is running, you will be presented with an interactive Command-Line Interface. 
The system operates entirely through this menu, updating the in-memory data structures immediately and persisting them to the data files when the application exits.

The main menu offers the following functionalities:

1. **Manage Professors:** Add, edit, or delete a professor's record.
2. **Manage Students:** Add, edit, or delete a student's record.
3. **Manage Courses:** Add, edit, or delete a course.
4. **Assign Professor to Course:** Link a specific professor to teach a course for the current semester.
5. **Enroll Student:** Register a student for an available course.
6. **Course Pass List:** Display and export a list of all students who successfully passed a specific course in a given semester.
7. **Professor Statistics:** Print teaching statistics and grade distributions for a specific professor.
8. **Student Transcript:** Print a student's detailed analytical grades for the current semester and their overall academic history.
9. **Graduation Eligibility:** Display a list of all students who have met the department's criteria to receive their degree.
10. **Register Grades (Extra):** Directly input or update grades for students enrolled in specific courses.

*Simply type the corresponding number and press `Enter` to navigate the system.*

## 📄 Data File Formats

The application relies on a specific formatting structure for its persistence
files. Any manual modification to the data files must follow these rules (though
all changes can be safely made via the CLI menu):

* **Student Format:**
  `[Name] [Surname] [Date_of_Birth] [Phone] [Email] [Semester] [ID] [Student_Type]
  [Course1] [Grade1] [Course2] [Grade2] ...`
  *(Note: Courses and their respective grades or "not_examined" status are
  interleaved until the End of Line, where a new student begins).*
* **Professor Format:**
  `[Name] [Surname] [Date_of_Birth] [Phone] [Email] [Office] [Website]
  [Specialization] [ID]`
* **Course Format:**
  `[Name] [ECTS] [Compulsory/Elective] [Semester] [Professor_ID]`

## 📋 Assignment Scope / Requirements

This project was initially developed as an extensive academic assignment. The
core requirements included:

* **Phase A (Core Infrastructure):**
  * Design a `Person` base class with proper encapsulation, constructors, and
    overloaded I/O operators. Count instantiated objects.
  * Implement a `Secretary` class managing dynamically allocated pointers to
    `Person` objects, utilizing operator overloading and the Rule of Three for
    deep copying.
* **Phase B (Business Logic):**
  * Implement `Student` and `Professor` classes inheriting from `Person`.
  * Create a `Course` class handling ECTS and mandatory/elective status.
  * Develop the semester logic: assigning professors to courses, handling
    student enrollments, and processing final exams.
  * Build a 9-option interactive CLI menu to manage the entire ecosystem,
    determine graduation eligibility, and persist state via File I/O.

## 🤝 Contributors

* [Stefanos Tzaferis](https://github.com/StefanosTzaf)
* [Eleftheria Galiatsatou](https://github.com/eeeleftheria)
  *Collaborated on the core implementation and architecture.*