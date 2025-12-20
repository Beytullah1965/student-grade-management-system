#include <iostream>
#include <limits>
#include <cctype>
#include "GradeManager.h"

using namespace std;

int readInt(const string& msg) {
    int v;
    while (true) {
        cout << msg;
        cin >> v;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number!\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
    }
}

double readGrade(const string& msg) {
    double v;
    while (true) {
        cout << msg;
        cin >> v;

        if (cin.fail() || v < 0 || v > 100) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid grade! Enter 0–100.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
    }
}

string readAlpha(const string& msg) {
    string s;
    while (true) {
        cout << msg;
        getline(cin, s);
        bool ok = !s.empty();
        for (char c : s)
            if (!isalpha((unsigned char)c) && c != ' ')
                ok = false;
        if (ok) return s;
        cout << "Only letters allowed!\n";
    }
}

string readString(const string& msg) {
    string s;
    while (true) {
        cout << msg;
        getline(cin, s);
        if (!s.empty()) return s;
    }
}

int main() {
    GradeManager manager;

    int choice;
    do {
        cout << "\n1. Add Student\n"
            << "2. Remove Student\n"
            << "3. Enter / Update Grade\n"
            << "4. List Students (with GPA)\n"
            << "5. Show Student Details\n"
            << "6. Rank Students by GPA\n"
            << "7. Save Data to File\n"
            << "8. Load Data from File\n"
            << "9. Show Transcript\n"
            << "10. Class Statistics\n"
            << "11. Show Students Without Grades\n"
            << "0. Exit\n";

        choice = readInt("Choice: ");

        if (choice == 1) {
            int id = readInt("Enter Student ID: ");
            string name = readAlpha("Enter Name: ");
            string surname = readAlpha("Enter Surname: ");
            string department = readAlpha("Enter Department: ");
            manager.addStudent(id, name, surname, department);
        }
        else if (choice == 2) {
            manager.removeStudent(readInt("ID: "));
        }
        else if (choice == 3) {
            manager.showCourses();
            int studentId = readInt("Enter Student ID: ");
            string courseCode = readString("Enter Course ID: ");
            double midterm = readGrade("Enter Midterm (%30): ");
            double project = readGrade("Enter Project (%20): ");
            double finalExam = readGrade("Enter Final (%50): ");

            manager.enterOrUpdateGrade(
                studentId, courseCode, midterm, project, finalExam);
        }
        else if (choice == 4) {
            manager.listStudents();
        }
        else if (choice == 5) {
            manager.showStudentDetails(readInt("Student ID: "));
        }
        else if (choice == 6) {
            manager.rankStudentsByGPA();
        }
        else if (choice == 7) {
            manager.saveToFile("grades.txt");
        }
        else if (choice == 8) {
            manager.loadFromFile("grades.txt");
        }
        else if (choice == 9) {
            manager.showTranscript(readInt("Student ID: "));
        }
        else if (choice == 10) {
            manager.showClassStatistics();
        }
        else if (choice == 11) {
            manager.showStudentsWithoutGrades();
        }

    } while (choice != 0);

    return 0;
}


