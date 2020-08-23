/*******************************************
** File:    Proj2Aux.h
** Project: CSCE 221 Project 2
** Author:  Marcel Thio
** Date:    March 5, 2020
** Section: 518
** E-mail:  marcel.m.thio@tamu.edu
**
**  C++ file:
**	Sort of like the interface between the driver and augmented binary search tree
**
**
**
*******************************************/
#ifndef PROJ2AUX_C
#define PROJ2AUX_C

#include <string>
#include <fstream>
#include "AugmentedBinarySearchTree.h"
#include "Exceptions.h"

using namespace std;

class Proj2Aux {
public:
	Proj2Aux();
	~Proj2Aux();

	void DoPrintCommand(string command, int depth);
	int DoRemoveCommand(string command, int element);
	int GetMedianCommand(string command);
	int GetNthElementCommand(string command, int nthElement);
	int GetRankCommand(string command, int element);
	int GetResidualsCommand(string command);
	bool IsComplete(string command);
	bool IsPerfect(string command);
	int ReadFromCommandFile(char* commandFile);
	int ReadFromInputFile(char* inputFile);
	void Check();

private:
	int GetNum(string arg);
	ifstream inFile;
	AugmentedBinarySearchTree<int> m_tree;
};

inline Proj2Aux::Proj2Aux() {
	//m_tree = AugmentedBinarySearchTree<int>();
}
inline Proj2Aux::~Proj2Aux()
{
	m_tree.RemoveResidue();
}
inline void Proj2Aux::DoPrintCommand(string command, int depth)
{
	cout << "\nPRINT " << depth <<":\n\n";
	m_tree.PrintLevels(depth);
	cout << endl;
}
inline int Proj2Aux::DoRemoveCommand(string command, int element)
{
	cout << "\nREMOVE " << element<<": " ;
	int i = m_tree.remove(element);
	if (i == 1) {
		cout << "SUCCESS\n";
	}
	else {
		cout << "FAILED\n";
	}
	return i;
}
inline int Proj2Aux::GetMedianCommand(string command)
{
	int x = m_tree.Median();
	cout << "\nMEDIAN: " << x << endl;
	return x;
}
inline int Proj2Aux::GetNthElementCommand(string command, int nthElement)
{
	int x = m_tree.NthElement(nthElement);
	cout << "\nNTH " << nthElement << ": " << x << endl;
	return x;
}
inline int Proj2Aux::GetRankCommand(string command, int element)
{
	int x = m_tree.Rank(element);
	cout << "\nRANK " << element << ": " << x << endl;
	return x;
}
inline int Proj2Aux::GetResidualsCommand(string command)
{
	int x = m_tree.RemoveResidue();
	cout << "\nRESIDUALS: "<< x << endl;
	return x;
}
inline bool Proj2Aux::IsComplete(string command)
{
	cout << "\nCOMPLETE: ";
	bool x = m_tree.IsComplete();
	if (x) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	return x;
}
inline bool Proj2Aux::IsPerfect(string command)
{
	cout << "\nPERFECT: ";
	bool x = m_tree.IsPerfect();
	if (x) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	return x;
}
inline int Proj2Aux::ReadFromCommandFile(char* commandFile)
{
	inFile.open(commandFile);
	if (!inFile.is_open()) {
		return 0;
	}
	string temp, temp2;
	
	while (!inFile.eof()) {
		getline(inFile, temp);
		//cout << temp << endl;
		if (temp[0] == '#' || temp == "" || temp[0] == '\n'|| temp.length()==1) {
			// skip this
			//continue;
			//cout << "comment" << endl;
		}
		else if (temp.find("PRINT") != string::npos) {
			// call print
			DoPrintCommand("PRINT", GetNum(temp));
		}
		else if (temp.find("RESIDUALS") != string::npos) {
			// call residuals
			GetResidualsCommand("RESIDUALS");
		}
		else if (temp.find("RANK") != string::npos) {
			// call rank and get the number
			GetRankCommand("RANK", GetNum(temp));
		}
		else if (temp.find("NTH") != string::npos) {
			// print nth integers
			GetNthElementCommand("NTH", GetNum(temp));
		}
		else if (temp.find("MEDIAN") != string::npos) {
			// get median
			GetMedianCommand("MEDIAN");
		}
		else if (temp.find("REMOVE") != string::npos) {
			// call remove on specific nth value
			DoRemoveCommand("REMOVE", GetNum(temp));
		}
		else if (temp.find("PERFECT") != string::npos) {
			// call perfect
			IsPerfect("PERFECT");
		}
		else if (temp.find("COMPLETE") != string::npos) {
			// call complete
			IsComplete("COMPLETE");
		}
		else {
			//cout<<
			try {
				throw CommandNotFound();
			}
			catch (exception& x) {
				if(temp.find(" ")!=string::npos){
					temp = temp.substr(0,temp.find(" "));
				}
				else{
					temp = temp.substr(0,temp.size()-1);
				}
				cerr <<"\n" <<x.what()<<" " << temp<<" is not a valid command.\n";
			}
		}
	}
	inFile.close();
	return 1;
}
inline int Proj2Aux::ReadFromInputFile(char* inputFile)
{
	inFile.open(inputFile);
	if (!inFile.is_open()) {
		return 0;
	}
	string temp;
	int tempInt;
	stringstream ss;
	while (!inFile.eof()) {
		//cout << "RAN HERE";
		getline(inFile,temp,' ');
		if (temp != "") {
			// dont insert
			stringstream ss(temp);;
			ss >> tempInt;
			m_tree.insert(tempInt);
		}
	}
	inFile.close();
	return 1;
}
inline void Proj2Aux::Check()
{
	m_tree.printTree();
}
inline int Proj2Aux::GetNum(string arg)
{
	int i = stoi(arg.substr(arg.find(" ")+1));
	return i;
}
#endif