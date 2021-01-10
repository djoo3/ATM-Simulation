#include "Card.h"
#include "BankAPI.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <limits.h>

bool BankAPI::loadData(std::ifstream& inputFile) {
	std::string cardNumber = "";
	std::string pinNumber = "";
	int CARD_NUMBER_LENGTH = 0;
	int PIN_NUMBER_LENGTH = 0;
	int checkingBalance = 0;
	int savingsBalance = 0;
	
	// set the length of card number and pin number according to the input file
	if (!(infile >> CARD_NUMBER_LENGTH >> PIN_NUMBER_LENGTH)) return false;
	
	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		
		if (!(line >> cardNumber >> pinNumber >> checkingBalance >> savingsBalance)) return false;
		
		// check that the card number input follows the card number format
		if (cardNumber.length() == CARD_NUMBER_LENGTH) {
			for (char& c : cardNumber)
				if (c >= '9' || c <= '0') return false;
		} else {
			return false;
		}
		
		// check that the pin number input follows the pin number format
		if (pinNumber.length() == PIN_NUMBER_LENGTH) {
			for (char& c : pinNumber)
				if (c >= '9' || c <= '0') return false;
		} else {
			return false;
		}
		
		Card card(cardNumber, pinNumber, checkingBalance, savingsBalance);
		
		cardData.insert({cardNumber, card});
	}
	
	return true;
}
	
bool BankAPI::checkCard(std::string cardNumber, std::string pin) {

	// check validity of card number
	if (cardData.find(cardNumber) == cardData.end()) return false;
  
	// check validity of pin number
	Card *c = cardData.find(cardNumber);
	return c -> validate(pin);
}
	
int BankAPI::getBalance(std::string cardNumber, int code) {
	Card *c = cardData.find(cardNumber);
	switch (code) {
		case CHECKING:
			return c -> getCheckingBalance();
		case SAVINGS:
			return c -> getSavingsBalance();
	}
	return INT_MIN;
}
  
int BankAPI::setAndGetBalance(std::string cardNumber, int code);
	Card *c = cardData.find(cardNumber);
	switch (code) {
		case CHECKING:
			return c -> setAndGetCheckingBalance();
		case SAVINGS:
			return c -> setAndGetSavingsBalance();
	}
	return INT_MIN;
};
