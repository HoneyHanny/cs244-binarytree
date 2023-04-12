#include "binarytree.h"
#include <cstdlib>
#include <iostream>


// +———————————————————————————————————+
// │	[SECTION]	Node		       │
// +———————————————————————————————————+

Node::Node(int data) {
	this->data = data;
	parent = NULL;
	left = NULL;
	right = NULL;
}

Node* Node::NewNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}


// +———————————————————————————————————+
// │	[SECTION]	Binary Tree 	   │
// +———————————————————————————————————+

BinaryTree::BinaryTree() {
	std::cout << "Constructor 1 (Binary Tree)" << std::endl;
	m_Index = 0;
	Node* m_Root = NULL;
}

BinaryTree::BinaryTree(int data) {
	std::cout << "Constructor 2 (Binary Tree)" << std::endl;
	m_Index = 1;
	Node* m_Root = new Node(data);
}

void BinaryTree::Insert(int data) {
	std::cout << "Insert " << data << " (Binary Tree)" << std::endl;
}

void BinaryTree::Insert(Node* node) {
	std::cout << "Insert " << node->data << " (Binary Tree)" << std::endl;
}

bool BinaryTree::Search(int data) const {
	std::cout << "Search " << data << " (Binary Tree)" << std::endl;
	return false;
}

int BinaryTree::GetData(int pos) const {
	std::cout << "GetData " << pos << " (Binary Tree)" << std::endl;
	Node*temp = m_Root;
	Node*prev = temp;

	int i = 0;
	while (i < pos) {
		DEBUG("> ");
		if (prev == temp->left || !temp->left && temp->right != prev) {
			DEBUG("1st cond : ");
			++i;
		} else if (!temp->right && !temp->left) {
			DEBUG("2nd cond: ");
			++i;
		}
		
		DEBUG("> "); 
		if (temp->left != prev && temp->left) {			// go left
			DEBUGN("Go left "); 
			prev = temp;
			temp = temp->left;
		} else if (temp->right != prev && temp->right) { // go right
			DEBUGN("Go right "); 
			prev = temp;
			temp = temp->right;
		} else {												// go up
			DEBUGN("Go up "); 
			prev = temp;
			temp = temp->parent;
		}
	}

	return prev->data;
}

Node* BinaryTree::Remove(int data) {
	std::cout << "Remove " << data << " (Binary Tree)" << std::endl;
	return NULL;
}

void BinaryTree::Print() const {
	std::cout << "Print (Binary Tree)" << std::endl;	
	Node* temp = m_Root;
	Node* prev = temp;

	if (!m_Root)
		return;

	int printed = 0;
	while (printed < m_Index) {
		DEBUG("> ");
		// && temp->right != prev
		// 
		
		if ((prev == temp->left || !temp->left) && prev != temp->right) {
			DEBUG("1st cond : ");
			++printed;
			std::cout << temp->data << ", ";
			// DEBUGN("");
		} else if (!temp->right && !temp->left) {
			DEBUG("2nd cond: ");
			++printed;
			std::cout << temp->data << ", ";
			// DEBUGN("");
		}
		
		DEBUG("> ");
		// && prev != temp->right
		if (temp->left != prev && temp->left && prev != temp->right) {		// go left
			DEBUGN("Go left "); 
			prev = temp;
			temp = temp->left;
		} else if (temp->right != prev && temp->right) { // go right
			DEBUGN("Go right "); 
			prev = temp;
			temp = temp->right;
		} else {												// go up
			DEBUGN("Go up "); 
			prev = temp;
			temp = temp->parent;
		}

	}

	std::cout << std::endl;

}

// TODO: Make a visualizer that draws the binary tree
void BinaryTree::Visualize() const {
	std::cout << "Visualize (Binary Tree)" << std::endl;

	//
	//						12
	//			10						15
	//	  2           11          13           17
	//	     5                       14     16
	//
	//
	// determine visual width and height of tree
	// evenly spread horizontal position
	// 1st = 1/2
	// 2nd = 1/4
	// 3rd = 1/8
	// ...
	//
	// 1st |________________1/2________________|
	// 2nd |_______1/4_______________1/4_______|
	// 3rd |__1/8_______1/8______1/8______1/8__|
	//
	// last row should have a horizontal distance of 1 char
	
	
// 	int height = GetHeight();
// 	int width = GetWidth();

}

Node* BinaryTree::GetNode(int data) const {
	std::cout << "GetNode " << data << " (Binary Tree)" << std::endl;
	return NULL;
}


// +———————————————————————————————————+
// │	[SECTION]	BST				   │
// +———————————————————————————————————+
//
// NOTE: BST don't allow duplicates

BST::BST() {
	std::cout << "Constructor 1 (BST)" << std::endl;
}

BST::BST(int data) : BinaryTree(data) {
	std::cout << "Constructor 2 (BST)" << std::endl;
}

void BST::Insert(int data) {
	std::cout << "Insert " << data << " (BST)" << std::endl;
	if (Search(data))
		return;
	SetSize(GetSize() + 1);
	Node* newNode = Node::NewNode(data);
	DEBUGN(">>>");
	if (GetRoot()) {
		SetRoot(newNode);
		return;
	}

	Node* temp = GetRoot();
	// while (temp->right || temp->left) {
	for (;;) {
		DEBUGN(">>>");
		// std::cout << ">>>" << std::endl;
		if (temp->data > data) {
			if (temp->left) {
				temp = temp->left;
			} else {
				temp->left = newNode;
				newNode->parent = temp;
				return;
			}
		} else {
			if (temp->right) {
				temp = temp->right;
			} else {
				temp->right = newNode;
				newNode->parent = temp;
				return;
			}
		}
	}
}

void BST::Insert(Node* node) {
	std::cout << "Insert " << node->data << " (BST)" << std::endl;
	SetSize(GetSize() + 1);
	DEBUGN(">>>");
	// std::cout << ">>>" << std::endl;
	if (!GetRoot()) {
		SetRoot(node);
		return;
	}

	Node* temp = GetRoot();
	// while (temp->right || temp->left) {
	for (;;) {
		std::cout << ">>>" << std::endl;
		if (temp->data > node->data) {
			if (temp->left) {
				temp = temp->left;
			} else {
				temp->left = node;
				node->parent = temp;
				return;
			}
		} else {
			if (temp->right) {
				temp = temp->right;
			} else {
				temp->right = node;
				node->parent = temp;
				return;
			}
		}
	}
}

// returns true if data exists in BST
// else returns false
bool BST::Search(int data) const {
	std::cout << "Search " << data << " (BST)" << std::endl;
	Node* temp = GetRoot();
	while (temp) {
		if (temp->data == data)
			return true;
		if (data < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return false;
}

// returns position of data
int BST::GetPos(int data) const {
	std::cout << "GetPos " << data << " (Binary Tree)" << std::endl;
	Node* temp = GetRoot();
	for (int i = 0; temp; ++i) {
		if (temp->data == data)
			return i;
		if (data < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return -1;
}

// NOTE: `Remove` doesn't free the node it just return the node
// If you want to free the node to avoid memory leaks free it using: `Delete`
//
// the node is also disconnected from the tree
Node* BST::Remove(int data) {
	std::cout << "Remove " << data << " (BST)" << std::endl;
	Node* temp = GetNode(data);
	if (!temp)
		return NULL;

	if (!temp->right && !temp->left) {
	
		DEBUGN(">>> if");

		// check direction from parent
		if (temp->parent->right == temp)
			temp->parent->right = NULL;
		else
			temp->parent->left = NULL;

	} else if (!temp->right) {

		DEBUGN(">>> right == NULL");
		if (temp->parent->right == temp) {
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		} else if (temp->parent->left == temp) {
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
		}

	} else if (!temp->left) {
		
		DEBUGN(">>> left == NULL");
		if (temp->parent->right == temp) {
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
		} else if (temp->parent->left == temp) {
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
		}
	
	} else {

		// 1. move one right and left all the way
		// 2. replace the original to the leftmost
		// 3. and delete leftmost

		DEBUGN(">>> else");
		Node* leftMost = temp->right;

		DEBUG("temp->right->data = ");
		DEBUGN(temp->right->data);
		// int dirFrmPrnt;
		// if (temp->parent->right == temp)
		// 	dirFrmPrnt = RIGHT;
		// else
		// 	dirFrmPrnt = LEFT;

		// search for leftmost
		while (leftMost->left)
			leftMost = leftMost->left;

		// replace original node 
		
		// check if no left
		if (leftMost != temp->right) {// if true then has leftmost
			leftMost->parent->left = leftMost->right;
			leftMost->right->parent = leftMost->parent;
		}
	
		leftMost->parent = temp->parent;

		if (temp == GetRoot()) { // if temp is root
			
			SetRoot(leftMost);

		} else {

			// check direction from temp->parent
			// if (dirFrmPrnt == RIGHT)
			if (temp->parent->right == temp)
				temp->parent->right = leftMost;
			else
				temp->parent->left = leftMost;

		}

		// leftmost point to temp left child
		leftMost->left = temp->left;
		if (leftMost != temp->right) {
			leftMost->right = temp->right;
			temp->right->parent = leftMost;
		}
		
		// left child of temp point to leftMost
		if (temp->left)
			temp->left->parent = leftMost;

	}

	temp->parent = NULL;
	temp->right = NULL;
	temp->left = NULL;

	SetSize(GetSize() - 1);
	return temp;
}

// deletes a node from the tree
// void BST::Delete(int data) {
// 	std::cout << "Delete " << data << " (BST)" << std::endl;
// 	Node* temp = GetNode(data);
// 	if (!temp)
// 		return;
// 
// 	if (!temp->right && !temp->left) {
// 	
// 		DEBUGN(">>> if");
// 
// 		// check direction from parent
// 		if (temp->parent->right == temp)
// 			temp->parent->right = NULL;
// 		else
// 			temp->parent->left = NULL;
// 
// 	} else if (temp->right) {
// 
// 		DEBUGN(">>> right == NULL");
// 		if (temp->parent->right == temp) {
// 			temp->parent->right = temp->left;
// 			temp->left->parent = temp->parent;
// 		} else if (temp->parent->left == temp) {
// 			temp->parent->left = temp->left;
// 			temp->left->parent = temp->parent;
// 		}
// 
// 	} else if (!temp->left) {
// 		
// 		DEBUGN(">>> left == NULL");
// 		if (temp->parent->right == temp) {
// 			temp->parent->right = temp->right;
// 			temp->right->parent = temp->parent;
// 		} else if (temp->parent->left == temp) {
// 			temp->parent->left = temp->right;
// 			temp->right->parent = temp->parent;
// 		}
// 	
// 	} else {
// 
// 		// 1. move one right and left all the way
// 		// 2. replace the original to the leftmost
// 		// 3. and delete leftmost
// 
// 		DEBUGN(">>> else");
// 		Node* leftMost = temp->right;
// 
// 		DEBUG("temp->right->data = ");
// 		DEBUGN(temp->right->data);
// 		// int dirFrmPrnt;
// 		// if (temp->parent->right == temp)
// 		// 	dirFrmPrnt = RIGHT;
// 		// else
// 		// 	dirFrmPrnt = LEFT;
// 
// 		// search for leftmost
// 		while (leftMost->left)
// 			leftMost = leftMost->left;
// 
// 		// replace original node 
// 		
// 		// check if no left
// 		if (leftMost != temp->right) {// if true then has leftmost
// 			leftMost->parent->left = leftMost->right;
// 			leftMost->right->parent = leftMost->parent;
// 		}
// 		
// 		leftMost->parent = temp->parent;
// 
// 		if (temp == GetRoot()) { // if temp is root
// 			
// 			SetRoot(leftMost);
// 
// 		} else {
// 
// 			// check direction from temp->parent
// 			// if (dirFrmPrnt == RIGHT)
// 			if (temp->parent->right == temp)
// 				temp->parent->right = leftMost;
// 			else
// 				temp->parent->left = leftMost;
// 
// 		}
// 
// 		// leftmost point to temp left child
// 		leftMost->left = temp->left;
// 		if (leftMost != temp->right) {
// 			leftMost->right = temp->right;
// 			temp->right->parent = leftMost;
// 		}
// 		
// 		// left child of temp point to leftMost
// 		if (temp->left)
// 			temp->left->parent = leftMost;
// 
// 	}
// 
// 	temp->parent = NULL;
// 	temp->right = NULL;
// 	temp->left = NULL;
// 
// 	SetSize(GetSize() - 1);
// 	free(temp);
// }

Node* BST::GetNode(int data) const {
	std::cout << "Search " << data << " (BST)" << std::endl;
	Node* temp = GetRoot();
	while (temp) {
		if (temp->data == data)
			return temp;
		if (data < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return NULL;
}

// Node* BST::Search(int data) {
// 	std::cout << "Search " << data << " (BST)" << std::endl;
// 	Node* temp = GetRoot();
// 	while (temp) {
// 		if (temp->data == data)
// 			return temp;
// 		if (data < temp->data)
// 			temp = temp->left;
// 		else
// 			temp = temp->right;
// 	}
// 
// 	return NULL;
// }
