
#ifndef VIOLATION_H
#define VIOLATION_H

#include <iostream>
#include <string>
using namespace std;

class Violation {
public:
    string description;
    string date;
    double fine;

    Violation(string desc, string d, double f)
        : description(desc), date(d), fine(f) {}

    void display() const {
        cout << date << ": " << description << " - fine: " << fine << " UAH" << endl;
    }
};

#endif
