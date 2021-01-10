#include "Card.h"
#include "Account.h"

#include <string>
#include <limits.h>

Card::Card(std::string cardNumber_, std::string pin_, int checkingBal, int savingsBal) :
    cardNumber(cardNumber_), pin(pin_), checking(checkingBal), savings(savingsBal) {}
	
bool Card::validate(std::string pinAttempt) {
    return pinAttempt == pin;
}
	
int Card::getCheckingBalance() {
    int bal = INT_MIN;
    if (checking.available()) {
        checking.changeUpdateState();
        bal = checking.getBalance();
        checking.changeUpdateState();
    }
    return bal;
}
	
int Card::getSavingsBalance() {
    int bal = INT_MIN;
    if (savings.available()) {
        savings.changeUpdateState();
        bal = savings.getBalance();
        savings.changeUpdateState();
    }
    return bal;
}
	
int Card::setAndGetCheckingBalance(int change) {
    int bal = INT_MIN;
    if (checking.available()) {
        checking.changeUpdateState();
        checking.setBalance(change);
        bal = checking.getBalance();
        checking.changeUpdateState();
    }
    return bal;
}
	
int Card::setAndGetSavingsBalance(int change) {
    int bal = INT_MIN;
    if (savings.available()) {
        savings.changeUpdateState();
        savings.setBalance(change);
        bal = savings.getBalance();
        savings.changeUpdateState();
    }
    return bal;
}
