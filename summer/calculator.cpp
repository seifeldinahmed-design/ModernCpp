#include <iostream>

using namespace std;

int main() {
    int num1, num2;
    char op;

    cout << " C++ Calculator App \n";
   
    // Get user input
    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter operator (+, -, *, /, %): ";
    cin >> op;

    cout << "Enter second number: ";
    cin >> num2;

    switch (op) {
        case '+':
            cout << "Result: " << num1 << " + " << num2 << " = " << (num1 + num2) << "\n";
            break;
        case '-':
            cout << "Result: " << num1 << " - " << num2 << " = " << (num1 - num2) << "\n";
            break;
        case '*':
            cout << "Result: " << num1 << " * " << num2 << " = " << (num1 * num2) << "\n";
            break;
        case '/':
            if (num2 == 0) {
                cout << "Error: Division by zero is undefined.\n";
            } else {
                // Cast to double for precise floating-point division
                cout << "Result: " << num1 << " / " << num2 << " = " << (static_cast<double>(num1) / num2) << "\n";
            }
            break;
        case '%':
            if (num2 == 0) {
                cout << "Error: Modulo by zero is undefined.\n";
            } else {
                cout << "Result: " << num1 << " % " << num2 << " = " << (num1 % num2) << "\n";
            }
            break;
        default:
            cout << "Error: Invalid operator. Please use +, -, *, /, or %.\n";
            break;
    }

    return 0;
}
