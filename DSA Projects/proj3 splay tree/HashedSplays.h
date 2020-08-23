/**************************************************************
 * File:    HashedSplays.h
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Marcel Thio
 * Date   : 08-April-2020
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * HashedSplays Class definition.
 *
 *************************************************************/
#ifndef HASHED_SPLAYS_H
#define HASHED_SPLAYS_H

#include "SplayTree.h"
#include "Node.h"
#include "Util.h"
#include <fstream>

// to handle capitals
#include <algorithm>
#include <string>
#include "dsexceptions.h"
#include <vector>

using namespace std;

class HashedSplays {
public:
	int m_trees;

	HashedSplays(int size) {
		// make the amount of trees required
		for(int i = 0;i<size;i++){
			table.push_back(SplayTree<Node>());
		}
		m_trees = size; // may be wrong
	}
	~HashedSplays() {
		// deconstructor clears vector
		table.empty();
	}
	void FileReader(string inFileName) {
		// open file 
		ifstream in(inFileName);
		if (in.is_open()) {
			string word;
			while (!in.eof() ) {
				in >> word;
				// go through each words
				string wordIn = "";
				for (unsigned int i = 0; i < word.length(); i++) { 
					//go through each character
					if ((int(word[i]) >= 97 && int(word[i]) <= 122) || (int(word[i]) >= 65 && int(word[i]) <= 90)) {
						// if its letters add
						wordIn = wordIn + word.substr(i, 1);
					}
					else if ((int(word[i]) == 45 || int(word[i]) == 39) && (i != word.length() - 1 && i != 0)) {
						// if its - or ' and is in the middle 
						// check if between letters
						if (((int(word[i - 1]) >= 97 && int(word[i - 1]) <= 122) || (int(word[i - 1]) >= 65 && int(word[i - 1]) <= 90)) &&
							((int(word[i + 1]) >= 97 && int(word[i + 1]) <= 122) || (int(word[i + 1]) >= 65 && int(word[i + 1]) <= 90))) {
							wordIn = wordIn + word.substr(i, 1);
						}
					}
					else {
						//its trash
					}
				}
				//add the word into a tree
				if (wordIn != "") {
					int num = int(wordIn[0]);
					if (num >= 97) {
						// if lower case make upper
						num -= 32;
					}
					table.at(num-65).insert(Node(wordIn,1));
				}
			}
		}
		else {
			cout << "Not open" << endl;
			return;
		}
	}
	void PrintTree(int index) {
		try {
			// go to specific index and print tree
			table.at(index).printTree();
			cout << "This tree has had " << table.at(index).getnumSplay() << " splays.\n\n";
		}
		catch (exception& e) {
			cerr << e.what() << " There does not exist this this index" << endl;
		}
	}
	void PrintTree(string letter) {
		try {
			// figure out the index based on the letter and print tree in the index
			if ((int(letter[0]) >= 97 && int(letter[0]) <= 122) || (int(letter[0]) >= 65 && int(letter[0]) <= 90)) {
				// convert from ascii to a usable value
				int num = int(letter[0]);
				if (num >= 97) {
					num -= 32;
				}
				// go to specific index and print tree
				table.at(num - 65).printTree();
				cout << "This tree has had " << table.at(num - 65).getnumSplay() << " splays.\n\n";
			}
		}
		catch (exception& e) {
			cerr << e.what() << " Not a letter" << endl;
		}
	}
	void PrintHashCounts() {
		// go throught the whole tree
		for(int i = 0; i <m_trees; i++){
			if (table.at(i).getNumNode() != 0) {
				// print tree if there is a tree built
				table.at(i).printRoot();
			}
			else {
				cout << "This tree starts has no nodes." << endl;
			}
		}
	}
	void FindAll(string inPart) {
		cout << "Printing the results of nodes that start with '"<<inPart<<"'" << endl;
		// make string lower case
		transform(inPart.begin(), inPart.end(), inPart.begin(), ::tolower);
		int num = int(inPart[0]);
		// find all strings that are similar
		table.at(num-65-32).printSimilar(inPart);
	}
	void PrintHashCountResults() {
		// go throught the whole tree
		for (int i = 0; i < m_trees; i++) {
			if (table.at(i).getNumNode() != 0) {
				// print tree if there is a tree built
				table.at(i).printRoot();
			}
			else {
				cout << "This tree starts has no nodes." << endl;
			}
		}
	}
private:
	vector<SplayTree<Node>> table;
	int GetIndex(string inLetter) {
		int ret = int(inLetter[0]);
		return ret;
	}
};

#endif