//
//  Created by Iris Kotsinas on 2021-02-20.
//

/*
 Register - Class definitions
 */

#include <stdio.h>
#include "Register.h"

// Default constructor
Register::Register() { }

// Constructor
Register::Register(std::string name, int value) {
    registerName = name;
    registerValue = value;
}

string Register::getRegisterName() {
    return registerName;
}

int Register::getRegisterValue() {
    return registerValue;
}

void Register::queueExpression(string operation, string value) {
    // Queue the expression
    operations.push_back(make_pair(operation, value));
}

void Register::print(list<Register> input) {
    // Print the result
    cout << calculate(input, 0) << endl;
    // Clear all registers
    clearQueue();
}

void Register::clearQueue() {
    operations.clear();
}

int Register::evaluate(string operation, int value) {
    if (operation == "add") {
        registerValue += value;
    } else if (operation == "subtract") {
        registerValue -= value;
    } else if (operation == "multiply") {
        registerValue *= value;
    }
    return registerValue;
}

int Register::calculate(list<Register> registers, int counter) {
    string theOperator;
    string theValue;
    bool isDigit;
    bool registerExists = false;
    
    for (int i = 0; i < operations.size(); i++) {
        theOperator = operations.at(i).first;
        theValue = operations.at(i).second;
                
        // Check if the value is a number
        isDigit = all_of(theValue.begin(), theValue.end(), ::isdigit);
        if (isDigit) {
            // Perform the operation
            evaluate(theOperator, stoi(theValue));
        // If the value is all letters do lazy evaluation
        } else {
            for (list<Register>::iterator i = registers.begin(); i != registers.end(); ++i) {
                // Check if register name is the same as the value
                if (i->getRegisterName() == theValue) {
                    counter++;
                    registerExists = true;
                    // Check if there is cyclic dependency with the registers
                    if (counter == registers.size() ) {
                        cout << "Error cyclic dependency detected" << endl;
                    } else {
                        // Perform the operation with lazy evaluation recursively
                        evaluate(theOperator, i->calculate(registers, counter));
                    }
                }
            }
            if (registerExists == false) {
                cout << "Error '" << theValue << "' as a value can't be found" << endl;
            }
        }
    }
    return registerValue;
}
