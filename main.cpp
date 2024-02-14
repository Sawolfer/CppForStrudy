#include <iostream>
#include <string>

using namespace std;



class Account{

protected:
    int accountNumber;
    double balance;
    string name;

public:
    Account(int accountNumber, double  balanse, string name){
        this->accountNumber = accountNumber;
        this->name = name;
        this->balance = balanse;
    }
    double getBalance(){
        return balance;
    }
    int getAccountNumber(){
        return accountNumber;
    }
    string getOwnerName(){
        return name;
    }

    void deposit(double money){
        balance+=money;
    }
    void withdraw(double money){
        if (balance>=money){
            balance-=money;
        } else {
            cout << "no enough money";
        }
    }

};

class SavingsAccount : public Account{

protected:
    double interestRate;

public:

    SavingsAccount(int accountNumber, double balance, string name, double interestRate) : Account(accountNumber, balance, name){
        this->interestRate = interestRate;
    }

    int calculateInterest(){
        int interest;
        interest = (interestRate/100)*balance;
        return interest;
    }

    int getInterestRate(){
        return interestRate;
    }

};

int main() {

    SavingsAccount savings(123456, 1000.0, "John Doe", 2.5);
    savings.deposit(500.0);
    savings.withdraw(200.0);
    savings.calculateInterest();

    cout << "Account Number: " << savings.getAccountNumber() << endl;
    cout << "Owner's Name: " << savings.getOwnerName() << endl;
    cout << "Current Balance: " << savings.getBalance() << endl;
    cout << "Interest Rate: " << savings.getInterestRate() << "%" << endl;
    return 0;
}