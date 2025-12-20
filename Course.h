#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string code;
    std::string name;
    int credit;

public:
    Course();
    Course(const std::string& code,
        const std::string& name,
        int credit);

    std::string getCode() const;
    std::string getName() const;
    int getCredit() const;
};

#endif


