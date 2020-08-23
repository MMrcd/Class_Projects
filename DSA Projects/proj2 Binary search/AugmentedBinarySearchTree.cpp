/*******************************************
** File:    AugmentedBinarySearchTree.cpp
** Project: CSCE 221 Project 2
** Author: Marcel Thio
** Date:    March 5, 2020
** Section: 518
** E-mail:  marcel.m.thio@tamu.edu
**
**  C++ file:
**	implments the augmented binary search tree
**
**
**
*******************************************/
#ifndef AUGMENTED_BINARY_SEARCH_TREE_CPP
#define AUGMENTED_BINARY_SEARCH_TREE_CPP
#include "AugmentedBinarySearchTree.h"
#include "Exceptions.h"
#include <cstring>
#include<string>
#include<cmath>

template<class Comparable>
AugmentedBinarySearchTree<Comparable>::AugmentedBinarySearchTree()
{
}
template<class Comparable>
AugmentedBinarySearchTree<Comparable>::AugmentedBinarySearchTree(const AugmentedBinarySearchTree<Comparable>& rhs)
{
	queue <BinaryNode<Comparable>*> q;
	q.push(rhs);
	// use queue to insert element in a similar order as rhs
	while (!q.empty()) {
		if (q.front()->left != NULL) {
			q.push(q.front->left);
		}
		if (q.front()->right != NULL) {
			q.push(q.front->right);
		}
		insert(q.front()->element);
		q.pop();
	}
}

template<class Comparable>
AugmentedBinarySearchTree<Comparable>::~AugmentedBinarySearchTree()
{
	makeEmpty();
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::remove(const Comparable& x)
{
	int i = remove(x, root);
	/*
	if (i == 0) {
		try {
			throw NodeNotFound();
		}
		catch (exception & e) {
			cerr << e.what() << " BST does not contain element 10\n";
		}
	}*/
	return i;
}

template<class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsPerfect()
{
	queue<BinaryNode<Comparable>*> q;
	q.push(root);
	int h = 0;
	BinaryNode<Comparable>* cursor = NULL;
	for (cursor = root; cursor->left != NULL; cursor = cursor->left) {
		h++;
	}
	return IsPerfect(q, h);
}

template<class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsComplete()
{
	queue<BinaryNode<Comparable>*> q;
	q.push(root);
	int h = 0;
	BinaryNode<Comparable>* cursor = NULL;
	for (cursor = root; cursor->left != NULL; cursor = cursor->left) {
		h++;
	}
	return IsComplete(q, h);
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::PrintLevels(int numlevels)
{
	queue<BinaryNode<Comparable>*> q;
	PrintLevels(q, numlevels);
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::makeEmpty()
{
	makeEmpty(root);
	delete ret;
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::RemoveResidue()
{
	//cout << "residue";
	int ret = 0;
	int* x = &ret;
	if (root == NULL) {
		return 0;
	}
	RemoveResidue(root, x);
	//delete x;
	//x = NULL;
	return ret;
}

template<class Comparable>
const Comparable& AugmentedBinarySearchTree<Comparable>::NthElement(int n)
{
	int x = 0;
	int* numVisited = &x;

	if (n > root->m_size) {
		try {
			throw ItemNotFound();
		}
		catch (exception & e) {
			cerr<<"\n" << e.what() << " There does not exist an nth element in the BST.\n";
		}
		return ret->element;
	}
	//delete numVisited;
	//numVisited = NULL;
	return NthElement(root, numVisited, n)->element;
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::Rank(const Comparable& x)
{
	int ret = 0;
	int* zoom = &ret;
	Rank(x, root, zoom);
	//delete zoom;
	//zoom = NULL;
	return ret;
}

template<class Comparable>
const Comparable& AugmentedBinarySearchTree<Comparable>::Median()
{
	if (root == NULL) {
		try {
			throw ArgumentNotFound();
		}
		catch (exception & e) {
			cerr <<"\n"<< e.what() << "No median value for a tree of zero size.\n";
		}
		return ret->element;
	}
	int size = root->m_size;

	if (size % 2 == 0) {
		size /= 2;
	}
	else {
		size /= 2;
		size += 1;
	}
	return NthElement(size);
}

template<class Comparable>
BinaryNode<Comparable>* AugmentedBinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t) const
{
	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	return findMin(t->left);
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::insert(const Comparable& x)
{
	//cout << x << " ";
	insert(x, root);
	return 0;
}


//---------------------------------------------END OF BOOTSTRAP-------------------------------------------------------------

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode<Comparable>*& t) const
{
	int i;
	//cout << x << " ";
	if (t == NULL) {
		t = new BinaryNode<Comparable>(x, NULL, NULL);
		t->m_size = 1;
		return 1;
	}
	else if (x < t->element) {
		i = insert(x, t->left);
		if (i != 0) {
			t->m_size += 1;
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (t->element < x) {
		i = insert(x, t->right);
		if (i != 0) {
			t->m_size += 1;
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;  // Duplicate;
	}
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode<Comparable>*& t) const
{
	int i;
	if (t != NULL) {
		if (x < t->element) { //element is less than so go left
			i = remove(x, t->left);
			if (i != 0) {
				t->m_size -= 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (t->element < x) { //element is greater than so go right
			i = remove(x, t->right);
			if (i != 0) {
				t->m_size -= 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (t->element == x) {
			if (t->left != NULL && t->right != NULL) // Two children
			{
				t->element = findMin(t->right)->element;
				remove(t->element, t->right);
			}
			else
			{
				BinaryNode <Comparable>* n = t;
				t = (t->left != NULL) ? t->left : t->right;
				delete n;
			}
			return 1;
		}
		else { // not found
			return 0;
		}
	}
	else return 0;
}
//--------------------------------------------------------------------------------------------------------------
template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::PrintLevels(queue<BinaryNode<Comparable>*> q, int levels)
{
	// print level 0 first
	if (root == NULL) {
		cout << "(NULL, NULL, NULL) ";
	}
	else {
		cout << "Level 0:\n" << "(" << root->element << ", " << root->m_size << ", NULL)";
	}
	int onlevel = 0;
	int limPerlevel = 1;
	int nInlevel = 1;
	if (levels > 1) {
		q.push(root); // ------------------ this could have a memory leak
		while (q.size() != 0) {

			// set counters and such fro every level
			if (nInlevel == limPerlevel) {
				onlevel += 1;
				limPerlevel = int(pow(2, onlevel));
				nInlevel = 0;
				// print the level headers 
				cout << "\n\nLevel " << onlevel << ":\n";
			}
			// print info ----------------
			// check for null
			if (q.front()->element == -1) {
				cout << "(NULL, NULL, NULL) (NULL, NULL, NULL) ";
				q.front()->left = new BinaryNode<Comparable>();
				q.front()->right = new BinaryNode<Comparable>();
			}
			else { // if b is not null
				if (q.front()->left == NULL) {// check left if null
					cout << "(NULL, NULL, " << q.front()->element << ") ";
					q.front()->left = new BinaryNode<Comparable>();
				}
				else {
					cout << "(" << q.front()->left->element << ", " << q.front()->left->m_size << ", " << q.front()->element << ") ";
				}
				// check right
				if (q.front()->right == NULL) {// check left if null
					cout << "(NULL, NULL, " << q.front()->element << ") ";
					q.front()->right = new BinaryNode<Comparable>();
				}
				else {
					cout << "(" << q.front()->right->element << ", " << q.front()->right->m_size << ", " << q.front()->element << ") ";
				}
			}
			nInlevel += 2;
			// check if theres six
			if (nInlevel % 6 == 0) {
				cout << "\n";
			}
			// adding to queue -------------------
			// check if theres another level to do
			if (levels - 1 != onlevel) {
				// add children to queue
				q.push(q.front()->left);
				q.push(q.front()->right);
			}
			q.pop();
		}
	}
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::RemoveResidue(BinaryNode<Comparable>*& t, int* deletions) const
{
	if (t == NULL) {
		// do nothin
		//cout << "Null" << endl;
	}
	else if (t->element == -1) { // if it is essentially a residue
		//cout << t->element << endl;
		*deletions += 1;
		RemoveResidue(t->left, deletions);
		RemoveResidue(t->right, deletions);
		delete t;
		t = NULL;
	}
	else { // if its a number
		//cout << t->element << endl;
		RemoveResidue(t->left, deletions);
		RemoveResidue(t->right, deletions);
	}
}

template<class Comparable>
BinaryNode<Comparable>* AugmentedBinarySearchTree<Comparable>::NthElement(BinaryNode<Comparable>* t, int* nodesVisited, int n) const
{
	int keep = *nodesVisited;
	if (t == NULL) {
		return NULL;
	}
	else {
		if (NthElement(t->left, nodesVisited, n) != NULL) {
			*nodesVisited = keep;
			return NthElement(t->left, nodesVisited, n);
		}
		//cout << t->element << " Nodes visited : " << *nodesVisited << endl;
		*nodesVisited += 1;
		keep = *nodesVisited;
		if (*nodesVisited == n) {
			//cout << "ret " << t->element << endl;
			return t;
		}
		if (NthElement(t->right, nodesVisited, n) != NULL) {
			*nodesVisited = keep;
			return NthElement(t->right, nodesVisited, n);
		}
		return NULL;
	}
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::Rank(const Comparable& x, BinaryNode<Comparable>* t, int* nodesVisited) const
{
	if (t != NULL) {
		if (x < t->element) { //element is less than so go left
			Rank(x, t->left, nodesVisited);
		}
		else if (t->element < x) { //element is greater than so go right
			if (t->left != NULL) {// add elements
				*nodesVisited += t->left->m_size;
			}
			*nodesVisited += 1;
			Rank(x, t->right, nodesVisited);
		}
		else if (t->element == x) {
			if (t->left != NULL) {// add elements
				*nodesVisited += t->left->m_size;
			}
			*nodesVisited += 1;// Match
		}
		else { // nothing
		}
	}
	else {
		try {
			throw ItemNotFound();
		}
		catch (exception & b) {
			cerr <<"\n"<< b.what() << " Node does not contain element " << x << endl;
			*nodesVisited = -1;
		}
	}
}

template<class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsPerfect(queue<BinaryNode<Comparable>*> q, int height)
{
	int onlevel = -1;
	int limPerlevel = 0;
	int nInlevel = 0;

	while (q.size() != 0) {
		// set counters and such fro every level
		if (nInlevel == limPerlevel) {
			onlevel += 1;
			limPerlevel = int(pow(2, onlevel));
			nInlevel = 0;
			// print the level headers 
			//cout << "\n\nLevel " << onlevel << ":\n";
		}
		// check the children
		//cout << q.front()->element << endl;
		if (onlevel != height) {// checks to make sure all front have children and add children

			if (q.front()->left != NULL && q.front()->right != NULL) { // check perfect
				// add children to queue
				q.push(q.front()->left);
				q.push(q.front()->right);
			}
			else {
				//cout << "FALSE1" << endl;
				return false;// if its not the end and there are no children nodes
			}
		}
		else { // when on the last level
			if (!(q.front()->left == NULL && q.front()->right == NULL)) {
				//cout << "FALSE2" << endl;
				return false;// if there are any children of the supposed end of nodes
			}
		}
		nInlevel += 1;
		//cout << "nInlevel: " << nInlevel << "\nlimPerlevel: " << limPerlevel << endl;
		q.pop();
	}
	return true;
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable>*& t) const
{
	if (t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}
template<class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsComplete(queue<BinaryNode<Comparable>*> q, int height)
{
	int onlevel = -1;
	int limPerlevel = 0;
	int nInlevel = 0;
	int c = 1;
	if (height > 0) {
		while (q.size() != 0) {
			// set counters and such fro every level
			if (nInlevel == limPerlevel) {
				onlevel += 1;
				limPerlevel = int(pow(2, onlevel));
				nInlevel = 0;
				// print the level headers 
				//cout << "\n\nLevel " << onlevel << ":\n";
			}
			// check the children
			//cout << q.front()->element << endl;
			if (onlevel < height - 1) {// checks to make sure all node not on last row to have children and add children
				if (q.front()->left != NULL && q.front()->right != NULL) { // check perfect
					// add children to queue
					q.push(q.front()->left);
					q.push(q.front()->right);
				}
				else {
					//cout << "FALSE1" << endl;
					return false;// if its not the end and there are no children nodes
				}
			}
			else { // when on the se cond to last level check children and childeren schildren
				//left skip
				if (c == 0 && q.front()->left != NULL) {// theres a skip
					return false;
				}
				if (q.front()->left == NULL) {
					c = 0;
				}
				else {
					c = 1;
				}
				// right skip
				if (c == 0 && q.front()->right != NULL) {// theres a skip
					return false;
				}
				if (q.front()->right == NULL) {
					c = 0;
				}
				else {
					c = 1;
				}
				// check if theres children in these children nodes
				// three cases, r == null, lr != null
				if (q.front()->right != NULL) {//lr != null
					if (!(q.front()->right->left == NULL && q.front()->right->right == NULL)) {
						return false;
					}
				}
				if (q.front()->left != NULL) {//r==null
					if (!(q.front()->left->left == NULL && q.front()->left->right == NULL)) {
						return false;
					}
				}
			}
			nInlevel += 1;
			//cout << "nInlevel: " << nInlevel << "\nlimPerlevel: " << limPerlevel << endl;
			q.pop();
		}
	}
	return true;
}
#endif