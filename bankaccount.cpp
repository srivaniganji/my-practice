#include <iostream>
using namespace std;

class BankAccount {
private: 
    long balance;

public: 
    BankAccount(long initialBalance) {
        if (initialBalance >= 0) {
            balance = initialBalance;
        }
    }

    bool deposit(long amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    bool withdraw(long amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    long getBalance() {
        return balance;
    }
};
int main() {
    BankAccount* acc = new BankAccount(1000);
    if(acc->deposit(500)) {
        cout << "Deposit of 500 successful" << endl;
    } else {
        cout << "Deposit of 500 failed" << endl;
    }
    if(acc->withdraw(300)) {
        cout << "Withdrawal of 300 successful" << endl;
    } else {
        cout << "Withdrawal of 300 failed" << endl;
    }
    if(acc->withdraw(1500)) {
        cout << "Withdrawal of 1500 successful" << endl;
    } else {
        cout << "Withdrawal of 1500 failed" << endl;
    }

    cout << "Total balance: " << acc->getBalance() << endl;
}