/************************************************
 * File     :   Driver.cpp
 * Project  :   CSCE 221 Project 1, Spring 2020
 * Author   :   Marcel Thio
 * Date     :   2/12/2020
 * Section  :   518
 * Email    :   marcel.m.thio@tamu.edu
 * 
 * Driver that tests the llama's functions
 *********************************************/

#include <iostream>
#include <string>
using namespace std;

#include "Llama.h"

int main() {
    // Test Llama with 1 and push, pop, and peek
    Llama<int, 1> S;
    S.push(5);
    S.push(7);
    S.push(8);
    S.push(3);
    cout << " this is S.peek(2) is " << S.peek(2) << endl;
    S.dump();

    S.pop();
    S.dump();

    S.pop();
    S.pop();
    // Test throw exceptions
    //S.pop();
    //S.pop();
    S.dump();
    // Test with string dup, swap, and rotate
    Llama<string, 2> T;
    // duplicate
    T.push("hello");
    T.dup();
    T.push("howdy");
    T.dump();
    //swap
    T.swap();
    T.dump();
    // rotate
    T.pop();
    T.push("hi");
    T.dump();
    T.rot();
    T.dump();
    // peek
    T.push("Hey");
    T.dump();
    cout << " this is T.peek(2) is " << T.peek(2) << endl;
    T.dump();
    // test copy
    cout << "\n\ncopyConstructor\n" << endl;
    Llama<string, 2> copyCon = T;
    copyCon.dump();
    T.dump();
    copyCon.dup();
    copyCon.dup();
    copyCon.dup();
    copyCon.dup();
    copyCon.dump();
    copyCon.dump();
    // test assignment operator
    T = copyCon;
    T.dump();
    //howdy



    // Push a bunch of strings 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
