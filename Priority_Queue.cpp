#include<iostream>
#include<stdlib.h>
#include"DataBase.h"
using namespace std;

void swapElement(int &a, int &b);
//Mininum Heap Class!
struct Queue // Node of priority Queue
{
	int priority;
	int code;
	Queue* next;
};

class Priority_Queue
{
private:
	int heapSize;
	int heapCap;// Heap Capacity
	Queue *heap; // Pointer to  Heap array
	DataBase d1;
public:
	Priority_Queue(int capacity) //Constructor
	{
		heapSize = 0;
		heapCap = capacity;
		heap = new Queue[heapCap];
		Menu();
	}

	bool isEmpty()
	{
		if (heapSize != 0)
			return false;

		return true;
	}

	int HeapSize()
	{
		return heapSize;
	}

	int parent(int index) // Return Parent INdex
	{
		return (index - 1) / 2;
	}

	int Height() // Height of tree
	{
		return (heapSize);
	}

	void Print()
	{
		cout << "\n\nQueue linearly is: ";
		for (int i = 0; i < heapSize; i++)
		{
			cout <<  heap[i].code << " (" <<  heap[i].priority << ") "<< "\t";
		}
	}

	int AddToQueue()
	{
		int priority;
		cout << "\n\t1. VIP"
			<< "\n\t2. Old"
			<< "\n\t3. Woman"
			<< "\n\t4. Other"
			<< "\n\t5. Man";
		cout << "\n Please enter the priority of the customer: ";
		cin >> priority;
		if (heapSize == heapCap)
		{
			cout << "\n Stack OverFlow!!";
			return 0;
		}

		heapSize++;
		int i = heapSize - 1;
		heap[i].priority = priority;
		heap[i].code = heapSize;
		while (i != 0 && heap[parent(i)].priority > heap[i].priority)// To compare if child is smaller than parent
		{
			swap(heap[parent(i)], heap[i]); // If it smaller than just swap. We do not need to consider other
											// childs because they were already greater than parent
			i = parent(i);
		}
	}

	void MakeTransaction()//Remove element of that index
	{
		if (isEmpty() == true)
		{
			cout << "\n Queue is empty!";
			return;
		}
		Queue temp = heap[0];//Store the first element
		heap[0] = heap[heapSize - 1]; //Store the last value into first node
		heapSize--;
		MinHeapify(0);//Compare the tree
		cout << "\n Next person in queue is: " << temp.code;

		d1.Menu();
	}

	void MinHeapify(int index)//To ensure the characteristics of heap are followed
	{
		int r = index * 2 + 2;
		int l = index * 2 + 1;
		int smallest = index;
		if (r<heapSize)
			if (heap[r].priority <= heap[index].priority)//Checking the minimum of the child
			{
				smallest = r; cout << r << "\t" << heap[r].code;
			}
		if (l<heapSize)
			if (heap[l].priority <= heap[smallest].priority)
			{
				smallest = l; cout << l;
			}

		if ((heap[l].priority == heap[r].priority) && (smallest == l || smallest == r)) // If both have same priority then
		{

			if (heap[l].code < heap[r].code)//Then we find one with the lower code
				smallest = l;
			else
				smallest = r;
		}
		if (smallest != index)
		{
			swap(heap[index], heap[smallest]);
			MinHeapify(smallest);
		}
	}

	void Menu()
	{

		int choice;
		do {
			cout << "\n1. Add to Queue"
				<< "\n2. Make Transaction"
				<< "\n3. Size of Queue"
				<< "\n4. Show Queue"
				<< "\n5. Exit"
				<< "\n\n Please select one of the option:";
			cin >> choice;

			if (choice == 1)
			{
				AddToQueue();
			}

			else if (choice == 2)
			{
				MakeTransaction();
			}

			else if (choice == 3)
			{
				cout << "\nSize:" << HeapSize();
			}

			else if (choice == 4)
			{
				Print();
			}

			//else if (choice == 5)
			//{
			//	//exit(1);
			//}
		} while (choice != 5);
	}
		
};



