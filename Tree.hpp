#include <string>
namespace ariel{

struct Node{
	int data;
	Node* _left=NULL;
	Node* _right=NULL;
	Node* _parent=NULL;
};

class Tree{
public:
	Tree();
	~Tree();
	
	
	bool insert(int);
	int size();
	bool contains(int);
	bool remove(int);
	int root();
	int parent(int);
	int left(int);
	int right(int);
	void removeNode(ariel::Node*);
	void print(); 
	

private:
	void printBT(const std::string&, Node*, bool);
	void destroy_tree(ariel::Node*);
	ariel::Node* minimum_Element(ariel::Node*);
	ariel::Node *find(int);
	ariel::Node *_root;
	int _size;
};
}

