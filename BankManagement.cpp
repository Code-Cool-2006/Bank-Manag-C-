#include <iostream>
#include <string>
using namespace std;

// Class representing a single Account
class Account {
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;

public:
    // Default Constructor
    Account() {
        accountNumber = 0;
        balance = 0.0;
    }

    // Parameterized Constructor
    Account(long accNum, string first, string last, float bal) {
        accountNumber = accNum;
        firstName = first;
        lastName = last;
        balance = bal;
    }

    // Getters
    long getAccountNumber() const { return accountNumber; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    float getBalance() const { return balance; }

    // Setters
    void setFirstName(string first) { firstName = first; }
    void setLastName(string last) { lastName = last; }

    // Operations
    void deposit(float amount) {
        balance += amount;
    }

    void withdraw(float amount) {
        balance -= amount;
    }

    void showAccount() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Balance: " << balance << endl;
        cout << "-------------------------" << endl;
    }
};

// Class to manage the collection of Accounts
class Bank {
private:
    Account* accounts; // Pointer to array of Account objects
    int totalAccounts; // Keeps track of how many accounts exist

public:
    // Constructor: Initialize empty bank
    Bank() {
        accounts = nullptr;
        totalAccounts = 0;
    }

    // Destructor: Clean up dynamic memory when Bank object is destroyed
    ~Bank() {
        if (accounts != nullptr) {
            delete[] accounts;
            accounts = nullptr;
        }
        cout << "Memory cleaned up successfully." << endl;
    }

    // Dynamic Entry: Manually resize array to add new account
    void openAccount() {
        long accNum;
        string first, last;
        float bal;

        cout << "Enter Account Number: ";
        cin >> accNum;

        // Check for duplicate
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                cout << "Account already exists!" << endl;
                return;
            }
        }

        cout << "Enter First Name: ";
        cin >> first;
        cout << "Enter Last Name: ";
        cin >> last;
        cout << "Enter Initial Balance: ";
        cin >> bal;

        // 1. Create temporary array of size + 1
        Account* newArray = new Account[totalAccounts + 1];

        // 2. Copy old data to new array
        for (int i = 0; i < totalAccounts; i++) {
            newArray[i] = accounts[i];
        }

        // 3. Add new account to the end
        newArray[totalAccounts] = Account(accNum, first, last, bal);

        // 4. Delete old array memory
        if (accounts != nullptr) {
            delete[] accounts;
        }

        // 5. Point accounts to the new array
        accounts = newArray;
        totalAccounts++;

        cout << "Account Created Successfully!" << endl;
    }

    void showAllAccounts() {
        if (totalAccounts == 0) {
            cout << "No accounts found." << endl;
            return;
        }
        for (int i = 0; i < totalAccounts; i++) {
            accounts[i].showAccount();
        }
    }

    void searchAccount(long accNum) {
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                cout << "Account Found:" << endl;
                accounts[i].showAccount();
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void deposit(long accNum, float amount) {
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                accounts[i].deposit(amount);
                cout << "Deposited. New Balance: " << accounts[i].getBalance() << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void withdraw(long accNum, float amount) {
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                if (accounts[i].getBalance() >= amount) {
                    accounts[i].withdraw(amount);
                    cout << "Withdrawn. New Balance: " << accounts[i].getBalance() << endl;
                } else {
                    cout << "Insufficient Balance!" << endl;
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }



    // Dynamic Deletion: Resize array to remove an item
    void deleteAccount(long accNum) {
        int index = -1;
        // Find the index
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Account not found." << endl;
            return;
        }

        // 1. Create new array of size - 1
        Account* newArray = new Account[totalAccounts - 1];

        // 2. Copy everything EXCEPT the one to delete
        int j = 0;
        for (int i = 0; i < totalAccounts; i++) {
            if (i != index) {
                newArray[j] = accounts[i];
                j++;
            }
        }

        // 3. Delete old array
        delete[] accounts;

        // 4. Update pointer and count
        accounts = newArray;
        totalAccounts--;

        cout << "Account Deleted Successfully!" << endl;
    }
};

int main() {
    Bank bank;
    int choice;
    long accNum;
    float amount;

    do {
        cout << "\n*** Banking Management System ***" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Show All" << endl;
        cout << "3. Search" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Withdraw" << endl;
        cout << "6. Delete" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.openAccount(); break;
            case 2: bank.showAllAccounts(); break;
            case 3: 
                cout << "Enter Account No: "; cin >> accNum;
                bank.searchAccount(accNum); 
                break;
            case 4: 
                cout << "Enter Account No: "; cin >> accNum;
                cout << "Amount: "; cin >> amount;
                bank.deposit(accNum, amount); 
                break;
            case 5: 
                cout << "Enter Account No: "; cin >> accNum;
                cout << "Amount: "; cin >> amount;
                bank.withdraw(accNum, amount); 
                break;
            case 6: 
                cout << "Enter Account No: "; cin >> accNum;
                bank.deleteAccount(accNum); 
                break;
            case 7: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 7);

     return 0;
}