#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class treeNode
{
public:
	vector<int> keys;
	vector<treeNode*> c;
	treeNode* parent;
	int size;
	bool leaf;
	treeNode(treeNode* parent, bool leaf)
	{
		this->leaf = leaf;
		this->parent = parent;
		size = 0;
	}
};
class BTree
{
private: 
	treeNode* root;
	int degree;
	void traverse(treeNode* node, int level, int target, ofstream& output);
	void insert(treeNode* node, int key);
	void insertKeyOnly(treeNode* node, int key);
	void splitNode(treeNode* right);
	int getHeight(treeNode* node);
public:

	BTree(int degree)
	{
		this->degree = degree;
		root = new treeNode(NULL, true);
		//root = NULL; 
	}
	void traverse(int target, ofstream &output)
	{
		traverse(root, 0, target, output);
	}
	void insert(int key)
	{
		insert(root, key);
	}
	int getHeight()
	{
		return getHeight(root);
	}
	treeNode* getRoot()
	{
		return root;
	}

};

