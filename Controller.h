#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "BankAPI.h"
#include <string>
#include <fstream>

enum class CardState { HASCARD, NOCARD };

enum class AccountState { CHECKING, SAVINGS };

class Controller {

    CardState cardState;
    AccountState accountState;
    BankAPI database;
    std::string currentCardNumber;

public:

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

    // returns updated balance after processing the amount given
    int update(int amount);
    
    // return selected account's new balance after processing withdraw
    int withdraw(int amount);
    
    // return selected account's newe balance after processing deposit
    int deposit(int amount);
    
    // Sets CardState of controller to NOCARD
    void eject();

};

#endif
