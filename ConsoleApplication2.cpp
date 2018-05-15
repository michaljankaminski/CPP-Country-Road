// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
class Data
{
	int i = 0;
	int width;
	int height;
	int row = 0;
	// values: 0 - wall, 1 - standard, 2 - border, 3 - road standard , 4 - road border;
	struct block
	{
		int country_id;
		int block_id;
		bool road = false;
		block* top; //1
		block* right; //2
		block* bottom; // 3
		block* left; //4
		int top_value;
		int right_value;
		int bottom_value;
		int left_value;

		int number;
	}*head, *last;
public:
	Data(int wid, int hei)
	{
		this->width = wid;
		this->height = hei;
		this->head = nullptr;
		this->last = nullptr;
	}
	~Data()
	{

	}
	int check()
	{
		block* checker = head;
		block* start = nullptr;
		int checked_country[25];
		for (int i = 0; i < 25; i++)
		{
			checked_country[i] = 0;
		}
		while (start != nullptr)
		{
			while (checker != nullptr)
			{
				if (checker->road = false)
				{
					if ((checker->left->road || checker->bottom->road || checker->right->road || checker->top->road) == false)
					{
						if ((checker->left_value || checker->bottom_value || checker->right_value || checker->top_value) == 2)
						{
							return 1;
						}
					}
				}

				if (checker->left_value = 4 )
					checked_country[checker->country_id]++;
				if (checker->bottom_value = 4)
					checked_country[checker->country_id]++;
				if (checker->right_value = 4)
					checked_country[checker->country_id]++;
				if (checker->top_value = 4)
					checked_country[checker->country_id]++;

				checker = checker->right;
			}
			start = start->bottom;
			checker = start;
		}
		for (int i = 0; i < 25; i++)
		{
			if (checked_country[i] != 2)
				return 1;
		}
		
	}
	void DFS()
	{
		int status[25];
		int visited[25];
		block *finder = head;
		block *current = finder;
	//	block *finder2 = head;
		int depth = 0;
		int visited_block = 0;
		while (check() != 0)
		{
			
			//0 - nie ruszony, 1 - przetwarzany , 2 - zrobiony
			status[current->block_id] = 1;
			if (current->left != nullptr)
			{
				current = current->left; 
				depth++; 
			}
			else if (current->bottom != nullptr)
			{
				depth++;
			}
			else if (current->right != nullptr)
			{
				depth++;
			}
			else if (current->top != nullptr)
			{
				depth++;
			}
		}
	}
	void print()
	{
	   /*o -+- o -+- x
		 + --- + --- |
		 o -+- x --- x
		 | --- + --- |
		 x -+- x --- x*/
		block* temp;
		block* start;
		temp = head;
		start = temp;
		while (start != nullptr)
		{
			while (temp != nullptr)
			{
				cout << "o ";
				if (temp->right_value == 2)
					cout << "-+- ";
				else if (temp->right_value == 1)
					cout << "--- ";
				else if (temp->right_value == 2)
				{

				}
				temp = temp->right;

			}
			cout << endl;
			temp = start;
			while (temp != nullptr && temp->bottom != nullptr)
			{
				if (temp->bottom_value == 1)
				{
					cout << "|";
					if (temp->right != nullptr)
					{
						cout << " --- ";
					}
				}
				if (temp->bottom_value == 2)
				{
					cout << "+";
					if (temp->right != nullptr)
					{
						cout << " --- ";
					}
				}
				temp = temp->right;
			}


			cout << endl;

			temp = start->bottom;
			start = temp;
		}

	}
	void add(int value, int value_2, int country)
	{
		block *temp = new block;
		temp->country_id = country;
		temp->block_id = i;
		i++;
		temp->right_value = value;
		temp->bottom_value = value_2;
		temp->bottom = nullptr;
		temp->right = nullptr;
		if (head == nullptr) // we are adding head block - postiion (0,0)
		{
			temp->top_value = 0;
			temp->left_value = 0;
			temp->right_value = value;
			temp->bottom_value = value_2;
			temp->top = nullptr;
			temp->right = nullptr;
			temp->bottom = nullptr;
			temp->left = nullptr;
			last = temp;
			head = temp;
			row = 1;
			return;
		}
		if (row == this->width)
		{
			block *finder;
			finder = last;
			while (finder->left != nullptr)
			{
				finder = finder->left;
			}
			finder->bottom = temp;
			temp->top = finder;
			temp->bottom = nullptr;
			temp->right = nullptr;
			temp->right_value = value;
			temp->bottom_value = value_2;
			temp->left = nullptr;
			temp->left_value = 0;
			last = temp;
			row = 1;
			finder = nullptr;
		}
		else
		{
			last->right = temp;
			temp->left = last;

			temp->left_value = last->right_value;
			if (last->top != nullptr)
			{
				temp->top = last->top->right;
				last->top->right->bottom = temp;
				temp->top_value = last->top->right->bottom_value;
			}
			else
			{
				temp->top = nullptr;
				temp->top_value = 0;
			}
			last = temp;
			this->row++;
			return;
		}
	}
};

using namespace std;
int main()
{	// values: 0 - wall, 1 - standard, 2 - border, 3 - road;
	Data* ss = new Data(5, 5);
	ss->add(1, 2,10);
	ss->add(1, 2,10);
	ss->add(1, 2,10);
	ss->add(1, 2,10);
	ss->add(0, 2,10);

	ss->add(1, 2,11);
	ss->add(2, 1,11);
	ss->add(2, 1,12);
	ss->add(1, 1,13);
	ss->add(0, 2,13);

	ss->add(2, 2,14);
	ss->add(2, 2,11);
	ss->add(2, 1,12);
	ss->add(2, 2,13);
	ss->add(0, 1,15);

	ss->add(1, 2,12);
	ss->add(1, 2,12);
	ss->add(1, 2,12);
	ss->add(2, 2,16);
	ss->add(0, 1,15);

	ss->add(2, 0,17);
	ss->add(1, 0,16);
	ss->add(1, 0,16);
	ss->add(2, 0,16);
	ss->add(0, 2,15);
	ss->print();
	getchar();

}
