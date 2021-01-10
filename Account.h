#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
	
	bool beingUpdated = false;
	int balance = 0;
	
public:
	
	Account(int bal);
	
	void changeUpdateState();
	
	bool available();
	
	int getBalance();
	
	void setBalance(int change);
	
};

#endif
