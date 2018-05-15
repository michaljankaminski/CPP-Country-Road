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
	int column = 0;
	int country_num = 0;
	// values: 0 - wall, 1 - standard, 2 - border, 3 - road standard , 4 - road border;
	struct block
	{
		int country_id;
		int block_id;
		bool road = false;
		block* top;
		block* right;
		block* bottom; 
		block* left; 
		int top_value;
		int right_value;
		int bottom_value;
		int left_value;

		int number;
	}*head, *last;
public:
	Data(int wid, int hei, int num_country)
	{
		this->width = wid;
		this->height = hei;
		this->head = nullptr;
		this->last = nullptr;
		this->country_num = num_country;
	}
	~Data()
	{

	}
	int check()
	{
		block* checker = head;
		block* start = head;
		int checked_country[25];
		for (int i = 0; i < country_num; i++)
		{
			checked_country[i] = 0;
		}
		while (start != nullptr)
		{
			while (checker != nullptr)
			{
				cout << "Node:" << checker->block_id << endl;
				if (checker->road == false)
				{
					if ((checker->left != nullptr )&& (checker->left->road == false) && (checker->left_value == 2))
					{
						cout << "Border left" << endl;
						return 1;
					}
					if ((checker->bottom != nullptr) && (checker->bottom->road == false) && (checker->bottom_value == 2))
					{
						cout << "Border bottom" << endl;
						return 1;
					}
					if ((checker->right != nullptr) && (checker->right->road == false) && (checker->right_value == 2))
					{
						cout << "Border right" << endl;
						return 1;
					}
					if ((checker->top != nullptr) && (checker->top->road == false) && (checker->top_value == 2))
					{
						cout << "Border top" << endl;
						return 1;
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
		for (int i = 0; i < country_num; i++)
		{
			if (checked_country[i] != 2)
				return 1;
		}
		return 0;
		
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
			column = 1;
			return;
		}
		if (column == this->width)
		{
			block *finder;
			finder = last;
			last->right_value = 0;
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
			column = 1;
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
			this->column++;
			return;
		}
	}
	void path()
	{
	///values: 0 - wall, 1 - standard, 2 - border, 3 - road standard, 4 - road border;
		block* roader = head;
		roader->road = true;
		roader->right_value = 3;
		cout << roader->block_id << endl;

		roader = roader->right;
		roader->left_value = 3;
		roader->right_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->right;
		roader->left_value = 3;
		roader->right_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->right;
		roader->left_value = 3;
		roader->right_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->right;
		roader->left_value = 3;
		roader->bottom_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->bottom;
		roader->top_value = 4;
		roader->left_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->left;
		roader->right_value = 3;
		roader->bottom_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->bottom;
		roader->top_value = 3;
		roader->right_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->right;
		roader->left_value = 4;
		roader->bottom_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->bottom;
		roader->top_value = 3;
		roader->left_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->left;
		roader->right_value = 4;
		roader->bottom_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->bottom;
		roader->top_value = 3;
		roader->left_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->left;
		roader->right_value = 3;
		roader->left_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->left;
		roader->right_value = 3;
		roader->left_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->left;
		roader->right_value = 4;
		roader->top_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->top;
		roader->bottom_value = 4;
		roader->top_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->top;
		roader->bottom_value = 4;
		roader->right_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->right;
		roader->left_value = 4;
		roader->top_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->top;
		roader->bottom_value = 3;
		roader->left_value = 3;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->left;
		roader->right_value = 3;
		roader->top_value = 4;
		roader->road = true;
		cout << roader->block_id << endl;

		roader = roader->top;
		roader->bottom_value = 4;
		cout << roader->block_id << endl;


	}
};

using namespace std;
int main()
{	// values: 0 - wall, 1 - standard, 2 - border, 3 - road;
	Data* ss = new Data(5, 5, 8);
	ss->add(1, 2, 0);
	ss->add(1, 2, 0);
	ss->add(1, 2, 0);
	ss->add(1, 2, 0);
	ss->add(0, 2, 0);

	ss->add(1, 2, 1);
	ss->add(2, 1, 1);
	ss->add(2, 1, 2);
	ss->add(1, 1, 3);
	ss->add(0, 2, 3);

	ss->add(2, 2, 4);
	ss->add(2, 2, 1);
	ss->add(2, 1, 2);
	ss->add(2, 2, 3);
	ss->add(0, 1, 5);

	ss->add(1, 2, 2);
	ss->add(1, 2, 2);
	ss->add(1, 2, 2);
	ss->add(2, 2, 6);
	ss->add(0, 1, 5);

	ss->add(2, 0, 7);
	ss->add(1, 0, 6);
	ss->add(1, 0, 6);
	ss->add(2, 0, 6);
	ss->add(0, 2, 5);
//	ss->print();
	ss->path();
	ss->check();
	getchar();

}
