//
//  word.hpp
//  BinarySearchTree
//
//  Created by Tahmid Imran on 11/11/19.
//  Copyright © 2019 Tahmid Imran. All rights reserved.
//

#ifndef word_h
#define word_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <cstddef>

class word{
private:
    //private members that have the key, value, all values of the key and size
    std::vector<std::string> values;
    std::string key;
    std::string single;
    int count;
public:
    //constructor
    word();
    //overloaded constructor
    word(std::string value);
    //destructor
    virtual ~word();
    //adds key of word to this word
    void add(const word &w);
    //returns the vector of values
    std::vector<std::string> getValues() const;
    //returns the size of the vector
    int size() const;
    //returns value at a specific index of the vector
    std::string getAt(int i) const;
    //returns value if only one value
    std::string getValue() const;
    //returns key
    std::string getKey() const;
    //print statement
    void printer(std::ostream &out) const;
    
public:
    //overloaded operators
    bool operator==(const word &rhs) const {return this->key == rhs.getKey();}
    bool operator!=(const word &rhs) const {return this->key != rhs.getKey();}
    bool operator<(const word &rhs) const {return this->key < rhs.getKey();}
    bool operator<=(const word &rhs) const {return this->key <= rhs.getKey();}
    bool operator>(const word &rhs) const {return this->key > rhs.getKey();}
    bool operator>=(const word &rhs) const {return this->key >= rhs.getKey();}
};
//overloaded operator for print method in binarySearchTree class
std::ostream& operator<<(std::ostream &out, const word &theWord);
#endif /* word_h */
