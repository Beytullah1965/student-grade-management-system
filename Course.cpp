#include "Course.h"

Course::Course() : credit(0) {}

Course::Course(const std::string& code,
    const std::string& name,
    int credit)
    : code(code), name(name), credit(credit) {
}

std::string Course::getCode() const { return code; }
std::string Course::getName() const { return name; }
int Course::getCredit() const { return credit; }

