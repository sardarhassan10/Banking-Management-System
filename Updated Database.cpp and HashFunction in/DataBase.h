#pragma once
#include"Account.h"
#include<stack>
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
	void ShowAccountInfo(int accNum);
	void Menu();
	int getNumberOfAccounts()
	{
		return numberOfAccounts;
	}
	int HashFunction(int i)
	{
		//int hashedValue = i;
		//Boundary folding
		int temp1 = i % 1000,temp2 = i/1000;
		int hashedValue = temp1+temp2;
		return hashedValue % 100;
	}
	~DataBase();
};

