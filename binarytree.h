#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstdlib>


// uncomment the line below to enable debug mode
// #define NDEBUG
#ifndef NDEBUG
#define DEBUG(x) 
#define DEBUGN(x)
#else
#define DEBUG(x) do { std::cerr << x; } while (0)
#define DEBUGN(x) do { std::cerr << x << std::endl; } while (0)
#endif

#define LEFT 0
#define RIGHT 1
#define PARENT 2

struct Node {
	int data;
	Node* parent;
	Node* left;
	Node* right;

	Node(int data);

	static Node* NewNode(int data);
};

class BinaryTree {
private:
	int m_Index;
	Node* m_Root;
	int m_Height;

public:
	BinaryTree();
	BinaryTree(int data);

	virtual void Insert(int data);
	virtual void Insert(Node* node);
	virtual bool Search(int data) const;
	virtual int GetData(int pos) const;
	virtual Node* Remove(int pos);
	inline virtual void Delete(int pos) { free(Remove(pos)); }
	inline int GetSize() const { return m_Index; }
	inline int GetHeight() const { return m_Height; }
	void Print() const;
	void Visualize() const;
	inline int GetRootData() const { return m_Root->data; }

protected:
	inline Node* GetRoot() const { return m_Root; }
	virtual Node* GetNode(int pos) const;
	inline void SetRoot(Node* root) { m_Root = root; }
	inline void SetSize(int size) { m_Index = size; }
	inline void SetHeight(int height) { m_Height = height; }
	
};

class BST : public BinaryTree {
public:
	BST();
	BST(int data);

	void Insert(int data) override;
	void Insert(Node* node) override;
	bool Search(int data) const override;
	int GetPos(int data) const;
	Node* Remove(int data) override;
	inline void Delete(int data) override { free(Remove(data)); }

protected:
	Node* GetNode(int data) const override;

};

#endif // BINARYTREE_H
