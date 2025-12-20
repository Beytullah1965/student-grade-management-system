#include "GradeManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

GradeManager::GradeManager() {
    courses = {
        {"MATH1102", {"MATH1102", "CALCULUS I", 4}},
        {"CMPE1101", {"CMPE1101", "INTRODUCTION TO PROGRAMMING", 4}},
        {"PHYS1101", {"PHYS1101", "PHYSICS I", 4}},
        {"MATH1202", {"MATH1202", "CALCULUS II", 4}},
        {"MATH1161", {"MATH1161", "LINEAR ALGEBRA", 3}},
        {"CMPE1604", {"CMPE1604", "OBJECT ORIENTED PROGRAMMING", 4}},
        {"PHYS1201", {"PHYS1201", "PHYSICS II", 4}},
        {"ELEC2151", {"ELEC2151", "CIRCUIT THEORY", 4}},
        {"CMPE2105", {"CMPE2105", "DATA STRUCTURES AND ALGORITHMS", 4}},
        {"MATH2128", {"MATH2128", "DIFFERENTIAL EQUATIONS", 3}},
        {"MATH2162", {"MATH2162", "DISCRETE MATHEMATICS", 3}},
        {"ECON1005", {"ECON1005", "INTRODUCTION TO ECONOMY AND FINANCE", 3}},
        {"CMPE3209", {"CMPE3209", "COMPUTER ORGANIZATION", 4}},
        {"CMPE3111", {"CMPE3111", "DATABASE DESIGN AND MANAGEMENT", 4}},
        {"CMPE3112", {"CMPE3112", "INTRODUCTION TO DATA SCIENCE", 4}},
        {"CMPE3110", {"CMPE3110", "OPERATING SYSTEMS", 4}}
    };
}

void GradeManager::showCourses() const {
    std::cout << "\nAVAILABLE COURSES\n";
    std::cout << std::left << std::setw(12) << "CODE"
        << std::setw(40) << "COURSE NAME"
        << "CR\n";
    for (const auto& c : courses) {
        std::cout << std::setw(12) << c.second.getCode()
            << std::setw(40) << c.second.getName()
            << c.second.getCredit() << "\n";
    }
}

void GradeManager::addStudent(int id,
    const std::string& name,
    const std::string& surname,
    const std::string& department) {
    for (const auto& s : students)
        if (s.getId() == id) {
            std::cout << "Student already exists.\n";
            return;
        }
    students.emplace_back(id, name, surname, department);
    std::cout << "Student added successfully.\n";
}

void GradeManager::removeStudent(int id) {
    auto it = std::remove_if(students.begin(), students.end(),
        [id](const Student& s) { return s.getId() == id; });

    if (it != students.end()) {
        students.erase(it, students.end());
        std::cout << "Student removed successfully.\n";
    }
    else {
        std::cout << "Student not found.\n";
    }
}

void GradeManager::enterOrUpdateGrade(int studentId,
    const std::string& courseCode,
    double midterm,
    double project,
    double finalExam) {
    if (courses.find(courseCode) == courses.end()) {
        std::cout << "Invalid course code.\n";
        return;
    }

    for (auto& s : students) {
        if (s.getId() == studentId) {
            s.setGrade(courseCode, midterm, project, finalExam);
            std::cout << "Grade saved.\n";
            return;
        }
    }
    std::cout << "Student not found.\n";
}

double GradeManager::calculateGPA(const Student& s) const {
    double total = 0;
    int credits = 0;

    for (const auto& g : s.getGrades()) {
        const Course& c = courses.at(g.first);
        double avg =
            g.second.midterm * 0.30 +
            g.second.project * 0.20 +
            g.second.finalExam * 0.50;

        total += avg * c.getCredit();
        credits += c.getCredit();
    }

    if (credits == 0) return 0.0;
    return (total / credits) / 25.0; // 100 -> 4.0
}

void GradeManager::listStudents() const {
    for (const auto& s : students) {
        std::cout << "ID: " << s.getId()
            << " | " << s.getName() << " " << s.getSurname()
            << " | GPA: " << calculateGPA(s) << "\n";
    }
}

void GradeManager::showStudentDetails(int studentId) const {
    for (const auto& s : students) {
        if (s.getId() == studentId) {
            std::cout << "\nStudent: " << s.getName() << " " << s.getSurname() << "\n";
            for (const auto& g : s.getGrades()) {
                std::cout << g.first
                    << " -> M:" << g.second.midterm
                    << " P:" << g.second.project
                    << " F:" << g.second.finalExam << "\n";
            }
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void GradeManager::rankStudentsByGPA() const {
    auto sorted = students;
    std::sort(sorted.begin(), sorted.end(),
        [this](const Student& a, const Student& b) {
            return calculateGPA(a) > calculateGPA(b);
        });

    for (const auto& s : sorted) {
        std::cout << s.getName() << " " << s.getSurname()
            << " -> GPA: " << calculateGPA(s) << "\n";
    }
}

void GradeManager::saveToFile(const std::string& filename) const {
    std::ofstream f(filename);
    for (const auto& s : students) {
        f << s.getId() << "|" << s.getName() << "|" << s.getSurname()
            << "|" << s.getDepartment() << "\n";
        for (const auto& g : s.getGrades()) {
            f << g.first << " "
                << g.second.midterm << " "
                << g.second.project << " "
                << g.second.finalExam << "\n";
        }
        f << "END\n";
    }
    std::cout << "Data saved to file.\n";
}

void GradeManager::loadFromFile(const std::string& filename) {
    students.clear();
    std::ifstream f(filename);
    if (!f) {
        std::cout << "File not found.\n";
        return;
    }

    while (true) {
        int id;
        f >> id;
        if (!f) break;

        std::string name, surname, dept;
        f.ignore();
        getline(f, name, '|');
        getline(f, surname, '|');
        getline(f, dept);

        Student s(id, name, surname, dept);

        while (true) {
            std::string code;
            f >> code;
            if (code == "END") break;

            double m, p, fin;
            f >> m >> p >> fin;
            s.setGrade(code, m, p, fin);
        }
        students.push_back(s);
    }
    std::cout << "Data loaded from file.\n";
}
void GradeManager::showTranscript(int studentId) const {
    for (const auto& s : students) {
        if (s.getId() == studentId) {

            std::cout << "\n========== TRANSCRIPT ==========\n";
            std::cout << s.getName() << " " << s.getSurname()
                << " | Department: " << s.getDepartment() << "\n\n";

            std::cout << std::left
                << std::setw(12) << "CODE"
                << std::setw(35) << "COURSE NAME"
                << std::setw(6) << "CR"
                << std::setw(10) << "AVG"
                << "LETTER\n";

            std::cout << "---------------------------------------------------------------\n";

            double totalWeighted = 0.0;
            int totalCredits = 0;

            for (const auto& g : s.getGrades()) {
                const Course& c = courses.at(g.first);

                double avg =
                    g.second.midterm * 0.30 +
                    g.second.project * 0.20 +
                    g.second.finalExam * 0.50;

                std::string letter;
                if (avg >= 90) letter = "AA";
                else if (avg >= 85) letter = "BA";
                else if (avg >= 80) letter = "BB";
                else if (avg >= 75) letter = "CB";
                else if (avg >= 70) letter = "CC";
                else if (avg >= 65) letter = "DC";
                else if (avg >= 60) letter = "DD";
                else letter = "FF";

                std::cout << std::left
                    << std::setw(12) << c.getCode()
                    << std::setw(35) << c.getName()
                    << std::setw(6) << c.getCredit()
                    << std::setw(10) << avg
                    << letter << "\n";

                totalWeighted += avg * c.getCredit();
                totalCredits += c.getCredit();
            }

            double gpa = (totalCredits == 0) ? 0.0 :
                (totalWeighted / totalCredits) / 25.0;

            std::cout << "\nTotal Credits: " << totalCredits << "\n";
            std::cout << "GPA (4.00): " << gpa << "\n";
            std::cout << "=================================\n";
            return;
        }
    }

    std::cout << "Student not found.\n";
}
void GradeManager::showClassStatistics() const {
    if (students.empty()) {
        std::cout << "No students available.\n";
        return;
    }

    std::vector<double> gpas;
    double totalGPA = 0.0;

    double highestGPA = -1.0;
    double lowestGPA = 5.0;

    int honorCount = 0; // GPA >= 3.50
    int riskCount = 0;  // GPA < 2.00

    for (const auto& s : students) {
        double gpa = calculateGPA(s);
        gpas.push_back(gpa);
        totalGPA += gpa;

        if (gpa > highestGPA) highestGPA = gpa;
        if (gpa < lowestGPA) lowestGPA = gpa;

        if (gpa >= 3.50) honorCount++;
        if (gpa < 2.00)  riskCount++;
    }

    int n = gpas.size();
    double classAvg = totalGPA / n;

    // Median
    std::sort(gpas.begin(), gpas.end());
    double median;
    if (n % 2 == 0)
        median = (gpas[n / 2 - 1] + gpas[n / 2]) / 2.0;
    else
        median = gpas[n / 2];

    // Std Deviation
    double variance = 0.0;
    for (double gpa : gpas)
        variance += (gpa - classAvg) * (gpa - classAvg);

    variance /= n;
    double stdDev = std::sqrt(variance);

    // Above / Below average
    int aboveAvg = 0, belowAvg = 0;
    for (double gpa : gpas) {
        if (gpa >= classAvg) aboveAvg++;
        else belowAvg++;
    }

    // Output
    std::cout << "\n========== CLASS STATISTICS ==========\n";
    std::cout << "Total Students     : " << n << "\n";
    std::cout << "Class Avg GPA      : " << classAvg << "\n";
    std::cout << "Median GPA         : " << median << "\n";
    std::cout << "Highest GPA        : " << highestGPA << "\n";
    std::cout << "Lowest GPA         : " << lowestGPA << "\n";
    std::cout << "Std Deviation      : " << stdDev << "\n";
    std::cout << "Above Avg Students : " << aboveAvg << "\n";
    std::cout << "Below Avg Students : " << belowAvg << "\n";
    std::cout << "Honor Students     : " << honorCount << " (GPA >= 3.50)\n";
    std::cout << "Risk Zone Students : " << riskCount << " (GPA < 2.00)\n";
    std::cout << "=====================================\n";
}

void GradeManager::showStudentsWithoutGrades() const {
    bool found = false;

    std::cout << "\n=== STUDENTS WITHOUT GRADES ===\n";
    for (const auto& s : students) {
        if (!s.hasAnyGrade()) {
            std::cout << s.getId() << " - "
                << s.getName() << " "
                << s.getSurname() << "\n";
            found = true;
        }
    }

    if (!found)
        std::cout << "All students have at least one grade.\n";

    std::cout << "===============================\n";
}




