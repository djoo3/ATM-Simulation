#include "Controller.h"
#include "BankAPI.h"

#include <fstream>
#include <string>
#include <limits.h>

Controller::Controller() {}

bool Controller::loadBankInformation(std::ifstream& inputFile) {
    return database.loadData(inputFile);    
}

bool Controller::atmAvailable() {
    return (cardState == CardState::NOCARD);
}

bool Controller::checkCardValid(std::string cardNumber, std::string pinNumber) {
    if (database.checkCard(cardNumber, pinNumber)) {
        cardState = CardState::HASCARD;
        currentCardNumber = cardNumber;
        return true;
    }
    return false;
}

bool Controller::selectAccount(std::string type) {
    if (type == "1") {
        accountState = AccountState::CHECKING;
        return true;
    } else if (type == "2") {
        accountState = AccountState::SAVINGS;
        return true;
    }
    return false;
}

int Controller::seeBalance() {
    switch (accountState) {
        case AccountState::CHECKING:
            return database.getBalance(currentCardNumber, 1);
        case AccountState::SAVINGS:
            return database.getBalance(currentCardNumber, 2);
    }
    return INT_MIN;
}

int Controller::update(int amount) {
    switch (accountState) {
        case AccountState::CHECKING:
            return database.setAndGetBalance(currentCardNumber, amount, 1);
        case AccountState::SAVINGS:
            return database.setAndGetBalance(currentCardNumber, amount, 2);
    }
    return INT_MIN;
}

int Controller::withdraw(int amount) {
    amount *= -1;
    update(amount);
}
    
int Controller::deposit(int amount) {
    update(amount);
}

void Controller::eject() {
    currentCardNumber = "";
    cardState = CardState::NOCARD;
}
