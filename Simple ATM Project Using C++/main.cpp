#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iomanip>  // For setw()

using namespace std;

class BankAccount {
public:
    string fullName;
    string fatherName;
    string nic;
    string phoneNumber;
    string accountNumber;
    string pin;
    double balance;

    // Constructor to initialize the account
    BankAccount() {
        accountNumber = "";
        pin = "";
        balance = 0.0;
    }

    // Function to generate a unique 7-digit account number
    string generateAccountNumber() {
        string accNum;
        do {
            accNum = to_string(rand() % 10000000);  // Generate a random 7-digit number
            while (accNum.length() < 7) {
                accNum = "0" + accNum; // Ensure it's 7 digits
            }
        } while (accNum.length() != 7); // Ensure it's exactly 7 digits
        return accNum;
    }

    // Function to create an account and save to Data.txt
    void createAccount() {
        system("cls");
        printHeader("Create Account");

        cout << setw(50) << "Enter your Full Name: ";
        cin.ignore(); // To ignore the newline character left in the input buffer
        getline(cin, fullName);
        cout << setw(50) << "Enter your Father's Name: ";
        getline(cin, fatherName);
        cout << setw(50) << "Enter your NIC: ";
        getline(cin, nic);
        cout << setw(50) << "Enter your Phone Number: ";
        getline(cin, phoneNumber);

        // Generate a unique account number
        accountNumber = generateAccountNumber();

        cout << setw(50) << "Your generated Account Number is: " << accountNumber << " (Note: Remember this number!)" << endl;

        cout << setw(50) << "Enter your PIN: ";
        cin >> pin;
        cout << setw(50) << "Enter Initial Deposit: ";
        cin >> balance;

        // Save account details to Data.txt
        ofstream outFile("Data.txt", ios::app);  // Append to the file
        if (outFile.is_open()) {
            outFile << "Full Name: " << fullName << endl;
            outFile << "Father's Name: " << fatherName << endl;
            outFile << "NIC: " << nic << endl;
            outFile << "Phone Number: " << phoneNumber << endl;
            outFile << "Account Number: " << accountNumber << endl;
            outFile << "PIN: " << pin << endl;
            outFile << "Initial Deposit: " << balance << endl;
            outFile << "-------------------------" << endl;
            outFile.close();
            cout << setw(50) << "Account created successfully! Data saved to Data.txt." << endl;
        } else {
            cout << setw(50) << "Error opening file." << endl;
        }
    }

    // Function to check the balance
    void checkBalance(const string& inputAccNum, const string& inputPin) {
        system("cls");
        printHeader("Check Balance");

        if (inputAccNum == accountNumber && inputPin == pin) {
            cout << setw(50) << "Your balance is: " << balance << endl;
        } else {
            cout << setw(50) << "Invalid account number or PIN." << endl;
        }
    }

    // Function to deposit money
    void deposit(double amount, const string& inputAccNum, const string& inputPin) {
        system("cls");
        printHeader("Deposit Money");

        if (inputAccNum == accountNumber && inputPin == pin) {
            balance += amount;
            cout << setw(50) << "Deposit successful! New balance: " << balance << endl;
        } else {
            cout << setw(50) << "Invalid account number or PIN." << endl;
        }
    }

    // Function to withdraw money
    void withdraw(double amount, const string& inputAccNum, const string& inputPin) {
        system("cls");
        printHeader("Withdraw Money");

        if (inputAccNum == accountNumber && inputPin == pin) {
            if (amount <= balance) {
                balance -= amount;
                cout << setw(50) << "Withdrawal successful! New balance: " << balance << endl;
            } else {
                cout << setw(50) << "Insufficient balance!" << endl;
            }
        } else {
            cout << setw(50) << "Invalid account number or PIN." << endl;
        }
    }

    // Function to delete the account
    bool deleteAccount(const string& inputAccNum, const string& inputPin) {
        system("cls");
        printHeader("Delete Account");

        if (inputAccNum == accountNumber && inputPin == pin) {
            // Resetting account details to simulate deletion
            accountNumber = "";
            pin = "";
            balance = 0;
            cout << setw(50) << "Account deleted successfully!" << endl;
            return true;
        } else {
            cout << setw(50) << "Invalid account number or PIN." << endl;
            return false;
        }
    }

    // Function to print a centered header
    void printHeader(const string& title) {
        cout << string(50, '=') << endl;
        cout << setw(40) << title << endl;
        cout << string(50, '=') << endl;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    BankAccount account;  // Initialize an empty account
    int choice;

    do {
        system("cls");
        cout << string(50, '=') << endl;
        cout << setw(40) << "--- ATM Menu ---" << endl;
        cout << string(50, '=') << endl;
        cout << setw(40) << "1. Create Account" << endl;
        cout << setw(40) << "2. Check Balance" << endl;
        cout << setw(40) << "3. Deposit Money" << endl;
        cout << setw(40) << "4. Withdraw Money" << endl;
        cout << setw(40) << "5. Delete Account" << endl;
        cout << setw(40) << "6. Exit" << endl;
        cout << string(50, '=') << endl;
        cout << setw(40) << "Enter your choice: ";
        cin >> choice;

        string inputAccNum, inputPin;

        switch (choice) {
            case 1:
                account.createAccount();
                break;

            case 2:
                cout << setw(50) << "Enter your account number: ";
                cin >> inputAccNum;
                cout << setw(50) << "Enter your PIN: ";
                cin >> inputPin;
                account.checkBalance(inputAccNum, inputPin);
                break;

            case 3:
                {
                    double depositAmount;
                    cout << setw(50) << "Enter your account number: ";
                    cin >> inputAccNum;
                    cout << setw(50) << "Enter your PIN: ";
                    cin >> inputPin;
                    cout << setw(50) << "Enter amount to deposit: ";
                    cin >> depositAmount;
                    account.deposit(depositAmount, inputAccNum, inputPin);
                }
                break;

            case 4:
                {
                    double withdrawAmount;
                    cout << setw(50) << "Enter your account number: ";
                    cin >> inputAccNum;
                    cout << setw(50) << "Enter your PIN: ";
                    cin >> inputPin;
                    cout << setw(50) << "Enter amount to withdraw: ";
                    cin >> withdrawAmount;
                    account.withdraw(withdrawAmount, inputAccNum, inputPin);
                }
                break;

            case 5:
                cout << setw(50) << "Enter your account number: ";
                cin >> inputAccNum;
                cout << setw(50) << "Enter your PIN: ";
                cin >> inputPin;
                account.deleteAccount(inputAccNum, inputPin);
                break;

            case 6:
                system("cls");
                cout << string(50, '=') << endl;
                cout << setw(40) << "Thank you for using the ATM!" << endl;
                cout << string(50, '=') << endl;
                break;

            default:
                cout << setw(50) << "Invalid choice. Please select again." << endl;
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 6);

    return 0;
}
