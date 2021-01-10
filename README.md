# ATM SIMULATION PROJECT SPECS

## Summary

This is a conceptual project representing how an ATM Controller may work, but without any API integrations or other external plugins.
The code will only cover basic ATM functions as follows:

*1. Process Card Information*
  - Change state of ATM to being used when card is inserted
  - Verify that card number exists and the PIN number is valid
  
*2. Select Account*
  - Select one of the following accounts associated with the card: **Checking Account**, **Savings Account**
  
*3. Select Action*
  - Select one of the following actions for the account selected: **See Balance**, **Withdraw**, **Deposit**

*4. Commit Action*
  - Run the action selected
  - Commit to the simulated bank database
  
*5. Finish*
  - Display changes to balance due to the action run
  - Eject card, change state of ATM as being unused
  
## Things to Note

- Bank APIs will be simulated using local data structures and class objects (for testing)
- **This project was made on a virtual machine which cannot download online files. Therefore this project cannot and has not been tested**

## Files

##### atm.cpp
- THIS IS THE MAIN; RUN THIS FILE TO RUN THE PROJECT
- Takes in file to load bank data into the bankAPI simulator, which is needed to test the code
- Takes in user input commands
- Runs functions in respect to user input

##### controller.h & controller.cpp
- Holds the current states of the ATM machine
  - CardState: YesCard, NoCard
  - AccountState: Checking, Savings
- Implements the following functions:
  - checkCardValid(cardNumber, PIN)
  - selectAccount(accountValue)
  - seeBalance()
  - withdraw(amount)
  - deposit(amount)
  - displayChanges()
  - eject()

##### bankApi.h & bankAPI.cpp
- Stores card numbers and their associated PIN numbers
  - While card information should be hashed and dynamically [salted](https://en.wikipedia.org/wiki/Salt_(cryptography)) for security, this has been omitted for simplicity
  - Each card is associated with a checking and savings account
- Implements the following functions:
  - loadData(inputfile)
  - checkCard(cardNumber, PIN)
  - pullAccount(cardNumber, accountValue)
  
##### Card.h & Card.cpp
- Implements Card class, which has the following data:
  - Card Number
  - PIN Number
  - Checking Account
  - Savings Account
- Implements setter and getter functions for the member variables

##### Account.h & Account.cpp
- Implements Account class, which has the following data:
  - beingUpdatedFlag (to make sure only one user accesses the account at a time)
  - Balance
- Implements setter and getter functions for the member variables

