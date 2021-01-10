#include "Controller.h"
#include <string>
#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

class ATMObject { 
    
    Controller ctrl;
    int attemptLimit = INT_MAX;
    bool dataImported = false;
    
    // HELPER: converts string value to int if it's a valid number
    int stringToInt(string s) {
        if (s.empty()) return INT_MIN;
        int num = 0;
        int multiplier = 1;
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] >= '0' && s[i] <= '9') {
                num += (s[i] - '0') * multiplier;
                multiplier *= 10;
            } else {
                return INT_MIN;
            }
        }
        return num;
    }
            

public:

    ATMObject() {}
    
    // Quit application
    void terminate() {
        cout << "\n\nTHANK YOU FOR USING NATIONAL BEAR BANK, HAVE A GREAT REST OF YOUR DAY!" << "\n";
        exit (EXIT_SUCCESS);
    }
    
    // Checks if bank data has been imported into the virtual ATM
    bool importedData() {
        return dataImported;
    }

    // Checks if ATM is currently processing a card
    bool isAvailable() {
        return ctrl.atmAvailable();
    }
    
    // First thing the virtual ATM prints upon successful compilation
    void printWelcome() {
        cout << "WELCOME TO THE NATIONAL BEAR BANK!" << "\n\n";
        cout << "If at any point you would like to terminate the program, please press \"q\" on your keyboard." << "\n\n";
        cout << "Before we get started, let's start with importing data from the bank." << "\n";
        cout << "Before importing the text file, please double check the formatting of the input file:" << "\n";
        cout << "\t- The first line should compose of two numbers separated by a space: the first the length of card numbers, the second the length of pin numbers" << "\n";
        cout << "\t- The number of digits for both the card numbers and the pin numbers should not be less than 1" << "\n";
        cout << "\t- All lines after the first should detail the following information separated by a space in the following order: card number, pin number, checking account balance, savins account balance" << "\n";
        cout << "Any deviations from the above guidelines will result in failure to run, or weird outputs. PLEASE DOUBLE CHECK YOUR FORMATTING!" << "\n\n";
    }
    
    // Takes user input file name and imports bank data from that file, into the virtual ATM
    // If the ATM already has a file that has been imported into the BankAPI, it will override the existing data with the new file
    bool importData() {
        cout << "Please write the name of the data file you would like to import below (e.g. testfile1.txt):" << "\n";
    
        string filename;
        cin >> filename;
    
        if (filename == "q") terminate();
    
        cout << "\n\nImporting data..." << "\n\n";
    
        ifstream dataFile(filename);
        if (dataFile.is_open()) {
            if (ctrl.loadBankInformation(dataFile)) {
                dataImported = true;
                cout << "And we have all the data ready to go!" << "\n\n";
                dataFile.close();
                return true;
            } else {
                cout << "Oh no! The input file had incorrect formatting. Please check your formatting and try again!" << "\n\n";
                dataFile.close();
                return false;
            }
        }
        
        cout << "Oh no! The file that you are attempting to import cannot be found. Please check your directory path and filename and try again!" << "\n\n";
        return false;
    }
    
    // Set the number of times a user is able to guess their card number and/or PIN number before the application shuts down
    void setAttemptLimit() {
        string numAttempt = 0;
        cout << "SECURITY: How many times would you like the user to be able to guess their card number and/or PIN before shutting machine down?" << "\n";
        while (cin >> numAttempt) {
            if (numAttempt == "q") terminate();
            int numLimit = stringToInt(numAttempt);
            if (numLimit == INT_MIN) {
                cout << "\nINVALID INPUT, please write a positive integer value: " << "\n";
                continue;
            } else {
                attemptLimit = numLimit;
                cout << "\nMaximum number of attempts has been confirmed" << "\n\n";
                return;
            }
        }
    }
    
    // Process the card number and PIN number inputted by user
    // If the user guesses wrong <attemptLimit> times, we go back to printWelcome
    void processCard(string& cardNumber, string& pinNumber) {
        bool success = false;
        
        int numberOfAttempts = 0;
        
        while (!success) {
            cout << "YOU HAVE " << (attemptLimit - numberOfAttempts) << " ATTEMPTS REMAINING" << "\n";
            
            cout << "Please write card number below (no spaces): " << "\n";
            cin >> cardNumber;
            if (cardNumber == "q") terminate();
            
            cout << "\nPlease write pin number below (no spaces): " << "\n";
            cin >> pinNumber;
            if (pinNumber == "q") terminate();
            
            success = ctrl.checkCardValid(cardNumber, pinNumber);
            if (success) break;
            
            numberOfAttempts += 1;
            if (numberOfAttempts > attemptLimit) {
                cout << "\nWe suspect that you are trying to do something illegal... shutting down" << "\n";
                exit (EXIT_SUCCESS);
            }
            
            if (!success) cout << "\nInvalid card number or PIN, try again." << "\n\n";
        }
    }
    
    // Prompt user to select account: either checking or savings
    // If input invalid, prompt user again
    void selectAccount() {
        cout << "SELECT ACCOUNT: \nPress \"1\" for CHECKING\nPress \"2\" for SAVINGS" << "\n";
        string accountType;
        while (cin >> accountType) {
            if (accountType == "q") terminate();
            if (accountType != "1" && accountType != "2") {
                cout << "\nINVALID INPUT: Press \"1\" for CHECKING, Press \"2\" for SAVINGS" << "\n";
            } else {
                ctrl.selectAccount(accountType);
                if (accountType == "1") cout << "\nCHECKING ACCOUNT SELECTED" << "\n\n";
                else if (accountType == "2") cout << "\nSAVINGS ACCOUNT SELECTED" << "\n\n";
                return;
            }
        }
    }
    
    // Prints current balance in selected account
    void seeBalance() {
        cout << "\nCURRENT BALANCE: " << ctrl.seeBalance() << "\n";
    }
    
    // Modifies balance of selected account, prints changes made
    // Withdrawal only performed if the the balance is greater than or equal to withdrawal amount specified by user
    void withdraw() {
        seeBalance();
        cout << "ENTER AMOUNT TO WITHDRAW: ";
        
        string val;
        while (cin >> val) {
            int amount = stringToInt(val);
            int balance = ctrl.seeBalance();
            if (amount == INT_MIN) {
                cout << "\nINVALID INPUT: please write a positive integer value: " << "\n";
                continue;
            } else if (amount > balance) {
                cout << "\nENTER AMOUNT LESS THAN OR EQUAL TO CURRENT BALANCE: ";
                continue;
            } else {
                ctrl.withdraw(amount);
                cout << "\nWITHDREW: " << amount;
                seeBalance();
                break;
            }
        }
    }
    
    // Modifies balance of selected account, prints changes made
    void deposit() {
        cout << "\nENTER AMOUNT TO DEPOSIT: ";
        
        string val;
        while (cin >> val) {
            int amount = stringToInt(val);
            int balance = ctrl.seeBalance();
            if (amount == INT_MIN) {
                cout << "\nINVALID INPUT: please write a positive integer value: " << "\n";
                continue;
            } else {
                ctrl.deposit(amount);
                cout << "\nDEPOSITED: " << amount;
                seeBalance();
                break;
            }
        }
    }
    
    // Prompt user to perform one of the following: see balance, withdraw, or deposit
    bool selectAndRunAction() {
        cout << "SELECT ONE OF THE FOLLOWING ACTIONS: " << "\n";
        cout << "Press \"1\" to SEE BALANCE\nPress \"2\" to WITHDRAW\nPress \"3\" to DEPOSIT\nPress \"q\" to quit program" << "\n";
        
        char selection;
        while(cin >> selection) {
            switch (selection) {
                case 'q':
                    terminate();
                case '1':
                    seeBalance();
                    return true;
                case '2':
                    withdraw();
                    return true;
                case '3':
                    deposit();
                    return true;
                default:
                    cout << "\nINVALID INPUT: Press \"1\" to SEE BALANCE, Press \"2\" to WITHDRAW, Press \"3\" to DEPOSIT, Press \"q\" to quit program" << "\n";
            }
        }
        cout << "\nINVALID INPUT: ";
        return false;
    }
    
    // Finish up the program, if prompted by user, then reset atm data
    bool finish(bool resetData) {
        cout << "If you would like to finish, please press \"1\"" << "\n";
        cout << "If you would like to make another transaction, please press \"2\"" << "\n";
        cout << "If you would like to reset the atm, please press \"3\"" << "\n";
        char selection;
        while(cin >> selection) {
            switch (selection) {
                case 'q':
                    terminate();
                case '1':
                    cout << "\nThank you for using The National Bear Bank!" << "\n";
                    return true;
                case '2':
                    while (!selectAndRunAction()) continue;
                    return true;
                case '3':
                    cout << "\nThank you for using The National Bear Bank! (RESET OPTION)" << "\n";
                    resetData = true;
                    return true;
                default:
                    cout << "\nINVALID INPUT: Press \"1\" to FINISH, Press \"2\" to MAKE ANOTHER TRANSACTION, Press \"3\" to RESET ATM, Press \"q\" to quit program" << "\n";
            }
        }
        cout << "\nINVALID INPUT: ";
        return false;
    }
    
};


int main() {

    ios_base::sync_with_stdio(false);

    ATMObject atm;
    string cardNumber = "";
    string pinNumber = "";
    bool resetData = true;
    
    while (1) {
        atm.printWelcome();
        
        // breaks when resetData == false
        while (resetData) resetData = !atm.importData();
        
        atm.setAttemptLimit();
        
        // while there is no card being processed and no call for ATM reset
        while(atm.isAvailable() && !resetData) {
            
            // process and validate card number and PIN; if user doesn't seem to know the card number and PIN number combination, shut down the application
            atm.processCard(cardNumber, pinNumber);
            
            // select checking or savings account for this transaction
            atm.selectAccount();
            
            // select one of the following actions to perform: see balance, withdraw, or deposit
            while (!atm.selectAndRunAction()) continue;

            // select one of the following actions to perform: finish, perform another transaction on this account, or finish and reset ATM data
            while (!atm.finish(resetData)) continue;
            
        }
        
    }
    
}
