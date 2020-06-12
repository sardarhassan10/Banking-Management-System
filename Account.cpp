#include "Account.h"



Account::Account()
{
	
}
void Account::TakeInput()
{

	cout << "\nPlease enter your account information:";
	cout << "\n\n Enter your name: ";
	cin >> name;
	cout << "\nEnter your password: ";
	cin >> password;
	
}

void Account::Menu()
{
	do
	{
		int choice;
		cout << "\nPlease enter one of the option: "
			<< "\n1. Credit"
			<< "\n2. Debit"
			<< "\n3. Show Account Information"
			<< "\n4. Show Balance"
			<< "\n5. Exit" << endl;
		cout << "\n Choice: ";
		cin >> choice;
		if (choice == 1)
		{
			Credit();
		}
		else if (choice == 2)
		{
			Debit();
		}
		else if (choice == 3)
		{
			ShowAccountInformation();
		}
		else if (choice == 4)
		{
			ShowBalance();
		}
		else if (choice == 5) // Break the loop and go to the menu
		{
			break;
		}
	} while (1);
}
int Account::getAccountNumber()
{
	return accountNumber;
}
Account::~Account()
{
}

void Account::ShowAccountInformation()
{
	cout << "\n\n---------------------------------------------";
	if (accountType == 1)
	{
		cout << "\nType : Current Account";
	}
	else
		cout << "\nType : Fixed Account";
	cout << "\n Name : " << name;
	cout << "\n Account Number is: " << setw(8) << setfill('0') << accountNumber;
	cout << "\nBalance: " << balance;

}

