#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class President
{
public:
	string name;
	int start;
	int end;
	string party;
	President* prev;
	President* next;

	President(string name, int start, int end, string party) : name(name), start(start), end(end), party(party), prev(nullptr), next(nullptr) {}
	President(President *ptr) : name(ptr->name), start(ptr->start), end(ptr->end), party(ptr->party), prev(nullptr), next(nullptr) {}
};

class List
{
public:
	int size;
	President* head;
	President* tail;

	List() : size(0), head(nullptr), tail(nullptr) {}

	void push_front(President president)
	{
		President* newElement = new President(president);
		if (head == nullptr)
		{
			head = newElement;
			tail = newElement;
		}
		else
		{
			newElement->prev = nullptr;
			newElement->next = head;
			head->prev = newElement;
			head = newElement;
		}
		size++;
	}

	void pop_front()
	{
		if (isEmpty())
		{
			cout << "\nList is already empty!";
			return;
		}
		else
		{
			head = head->next;
			if (head != nullptr) head->prev = nullptr;
		}
		size--;
	}

	void push_back(President president)
	{
		President* newElement = new President(president);
		if (head == nullptr)
		{
			head = newElement;
			tail = newElement;
		}
		else
		{
			newElement->prev = tail;
			newElement->next = nullptr;
			tail->next = newElement;
			tail = newElement;
		}
		size++;
	}

	void push_back(President* president)
	{
		if (head == nullptr)
		{
			head = president;
			tail = president;
		}
		else
		{
			president->prev = tail;
			president->next = nullptr;
			tail->next = president;
			tail = president;
		}
		size++;
	}

	void pop_back()
	{
		if (isEmpty())
		{
			cout << "\nList is already empty!";
		}
		else
		{
			tail = tail->prev;
			if (tail != nullptr) tail->next = nullptr;
			size--;
		}
	}

	void display()
	{
		President* ptr = head;
		while (ptr != NULL)
		{
			cout << ptr->name << "\n";
			ptr = ptr->next;
		}
	}

	President front()
	{
		return head;
	}

	President back()
	{
		return tail;
	}

	bool isEmpty()
	{
		if (head == nullptr || tail == nullptr || size == 0) return 1;
		else return 0;
	}

	void clean()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	List shortest_ruling() //task1
	{
		List result;
		int shortest = 4;
		President* curr = head;
		while (curr != nullptr)
		{
			if (curr->end - curr->start < shortest)
			{
				result.clean();
				shortest = curr->end - curr->start;
				result.push_back(President(curr));
			}
			else if (curr->end - curr->start == shortest)
			{
				result.push_back(President(curr));
			}
			curr = curr->next;
		}
		return result;
	}

	List from_single_party(string party) // task2
	{
		{
			List result;
			President* curr = head;
			while (curr != nullptr)
			{
				if (curr->party == party)
					result.push_back(President(curr));
				curr = curr->next;
			}
			return result;
		}
	}

	President ruling_in(int year) // task3
	{
		if (year < 1789 || year > 1900)
		{
			cout << "No data!";
			return President("", 0, 0, "");
		}
		President* curr = head;
		while (curr != nullptr)
		{
			if (curr->start <= year && curr->end > year) return President(curr);
			curr = curr->next;
		}
	}
};

int main()
{
	const string filePath = "presidents.txt";
	List presidents;

	ifstream file(filePath);

	string line, name, start, end, party;

	while (getline(file, line))
	{
		stringstream ss(line);
		getline(ss, name, '\t');
		getline(ss, start, '\t');
		getline(ss, end, '\t');
		getline(ss, party, '\t');

		presidents.push_back(President(name, stoi(start), stoi(end), party));
	}

	file.close();

	cout << "TASK 1: \n";
	List list1 = presidents.shortest_ruling();
	list1.display();

	cout << "\n\nTASK 2: \n";
	List list2 = presidents.from_single_party("Republican");
	list2.display();

	cout << "\n\nTASK 3: \n";
	President president1 = presidents.ruling_in(1805);
	cout << president1.name;

	return 0;
}
