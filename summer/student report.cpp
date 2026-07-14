#include <iostream>
#include <string>

using namespace std;

void inputMarks(int *math, int *physics, int *english);
double calculateAverage(int *math, int *physics, int *english);
char calculateGrade(double average);
void printReport(string name, int *math, int *physics, int *english);

int main() {
    string studentName;
    int mathMark;
    int physicsMark;
    int englishMark;
    int choice;

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    inputMarks(&mathMark, &physicsMark, &englishMark);
    
    printReport(studentName, &mathMark, &physicsMark, &englishMark);

    do {
        cout << "\nMenu Options:\n";
        cout << "1. Update Math mark\n";
        cout << "2. Update Physics mark\n";
        cout << "3. Update English mark\n";
        cout << "4. Print Report\n";
        cout << "5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter new Math mark: ";
            cin >> mathMark;
        } else if (choice == 2) {
            cout << "Enter new Physics mark: ";
            cin >> physicsMark;
        } else if (choice == 3) {
            cout << "Enter new English mark: ";
            cin >> englishMark;
        } else if (choice == 4) {
            printReport(studentName, &mathMark, &physicsMark, &englishMark);
        } else if (choice == 5) {
            cout << "Exiting system...\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void inputMarks(int *math, int *physics, int *english) {
    cout << "Enter Math mark: ";
    cin >> *math;
    cout << "Enter Physics mark: ";
    cin >> *physics;
    cout << "Enter English mark: ";
    cin >> *english;
}

double calculateAverage(int *math, int *physics, int *english) {
    double sum = *math + *physics + *english;
    return sum / 3.0; 
}

char calculateGrade(double average) {
    if (average >= 90) {
        return 'A';
    } else if (average >= 80) {
        return 'B';
    } else if (average >= 70) {
        return 'C';
    } else if (average >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

void printReport(string name, int *math, int *physics, int *english) {
    double average = calculateAverage(math, physics, english);
    char grade = calculateGrade(average);

    cout << "\n========================\n";
    cout << "Student: " << name << "\n";
    cout << "Math: " << *math << "\n";
    cout << "Physics: " << *physics << "\n";
    cout << "English: " << *english << "\n";
    cout << "Average: " << average << "\n";
    cout << "Grade: " << grade << "\n";
    cout << "========================\n";
}
