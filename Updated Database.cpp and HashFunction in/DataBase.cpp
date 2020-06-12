#include "DataBase.h"
#include<string>
#include<algorithm>
#include<fstream>
#include<vector>

#include<iomanip>

void Insert(Node*& root, Account*& acc);
Node*& searchWithKey(Node*& root, int key);
Node* Minimum(Node* node);
Node* succ(Node* node);
bool deleteNode(int key, Node *& root);
int Decrypt(int);
string Decrypt(string);
int Encrypt(int);
string Encrypt(string);
vector<Account*> tempAccounts; //For temporary storage of data


//Encryption data
int n_modulus = 3233;
int e_exponent = 17;
int d_exponent = 413;
int Decrypt(int);
string Decrypt(string);
int Encrypt(int);
string Encrypt(string);


//Constructor
DataBase::DataBase(): numberOfAccounts(line_count()) //Line counts represent number of accounts
{
	//read the data in data base
	read();
}

//Destructor store the data before closing
DataBase::~DataBase()
{
	save();
}

//////////////////////////////
//Insert New account
void DataBase::NewAccount()
{
	Account* newAccount;
	int type;
	numberOfAccounts++;
	cout << "\n1. Current"
		<< "\n2. Fix";
	cout << "\n Which type of account? ";
	cin >> type;
	if (type == 1)
	{
		newAccount = new CurrentAccount;
		newAccount->setAccountType(type);
	}
	else  
	{
		newAccount = new FixAccount;
		newAccount->setAccountType(type);
	}
	system("pause");
	system("cls");
	newAccount->TakeInput();
	newAccount->setAccountNumber(GenerateAccountNumber());//Generation and setting is little complex
	cout << "\n Account Number Generated is: " << setw(8) << setfill('0') << newAccount->getAccountNumber();
	int index = HashFunction(newAccount->getAccountNumber());
	Insert(dataBase[index], newAccount);
	tempAccounts.push_back(newAccount);
}

///////////////////////////
//Searching algorithm

bool DataBase::SearchAccount(int key) // Key is usually the account number
{
	int index = HashFunction(key);
	Node* temp = searchWithKey(dataBase[index], key);
	return temp != NULL ? true : false;
}

void DataBase::ShowAccountInfo(int accNum)
{
	int index = HashFunction(accNum);
	Node* temp = searchWithKey(dataBase[index], accNum);
	if (temp != NULL)
		temp->account->ShowAccountInformation();
	else
		cout << "\n Account do not exist";
}
////////////////////////////
//Deleting

void DataBase::DeleteAccount(int key)
{
	int index = HashFunction(key);
	 deleteNode(key,dataBase[index]);
	
}


//////////////////////////////////////////////////////////////////////////////////
//All below is binary search tree functions

void Insert(Node*& root, Account*& acc) // Root represents the actual root or root of subtree
{
	static int count = 0;
	Node *temporary = new Node;
	temporary->account = acc;
	temporary->left = temporary->right = NULL;
	Node* temp = temporary;
	if (root == NULL)// No node
	{
		root = temp;

	
	}

	if (root->account->getAccountNumber()> acc->getAccountNumber()) // If less than left sub tree
	{
		if (root->left != NULL)
		{
			Insert(root->left, acc);
		}
		else
		{
			root->left = temp;
		}
	}
	else if (root->account->getAccountNumber()< acc->getAccountNumber()) // If greater than right
	{
		if (root->right != NULL) //If there is element at right
		{
			Insert(root->right, acc);
		}
		else
		{
			root->right = temp;
		}
	}

}

//For searching if we have Account
Node*& search(Node*& root, Account*& acc)
{
	// Base Cases: Either root is null or the account is present at root 
	if (root == NULL || root->account->getAccountNumber()== acc->getAccountNumber())
	{

		return root;
	}

	// if the given account is greater than root's account 
	if (root->account->getAccountNumber()< acc->getAccountNumber())
		return search(root->right, acc);

	// if the given account is smaller than root's account 
	return search(root->left, acc);
}

//replica if we have key
Node*& searchWithKey(Node*& root, int key)
{
	// Base Cases: Either root is null or the account is present at root 
	if (root == NULL || root->account->getAccountNumber() == key)
	{

		return root;
	}

	// if the given account is greater than root's account 
	if (root->account->getAccountNumber()< key)
		return searchWithKey(root->right, key);

	// if the given account is smaller than root's account 
	return searchWithKey(root->left, key);
}
Node* Minimum(Node* node) // Minimum value of a root node
{
	while (node->left != NULL) // The minimum values the at the leftmost position
	{
		node = node->left;
	}
	return node;
}

Node* succ(Node* node) // To find the successor of a node
{
	if (node->right == NULL)
		return NULL;
	else
		return Minimum(node->right);

}



//Deleting a node
bool deleteNode(int key, Node *& root) {
	Node*& handle = searchWithKey(root, key);
	Node * toDelete = handle;
	if (handle != NULL) {
		/* Node* temp = searchWithKey(dataBase[index], key);*/
		tempAccounts.erase(remove(tempAccounts.begin(), tempAccounts.end(), handle->account), tempAccounts.end());
		if (handle->left == NULL) { // Leaf or one child
			handle = handle->right;
			delete toDelete;
			
			return true;
		}
		else if (handle->right == NULL) { // One child
			handle = handle->left;
			delete toDelete;
			
			return true;
		}
		else { // Two children
			   // The algorithm replace the node with successor and then delete it in succesive tree
			Node* successor = succ(root);
			handle->account = successor->account;
			deleteNode(successor->account->getAccountNumber(), handle->right);
			return true;
			
		}
	}
	else
	{
		cout << "\nNot Deleted";
		return false;
	}
}

//End of BST
//////////////////////////////////////////////////////////////////////////////////////

int DataBase::GenerateAccountNumber()
{
	// This is specialize algorithm to generate account number such that balance binary search tree is produced
	Account* temp = tempAccounts.back();
	int n;
	if (temp == NULL)
		
	{
		n = 227761;
		return n;
	}
	
	
	 if (temp->getAccountNumber() % 2 == 0)
	{
		n = temp->getAccountNumber()- 100000;
		n++;
		return n;
	}
	else
	{
		return temp->getAccountNumber() + 100001;
	}

	
}




void DataBase:: Menu()
{
	do
	{
		int choice;
		cout << "\nPlease enter one of the option: "
			<< "\n1. Add New Account"
			<< "\n2. Delete Account"
			<< "\n3. Make Transactions"
			<< "\n4. Exit" << endl;
		cout << "\n Choice: ";
		cin >> choice;
		system("pause");
		system("cls");
		if (choice == 1)
		{
			NewAccount();
		}
		else if (choice == 2)
		{
			int accNum;
			cout << "\n Please enter the account Number: ";
			cin >> accNum;
			DeleteAccount(accNum);
		}
		else if (choice == 3)
		{
			int accNum;
			string password;
			cout << "\n Please enter the account Number: ";
			cin >> accNum;
			bool find = SearchAccount(accNum);
			if (find)
			{
				int tries = 0; //Number of tries for password
				int index = HashFunction(accNum);
				Node* temp = searchWithKey(dataBase[index], accNum);
				cout << "\n Enter the password: ";
				cin >> password;
				while (password != temp->account->getPassword() && tries < 3)
				{
					tries++;
					cout << "\n Wrong Password!";
					cout << "\n Enter the password again: ";
					cin >> password;
				}
				if (tries == 3) //No transaction would be made
				{
					cout << "\n You have entered the wrong password more than 3 times!";
					return;
				}
				temp->account->Menu();
			}
			else
			{
				cout << "\nIncorrect Account Number";
			}
		}
		else if (choice == 4)
			break;
	} while (1);
}


int DataBase::line_count() //Line count
{
	int number_of_lines = 0;
	string line;
	ifstream myfile("data.txt");

	while (getline(myfile, line))
		++number_of_lines;
	return number_of_lines;
}

void DataBase::read() // Function for reading from file
{
	string password, name;
	int balance, accNum,type; //temporary variva
	vector<Account*> usama;
	
	Account* accounts;
	ifstream infile;
	int index;
	infile.open("data.txt");

	for(int i =0;i<numberOfAccounts;i++)
	{
		
		infile >> type  >> password >> name >> balance >> accNum;
		// cout << "\nIn read" << password << name << balance << accNum;*/
		
		 if (type == 1)
		 {
			 accounts = new CurrentAccount;
			
		 }
		 else
		 {
			 accounts = new FixAccount;
		 }

	    accounts->setType((type));
		accounts->setPassword(Decrypt(password));
		accounts->setName(Decrypt(name));
		accounts->setBalance((balance));
		accounts->setAccountNumber((accNum));
		infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		index = HashFunction(accounts->getAccountNumber()); 
		Insert(dataBase[index], accounts); //To store into hash data base
		tempAccounts.push_back(accounts); //To store into array
	}
	
	
	infile.close();
}

void DataBase::save() //For saving teh document before closing
{
	ofstream outfile;
	outfile.open("data.txt");
	

	for (int i = 0; i<tempAccounts.size(); i++)
	{
		cout << "Hello";
		//if(tempAccounts[i]->getAccountNumber()==deletedAccNum[c)
		outfile << (tempAccounts[i]->getType() )<< " " <<Encrypt(tempAccounts[i]->getPassword()) << " "
			<< Encrypt(tempAccounts[i]->getName()) << " "
			<<(tempAccounts[i]->getBalance()) << " "
			<< (tempAccounts[i]->getAccountNumber()) << "\n";
	}
	outfile.close();
	
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Encryption Maths

//////////////////////////////////////////////////////
//Calculates the absolute value
int absolute(int x)
{
	int y;
	y = x;
	return y;
}

//Calcultes gcd of two arguments passed
int euclidean_algorithm(int a, int b)
{
	int r;

	do
	{
		r = a % b;
		a = b;
		b = r;
	} while (b != 0);

	return a;
}

//Calcultes modular inverse
int modular_inverse(int a, int m)
{
	float y = 1;
	while (1)
	{
		if ((1 + m * y) / a == absolute((1 + m * y) / a))
			break;
		else
			y++;
	}

	return (1 + m * y) / a;
}

//Calculates totient of two primes passed as argument
int totient(int a, int b)
{
	return (a - 1)*(b - 1);
}

//Modular exponentian.
long long int modular_exponentiation(int b, int e, int m)
{
	int counter = 1;
	long long int c = b;
	while (counter<e) {
		c *= b;
		c = c % m;
		counter++;
	}
	return c;
}

int key(int e, int m)
{
	return modular_inverse(e, m);
}

int Encrypt(int m)
{
	return modular_exponentiation(m, e_exponent, n_modulus);
}

//Number decryptor

int  Decrypt(int m)
{
	return modular_exponentiation(m, d_exponent, n_modulus);
}

//String encryptor
string Encrypt(string input)
{
	int n = input.length();

	char* c = new char[n + 1];
	c[n] = '\0';

	for (int i = 0; i<n; i++)
	{
		c[i] = input.at(i) + i;
	}

	string output = c;
	return output;
}

//String decryptor
string Decrypt(string input)
{
	int n = input.length();

	char* c = new char[n + 1];
	c[n] = '\0';

	for (int i = 0; i<n; i++)
	{
		c[i] = input.at(i) - i;
	}

	string output = c;
	return output;
}



