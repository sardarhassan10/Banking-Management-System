#pragma once
#include"Account.h"
#include<iostream>

//Node Definition
struct Node
{
	Account* account;
	Node* left;
	Node* right;
};

class DataBase
{

private:
	Node * dataBase[100] = { NULL };//Data Base for storing value
	
	int buckets;//Number of indexes in the dataBase
	int numberOfAccounts;
	
public:

	DataBase();
	Account*& TakeInput();
	int GenerateAccountNumber();
	void read();//To read from file
	void save();
	int line_count();
	void NewAccount();
	bool SearchAccount(int );
	void DeleteAccount(int);
	void  double_main_for_testing()
	{
		NewAccount();
		NewAccount();
		NewAccount();
		ShowAccountInfo(227763);
		bool find = SearchAccount(227763);
		if (find == true)
			cout << "\nFound";
		else cout << "\nNot found";
		DeleteAccount(227763);
		find = SearchAccount(227763);
		if (find == true)
			cout << "\nFound";
		else cout << "\nNot found";
	}
	
	void ShowAccountInfo(int accNum);
	void Menu();
	int HashFunction(int i)
	{	

		return i % 100;
	}
	~DataBase();
};

