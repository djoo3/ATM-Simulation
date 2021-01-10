#ifndef BANKAPI_H
#define BANKAPI_H

#include "Card.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <limits.h>

class BankAPI {
	
	std::unordered_map<std::string, Card> cardData;
	int CHECKING = 1;
	int SAVINGS = 2;
	
public:

	bool loadData(std::ifstream& inputFile);
	
	bool checkCard(std::string cardNumber, std::string pin);
	
	int getBalance(std::string cardNumber, int code);
  
  	int setAndGetBalance(std::string cardNumber, int code);
	
};

#endif
