# ATM SIMULATION PROJECT SPECS

## Summary

This is a conceptual project representing how an ATM Controller may work, but without any API integrations or other external plugins.
The code will only cover basic ATM functions as follows:

*Preprocessing*
  - Import card and account information from a formatted text file

*1. Process Card Information*
  - Change state of ATM to being used when card is inserted
  - Verify that the card number exists and the PIN number is valid
  
*2. Select Account*
  - Select one of the following accounts associated with the card: **Checking Account**, **Savings Account**
  
*3. Select Action*
  - Select one of the following actions for the account selected: **See Balance**, **Withdraw**, **Deposit**

*4. Commit Action*
  - Run the action selected
  - Commit to the simulated bank database
  
*5. Finish*
  - Display changes to balance due to the action run
  - Prompt user to make another transaction, finish, or finish and reset the ATM data
  - Eject card, change state of ATM as being unused
  
## Things to Note

- Bank API will be simulated using local data structures and class objects (for testing)
- Implements a security feature where the program automatically shuts down if the user inputs the wrong card number and/or PIN number multiple times
- The cash bin part of the ATM has not been simulated, so the atm has an infinite amount of cash
- Assumes that balances can be stored in int data type, therefor no multi billionaires allowed (integer overflow)
- Assumes that balances are not allowed to go negative, so withdrawal requests with values larger than the current account balance will be rejected

## Files

##### atm.cpp
- THIS IS THE MAIN; RUN THIS FILE TO RUN THE PROJECT
- Creates an instance of an ATM object
- Takes in file to load bank data into the bankAPI simulator, which is needed to test the code
- Takes in user input commands
- Runs functions in respect to user input

##### Controller.h & Controller.cpp
- Holds the current states of the ATM machine
  - CardState: HASCARD, NOCARD
  - AccountState: CHECKING, SAVINGS
- Implements the following functions:
  - loadBankInformation(inputfile)
  - checkCardValid(cardNumber, PIN)
  - atmAvailable()
  - selectAccount(accountValue)
  - seeBalance()
  - update(amount)
  - withdraw(amount)
  - deposit(amount)
  - eject()

##### BankApi.h & BankAPI.cpp
- Stores card numbers and their associated PIN numbers
  - While card information should be hashed and dynamically [salted](https://en.wikipedia.org/wiki/Salt_(cryptography)) for security, this has been omitted for simplicity
  - Each card is associated with a checking and savings account
- Implements the following functions:
  - loadData(inputfile)
  - checkCard(cardNumber, PIN)
  - getBalance()
  - setAndGetBalance(amount)
  
##### Card.h & Card.cpp
- Implements Card class, which has the following data:
  - Card Number
  - PIN Number
  - Checking Account
  - Savings Account
- Implements the following functions:
  -validate(PIN)
  -getCheckingBalance()
  -getSavingsBalance()
  -getAndSetCheckingBalance()
  -getAndSetSavingsBalance()

##### Account.h & Account.cpp
- Implements Account class, which has the following data:
  - beingUpdated flag (to make sure only one user accesses the account at a time)
  - Balance
- Implements the following functions:
  - changeUpdateState()
  - available()
  - getBalance()
  - setBalance(amount)
  
##### test_files folder
  - Holds test case text files that should run without throwing any errors
  
## HOW TO RUN THE PROGRAM
  - Run atm.cpp in commandline shell
  - Follow the user prompts

Thank you for taking your time to take a look at this little project!
