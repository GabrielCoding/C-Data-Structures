#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "adaptiveHuffman.h"
#include <stdlib.h>
using namespace std;

struct node
{
	node * parent = NULL;
	node * left = NULL;
	node *	right = NULL;
	node * leftChild = NULL;
	node * rightChild = NULL;
	string * alphabet = NULL;
	int weight =  0;
	int height = 0;
};
class AdaptiveHuffman
{
public:
	string * alphabet;
	node * root = NULL;
	void encode(string *msg);
	void decode(string *msg);
	void populateList(string *alphabet);
    void insertNodePopulate(string * tempSymbol);
    void printList();
    void sortList();
    void makeTree();
    string * getEncode(char * symbol);
	AdaptiveHuffman(string  *alphabet)
	{
		this->alphabet = alphabet;
	};
	//~AdaptiveHuffman();

};
void AdaptiveHuffman::insertNodePopulate(string * newSymbol)
{
    node * currentNode;
    node * previousNode;
    int counter = 0;
    int tempWeight = 0;
    string * symbol = new string();
    string * weight = new string();
    //separate the symbol and the number
    string::iterator i;
    for(i = newSymbol->begin(); i < newSymbol->end(); i++)
    {
        if(counter == 0)
        {
            char * tempChar = new char(*i);
            *symbol += *tempChar;
            counter++;
        } else
        {
            char * tempChar = new char(*i);
            *weight += *tempChar;
        }
    }
    //now turn the string of numbers into an int for weight
    tempWeight = atoi(weight->c_str());
    if(root == NULL)
    {
        root = new node;
        root->alphabet = new string(*symbol);
        root->right = new node;
        root->right->alphabet = new string(*symbol);
        root->right->left = root;
        root->right->weight = tempWeight;

    } else
    {
        currentNode = root;
        previousNode = currentNode;
        while(currentNode && (currentNode->alphabet->compare(*newSymbol) != 0))
        {
            previousNode = currentNode;
            currentNode = currentNode->right;
        }
        if(currentNode)
        {
            currentNode->weight += tempWeight;
        } else
        {
            previousNode->right = new node;
            previousNode->right->alphabet = symbol;
            previousNode->right->left = previousNode;
            previousNode->right->weight = tempWeight;
            root->alphabet->append(*symbol);
        }
    }
}
void AdaptiveHuffman::populateList(string * alphabet)
{
    string * tempSymbol = new string();
    string::iterator i;
    for(i = alphabet->begin(); i < alphabet->end(); i++)
    {
        if(*i != '~' )
        {
            char * tempChar = new char(*i);
            *tempSymbol += *tempChar;
        } else
        {
            insertNodePopulate(tempSymbol);
            *tempSymbol = "";
        }

    }
    sortList();
    makeTree();
}
void AdaptiveHuffman::printList()
{
    node * currentNode = root;
    while(currentNode)
    {
        cout << *currentNode->alphabet << " " << currentNode->weight << endl;
        currentNode = currentNode->right;
    }
}
void AdaptiveHuffman::sortList()
{
    node * currentNode = root->right;
    node * previousNode =  currentNode;
    while(currentNode)
    {
        previousNode = currentNode;
        if(currentNode->right)
        {
            if(currentNode->right->weight > currentNode->weight)
            { 
                currentNode->right->left = currentNode->left;
                currentNode->left->right = currentNode->right;
                currentNode->right = currentNode->right->right;
                currentNode->left = currentNode->left->right;
                currentNode->left->right = currentNode;
				if(currentNode->right)
				{
					currentNode->right->left = currentNode;
				}
                currentNode = root;
            }
        }
        currentNode = currentNode->right;
    }
}
void AdaptiveHuffman::makeTree()
{
    int flipFlop = 1;
    int toParent = 1;
    if(root->right == NULL)
    {
        return;
    }
    node * currentNode = root->right;
    node * tempNode = currentNode;
    while(currentNode)
    {
        tempNode = currentNode;
        for(int i = 0; i < toParent; i++)
        {
            tempNode = tempNode->left;
        }
        if(flipFlop == 1)
        {
            tempNode->leftChild = currentNode;
            flipFlop++;
			toParent++;
        } else
        {
            tempNode->rightChild = currentNode;
            flipFlop--;
        }
        currentNode->parent = tempNode;
        currentNode = currentNode->right;
    }
}
void AdaptiveHuffman::encode(string * msg)
{
    string * encodedMsg = new string();
    string * addToEncode = new string();
    string * tempSymbol = new string();
    string::iterator i;
    for(i = msg->begin(); i < msg->end(); i++)
    {
        char * tempChar = new char(*i);
        addToEncode = getEncode(tempChar);
        *encodedMsg += *addToEncode;
    }
    cout << *encodedMsg << endl;

    ofstream out("outputEncoded.txt");
    out << *encodedMsg;
    out.close();
}
string * AdaptiveHuffman::getEncode(char * symbol)
{
    string * encode = new string();
    node * currentNode = root->right;
    while(currentNode && *currentNode->alphabet->c_str() != *symbol)
    {
        if(currentNode == NULL)
        {
            return encode;
        }
        currentNode = currentNode->right;
    }
    while(currentNode != root)
    {
        if(currentNode->parent->leftChild ==  currentNode)
        {
            *encode += "0";
        } else if(currentNode->parent->rightChild == currentNode)
        {
            *encode += "1";
        }
        currentNode = currentNode->parent;
    }
    *encode += "~";
    return encode;
}
void AdaptiveHuffman::decode(string * msg)
{
	string::iterator i;
	string * decodedMsg = new string();
	string * tempSymbol = new string();
    int counter = 0;
	int direction = 2;// something not 1 or 0 for initialization
	node * currentNode = root;
	for(i = msg->begin(); i < msg->end(); i++)
	{
		if(*i != '~')
		{
			char * tempChar = new char(*i);
			direction = *tempChar - '0';
			if(direction == 0)
			{
				currentNode = currentNode->leftChild;
			} else if(direction == 1)
			{
				currentNode = currentNode->rightChild;
				if(currentNode == NULL)
				{
					cout << "encountered NULL" << endl;
				}
			}
			
		} else
		{
            counter++;
			*decodedMsg = *decodedMsg + *currentNode->alphabet;
			direction = 2;
			currentNode = root;
		}
	}
	cout << endl << endl << *decodedMsg << endl << endl;
	ofstream out("outputDecoded.txt");
    out << *decodedMsg;
    out.close();
}