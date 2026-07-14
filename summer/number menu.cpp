#include <iostream>

using namespace std;

void increment(int *num);
void decrement(int *num);
void reset(int *num);
void printNumber(int *num);

int main() {
    int number;
    int choice;

    cout << "Enter number: ";
    cin >> number;

    do {
        cout << "\n1. Increment\n2. Decrement\n3. Reset to 0\n4. Show Number\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            increment(&number);
            printNumber(&number);
        } else if (choice == 2) {
            decrement(&number);
            printNumber(&number);
        } else if (choice == 3) {
            reset(&number);
            printNumber(&number);
        } else if (choice == 4) {
            printNumber(&number);
        } else if (choice == 5) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void increment(int *num) {
    *num = *num + 1;
}

void decrement(int *num) {
    *num = *num - 1;
}

void reset(int *num) {
    *num = 0;
}

void printNumber(int *num) {
    cout << "Current Number = " << *num << "\n";
}
