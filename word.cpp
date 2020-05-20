//
//  word.cpp
//  BinarySearchTree
//
//  Created by Tahmid Imran on 11/11/19.
//  Copyright © 2019 Tahmid Imran. All rights reserved.
//

#include "word.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <utility> 

//constructor
word::word(){}

//default constructor
word::word(std::string value)
{
    count = 1;
    //sets single to value given
    single = value;
    key = value;
    //transforms key to lower case and sorted
    transform(key.begin(), key.end(), key.begin(), :: tolower);
    sort(key.begin(), key.end());
    //adds value to vector
    values.push_back(single);
}

//destructor
word::~word()
{
}

//adds value of a word to this word
void word::add(const word &w)
{
    count++;
    std::string temp = w.getValue();
    //adds value to this word
    values.push_back(temp);
}

//returns vector of values
std::vector<std::string> word::getValues() const
{
    return values;
}

//returns single/orginal value
std::string word::getValue() const
{
    return single;
}

//returns key
std::string word::getKey() const
{
    return key;
}

//returns size of vector
int word::size() const
{
    return count;
}

//returns value at specified index of vector
std::string word::getAt(int i) const
{
    return values.at(i);
}

//overloaded operator for print statement in binarySearchTree class
std::ostream& operator<<(std::ostream &out, const word &theWord)
{
    out << "[" << theWord.getKey() << ", {";
    for(int i = 0; i < theWord.size() - 1; i++)
        out << theWord.getAt(i) << ", ";
    out << theWord.getAt(theWord.size() - 1) << "}]";
    return out;
}

//print statement for the values
void word::printer(std::ostream &out) const
{
    for(unsigned int i = 0; i < values.size(); i++)
           std::cout << values.at(i) << " ";
    std::cout << std::endl;
}


