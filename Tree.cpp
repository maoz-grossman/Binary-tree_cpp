#include <iostream>
#include <exception>
#include <string>
#include "Tree.hpp"
using namespace std;
using namespace ariel;

//tree constructor 
	Tree::Tree(){
		this->_size = 0;
		this->_root=NULL;
	}
//tree destructor
	Tree::~Tree(){
		destroy_tree(_root);
	}
/* insert new node to the tree with data=i.
if we succeed we will return true, else we ill return false.*/
	bool Tree::insert(int i){
			Node* nd = new Node;
		nd->data = i;
		//if the tree is empty, the new node will be the root
		if (_root == NULL) {
			_root = nd;
			_size++;
			return true;
		}
		//else, we will search for the right place in the tree
		Node *ptr = _root;
		for (;;) {
			//if the data of the new node is smaller then the current node
			if (ptr->data < i) {
				if (ptr->_right == NULL) {
					ptr->_right = nd;
					nd->_parent = ptr;
					_size++;
					return true;
				}
				else ptr = ptr->_right;
			}
			//if the data of the new node is larger then the current node
			else if (ptr->data > i) {
				if (ptr->_left == NULL) {
					ptr->_left = nd;
					nd->_parent = ptr;
					_size++;
					return true;
				}
				else ptr = ptr->_left;
			}
			//throw exception when the node is already exist in the tree
			else throw "duplicate data";
		}
	}
/*find node in the tree with data=i, start searching from the root. 
we will go right if the current node data is larger then the number we look for,else we will go left. 
we will return pointer to the right node if exists.*/
	Node* Tree::find(int i){
		Node *ptr = this->_root;
		while (ptr != NULL) {
			if (ptr->data == i)
				return ptr;
			else if (ptr->data < i) 
				ptr = ptr->_right;
			
			else
				ptr = ptr->_left;
		}
		return NULL;	
	}

	int Tree::size(){
		return this->_size;
	}
//using the find function to check if the tree contains node with data=i
	bool Tree::contains(int i){
		return (find(i) != NULL);
	}
/*if node with data=i exists in the tree we will use the find function and the removeNode function to remove it from the tree.
else we will throw an exception*/
	bool Tree::remove(int i){
		Node* Z = find(i);
		if(Z==NULL) throw std::invalid_argument("exception: remove");
		removeNode(Z);
		this->_size--;
		return true;
	}
//helper function to remove node from the tree, thanks to: http://vlib.eitan.ac.il/ds1/c_bst_delete.html
	void Tree::removeNode(Node *Z) {
		Node *X, *Y;
		 /* Y will be removed from the parent chain */
		if (!Z || Z == NULL) return;

		/* find tree successor */
		if (Z->_left == NULL || Z->_right == NULL)
			Y = Z;
		else {

			Y = Z->_right;
			while (Y->_left != NULL) Y = Y->_left;
		}

		/* X is Y's only child */
		if (Y->_left != NULL)
			X = Y->_left;
		else
			X = Y->_right;

		/* remove Y from the parent chain */
		if (X) X->_parent = Y->_parent;
		if (Y->_parent)
			if (Y == Y->_parent->_left)
				Y->_parent->_left = X;
			else
				Y->_parent->_right = X;
		else
			_root = X;

		/* Y is the node we're removing */
		/* Z is the data we're removing */
		/* if Z and Y are not the same, replace Z with Y. */
		if (Y != Z) {
			Y->_left = Z->_left;
			if (Y->_left) Y->_left->_parent = Y;
			Y->_right = Z->_right;
			if (Y->_right) Y->_right->_parent = Y;
			Y->_parent = Z->_parent;
			if (Z->_parent)
				if (Z == Z->_parent->_left)
					Z->_parent->_left = Y;
				else
					Z->_parent->_right = Y;
			else
				_root = Y;
			delete (Z);
			Z=NULL;
		}
		else {
			delete (Y);
			Y=NULL;
		}
	}

	int Tree::root(){
			if (_root==NULL)
				throw std::invalid_argument("exception: parent");
		return _root->data;
		
	}

	int Tree::parent(int i){
		 Node* ptr = find(i);
		 if (ptr == NULL)throw std::invalid_argument("exception: parent");
		 else if(ptr==_root) throw std::invalid_argument("exception: parent");
		 else
		 return ptr->_parent->data;
	}


	int Tree::left(int i){
		 Node* ptr = find(i);
		 if (ptr == NULL)throw std::invalid_argument("exception: parent");
		 if(ptr->_left==NULL) throw std::invalid_argument("exception: parent");
		return ptr->_left->data;
	}

	int Tree::right(int i){
		Node* ptr = find(i);
		 if (ptr == NULL)throw std::invalid_argument("exception: node null right");
		 if(ptr->_right==NULL) throw std::invalid_argument("exception: son of node right");
		return ptr->_right->data;
	}
//using the printBT function to print the tree
	void Tree::print(){
		printBT("", _root, false);
	} 
//recursive function to delete the tree and release memory
	void Tree::destroy_tree(Node* _Node){
		if (_Node == NULL) return;
		destroy_tree(_Node->_left);
		destroy_tree(_Node->_right);
		delete(_Node);
		_Node=NULL;
	}
	
	Node* Tree::minimum_Element(Node* mini) {
		if (mini->_left== NULL)
			return mini; 
		return minimum_Element(mini->_left);
	}
//helper function that works in recursive way to print the tree.
void Tree::printBT(const std::string& prefix, Node* node, bool isRight){
	/*thanks to:
	 https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-sing-c
	 */
		if (node != nullptr){
			cout << prefix;

			cout << (isRight ? "|--" : "\\--");

			// print the value of the node
			cout << node->data << endl;

			// enter the next tree level - left and right branch
			printBT(prefix + (isRight ? "|   " : "    "), node->_right, true);
			printBT(prefix + (isRight ? "|   " : "    "), node->_left, false);
		}
	}

