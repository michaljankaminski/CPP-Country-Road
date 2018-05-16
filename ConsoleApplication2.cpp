#include "stdafx.h"
#include <iostream>
#include <stack>

using namespace std;
class Data
{
	int i = 0;
	int width;
	int height;
	int column = 0;
	int country_num = 0;
	stack <int> stos;
	// values: 0 - wall, 1 - standard, 2 - border, 3 - road standard , 4 - road border;
	struct block
	{
		int country_id;
		int block_id;
		int status; // 0 - pusty, 1 - odwiedzony, 2 - zakonczony 
		int level; // poziom na którym znajduje się wierzcholek
		bool road = false;
		block* top;
		block* right;
		block* bottom;
		block* left;
		block* parrent;
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
					if ((checker->left != nullptr) && (checker->left->road == false) && (checker->left_value == 2))
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

				if (checker->left_value == 4)
				{
					checked_country[checker->country_id]++;
				}

				if (checker->bottom_value == 4)
				{
					checked_country[checker->country_id]++;
				}

				if (checker->right_value == 4)
				{
					checked_country[checker->country_id]++;
				}

				if (checker->top_value == 4)
				{
					checked_country[checker->country_id]++;
				}
				checker = checker->right;
			}
			start = start->bottom;
			checker = start;
		}
		cout << "-----" << endl;
		for (int x = 0; x < country_num; x++)
		{
			cout << checked_country[x] << endl;
			if (checked_country[x] != 2)
			{
				cout << "out of range" << endl;
				return 1;
			}

		}
		return 0;

	}
	void clearStatus()
	{
		block *vertical = head;
		block *horizontal = vertical;

		while (vertical != nullptr)
		{
			while (horizontal != nullptr)
			{
				horizontal->status = 0;
				horizontal = horizontal->right;
			}
			vertical = vertical->bottom;
			horizontal = vertical;
		}
	}
	void printStatus()
	{
		block *vertical = head;
		block *horizontal = vertical;

		while (vertical != nullptr)
		{
			while (horizontal != nullptr)
			{
				cout << horizontal->status << " ";
				horizontal = horizontal->right;
			}
			cout << endl;
			vertical = vertical->bottom;
			horizontal = vertical;
		}
	}
	void iterativeDFS()
	{
		block *start = head;
		int min = 0;
		int max = 5;

		for (int i = min + 1; i <= max; i++)
		{
			this->clearStatus();
			cout << "LEVEL: " << i << endl;
			this->recursiveDFS(start, i);
			cout << endl;
			this->printStack();
			cout << endl;
			cout << "**";
			cout << endl;
		}
	}
	void recursiveDFS(block *root, int depth)
	{
		block *start = root;
		block *horizontal = root;

		//cout << horizontal->block_id << "- ";

		if (horizontal->level <= depth)
		{
			cout << horizontal->block_id << " ";
			if (horizontal->bottom != nullptr && horizontal->bottom->level <= depth && horizontal->bottom->status != 2)
			{

				if (horizontal->status == 0)
				{
					horizontal->status = 1; // ustawiamy status na 1 - w trakcie
				}
				stos.push(horizontal->block_id);
				horizontal->bottom->parrent = horizontal; // Wierzchołek posiada dzieci, na które możemy przejść. Jego dziecku ustawiamy rodzica
				horizontal = horizontal->bottom; // przechodzimy na dziecko;

				this->recursiveDFS(horizontal, depth);
			}
			else if (horizontal->right != nullptr && horizontal->right->level <= depth && horizontal->right->status != 2)
			{
				if (horizontal->status == 0)
				{
					horizontal->status = 1;
				}

				stos.push(horizontal->block_id);
				horizontal->right->parrent = horizontal;
				horizontal = horizontal->right;
				this->recursiveDFS(horizontal, depth);
			}
			else if (horizontal->top != nullptr && (horizontal->parrent != horizontal->top || horizontal->top == root))
			{
				if (horizontal->top == root)
				{
				}
				else
				{
					stos.push(horizontal->block_id);
					horizontal->status = 2;
					horizontal->parrent->status = 2;
					horizontal->parrent = horizontal->top;

					horizontal = horizontal->top;
					this->recursiveDFS(horizontal, depth);
				}

			}
			else if (horizontal->left != nullptr && (horizontal->parrent != horizontal->left || horizontal->left == root))
			{
				if (horizontal->left == start)
				{

				}
				else
				{
					stos.push(horizontal->block_id);
					horizontal->status = 2;
					horizontal->parrent = horizontal->left;

					horizontal = horizontal->left;
					this->recursiveDFS(horizontal, depth);
				}
			}
			else if (horizontal->parrent != nullptr && horizontal->parrent != horizontal)
			{
				if (horizontal->parrent->block_id == 0)
				{
					horizontal->status = 2;

				}
				else
				{
					stos.push(horizontal->block_id);
					horizontal->status = 2;

					horizontal = horizontal->parrent;
					horizontal->status = 2;
					this->recursiveDFS(horizontal, depth);
				}
			}

		}
		else
			cout << "Brak";

	}
	void printStack()
	{
		int size = stos.size();

		while (stos.empty() == false)
		{
			cout << stos.top() << " <- ";
			stos.pop();
		}
	}



	void print()
	{
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
	void add(int value, int value_2, int country, int level)
	{
		block *temp = new block;

		temp->parrent = nullptr;
		temp->country_id = country;
		temp->block_id = i;
		i++;
		temp->right_value = value;
		temp->bottom_value = value_2;
		temp->bottom = nullptr;
		temp->right = nullptr;
		temp->level = level;
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
		//example correct path for checking check() function
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
	//implementing our map
	ss->add(1, 2, 0, 0);
	ss->add(1, 2, 0, 1);
	ss->add(1, 2, 0, 2);
	ss->add(1, 2, 0, 3);
	ss->add(0, 2, 0, 4);

	ss->add(1, 2, 1, 1);
	ss->add(2, 1, 1, 2);
	ss->add(2, 1, 2, 3);
	ss->add(1, 1, 3, 4);
	ss->add(0, 2, 3, 5);

	ss->add(2, 2, 4, 2);
	ss->add(2, 2, 1, 3);
	ss->add(2, 1, 2, 4);
	ss->add(2, 2, 3, 5);
	ss->add(0, 1, 5, 6);

	ss->add(1, 2, 2, 3);
	ss->add(1, 2, 2, 4);
	ss->add(1, 2, 2, 5);
	ss->add(2, 2, 6, 6);
	ss->add(0, 1, 5, 7);

	ss->add(2, 0, 7, 4);
	ss->add(1, 0, 6, 5);
	ss->add(1, 0, 6, 6);
	ss->add(2, 0, 6, 7);
	ss->add(0, 2, 5, 8);
	ss->print();

	ss->iterativeDFS();
	cout << endl;
	ss->printStatus();
	//ss->path();
	//ss->check();
	getchar();

}