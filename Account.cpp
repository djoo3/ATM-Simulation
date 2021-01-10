#include "Account.h"

Account::Account(int bal) : balance(bal) {}
	
void Account::changeUpdateState() {
    beingUpdated = beingUpdated ? false : true;
}
	
bool Account::available() {
    return !beingUpdated;
}
	
int Account::getBalance() {
    return balance;
}
	
void Account::setBalance(int change) {
    balance += change;
}
