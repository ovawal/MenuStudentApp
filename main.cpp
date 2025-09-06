/* Menu Driven Student GReade Application
By: Walter Okova
ID: 800866617
*/
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

// Structure Definitions

struct Student {
    string Fname;
    string Lname;
    int ID;
    string Phone;
};

struct Course {
    string Num;
    string Name;
};

struct StdGrade {
    int ID;
    string Number;
    char Grade;
};

// Global vectors to store data
vector<Student> students;
vector<Course> courses;
vector<StdGrade> grades;

// Functions to read data from files.
void readFiles() {
    string studentFile = "student.dat";
    string courseFile = "course.dat";
    string gradeFile = "grade.dat";
    // Read Student.dat file

     ifstream sFile(studentFile);
    if (sFile) {
        string header;
        getline(sFile, header); // Discard the header line
        string Fname, Lname, Phone;
        int ID;
        while (sFile >> Fname >> Lname >> ID >> Phone) {
            students.push_back({Fname, Lname, ID, Phone});
        }
    } else {
        cerr << "Error opening student file. Please check the file path." << endl;
    }


    // Read Course.dat file
    ifstream cFile(courseFile);
    if (cFile.is_open()) {
        string Num, Name;
        while (cFile >> Num) {
            getline(cFile >> ws, Name); // Handle course names with spaces
            courses.push_back({Num, Name});
        }
        cFile.close();
    } else {
        cerr << "Error opening course file." << endl;
    }

    // Read Grade.dat file
  
ifstream gFile(gradeFile);
    if (gFile) {
        string header;
        getline(gFile, header);        
        int ID;
        string Number;
        char Grade;
        while (gFile >> ID >> Number >> Grade) {
            grades.push_back({ID, Number, Grade});
        }
    } else {
        cerr << "Error: Could not open " << gradeFile << "\n";
    }

     // To test file reading, uncomment the following code block

/* Display Students
     cout << "\nStudents:\n";
    if (students.empty()) {
        cout << "No students found.\n";
    } else {
        for (const auto& student : students) {
            cout   << student.ID << "  " << student.Fname << " " << student.Lname << endl;
        }
    }
// Display Courses
    cout << "\nCourses:\n";
    if (courses.empty()) {
        cout << "No courses found.\n";
    } else {
        for (const auto& course : courses) {
            cout  << course.Num << "  " << course.Name << endl;
        }
    }
// Display Grades
     cout << "\nGrades:\n";
    if (grades.empty()) {
        cout << "No grades found.\n";
    } else {
        for (const auto& grade : grades) {
            cout << "  " << grade.ID << "  " << grade.Number << "  " << grade.Grade << endl;
        }
    } 
*/
}

// Function to save Grades
void saveGrades() {
    string gradeFile = "grade.out";
    ofstream gFile(gradeFile);
    if (gFile.is_open()) {
        for (const auto& grade : grades) {
            gFile << grade.ID << " " << grade.Number << " " << grade.Grade << endl;
        }
        gFile.close();
    } else {
        cerr << "Error saving grades to file." << endl;
    }
}

// Function to save Students
void saveStudents() {
    string studentFile = "student.out";
    ofstream sFile(studentFile);
    if (sFile.is_open()) {
        sFile << left << " " << "Firstname" << " " << "Lastname" << " " << "ID" << "Phone" << endl;
        for (const auto& student : students) {
            sFile << left << " " << student.Fname << " " << student.Lname << " " << student.ID << student.Phone << endl;
        }
        sFile.close();
    } else {
        cerr << "Error saving student file." << endl;
    }
}

// Function to save Courses

void saveCourses() {
    string courseFile = "course.out";
    ofstream cFile(courseFile);
    if (cFile.is_open()) {
        for (const auto& course : courses) {
            cFile << course.Num << " " << course.Name << endl;
        }
        cFile.close();
    } else {
        cerr << "Error saving course file." << endl;
    }
}
// Menu Functions
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. [A]dd/modify a grade\n";
    cout << "2. [R]emove a grade\n";
    cout << "3. [S]tudent grade report\n";
    cout << "4. [C]ourse grade report\n";
    cout << "5. [L]ist students\n";
    cout << "6. [D]isplay course listing\n";
    cout << "7. [E]xit\n";
}

// Function to Add/Modify grade
void modifyGrade() {
    int ID;
    string Number;
    char Grade;

    cout << "Please enter student ID: ";
    while (!(cin >> ID)) {
        cout << "Invalid input. Please enter a numeric student ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter course number: ";
    cin >> Number;

    cout << "Enter grade (A-F): ";
    cin >> Grade;
    Grade = toupper(Grade); // Convert to uppercase for consistency
    while (Grade < 'A' || Grade > 'I') {
        cout << "Invalid grade. Please enter a grade (A-I): ";
        cin >> Grade;
        Grade = toupper(Grade);
    }

    // Check if grade already exists
    for (auto& grade : grades) {
        if (grade.ID == ID && grade.Number == Number) {
            grade.Grade = Grade;
            cout << "Grade updated successfully.\n";
            saveGrades();
            return;
        }
    }

    // If grade doesn't exist, add new grade
    grades.push_back({ID, Number, Grade});
    cout << "Grade added successfully.\n";
    saveGrades();
}

// Function to Remove grade
void removeGrade() {
    int ID;
    string Number;

    cout << "Please enter student ID: ";
    while (!(cin >> ID)) {
        cout << "Invalid input. Please enter a numeric student ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter course number: ";
    cin >> Number;

    for (auto it = grades.begin(); it != grades.end(); ++it) {
        if (it->ID == ID && it->Number == Number) {
            grades.erase(it);
            cout << "Grade removed successfully.\n";
            saveGrades();
            return;
        }
    }
    cout << "Grade not found.\n";
}



// Function to display student(s) grade report
void studentGradeReport() {
    int ID;
    cout << "Please enter student ID for grade report or '*' for all students: ";

    string input;
    cin >> input;

    if (input == "*") {
        for (const auto& student : students) {
            cout << "\nGrade Report for " << student.Fname << " " << student.Lname << " (ID: " << student.ID << "):\n";
            bool found = false;
            for (const auto& grade : grades) {
                if (grade.ID == student.ID) {
                    found = true;
                    string courseName = "Unknown";
                    for (const auto& course : courses) {
                        if (course.Num == grade.Number) {
                            courseName = course.Name;
                            break;
                        }
                    }
                    cout << " " << grade.Number << " (" << courseName << "): " << grade.Grade << endl;
                }
            }
            if (!found) {
                cout << " No grades found for this student.\n";
            }
        }
    } else {
        try {
            ID = stoi(input);
            string studentName = "Unknown";
            for (const auto& student : students) {
                if (student.ID == ID) {
                    studentName = student.Fname + " " + student.Lname;
                    break;
                }
            }

            bool found = false;
            for (const auto& grade : grades) {
                if (grade.ID == ID) {
                    found = true;
                    string courseName = "Unknown";
                    for (const auto& course : courses) {
                        if (course.Num == grade.Number) {
                            courseName = course.Name;
                            break;
                        }
                    }
                    cout << " " << grade.Number << " (" << courseName << "): " << grade.Grade << endl;
                }
            }
            if (!found) {
                cout << "No grades found for this student.\n";
            }
        } catch (const invalid_argument& ia) {
            cout << "Invalid input. Please enter a numeric student ID or '*'.\n";
        }
    }
}


// Function to display course grade report
void courseGradeReport() {
    string Number;
    cout << "Please enter course number: ";
    cin >> Number;

    // Find course name
    string courseName = "Unknown";
    for (const auto& course : courses) {
        if (course.Num == Number) {
            courseName = course.Name;
            break;
        }
    }

    bool found = false;
    for (const auto& grade : grades) {
        if (grade.Number == Number) {
            found = true;
            // Find student name
            string studentName = "Unknown";
            for (const auto& student : students) {
                if (student.ID == grade.ID) {
                    studentName = student.Fname + " " + student.Lname;
                    break;
                }
            }
            cout << " " << studentName << " (ID: " << grade.ID << "),  " << grade.Grade << endl;
        }
    }
    if (!found) {
        cout << "No grades found for this course.\n";
    }
}

// Funncction to list all students
void listStudents() {
    cout << "\nStudent List:\n";
    for (const auto& student : students) {
        cout  << " " << student.ID << " " <<  student.Fname << " " << student.Lname << endl;
    }
}

// Functions to display all courses
void displayCourseListing() {
    cout << "\nCourse Listing:\n";
    for (const auto& course : courses) {
        cout << course.Num  << " " << course.Name << endl;
    }
}

// Function to exit and save data
void logout() {
    cout << "Logged out successfully.\n";
    saveGrades();
    saveStudents();
    saveCourses();
    exit(0);
}

int main() {
    readFiles();

    char choice;
    while (true) {
        displayMenu();
        cout << "Please enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = toupper(choice); // Convert to uppercase for consistency

        switch (choice) {
            case 'A':
                modifyGrade();
                break;
            case 'R':
                removeGrade();
                break;
            case 'S':
                studentGradeReport();
                break;
            case 'C':
                courseGradeReport();
                break;
            case 'L':
                listStudents();
                break;
            case 'D':
                displayCourseListing();
                break;
            case 'E':
                logout();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }

    return 0;
}

