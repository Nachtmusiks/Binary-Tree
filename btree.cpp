#include "btree.h"

void BTree::traverse(treeNode* node, int level, int target, ofstream &output)
{
	if (node == NULL)
	{
		return;
	}
	for (int i = 0; i < node->size; i++)
	{
		if (level == target)
		{
			output << node->keys[i] << " ";
		}
	}
	if (node->leaf == false)
	{
		for (int i = 0; i < node->c.size(); i++)
		{
			traverse(node->c[i], level + 1, target, output);
		}
	}
}

void BTree::insert(treeNode* node, int key)
{
	if (node->leaf)
	{
		insertKeyOnly(node, key);
		return;
	}
	int i = 0;
	while (i < node->size && key > node->keys[i])
	{
		i++;
	}
	insert(node->c[i], key);
}

void BTree::insertKeyOnly(treeNode* node, int key)
{
	node->keys.push_back(key);
	sort(node->keys.begin(), node->keys.end()); //make our own
	node->size++;

	if (node->size >= degree)
	{
		splitNode(node);
	}
}

void BTree::splitNode(treeNode* right)
{
	int del = 0;
	treeNode* left = new treeNode(right->parent, right->leaf);
	int newSize;
	if (degree % 2 == 0)
	{
		newSize = degree / 2 - 1;
	}
	else
	{
		newSize = degree / 2;
	}
	for (int i = 0; i < newSize; i++) //ERROR TXT 5
	{
		left->keys.push_back(right->keys[i]);
		left->size++;
		del++; //delete afterward so we dont get access issues
	}
	for (int i = 0; i < del; i++)
	{
		right->keys.erase(right->keys.begin()); 
	}
	int splitNodeKey = right->keys[0];
	right->keys.erase(right->keys.begin());
	del = 0;
	if (right->leaf == false)
	{
		for (int i = 0; i < newSize + 1; i++)
		{
			left->c.push_back(right->c[i]);
			left->c[i]->parent = left;
			del++;
		}
		for (int i = 0; i < del; i++)
		{
			right->c.erase(right->c.begin()); //delete afterward so we dont get access issues
		}
	}
	
	right->size = degree / 2;
	if (right->parent == NULL) //if no parent it's a root
	{
		treeNode* tempR = new treeNode(NULL, false);
		tempR->c.push_back(left);
		tempR->c.push_back(right);

		tempR->c[0]->parent = tempR;
		tempR->c[1]->parent = tempR;

		tempR->keys.push_back(splitNodeKey);
		tempR->size++;
		root = tempR;
		return;
	}

	treeNode* parent = right->parent;
	right->parent->c.insert(find(parent->c.begin(), parent->c.end(), right), left);
	insertKeyOnly(right->parent, splitNodeKey);
}

int BTree::getHeight(treeNode* node)
{
	if (node == NULL)
	{
		return 0;
	}
	if (node->leaf) //no children
	{
		return 1;
	}
	else
	{
		int height = 1 + getHeight(node->c[0]);
		return height;
	}
}
