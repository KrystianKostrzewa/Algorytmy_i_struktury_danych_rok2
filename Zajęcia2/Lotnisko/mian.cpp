#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class BSTNode
{
public:
	int key;
	BSTNode* Left;
	BSTNode* Right;
	BSTNode* Parent;

	BSTNode(int key) : key(key), Left(NULL), Right(NULL), Parent(NULL) {}
	BSTNode() : key(0), Left(NULL), Right(NULL), Parent(NULL) {}

	void Insert(BSTNode* node)
	{
		if (this == NULL)
		{
			this->key = node->key;
			this->Left = NULL;
			this->Right = NULL;
			this->Parent = NULL;
		}
		else if (this->key < node->key)
		{
			if (this->Right == NULL)
			{
				this->Right = node;
				node->Parent = this;
			}
			else
			{
				this->Right->Insert(node);
			}
		}
		else
		{
			if (this->Left == NULL)
			{
				this->Left = node;
				node->Parent = this;
			}
			else
			{
				this->Left->Insert(node);
			}
		}
	}

};

BSTNode* min(BSTNode* root) //task 2a
{
	while (root->Left != NULL) root = root->Left;
	return root;
}

BSTNode* max(BSTNode* root) //task 2b
{
	while (root->Right != NULL) root = root->Right;
	return root;
}

BSTNode* successor(BSTNode* node)
{
	if (node->Parent == NULL) return NULL;
	else if (node->Right != NULL) return min(node->Right);
	else
	{
		BSTNode* nodeTmp = node->Parent;
		while (nodeTmp != NULL && nodeTmp->Left != node)
		{
			node = nodeTmp;
			nodeTmp = nodeTmp->Parent;
		}
		return nodeTmp;
	}
}

BSTNode* predecessor(BSTNode* node)
{
	if (node->Parent == NULL) return NULL;
	else if (node->Left != NULL) return max(node->Left);
	else
	{
		BSTNode* nodeTmp = node->Parent;
		while (nodeTmp != NULL && nodeTmp->Right != node)
		{
			node = nodeTmp;
			nodeTmp = nodeTmp->Parent;
		}
		return nodeTmp;
	}
}

BSTNode* Delete(BSTNode* Tree, BSTNode* DeleteNode) {
	BSTNode* y;
	if (DeleteNode->Left == nullptr || DeleteNode->Right == nullptr)
		y = DeleteNode;
	else
		y = successor(DeleteNode);
	BSTNode* x;
	if (y->Left != nullptr)
		x = y->Left;
	else
		x = y->Right;
	if (x != nullptr)
		x->Parent = y->Parent;
	if (y->Parent == nullptr)
		Tree = x;
	else if (y == y->Parent->Left)
		y->Parent->Left = x;
	else
		y->Parent->Right = x;
	if (y != DeleteNode) {
		DeleteNode->key = y->key;
	}
	return y;
}

void display_main_menu()
{
	cout << "======AIRPORT CONTROL PANEL======" << endl
		<< "Actions:" << endl
		<< "1. Display planned events." << endl
		<< "2. Add new event." << endl
		<< "3. Display recent time." << endl
		<< "0. Leave Control Panel." << endl
		<< "Choose action: ";
}

void display(BSTNode* node)
{
	if (node->Left != NULL) display(node->Left);
	if (node->key > 0 && node->key < 1000) cout << node->key << " ";
	if (node->Right != NULL) display(node->Right);
}

void display_planned_events(BSTNode* node)
{
	cout << "Planned events: ";
	if (node->Left != NULL) display(node->Left);
	if (node->key > 0 && node->key < 1000) cout << node->key << " ";
	if (node->Right != NULL) display(node->Right);
}

int recent_time()
{
	time_t currentTime = time(nullptr);
	return (currentTime) / 2 % 1000;
}

void display_recent_time()
{
	cout << "Recent time is: " << recent_time();
}

void add_new_event(BSTNode* root)
{
	int time;
	cout << "What time is the landing planned? (1-999): ";
	cin >> time;

	BSTNode* newElement = new BSTNode(time);
	root->Insert(newElement);
	if (time > 0 && time <= 999)
	{
		if (successor(newElement) == NULL && predecessor(newElement) == NULL)
		{
			if (recent_time() < newElement->key)
			{
				cout << "Reservation attempt. Time: " << time << ". ACCEPTED!";
				return;
			}
			else
			{
				cout << "Reservation attempt. Time: " << time << ". DENIED!";
				Delete(root, newElement);
			}
		}
		else if (recent_time() < newElement->key && successor(newElement)->key - newElement->key >= 3 && newElement->key - predecessor(newElement)->key >= 3)
		{
			cout << "Reservation attempt. Time: " << time << ". ACCEPTED!";
			return;
		}
		else
		{
			cout << "Reservation attempt. Time: " << time << ". DENIED!";
			Delete(root, newElement);
			return;
		}
	}
	else
	{
		cout << "Reservation attempt. Time: " << time << ". DENIED! Out of range!";
	}
}

bool continue_choice()
{
	char choice;
	while (true)
	{
		cout << "\nDo you want to continue? (y/n) ";
		cin >> choice;
		if (choice == 'y') return true;
		else if (choice == 'n') return false;
		cout << "Your choice has to be y/n!";
	}
}

void delete_expired_events(BSTNode* node, BSTNode* tree)
{
	if (node->Left != NULL) delete_expired_events(node->Left, tree);
	if (node->key > 0 && node->key < 1000 && node->key < recent_time()) Delete(tree, node);
	if (node->Right != NULL) delete_expired_events(node->Right, tree);
}

int main()
{
	BSTNode* database = new BSTNode(-3);
	BSTNode* databaseTop = new BSTNode(1002);

	database->Insert(databaseTop);

	bool start = true;
	while (start)
	{
		int action;
		display_main_menu();
		cin >> action;
		delete_expired_events(database, database);

		switch (action)
		{
		case 1:
		{
			display_planned_events(database);
			break;
		}

		case 2:
		{
			add_new_event(database);
			break;
		}

		case 3:
		{
			display_recent_time();
			break;
		}

		case 0:
		{
			cout << "Leaving Control Panel";
			start = false;
			break;
		}

		default:
		{
			cout << "There's no this option in menu.";
		}
		}

		if (start == true)
		{
			if (continue_choice() == false) break;
			system("CLS");
		}
	}

	delete database;
	delete databaseTop;
	return 0;
}
