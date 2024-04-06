#include <iostream>
#include <cstdlib>

using namespace std;

class StackElement
{
public:
	int value;
	StackElement* next_ptr;

	StackElement(const int value) : value(value), next_ptr(nullptr) {}
};

class Stack
{
public:
	int size;
	StackElement* topElement;

	Stack() : topElement(nullptr), size(0){}

	void display()
	{
		StackElement *ptr = topElement;
		while (ptr != NULL)
		{
			cout << ptr->value << ", ";
			ptr = ptr->next_ptr;
		}
	}

	void push(const int value)
	{
		{
			StackElement* newElement = new StackElement(value);
			newElement->next_ptr = topElement;
			topElement = newElement;
			size++;
		}
	}

	bool isEmpty()
	{
		if (size == 0) return true;
		else return false;
	}

	void pop()
	{
		if (!isEmpty())
		{
			topElement = topElement->next_ptr;
			--size;
		}
		else cout << "\nStack is empty!\n";
	}

	int top()
	{
		if (!isEmpty()) return topElement->value;
		else 
		{
			cout << "\nStack is empty!\n";
			return -1;
		}
	}

	int getSize()
	{
		return size;
	}

	void empty()
	{
		while (!isEmpty())
			pop();
	}

	void flip() //task 2.b
	{
		StackElement *prev, *cur, *succ;
		prev = topElement;
		cur = prev->next_ptr;
		prev->next_ptr = nullptr;
		while (cur != nullptr)
		{
			succ = cur->next_ptr;
			cur->next_ptr = prev;
			prev = cur;
			cur = succ;
		}
		topElement = prev;
	}

};

Stack StackL(int sequence[], int size, int devider) // task1
{
	Stack stack;
	for (int i = 0; i < size; i++)
	{
		if (sequence[i] % devider == 0)
		{
			stack.push(sequence[i]);
		}
	}
	return stack;
}

class TabStack
{
public:
	static const int maxSize = 30;
	int table[maxSize];
	int topIndex;

	TabStack() : topIndex(-1) {}

	bool isEmpty()
	{
		if (topIndex < 0) return true;
		else return false;
	}

	void push(int value)
	{
		if (topIndex < maxSize)
		{
			topIndex++;
			table[topIndex] = value;
		}
		else cout << "\nYou can't put more elements on the stack!";
	}

	void pop()
	{
		if (!isEmpty())
		{
			table[topIndex] = 0;
			topIndex--;
		}
		else cout << "\nStack is empty!";
	}

	void display()
	{
		if (isEmpty()) cout << "\nStack is empty!";
		else
		{
			for (int i = topIndex; i > -1; i--)
			{
				cout << table[i] << ", ";
			}
		}
	}

	int top()
	{
		if (isEmpty())
		{
			cout << "\nStack is empty!";
			return -1;
		}
		else return table[topIndex];
	}

	int getSize()
	{
		return topIndex + 1;
	}

	void cutOut(int index) //task3
	{
		if (!isEmpty())
		{
			if (index <= topIndex)
			{
				for (int i = topIndex - index; i < topIndex; i++)
				{
					table[i] = table[i + 1];
				}
				table[topIndex] = 0;
				topIndex--;
			}
			else cout << "\nThere're not enough elements on the stack!";
		}
		else cout << "\nStack is empty!";
	}
};

class ListElement
{
public:
	int value;
	ListElement* prev;
	ListElement* next;

	ListElement(const int value) : value(value), prev(nullptr), next(nullptr) {}
	ListElement() : value(0), prev(nullptr), next(nullptr) {}
};

class List
{
public:
	int size;
	ListElement* head;
	ListElement* tail;

	List() : size(0), head(nullptr), tail(nullptr) {}

	void push_front(int value)
	{
		ListElement* newElement = new ListElement(value);
		if (head == nullptr)
		{
			head = newElement;
			tail = newElement;
		}
		else
		{
			newElement->prev = nullptr;
			newElement->next = head;
			if (head != nullptr) head->prev = newElement;
			head = newElement;
			if (tail == nullptr) tail = newElement;
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

	void push_back(int value)
	{
		ListElement* newElement = new ListElement(value);
		if (head == nullptr)
		{
			head = newElement;
			tail = newElement;
		}
		else
		{
			newElement->prev = tail;
			newElement->next = nullptr;
			if (tail != nullptr) tail->next = newElement;
			tail = newElement;
			if (head == nullptr) head = newElement;
		}
		size++;
	}

	void push_back(ListElement *newElement)
	{
		if (head == nullptr)
		{
			head = newElement;
			tail = newElement;
		}
		else
		{
			newElement->prev = tail;
			newElement->next = nullptr;
			if (tail != nullptr) tail->next = newElement;
			tail = newElement;
			if (head == nullptr) head = newElement;
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
		ListElement* ptr = head;
		while (ptr != NULL)
		{
			cout << ptr->value << ", ";
			ptr = ptr->next;
		}
	}

	int getSize()
	{
		return size;
	}

	int front()
	{
		return head->value;
	}

	int back()
	{
		return tail->value;
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
};

//I TRIEND TOO LONG TO DO THIS THAT WAY... SO I NEED TO LEAVE THIS HERE FOR MY FUTURE ME :)
//void combine(list& list1, list& list2)
//{
//	if (list2.isempty()) return;
//
//	if (list1.isempty())
//	{
//		list1 = list2;
//		list1.head = nullptr;
//		list1.tail = nullptr;
//		list1.size = 0;
//		return;
//	}
//
//	listelement* prev, * next, * add;
//	add = list2.head;
//	prev = list1.head;
//	next = prev->next;
//	while (prev != nullptr && !list2.isempty())
//	{
//		prev->next = add;
//		add->prev = prev;
//		add->next = next;
//		if (next != nullptr) next->prev = add;
//
//		list2.pop_front();
//		add = list2.head;
//		prev = next;
//		if (next != nullptr)
//		{
//			next = next->next;
//		}
//	}
//
//	while (!list2.isempty())
//	{
//		list1.push_back(list2.head);
//		list2.pop_front();
//	}
//}

void combine(List& list1, List& list2) //
{
	if (list2.isEmpty()) return;

	if (list1.isEmpty())
	{
		list1 = list2;
		list2.clean();
		return;
	}

	List temp = list1;
	list1.clean();

	while (!temp.isEmpty() && !list2.isEmpty())
	{
		list1.push_back(temp.head->value);
		list1.push_back(list2.head->value);
		temp.pop_front();
		list2.pop_front();
	}

	while (!temp.isEmpty())
	{
		list1.push_back(temp.head->value);
		temp.pop_front();
	}

	while (!list2.isEmpty())
	{
		list1.push_back(list2.head->value);
		list2.pop_front();
	}
}

class Queue
{
public:
	static const int maxSize = 30;
	int table[maxSize];
	int topIndex;

	Queue() : topIndex(-1) {}

	void push(char symbol)
	{
		topIndex++;
		table[topIndex] = symbol;
	}

	void pop()
	{
		for (int i = 0; i < topIndex; i++)
		{
			table[i] = table[i + 1];
		}
		table[topIndex] = 0;
		topIndex--;
	}

	void display()
	{
		for (int i = 0; i < topIndex+1; i++)
		{
			cout << table[i] << ", ";
		}
	}

	bool isEmpty()
	{
		if (topIndex < 0) return true;
		else return false;
	}

	void DeleteX(int x) //task5
	{
		bool same = true;
		for (int i = 0; i < topIndex + 1; i++)
		{
			if (table[i] == x)
			{
				same = false;
				for (int j = i; j < topIndex; j++)
				{
					table[j] = table[j + 1];
				}
				table[topIndex] = 0;
				topIndex--;
			}
		}
		if (same) cout << "\nThere's no element '" << x << "' in the queue!";
	}

};

int main()
{
	cout << "THERE IS A STANDARD FOR EACH DISPLAYED STACK: LEFT - TOP, RIGHT - BOTTOM\n";
	cout << "TASK 1:\n";
	srand(time(NULL));
	const int m = 30, i = 5;

	int table[m];
	for (int j = 0; j < m; j++)
	{
		int randNumber = (rand() % 30) + 1;
		table[j] = randNumber;
	}

	Stack stack1 = StackL(table, m, i);

	cout << "stack1: ";
	stack1.display();

	cout << "\n\n\nTASK 2:\n";
	cout << "a)\n"; //task 2.a
	Stack stack2;
	Stack stackTemp;
	stack2.push(1);
	stack2.push(2);
	stack2.push(3);
	stack2.push(4);
	stack2.push(5);
	cout << "stack2 before action: ";
	stack2.display();

	int size2 = stack2.getSize();
	stackTemp = stack2;
	stack2.empty();
	for (int i = 0; i < size2; i++)
	{
		stack2.push(stackTemp.top());
		stackTemp.pop();
	}

	cout << "\nstack2 after action: ";
	stack2.display();

	cout << "\nb)\n";
	Stack stack3;
	stack3.push(1);
	stack3.push(2);
	stack3.push(3);
	stack3.push(4);
	stack3.push(5);
	stack3.push(6);

	cout << "stack3 before action: ";
	stack3.display();

	stack3.flip();

	cout << "\nstack3 after action: ";
	stack3.display();

	cout << "\n\n\nTASK 3:\n";
	TabStack stack4;
	stack4.push(1);
	stack4.push(2);
	stack4.push(3);
	stack4.push(4);
	stack4.push(5);
	stack4.push(6);
	stack4.push(7);

	cout << "stack4 before action: ";
	stack4.display();

	stack4.cutOut(2);

	cout << "\nstack4 after action: ";
	stack4.display();

	cout << "\n\n\nTHERE IS A STANDARD FOR EACH DISPLAYED LIST: LEFT - FRONT, RIGHT - BACK\n";
	cout << "TASK 4:";
	List list1, list2;

	list1.push_back(1);
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(7);
	list2.push_back(2);
	list2.push_back(4);
	list2.push_back(6);
	list2.push_back(8);
	list2.push_back(9);
	list2.push_back(9);

	cout << "\nlist1 before action: ";
	list1.display();
	
	cout << "\nlist2 before action: ";
	list2.display();

	combine(list1, list2);

	cout << "\nlist1 after action: ";
	list1.display();

	cout << "\nlist2 after action: ";
	list2.display();

	cout << "\n\n\nTHERE IS A STANDARD FOR EACH DISPLAYED QUEUE: LEFT - FIRST TO OUT, RIGHT - ADDED LATEST\n";
	cout << "TASK 5:";
	Queue queue1;

	queue1.push(1);
	queue1.push(2);
	queue1.push(3);
	queue1.push(4);
	queue1.push(5);
	queue1.push(6);
	
	cout << "\nqueue1 before action: ";
	queue1.display();

	queue1.DeleteX(4);

	cout << "\nqueue1 after action: ";
	queue1.display();
	 
	return 0;
}
