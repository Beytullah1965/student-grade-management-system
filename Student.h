#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>

class Student {
public:
    struct Grade {
        double midterm;
        double project;
        double finalExam;
    };

private:
    int id;
    std::string name;
    std::string surname;
    std::string department;
    std::map<std::string, Grade> grades;

public:
    Student(int id = 0,
        const std::string& name = "",
        const std::string& surname = "",
        const std::string& department = "");

    int getId() const;
    std::string getName() const;
    std::string getSurname() const;
    std::string getDepartment() const;

    void setGrade(const std::string& courseCode,
        double midterm,
        double project,
        double finalExam);

    const std::map<std::string, Grade>& getGrades() const;

   
    bool hasAnyGrade() const;
};

#endif
