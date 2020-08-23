/**************************************************************
 * File:    SplayTree.h
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Marcel Thio
 * Date   : 08-April-2020
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * Splay Tree definition
 *************************************************************/
#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "dsexceptions.h"
#include "Node.h"
#include <iostream>        // For NULL

// to handle capitals
#include <algorithm>
#include <string>
using namespace std;

// SplayTree class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class SplayTree
{
public:
    SplayTree()
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
        numNode = numSplay = 0;
    }

    SplayTree(const SplayTree& rhs)
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
        *this = rhs;
        numNode = numSplay = 0;
    }

    ~SplayTree()
    {
        makeEmpty();
        //if(!nullNode)
            delete nullNode;
        //if(!root)
            //delete root;
        //if (!nodePtr) 
            //delete nodePtr;
        nodePtr = nullptr;
        root = nullptr;
        nullNode = nullptr;
        ptr = nullptr;
    }

    /**
     * Find the smallest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     smaller than any item in the tree, then call findMin.
     * Return the smallest item or throw UnderflowException if empty.
     */
    const Comparable& findMin()
    {
        if (isEmpty())
            throw UnderflowException();

        ptr = root;

        while (ptr->left != nullNode)
            ptr = ptr->left;

        splay(ptr->element, root);
        return ptr->element;
    }

    /**
     * Find the largest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     larger than any item in the tree, then call findMax.
     * Return the largest item or throw UnderflowException if empty.
     */
    const Comparable& findMax()
    {
        if (isEmpty())
            throw UnderflowException();

        ptr = root;

        while (ptr->right != nullNode)
            ptr = ptr->right;

        splay(ptr->element, root,false);
        return ptr->element;
    }


    bool contains(const Comparable& x)
    {
        if (isEmpty())
            return false;
        splay(x, root,false);
        return root->element == x;
    }

    bool isEmpty() const
    {
        return root == nullNode;
    }

    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    void makeEmpty()
    {
        /******************************
         * Comment this out, because it is prone to excessive
         * recursion on degenerate trees. Use alternate algorithm.

            reclaimMemory( root );
            root = nullNode;
         *******************************/
        while (!isEmpty())
        {
            findMax();        // Splay max item to root
            remove(root->element);
        }
    }

    int getNumNode() {
        return numNode;
    }
    int getnumSplay() {
        return numSplay;
    }

    void printRoot() {
        cout << "This tree starts with the Node " << *printRoot(true) << " and has " << getNumNode() << " nodes." << endl;
    }



    void printSimilar(string word) {
        printSimilar(word, root);
    }

    void insert(const Comparable& x) {
        insert(x,root);
    }

    void remove(const Comparable& x)
    {
        BinaryNode* newTree;

        // If x is found, it will be at the root
        if (!contains(x))
            return;   // Item not found; do nothing

        if (root->left == nullNode)
            newTree = root->right;
        else
        {
            // Find the maximum in the left subtree
            // Splay it to the root; and then attach right child
            newTree = root->left;
            splay(x, newTree, false);
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
        newTree=nullptr;
    }

    const SplayTree& operator=(const SplayTree& rhs)
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }

        return *this;
    }

private:
    int numNode, numSplay;
    Node* nodePtr = nullptr;
    struct BinaryNode
    {
        Comparable  element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode() : left(NULL), right(NULL) { }
        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
            : element(theElement), left(lt), right(rt) { }
    };

    BinaryNode* root;
    BinaryNode* nullNode;
    BinaryNode* ptr;

    /**
     * Internal method to reclaim internal nodes in subtree t.
     * WARNING: This is prone to running out of stack space.
     */
    void reclaimMemory(BinaryNode* t)
    {
        if (t != t->left)
        {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
        }
    }

    /**
     * Internal method to print a subtree t in sorted order.
     * WARNING: This is prone to running out of stack space.
     */
    void printTree(BinaryNode* t) const
    {
        if (t != nullNode)
        {
            if(t->left!=NULL)
                printTree(t->left);
            cout << t->element << endl;
            if (t->right!=NULL)
                printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     * WARNING: This is prone to running out of stack space.
     */
    BinaryNode* clone(BinaryNode* t) const
    {
        if (t == t->left)  // Cannot test against nullNode!!!
            return nullNode;
        else
            return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
    // print the nodes containing the given word
    void printSimilar(string word, BinaryNode* t) {
        if (t != nullNode)
        {           
            // actual checking
            nodePtr = (Node*)&t->element;//sure
            string tword = nodePtr->GetWord();
            transform(tword.begin(), tword.end(), tword.begin(), ::tolower);
            size_t wordindx = tword.find(word);
            // check if word is similar
            if (wordindx != string::npos && wordindx == 0) {
                cout << t->element << endl;
                
            }
            // go to other nodes
            if (t->left != NULL)// branch left
                printSimilar(word, t->left);
            if (t->right != NULL)// branch right
                printSimilar(word,t->right);
        }
    }
    // Tree manipulations
    void rotateWithLeftChild(BinaryNode*& k2)
    {
        BinaryNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
        k1 = nullptr;
    }

    void rotateWithRightChild(BinaryNode*& k1)
    {
        BinaryNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
        k2=nullptr;
    }

    /**
     * Internal method to perform a top-down splay.
     * The last accessed node becomes the new root.
     * This method may be overridden to use a different
     * splaying algorithm, however, the splay tree code
     * depends on the accessed item going to the root.
     * x is the target item to splay around.
     * t is the root of the subtree to splay.
     */
    void splay(const Comparable& x, BinaryNode*& t, bool ins)
    {
        numSplay += 1;
        BinaryNode* leftTreeMax, * rightTreeMin;
        static BinaryNode header;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;   // Guarantee a match
        try {
            Node* newx = (Node*)&x;
            Node* newT;
            for (; ; ) {
                newT = (Node*)&t->element;
                //numSplay += 1;
                if (x < t->element)
                {
                    if (x < t->left->element)
                        rotateWithLeftChild(t);
                    if (t->left == nullNode)
                        break;
                    // Link Right
                    rightTreeMin->left = t;
                    rightTreeMin = t;
                    t = t->left;
                }
                else if (t->element < x)
                {
                    if (t->right->element < x)
                        rotateWithRightChild(t);
                    if (t->right == nullNode)
                        break;
                    // Link Left
                    leftTreeMax->right = t;
                    leftTreeMax = t;
                    t = t->right;
                }
                else {
                    // check if word exist, if so add frequency
                    if (newT->GetWord() == newx->GetWord() && ins) {
                        newT->IncrementFrequency();
                        numNode -= 1;
                        //cout << "Loc 3\n";
                    }
                    break;
                }
            }
            newx = nullptr;
            newT = nullptr;
        }
        catch (exception& e) {
            cerr << e.what() << " Its not Comparable is not Node" << endl;
        }
        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    }
    void insert(const Comparable& x,BinaryNode* & root)
    {
        static BinaryNode* newNode = NULL;

        if (newNode == NULL)
            newNode = new BinaryNode;
        newNode->element = x;
        numNode += 1;
        if (root == nullNode) // first node
        {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        }
        else
        {
            splay(x, root, true);
            if (x < root->element)
            {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
            }
            else
                if (root->element < x)
                {
                    newNode->right = root->right;
                    newNode->left = root;
                    root->right = nullNode;
                    root = newNode;
                }
                else //test if same
                {

                    return;
                }
        }
        newNode = NULL;   // So next insert will call new
    }
    Node* printRoot(bool priv) {
        nodePtr = (Node*)&root->element;
        return nodePtr;
    }
};

#endif