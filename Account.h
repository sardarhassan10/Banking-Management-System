#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<time.h>
using namespace std;

class Account
{
protected:
	// Account Details
	int accountNumber=0;
	int balance; // Balance can only be in interger
	string password;
	string forgotPassword;//Anything in case for forgetting password
	string name;
	int accountType;//Current fixed etc
public:
	Account();
	void WriteFile();
	virtual void TakeInput();//Virtual Function
	void changePassword();
	void ForgotPassword();
	void ShowAccountInformation();
	virtual void Credit()=0; //Pure Virtual Functions
	virtual void Debit()=0;	//Pure Virtual Functions
	virtual void ShowBalance()=0;	//Pure Virtual Functions
	virtual void Menu();
	int getAccountNumber();
	
	int getType()
	{
		return accountType;
	}
	void setType(int t)
	{
		accountType = t;
	}
	int getBalance()
	{
		return balance;
	}
	void setBalance(int b)
	{
		balance = b;
	}
	void setName(string n)
	{
		name = n;
	}
	string getName()
	{
		return name;
	}
	void setPassword(string p)
	{
		password = p;
	}
	string getPassword()
	{
		return password;
	}
	void setAccountNumber(int acc)
	{
		accountNumber = acc;
	}
	void setAccountType(int t)
	{
		accountType = t;
	}
	~Account();
};

///////////////////////////////////////////
//Current Account
class CurrentAccount : public Account
{
public:
	void TakeInput()
	{
		Account::TakeInput();
		cout << "\nHow much money you want to deposit? ";
		cin >> balance;
	}
	void Credit()
	{
		int credit;
		do {
			cout << "\nEnter the amount to deposit: ";
			cin >> credit;
		} while (credit < 0);
		balance += credit;
		cout << "\n Your new balance is: " << balance;
	}
	void Debit()
	{
		int debit;
		do {
			cout << "\nEnter the amount to deposit: ";
			cin >> debit;
		} while (debit < 0);
		if (debit > balance)
		{
			cout << "\nNot enought money!";
			cout << "\n Your balance is: " << balance;
		}
		else
		{
			balance -= debit;
			cout << "\n Your new balance is: " << balance;
		}
	}

	void ShowBalance()
	{
		cout << "\n Your current balance is: " << balance;
	}
};

//////////////////////////////////////////////////////////
//Fix for 1 year account
class FixAccount : public Account
{
	time_t begin = clock(); // Vairaible for time 
public:
	void TakeInput()
	{
		Account::TakeInput();
		do
		{
			cout << "\nHow much money you want to deposit (Should be greater than 9999 Rs) ? ";
			cin >> balance;
		} while (balance < 10000);
		
	}

	void Credit()
	{
		cout << "\n This account is fixed account!"
			<< " You can credit or debit it for 1 year!"
			<< "\n Time Left is :" << clock() - begin;

	}

	void Debit()
	{
		cout << "\n This account is fixed account!"
			<< " You can credit or debit it for 1 year!"
			<< "\n Time Left is :" << clock() - begin;
	}

	void ShowBalance()
	{
		cout << "\n Your current balance is: " << balance;
		cout << "\n You would recieve : " << .15*balance << " Rs after " << clock() - begin;
	}
};

