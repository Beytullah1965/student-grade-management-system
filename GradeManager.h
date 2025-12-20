#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <vector>
#include <map>
#include "Student.h"
#include "Course.h"

class GradeManager {
private:
    std::vector<Student> students;
    std::map<std::string, Course> courses;

public:
    GradeManager();

    // Course
    void showCourses() const;

    // Student
    void addStudent(int id,
        const std::string& name,
        const std::string& surname,
        const std::string& department);

    void removeStudent(int id);

    // Grades
    void enterOrUpdateGrade(int studentId,
        const std::string& courseCode,
        double midterm,
        double project,
        double finalExam);

    // Listing
    void listStudents() const;
    void showStudentDetails(int studentId) const;
    void rankStudentsByGPA() const;

    // GPA
    double calculateGPA(const Student& s) const;

    // File I/O
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // Statistics
    void showTranscript(int studentId) const;
    void showClassStatistics() const;

    
    void showStudentsWithoutGrades() const;
};

#endif

