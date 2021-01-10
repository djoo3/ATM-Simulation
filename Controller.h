#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "BankAPI.h"
#include <string>
#include <limits.h>

enum class CardState { HASCARD, NOCARD };

enum class AccountState { CHECKING, SAVINGS };

class Controller {

    int serial;
    CardState cardState;
    AccountState accountState;
    BankAPI database;

public:

    Controller(int n) : serial(n) {}

    // load information into database
    bool loadBankInformation(std::ifstream& inputFile);

    // returns true if no card is currently being processed; cardState == CardState::NOCARD
    bool atmAvailable();
    
    // returns true if card number and pin number are valid, and sets CardState of controller to HASCARD
    bool checkCardValid(std::string cardNumber, std::string pinNumber);
    
    // returns false if type is invalid, otherwise sets AccountState of controller to the type indicated and returns true
    bool selectAccount(std::string type);
    
    // returns selected account's balance
    int seeBalance();
    
    // return selected account's new balance after processing withdraw
    int withdraw(int amount);
    
    // return selected account's newe balance after processing deposit
    int deposit(int amount);
    
    // Sets CardState of contrtoller to NOCARD
    void eject();

};

#endif
