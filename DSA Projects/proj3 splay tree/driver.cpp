/**************************************************************
 * File:    driver.cpp
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Marcel Thio
 * Date   : 08-April-2020
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * HashedSplays Class implementation.
 *
 *************************************************************/
#include "HashedSplays.h"  // Includes constants
#include "dsexceptions.h"
using namespace std;

int main(int argc, char* argv[]) {
    try {

        // Instatiate the main object
        HashedSplays wordFrequecy(26);
        // Build the trees
        wordFrequecy.FileReader(argv[1]);

        // Test methods to show hashed splay trees work
        wordFrequecy.PrintHashCountResults();
        wordFrequecy.PrintTree(19); // Prints the "T" tree
        wordFrequecy.PrintTree("F");
        wordFrequecy.PrintTree("K"); // should be mpty running input1
        wordFrequecy.FindAll("The"); // should find all the's (ignoring case)
        cout << endl;
    }
    // Error catching
    catch (exception& cException) {
        cout << "EXCEPTION: " << cException.what() << endl;
        return 1;
    }

    //Uncomment for number of seconds running.
    //cout << clock() / (float)(CLOCKS_PER_SEC) << endl;
    


    return 0;
}

/*int main(){
    HashedSplays wordFrequecy(26);
    wordFrequecy.FileReader("input1.txt");//2asssssssssssssssssssssdssssssssswssssssssssssssssssssssssssssssssdssssssssssss
    wordFrequecy.PrintHashCountResults();
    wordFrequecy.PrintTree(19); // Prints the "T" tree
    //cout << "T is done" << endl;
    wordFrequecy.PrintTree("F");
    wordFrequecy.PrintTree("K"); // should be mpty running input1
    wordFrequecy.FindAll("The"); // should find all the's (ignoring case)
    cout << endl;
    */