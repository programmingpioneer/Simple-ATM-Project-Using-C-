#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

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
        cout << "Enter your Full Name: ";
        cin.ignore(); // To ignore the newline character left in the input buffer
        getline(cin, fullName);
        cout << "Enter your Father's Name: ";
        getline(cin, fatherName);
        cout << "Enter your NIC: ";
        getline(cin, nic);
        cout << "Enter your Phone Number: ";
        getline(cin, phoneNumber);

        // Generate a unique account number
        accountNumber = generateAccountNumber();

        cout << "Your generated Account Number is: " << accountNumber << " (Note: Remember this number!)" << endl;

        cout << "Enter your PIN: ";
        cin >> pin;
        cout << "Enter Initial Deposit: ";
        cin >> balance;

        // Save account details to Data.txt
        ofstream outFile("Data.txt", ios::app);  // Append to the file
        if (outFile.is_open()) {
            outFile << "// Output The Data.txt File" << endl;
            outFile << "Full Name: " << fullName << endl;
            outFile << "Father's Name: " << fatherName << endl;
            outFile << "NIC: " << nic << endl;
            outFile << "Phone Number: " << phoneNumber << endl;
            outFile << "Account Number: " << accountNumber << endl;
            outFile << "PIN: " << pin << endl;
            outFile << "Initial Deposit: " << balance << endl;
            outFile << "-------------------------" << endl;
            outFile.close();
            cout << "Account created successfully! Data saved to Data.txt." << endl;
        } else {
            cout << "Error opening file." << endl;
        }
    }

    // Function to check the balance
    void checkBalance(const string& inputAccNum, const string& inputPin) {
        if (inputAccNum == accountNumber && inputPin == pin) {
            cout << "Your balance is: " << balance << endl;
        } else {
            cout << "Invalid account number or PIN." << endl;
        }
    }

    // Function to deposit money
    void deposit(double amount, const string& inputAccNum, const string& inputPin) {
        if (inputAccNum == accountNumber && inputPin == pin) {
            balance += amount;
            cout << "Deposit successful! New balance: " << balance << endl;
        } else {
            cout << "Invalid account number or PIN." << endl;
        }
    }

    // Function to withdraw money
    void withdraw(double amount, const string& inputAccNum, const string& inputPin) {
        if (inputAccNum == accountNumber && inputPin == pin) {
            if (amount <= balance) {
                balance -= amount;
                cout << "Withdrawal successful! New balance: " << balance << endl;
            } else {
                cout << "Insufficient balance!" << endl;
            }
        } else {
            cout << "Invalid account number or PIN." << endl;
        }
    }

    // Function to delete the account
    bool deleteAccount(const string& inputAccNum, const string& inputPin) {
        if (inputAccNum == accountNumber && inputPin == pin) {
            // Resetting account details to simulate deletion
            accountNumber = "";
            pin = "";
            balance = 0;
            cout << "Account deleted successfully!" << endl;
            return true;
        } else {
            cout << "Invalid account number or PIN." << endl;
            return false;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    BankAccount account;  // Initialize an empty account
    int choice;

    do {
        cout << "--- ATM Menu ---" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Check Balance" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string inputAccNum, inputPin;

        switch (choice) {
            case 1:
                cout << "--- Create Account ---" << endl;
                account.createAccount();
                break;

            case 2:
                cout << "--- Check Balance ---" << endl;
                cout << "Enter your account number: ";
                cin >> inputAccNum;
                cout << "Enter your PIN: ";
                cin >> inputPin;
                account.checkBalance(inputAccNum, inputPin);
                break;

            case 3:
                {
                    double depositAmount;
                    cout << "--- Deposit Money ---" << endl;
                    cout << "Enter your account number: ";
                    cin >> inputAccNum;
                    cout << "Enter your PIN: ";
                    cin >> inputPin;
                    cout << "Enter amount to deposit: ";
                    cin >> depositAmount;
                    account.deposit(depositAmount, inputAccNum, inputPin);
                }
                break;

            case 4:
                {
                    double withdrawAmount;
                    cout << "--- Withdraw Money ---" << endl;
                    cout << "Enter your account number: ";
                    cin >> inputAccNum;
                    cout << "Enter your PIN: ";
                    cin >> inputPin;
                    cout << "Enter amount to withdraw: ";
                    cin >> withdrawAmount;
                    account.withdraw(withdrawAmount, inputAccNum, inputPin);
                }
                break;

            case 5:
                cout << "--- Delete Account ---" << endl;
                cout << "Enter your account number: ";
                cin >> inputAccNum;
                cout << "Enter your PIN: ";
                cin >> inputPin;
                account.deleteAccount(inputAccNum, inputPin);
                break;

            case 6:
                cout << "--- Exit Program ---" << endl;
                cout << "Thank you for using the ATM. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please select again." << endl;
        }
        cout << endl;

    } while (choice != 6);

    return 0;
}