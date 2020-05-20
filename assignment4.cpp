//
//  main.cpp
//  BinarySearchTree
//
//  Created by Tahmid Imran on 11/11/19.
//  Copyright © 2019 Tahmid Imran. All rights reserved.
//


#include "binarySearchTree.h"
#include "word.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <utility>

//stand alone function for insert
template <class DataType>
void processFound(DataType &existingItem, DataType const &newItem);

//stand alone function for find
template <class DataType>
void printer(DataType& existing);

int main()
{
    //instantion of dictionary that is a binarySeachTree
    binarySearchTree<word> dict;
    std::string t = "";
    std::ifstream inFile;
    inFile.open("english_words.txt");
    //checks if file was opened correctly
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1);
    }
    //inserts each word into binarytree, and if word with duplicate key is found then
    //the value corresponding to that key is added to the original word
    while (inFile >> t) {
        word wo(t);
        dict.insert(wo, &processFound);
    }
    inFile.close();
    //User Interface
    std::cout << "Test of find words" << std::endl << std::endl;
    std::cout << "The dictionary has been built with " << dict.size() << " keys in the dictionary" << std::endl;
    std::cout << "Word to unscramble (quit-now to stop): " << std::endl;
    std::string input = "";
    
    while(std::cin >> input)
    {
        std::cout << std::endl;
        if(input == "quit-now")
            exit(1);
        std::string temp = input;
        transform(input.begin(), input.end(), input.begin(), :: tolower);
        sort(input.begin(), input.end());
        //constructs a new word using user input to see if a word with that key is in
        //the binary tree
        word user (input);
        if(dict.find(user) == 1)
        {
            std::cout << "Scrambled word " << temp;
            //if the word is found, its vector is printed using stand alone function
            dict.find(user, &printer);
            std::cout << std::endl;
        }
        //otherwise outputs that word is not in the binary tree
        else
        {
            std::cout << "Scrambled word " << temp << " was not found" << std::endl << std::endl;;
        }
        std::cout << "Word to unscramble (quit-now to stop): " << std::endl;
    }
    return 0;
}

//stand alone function
template <class DataType>
void processFound(DataType &existingItem, DataType const &newItem)
{
    //adds the value from duplicate to original
    existingItem.add(newItem);
}

template <class DataType>
void printer(DataType& existing)
{
    //prints the values of the word
    if(existing.size() > 1)
        std::cout << " maps to words: ";
    else
        std::cout << " maps to word: ";
    existing.printer(std::cout);
}


