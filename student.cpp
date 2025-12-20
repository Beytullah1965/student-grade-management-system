#include "Student.h"

Student::Student(int id,
    const std::string& name,
    const std::string& surname,
    const std::string& department)
    : id(id), name(name), surname(surname), department(department) {
}

int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
std::string Student::getSurname() const { return surname; }
std::string Student::getDepartment() const { return department; }

void Student::setGrade(const std::string& courseCode,
    double midterm,
    double project,
    double finalExam) {
    grades[courseCode] = { midterm, project, finalExam };
}

const std::map<std::string, Student::Grade>& Student::getGrades() const {
    return grades;
}


bool Student::hasAnyGrade() const {
    return !grades.empty();
}
