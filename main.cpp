#include <iostream>
#include <map>
#include <vector>
#include "Violation.h"
using namespace std;

void printDatabase(const map<string, vector<Violation>>& database) {
    for (const auto& entry : database) {
        cout << "Car number: " << entry.first << endl;
        for (const auto& violation : entry.second) {
            violation.display();
        }
        cout << endl;
    }
}

void printViolationsByNumber(const map<string, vector<Violation>>& database, const string& carNumber) {
    auto it = database.find(carNumber);
    if (it != database.end()) {
        for (const auto& violation : it->second) {
            violation.display();
        }
    }
    else {
        cout << "No violations found for car number: " << carNumber << endl;
    }
}

double calculateTotalFines(const map<string, vector<Violation>>& database, const string& carNumber) {
    double total = 0;
    auto it = database.find(carNumber);
    if (it != database.end()) {
        for (const auto& violation : it->second) {
            total += violation.fine;
        }
    }
    return total;
}

void payFine(map<string, vector<Violation>>& database, const string& carNumber, const string& date) {
    auto it = database.find(carNumber);
    if (it != database.end()) {
        auto& violations = it->second;
        for (auto vit = violations.begin(); vit != violations.end(); ++vit) {
            if (vit->date == date) {
                violations.erase(vit);
                cout << "Fine paid for violation on " << date << endl;
                return;
            }
        }
        cout << "No violation found on " << date << endl;
    }
    else {
        cout << "No violations found for car number: " << carNumber << endl;
    }
}

void printViolationsByPeriod(const map<string, vector<Violation>>& database, const string& startDate, const string& endDate) {
    for (const auto& entry : database) {
        cout << "Car number: " << entry.first << endl;
        for (const auto& violation : entry.second) {
            if (violation.date >= startDate && violation.date <= endDate) {
                violation.display();
            }
        }
        cout << endl;
    }
}

int main() {
    map<string, vector<Violation>> database;
    int choice;

    while (true) {
        cout << "Enter your choice:" << endl;
        cout << "1 - Add violation" << endl;
        cout << "2 - Print full database" << endl;
        cout << "3 - Print violations by car number" << endl;
        cout << "4 - Calculate total fines by car number" << endl;
        cout << "5 - Pay fine for specific violation" << endl;
        cout << "6 - Print violations by period" << endl;
        cout << "7 - Exit" << endl;
        cin >> choice;

        if (choice == 1) {
            string carNumber, description, date;
            double fine;
            cout << "Enter car number: ";
            cin >> carNumber;
            cout << "Enter violation description: ";
            cin >> description;
            cout << "Enter violation date (yyyy-mm-dd): ";
            cin >> date;
            cout << "Enter fine amount: ";
            cin >> fine;
            database[carNumber].emplace_back(description, date, fine);

        }
        else if (choice == 2) {
            printDatabase(database);

        }
        else if (choice == 3) {
            string carNumber;
            cout << "Enter car number: ";
            cin >> carNumber;
            printViolationsByNumber(database, carNumber);

        }
        else if (choice == 4) {
            string carNumber;
            cout << "Enter car number: ";
            cin >> carNumber;
            double total = calculateTotalFines(database, carNumber);
            cout << "Total fines for car " << carNumber << ": " << total << " UAH" << endl;

        }
        else if (choice == 5) {
            string carNumber, date;
            cout << "Enter car number: ";
            cin >> carNumber;
            cout << "Enter violation date (yyyy-mm-dd): ";
            cin >> date;
            payFine(database, carNumber, date);

        }
        else if (choice == 6) {
            string startDate, endDate;
            cout << "Enter start date (yyyy-mm-dd): ";
            cin >> startDate;
            cout << "Enter end date (yyyy-mm-dd): ";
            cin >> endDate;
            printViolationsByPeriod(database, startDate, endDate);

        }
        else if (choice == 7) {
            break;

        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
