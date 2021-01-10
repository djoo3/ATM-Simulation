#include "Card.h"
#include "BankAPI.h"
#include <fstream>
#include <sstream>
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
	if (!(inputFile >> CARD_NUMBER_LENGTH >> PIN_NUMBER_LENGTH)) return false;
	
	std::string line;
	while (std::getline(inputFile, line)) {
		std::istringstream iss (line);
		
		if (!(iss >> cardNumber >> pinNumber >> checkingBalance >> savingsBalance)) return false;
		
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
		
		Card *card = new Card(cardNumber, pinNumber, checkingBalance, savingsBalance);
		
		cardData.insert({cardNumber, card});
	}
	
	return true;
}
	
bool BankAPI::checkCard(std::string cardNumber, std::string pin) {

	// check validity of card number
	if (cardData.find(cardNumber) == cardData.end()) return false;
  
	// check validity of pin number
	return cardData[cardNumber] -> validate(pin);
}
	
int BankAPI::getBalance(std::string cardNumber, int code) {
	switch (code) {
		case 1:
			return cardData[cardNumber] -> getCheckingBalance();
		case 2:
			return cardData[cardNumber] -> getSavingsBalance();
	}
	return INT_MIN;
}
  
int BankAPI::setAndGetBalance(std::string cardNumber, int amount, int code) {
	switch (code) {
		case 1:
			return cardData[cardNumber] -> setAndGetCheckingBalance(amount);
		case 2:
			return cardData[cardNumber] -> setAndGetSavingsBalance(amount);
	}
	return INT_MIN;
}
