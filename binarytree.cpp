#include "binarytree.h"


// +———————————————————————————————————+
// │	[SECTION]	Node		       │
// +———————————————————————————————————+

Node::Node(int data) {
	this->data = data;
	height = 1;
	parent = NULL;
	left = NULL;
	right = NULL;
}

Node* Node::NewNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->height = 1;
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void Node::SetHeight() {
	if (left && right) {
		height = std::max(left->height, right->height) + 1; 
		return;
	}

	int hLeft, hRight;

	if (left)
		hLeft = left->height;
	else
		hLeft = 0;

	if (right)
		hRight = right->height;
	else
		hRight = 0;

	height = std::max(hLeft, hRight) + 1;
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
	Node* m_Root = Node::NewNode(data);
	DEBUGN("m_Root->data = " << m_Root->data);
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
		} else {										// go up
			DEBUGN("Go up "); 
			prev = temp;
			temp = temp->parent;
		}
	}

	return prev->data;
}

Node* BinaryTree::Remove(int pos) {
	std::cout << "Remove " << pos << " (Binary Tree)" << std::endl;
	return NULL;
}

void BinaryTree::Print() const {
	std::cout << "Print (Binary Tree)" << std::endl;
	if (!m_Root)
		return;
	Node* temp = m_Root;
	Node* prev = temp;

	int printed = 0;
	while (printed < m_Index) {
		DEBUG("> ");
		
		if ((prev == temp->left || !temp->left) && prev != temp->right) {
			DEBUG("1st cond : ");
			++printed;
			std::cout << temp->data << ", ";
		} else if (!temp->right && !temp->left) {
			DEBUG("2nd cond: ");
			++printed;
			std::cout << temp->data << ", ";
		}
		
		DEBUG("> ");
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
	DEBUGN("GetNode " << data << " (Binary Tree)");
	return NULL;
}

void BinaryTree::UpdateHeight(Node* node) {
	while (node) {
		node->SetHeight();
		node = node->parent;
	}
}

void BinaryTree::RotateRight(Node* parent) {
	Node* child = parent->left;
	
	parent->left = child->right;
	child->parent = parent->parent;
	child->right = parent;
	parent->parent = child;
}

void BinaryTree::RotateLeft(Node* parent) {
	Node* child = parent->right;

	parent->right = child->left;
	child->parent = parent->parent;
	child->left = parent;
	parent->parent = child;

}

// rotate two nodes
// void BinaryTree::RotateNode(Node* node, Direction dir) {
// 	DEBUGN("RotateNode " << data << " (Binary Tree)");
// 
// 	if (dir == Direction::Right) {
// 		RotateRight(node);
// 	} else {
// 		RotateLeft(node);
// 	}
// }

// z y x
//
//		+-b-+
//		|	|
//		a	c
//
//	ZL ZR ZZL ZZR
//	rotates 3 nodes
void BinaryTree::TrinodeRestructure(Node* node) {
	DEBUGN("TrinodeRestructure " << data << " (Binary Tree)");
	Direction dir1, dir2;
	Node* child;

	if (node->left->height > node->right->height) {
		dir1 = Direction::Left;
		child = node->left;
	} else {
		dir1 = Direction::Right;
		child = node->right;
	}

	if (child->left->height > child->right->height)
		dir2 = Direction::Left;
	else
		dir2 = Direction::Right;
	
	if (dir1 == Direction::Left && dir2 == Direction::Left) // ZR 
		ZigLeft(node);
	else if (dir1 == Direction::Right && dir2 == Direction::Right) // ZL
		ZigRight(node);
	else if (dir1 == Direction::Left && dir2 == Direction::Right) // ZZR
		ZigZagRight(node);
	else if (dir1 == Direction::Right && dir2 == Direction::Left) // ZZL
		ZigZagLeft(node);
}

void BinaryTree::ZigLeft(Node* z) {
	DEBUGN("ZigLeft " << z->data << " (Binary Tree)");
	Node* y = z->right;

	z->left = y->right;
	y->right = z;
	y->parent = z->parent;
	z->parent = y;
}

void BinaryTree::ZigRight(Node* z) {
	DEBUGN("ZigRight " << z->data << " (Binary Tree)");
	Node* y = z->left;

	z->right = y->left;
	y->left = z;
	y->parent = z->parent;
	z->parent = y;
}

void  BinaryTree::ZigZagLeft(Node* z) {
	DEBUGN("ZigZagLeft " << z->data << " (Binary Tree)");
	Node* y = z->right;
	Node* x = y->left;

	y->left = x->right;
	x->right = y;
	x->parent = y->parent;
	y->parent = x;
	ZigRight(z);
}

void BinaryTree::ZigZagRight(Node* z) {
	DEBUGN("ZigZagRight " << z->data << " (Binary Tree)");
	Node* y = z->left;
	Node* x = y->right;

	y->right = x->left;
	x->left = y;
	x->parent = y->parent;
	y->parent = x;
	ZigLeft(z);
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

// void BST::Insert(int data) {
// 	std::cout << "Insert " << data << " (BST)" << std::endl;
// 	if (Search(data))
// 		return;
// 	SetSize(GetSize() + 1);
// 	Node* newNode = Node::NewNode(data);
// 	DEBUGN("Insert >>>");
// 	if (!GetRoot()) {
// 		SetRoot(newNode);
// 		return;
// 	}
// 
// 	Node* temp = GetRoot();
// 	for (;;) {
// 		DEBUGN("Insert 2 >>>");
// 		if (temp->data > data) {
// 			if (temp->left) {
// 				temp = temp->left;
// 			} else {
// 				temp->left = newNode;
// 				newNode->parent = temp;
// 				SetHeight(temp);
// 				return;
// 			}
// 		} else {
// 			if (temp->right) {
// 				temp = temp->right;
// 			} else {
// 				temp->right = newNode;
// 				newNode->parent = temp;
// 				SetHeight(temp);
// 				return;
// 			}
// 		}
// 	}
// }

void BST::Insert(Node* node) {
	std::cout << "Insert " << node->data << " (BST)" << std::endl;
	SetSize(GetSize() + 1);
	DEBUGN(">>>");
	if (!GetRoot()) {
		SetRoot(node);
		return;
	}

	Node* temp = GetRoot();
	for (;;) {
		DEBUGN(">>>");
		if (temp->data > node->data) {
			if (temp->left) {
				temp = temp->left;
			} else {
				temp->left = node;
				node->parent = temp;
				UpdateHeight(temp);
				return;
			}
		} else {
			if (temp->right) {
				temp = temp->right;
			} else {
				temp->right = node;
				node->parent = temp;
				UpdateHeight(temp);
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
	DEBUGN("Search check temp");
	while (temp) {
		DEBUG("Search >>>");
		if (temp->data == data)
			return true;
		DEBUGN("Search <<<");
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

	if (!temp->right && !temp->left) { // if no child 
	
		DEBUGN(">>> if");

		// check direction from parent
		if (temp->parent->right == temp) {
			temp->parent->right = NULL;
		} else {
			temp->parent->left = NULL;
		}

		UpdateHeight(temp->parent);

	} else if (!temp->right) { // if right = NULL 

		DEBUGN(">>> right == NULL");
		if (temp->parent->right == temp) {
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		} else if (temp->parent->left == temp) {
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
		}

		UpdateHeight(temp->parent);

	} else if (!temp->left) { // if left = NULL 
		
		DEBUGN(">>> left == NULL");
		if (temp->parent->right == temp) {
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
		} else if (temp->parent->left == temp) {
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
		}

		UpdateHeight(temp->parent);
	
	} else { // if has two child

		// 1. move one right and left all the way
		// 2. replace the original to the leftmost
		// 3. and delete leftmost

		DEBUGN(">>> else");
		Node* leftMost = temp->right;
		Node* lmParent;

		DEBUGN("temp->right->data = " << temp->right->data);

		// search for leftmost
		while (leftMost->left)
			leftMost = leftMost->left;

		// replace original node
		
		// check if no left
		if (leftMost != temp->right) { // if true then has leftmost
			leftMost->parent->left = leftMost->right;
			leftMost->right->parent = leftMost->parent;
		}
		// found leftmost
		lmParent = leftMost->parent;
	
		leftMost->parent = temp->parent;

		if (temp == GetRoot()) { // if temp is root
			
			SetRoot(leftMost);

		} else { // if temp is not root

			// check direction from temp->parent
			if (temp->parent->right == temp)
				temp->parent->right = leftMost;
			else
				temp->parent->left = leftMost;

		}

		// SWAP

		// leftmost point to temp left child
		leftMost->left = temp->left;
		if (leftMost != temp->right) { // if leftmost is not a child of temp
			leftMost->right = temp->right;
			temp->right->parent = leftMost;
		}
		
		// left child of temp point to leftMost
		if (temp->left)
			temp->left->parent = leftMost;

		UpdateHeight(lmParent);

	}

	temp->parent = NULL;
	temp->right = NULL;
	temp->left = NULL;

	SetSize(GetSize() - 1);
	return temp;
}

Node* BST::GetNode(int data) const {
	std::cout << "GetNode " << data << " (BST)" << std::endl;
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


// +———————————————————————————————————+
// │	[SECTION]	AVL			       │
// +———————————————————————————————————+

AVL::AVL() {
	DEBUGN("Constructor 1 (AVL)");
}

AVL::AVL(int data) : BST(data) {
	DEBUGN("Constructor 2 (AVL)");
}

void AVL::Insert(Node* node) {
	DEBUGN("Insert " << node->data << " (AVL)");
	SetSize(GetSize() + 1);
	DEBUGN(">>>");
	if (!GetRoot()) {
		SetRoot(node);
		return;
	}

	Node* temp = GetRoot();
	for (;;) {
		DEBUGN(">>>");
		if (temp->data > node->data) {
			if (temp->left) {
				temp = temp->left;
			} else {
				temp->left = node;
				node->parent = temp;
				BalanceTree(node);
				return;
			}
		} else {
			if (temp->right) {
				temp = temp->right;
			} else {
				temp->right = node;
				node->parent = temp;
				BalanceTree(node);
				return;
			}
		}
	}
}

// NOTE: `Remove` doesn't free the node it just return the node
// If you want to free the node to avoid memory leaks free it using: `Delete`
//
// the node is also disconnected from the tree
Node* AVL::Remove(int data) {
	DEBUGN("Remove " << data << " (AVL)");
	Node* temp = GetNode(data);
	if (!temp)
		return NULL;

	if (!temp->right && !temp->left) { // if both child is null 
	
		DEBUGN(">>> left && right == NULL");

		// check direction from parent
		if (temp->parent->right == temp) {
			temp->parent->right = NULL;
		} else {
			temp->parent->left = NULL;
		}

		BalanceTree(temp->parent);

	} else if (!temp->right) { // if right = NULL 

		DEBUGN(">>> right == NULL");
		if (temp->parent->right == temp) {
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		} else if (temp->parent->left == temp) {
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
		}


		BalanceTree(temp->parent);

	} else if (!temp->left) { // if left = NULL 
		
		DEBUGN(">>> left == NULL");
		if (temp->parent->right == temp) {
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
		} else if (temp->parent->left == temp) {
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
		}

		BalanceTree(temp->parent);
	
	} else { // if has two child

		// 1. move one right and left all the way
		// 2. replace the original to the leftmost
		// 3. and delete leftmost

		DEBUGN(">>> else");
		Node* leftMost = temp->right;
		Node* lmParent;

		DEBUGN("temp->right->data = " << temp->right->data);

		// search for leftmost
		while (leftMost->left)
			leftMost = leftMost->left;

		// replace original node
		
		// check if no left
		if (leftMost != temp->right) { // if true then has leftmost
			leftMost->parent->left = leftMost->right;
			leftMost->right->parent = leftMost->parent;
		} // found leftmost

		// save leftmost parent for later
		lmParent = leftMost->parent;
	
		leftMost->parent = temp->parent;

		if (temp == GetRoot()) { // if temp is root
			
			SetRoot(leftMost);

		} else { // if temp is not root

			// check direction from temp->parent
			if (temp->parent->right == temp)
				temp->parent->right = leftMost;
			else
				temp->parent->left = leftMost;

		}

		// SWAP

		// leftmost point to temp left child
		leftMost->left = temp->left;
		if (leftMost != temp->right) { // if leftmost is not a child of temp
			leftMost->right = temp->right;
			temp->right->parent = leftMost;
		}
		
		// left child of temp point to leftMost
		if (temp->left)
			temp->left->parent = leftMost;

		BalanceTree(lmParent);

	}

	temp->parent = NULL;
	temp->right = NULL;
	temp->left = NULL;

	SetSize(GetSize() - 1);
	return temp;
}

void AVL::BalanceTree(Node* node) {
	while (node) {
		int diff = abs(node->left->height - node->right->height);

		// Rebalance this shit
		// curr node is z
		// its child is y
		// its grandchild is x
		// identify if ZL ZR ZZL ZZR
		// set to a, b, c order
		if (diff > 1) { 
						
			Node* z = node;
			Node* y;
			if (node->left->height > node->right->height)
				y = node->left;
			else
				y = node->right;
			Node* x;
			if (y->left->height > y->right->height)
				x = y->left;
			else
				x = y->right;

			TrinodeRestructure(node);		
		
		}
		node->SetHeight();
		node = node->parent;
	}
}
