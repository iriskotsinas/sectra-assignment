//
//  Created by Iris Kotsinas on 2021-02-20.
//

#ifndef Register_h
#define Register_h
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>

using namespace std;

class Register {
public:
    // Default constructor
    Register();
    
    // Constructor
    Register(string name, int value);
    
    // Getters
    string getRegisterName();
    int getRegisterValue();
        
    // Operators
    void operator+=(int &value);
    void operator-=(int &value);
    void operator*=(int &value);
    
    void queueExpression(string operation, string value);
    
    void print(list<Register> input);
    
    int calculate(list<Register> registers);
    
    int evaluate(string operation, int value);
    
    void clearQueue();

private:
    string registerName;
    int registerValue;
    
    // Vector to store all operations
    vector<pair<string, string>> operations;
};

#endif /* Register_h */
