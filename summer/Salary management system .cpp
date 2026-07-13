#include <iostream>

using namespace std;

int main() {
    char firstName[20];
    char lastName[20];
    int id;
    double hrs, rate, otHrs;
    char pos, bonusChoice;

    cout << "Employee name: ";
    cin >> firstName >> lastName;

    cout << "Employee ID: ";
    cin >> id;

    cout << "Working Hrs: ";
    cin >> hrs;

    cout << "Hourly Rate: ";
    cin >> rate;

    cout << "Position (m = manager, e = employee): ";
    cin >> pos;
    
    while (pos != 'm' && pos != 'e') {
        cout << "Invalid position. Enter m or e: ";
        cin >> pos;
    }

    cout << "OverTime hrs: ";
    cin >> otHrs;

    double salary = (hrs * rate) + (otHrs * rate * 1.5);
    
    cout << "\nSalary before TAX: " << salary << " $\n\n";

    cout << "Add Bonus ? (y/n): ";
    cin >> bonusChoice;

    double totalSalary = salary;
    
    if (bonusChoice == 'y') {
        totalSalary = totalSalary + 100; 
        cout << "Bonus added.\n";
    }

    double tax = totalSalary * 0.10; 
    double finalSalary = totalSalary - tax;

    cout << "====================PayRoll====================\n";
    cout << "Employee: " << firstName << " " << lastName << "\n";
    cout << "ID : " << id << "\n";
    cout << "TAX: " << tax << " $\n";
    cout << "Final Salary: " << finalSalary << " $\n";

    return 0;
}
