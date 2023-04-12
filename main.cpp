#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "binarytree.h"

void DisplayMenu(BST* bst) {

	int size = bst->GetSize();
	std::cout << "[1] Insert \t\tSize: " << size << std::endl;
	if (size == 0)
		std::cout << "[2] Delete \t\tRoot: NULL" << std::endl;
	else 
		std::cout << "[2] Delete \t\tRoot: " << bst->GetRootData() << std::endl;
	std::cout << "[3] Search " << std::endl;
	std::cout << "[4] Position " << std::endl;
	std::cout << "[5] Print " << std::endl;
	std::cout << "[6] Exit " << std::endl;

}

int main(void) {

	BST* bst = new BST();

	char op;
	int data;

	bst->Insert(4);
	bst->Insert(2);
	bst->Insert(1);
	bst->Insert(3);
	bst->Insert(7);
	bst->Insert(5);
	bst->Insert(6);
	bst->Insert(10);
	bst->Insert(8);
	bst->Insert(9);

	do {

		DisplayMenu(bst);
		op = getch();
		std::cout << op << ": ";

		switch (op) {
			case '1':
				std::cin >> data;
				bst->Insert(data);
				break;

			case '2':
				std::cin >> data;
				bst->Delete(data);
				break;

			case '3':
				std::cin >> data;
				bst->Search(data);
				break;

			case '4':
				std::cin >> data;
				std::cout << bst->GetPos(data) << std::endl;
				break;

			case '5':
				std::cout << std::endl;
				bst->Print();
				break;
		}

		system("pause");
		system("cls");
		fflush(stdout);

	} while (op != '6');

	std::cout << "Exiting" << std::endl;
	delete bst;

	return 0;
}
