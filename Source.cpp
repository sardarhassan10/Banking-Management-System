#include"DataBase.h"
#include"Priority_Queue.cpp"
using namespace std;

void Menu()
{
	DataBase d1;
	Priority_Queue q1(100);
	int choice;
	do
	{
	cout << "\nPlease enter one of the option: "
		<< "\n1. Make Transaction"
		<< "\n2. Add to Queue"
		<< "\n3. Exit" << endl;
	cout << "\n Choice: ";
	cin >> choice;
	if (choice == 1)
	{
		d1.Menu();
	}
	else if(choice == 2)
	{
		q1.Menu();
	}
	} while (1);
}

int main()
{
	{
		Priority_Queue q1(100); 
		system("pause");
	}
	system("pause");
	system("pause");
}
