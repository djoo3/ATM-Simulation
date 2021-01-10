#ifndef CARD_H
#define CARD_H

#include "Account.h"
#include <string>

class Card {

	std::string cardNumber;
	std::string pin;
	Account checking;
	Account savings;
	
public:
	
	Card(std::string cardNumber_, std::string pin_, int checkingBal, int savingsBal);
	
	bool validate(std::string pinAttempt);
	
	int getCheckingBalance();
	
	int getSavingsBalance();
	
	int setAndGetCheckingBalance(int change);
	
	int setAndGetSavingsBalance(int change);

};

#endif
