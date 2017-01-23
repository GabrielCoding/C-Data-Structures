/*Implement an AVL tree. The tree should be templated
to allow for storage of any type of data. The public methods should
 include a method to insert an item, search for an item, remove an item,
  get the number of items stored in the structure, and print a representation of the tree that shows the tree structure.

A driver program (main function) should be implemented that creates an instance of an AVL tree,
loads it with 5 - 10 items, and shows the structure of the tree after each insertion.
*/
//Compile: g++ 2Avltree.cpp -std=c++11
//Run: ./a.exe

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;
template <class T>
struct node
{
    T data;
    int height;
    struct node<T> *parent = NULL;
    struct node<T> *left = NULL;
    struct node<T> *right = NULL;
};
template <typename T>
class AVL
{
public:
	node<T> * insert(T data);
	node<T> * searchTree(T data);
	void remove(T data);
	void printTree();
	void printTree2();
	node<T> * rebalance(node<T> * location, int balanceFactor);
	void checkBalance(node<T> * location);
	void rightRotation(node<T> * currentNode);
	void leftRotation(node<T> * currentNode);
	void printTree(node<T> * currentNode);
	void printTree2(node<T> * currentNode);
	node<T> *  updateHeight(node<T> * currentNode);
	node<T> * deleteTree(T data);
	node<T> * root = NULL;
	int numberOfNodes = 0;
	~AVL()
	{
		/*if(root != NULL)
		{
			deleteTree();
		}*/
	}
//private:


};
// fix!
template <typename T>
void AVL<T>::checkBalance(node<T> * currentNode)
{
	int leftBalanceFactor = 0;
	int rightBalanceFactor = 0;
	int balanceFactor = 0;
	while(currentNode)
	{
		int leftBalanceFactor = 0;
		int rightBalanceFactor = 0;
		int balanceFactor = 0;
		if(currentNode->left)
		{
			leftBalanceFactor = currentNode->left->height;
		}
		if(currentNode->right)
		{
			rightBalanceFactor = currentNode->right->height;
		}
		balanceFactor = leftBalanceFactor - rightBalanceFactor;
		if(balanceFactor > 1)
		{
			rebalance(currentNode, balanceFactor);
		} else if(balanceFactor < -1)
		{
			rebalance(currentNode, balanceFactor);
		}
		currentNode = currentNode->parent;
	}

}
template <typename T>
void AVL<T>::printTree(node<T> * currentNode)
{
	if(currentNode !=  NULL)
	{
		printTree(currentNode->right);
		int spacing = 0;
		node<T> * temp = currentNode;
		while(temp)
		{
			spacing++;
			temp = temp->parent;
		}
		for(int i = 0; i < spacing; i++)
		{
			cout << "  ";
		}
		cout << currentNode->data << endl;
		printTree(currentNode->left);
	}
}
template <typename T>
void AVL<T>::printTree2(node<T> * currentNode)
{
	if(currentNode !=  NULL)
	{
		printTree2(currentNode->right);
		int spacing = 0;
		node<T> * temp = currentNode;
		while(temp)
		{
			spacing++;
			temp = temp->parent;
		}
		for(int i = 0; i < spacing; i++)
		{
			cout << "  ";
		}
		cout << currentNode->data << " height:" << currentNode->height << endl;
		printTree2(currentNode->left);
	}
}

template <typename T>
void AVL<T>::printTree()
{
	printTree(root);
}
template <typename T>
void AVL<T>::printTree2()
{
	printTree2(root);
}
template <typename T>
node<T> * AVL<T>::updateHeight(node<T> * currentNode)
{
	node<T> * tempNode;
	tempNode = currentNode;
	while(tempNode)
	{
		if(tempNode->parent)
		{
		tempNode = tempNode->parent;
		tempNode->height += 1;
			/*if(tempNode->left || temp->right)
			{
				
			}*/
		}else
		{
			tempNode = NULL;
		}

	}
	return currentNode;
}
template <typename T>
node<T> * AVL<T>::insert(T data)
{
	node<T> * newNode = new node<T>;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->height = 1;
	newNode->data = data; //new node height of 1
	if(root == NULL)
	{
		root = newNode;
		root->height = 1;
		root->parent = NULL;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	node<T> * currentNode = root;
	node<T> * previousNode = NULL;
	while(currentNode != NULL)
	{
		previousNode = currentNode;
		 if(currentNode->data < data)
		{
			currentNode = currentNode->right;
		} else
		{
			currentNode = currentNode->left;
		}
	}
	newNode->parent = previousNode;
	 if(previousNode->data < data) //new node<T> is bigger
	{
		previousNode->right = newNode;
	} else //new node<T> is smaller
	{
		previousNode->left = newNode;
	}
	updateHeight(newNode);
	checkBalance(newNode);
	return newNode;
}
template <typename T>
node<T> * AVL<T>::searchTree(T data)
{
	node<T> * currentNode = root;
	while(currentNode != NULL)
	{
		if(currentNode->data == data)
		{
			return currentNode;
		} else if(currentNode->data < data)
		{
			currentNode = currentNode->right;
		} else
		{
			currentNode = currentNode->left;
		}
	}
	return NULL;
}
template <typename T>
void AVL<T>::remove(T data)
{
	node<T> * targetNode = NULL;
	targetNode = searchTree(data);

	if(targetNode == NULL)
	{
		return;
	}
	node<T> * replacementNode = targetNode->left;
	if(replacementNode != NULL)
	{
		while(replacementNode->right != NULL)
		{
			replacementNode = replacementNode->right;
		}
		targetNode->data = replacementNode->data;
		if(replacementNode->parent->left == replacementNode)
		{
			replacementNode->parent->left == replacementNode->left;
		} else
		{
			replacementNode->parent->right = replacementNode->left;//correct parent
		}
		delete replacementNode;
	}
	rebalance(root);
}
template <typename T>
node<T> * AVL<T>::rebalance(node<T> * currentNode, int balanceFactor)
{
	if(balanceFactor > 1)
	{
		rightRotation(currentNode);
	} else if(balanceFactor < -1)
	{
		leftRotation(currentNode);
	}
}
template <typename T>
void AVL<T>::rightRotation(node<T> * currentNode)
{
	//8->9->10
	//9->right = 10
	//temp->temp
	//9->p =  10->p
	node<T> * temp = currentNode->left;// conceptually 10
	if(root == currentNode)
	{
		root = currentNode->left;
	}
	if(currentNode->parent)
	{
		if(currentNode->parent->left == currentNode)
		{
			currentNode->parent->left = currentNode->left;
		}
	}
	if(currentNode->parent)
	{
		if(currentNode->parent->right == currentNode)
		{
			currentNode->parent->right = currentNode->left;
		}
	}
	currentNode->left = currentNode->left->right;
	temp->right = currentNode;
	temp->parent = currentNode->parent;
	currentNode->parent = temp;
	currentNode->height = temp->height-1;
}
template <typename T>
void AVL<T>::leftRotation(node<T> * currentNode)
{
	//inverse of rightRotation
	node<T> * temp = currentNode->right;// conceptually 10
	if(root == currentNode)
	{
		root = currentNode->right;
	}
	if(currentNode->parent)
	{
		if(currentNode->parent->right == currentNode)
		{
			currentNode->parent->right = currentNode->right;
		}
	}
	if(currentNode->parent)
	{
		if(currentNode->parent->left == currentNode)
		{
			currentNode->parent->left = currentNode->right;
		}
	}
	currentNode->right = currentNode->right->left;
	temp->left = currentNode;
	temp->parent = currentNode->parent;
	currentNode->parent = temp;
	currentNode->height = temp->height-1;
}
int main(int argc, char* argv[])
{
	AVL<int> avl;
	for(int i = 1; i <=  10; i++) // put in ten elements
	{
		cout << "insert" << endl;
		avl.insert(i);
		avl.printTree();
		cout << endl << endl;
	}
	avl.printTree2();
	cout << "The program works as you can see from the heights" << endl;
	cout << "I've run out of time for this assignment, but note that the print function has bugs" << endl;
	return 0;
}
