//
//  Created by Iris Kotsinas on 2021-02-20.
//
/* ------------------------------------------------------
 
 SECTRA ASSIGNMENT
 
 This is a program for a simple calculator that can
 add, subtract and multiply values in a set of registers
 
 The input is read from a simple text file,
 where each line is one command
 
 The syntax for your input is:
 <register> <operation> <value>
 print <register>
 quit
 
 ------------------------------------------------------ */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm> // transform

#include "Register.h"

using namespace std;

void startMessage() {
    cout << "\nWelcome!\nPlease enter an operation in the form of:\n<register> <operation> <value>\n" << endl;
}

Register findRegister(list<Register> registers, string seekRegister) {
    for (list<Register>::iterator i = registers.begin(); i != registers.end(); ++i) {
        if (i->getRegisterName() == seekRegister) {
            return *i;
        }
    }
    return Register();
}

int main(int argc, char* argv[]) {

    // List with registers
    list<Register> registers;
    ifstream inputFile;
    bool registerExists = false;
    string line;
        
    // Check the number of input arguments
    if (argc == 2) {
        inputFile.open(argv[1]);
        
        if (!inputFile) {
            cout << "Error textfile could not be found." << endl;
            return 1;
        }
    } else {
        cout << "Not enough input arguments, usage: "<< argv[0] <<" <filename>\n";
        return 1;
    }
    
    startMessage();
    
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {

            // Negate case sensitivity
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            
            // Put input string in stream
            istringstream iss(line);
            // Populate vector with "words"
            vector<string> words(istream_iterator<string>(iss), istream_iterator<string>{});
                
            // Check if command is an expression
            if (words.size() == 3) {
                registerExists = false;
                // Check if first word (register) is all digits
                bool isAllDigits = std::all_of(words.at(0).begin(), words.at(0).end(), ::isdigit); // C++11
                
                if (isAllDigits) {
                    cout << "Error '" + words.at(0) + "' is not a valid register name" << endl;
                } else {
                    if (words.at(1) == "add" || words.at(1) == "subtract" || words.at(1) == "multiply") {

                        // Iterate over list of registers
                        for (list<Register>::iterator i = registers.begin(); i != registers.end(); ++i) {
                            // If register name is found, queue the expression
                            if (i->getRegisterName() == words.at(0)) {
                                registerExists = true;
                                (*i).queueExpression(words.at(1), words.at(2));
                            }
                        }
                        
                        if (!registerExists) {
                            // Create new register with start value 0 and queue it
                            Register newReg(words.at(0), 0);
                            newReg.queueExpression(words.at(1), words.at(2));
                            //  Add new register to list of registers
                            registers.push_back(newReg);
                        }
                        
                    } else {
                        cout << "Error '" + words.at(1) + "' is not a valid operator" << endl;
                    }
                }
            // Check if input is empty
            } else if (words.size() == 0) {
                cout << "Error the input can not be empty" << endl;
                
            } else {
                if (words.at(0) == "quit") {
                    cout << endl << "Exiting calculator" << endl;
                    return 0;
                } else if (words.at(0) == "print") {
                    // Check if register exists and find register
                    Register reg = findRegister(registers, words.at(1));
            
                    // If the register does not exist, error
                    if (reg.getRegisterName() == "") {
                        cout << "Error there is no register with name '" + words.at(1) +"'" << endl;
                    } else {
                        // Print the result
                        reg.print(registers);
                    }
                } else {
                    cout << "Error '" << words.at(0) << "' is not a valid command" << endl;
                }
            }
        }
        inputFile.close();
    }
}
