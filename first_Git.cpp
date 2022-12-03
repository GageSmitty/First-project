/***************

**  No MakeFile was required. Code should 
**  comile and run properly 
**  as long as 
**  Header file is in the same directory

****************/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <algorithm>
#include "firstGit.h"

using namespace std;

// A function used to remove any non char elements from the words in the text file
// side note - I found this algorithm online and tried to re-create it to the best of my ability
string cleanString(string word){
    
        for (int i=0; i<word.size(); ++i) {
         
            if (word[i]<'A' || word[i]>'Z' && word[i]<'a' || word[i]>'z'){  
                word = word.erase(i, 1);
                i--;
            }
        }
    return word;
    }

    // A function that I used specifically to print all the unique words from the text file with there corresponding count value 
    // prints directly to an output file
    template<typename T>
    void printFreq(Node<T>* root, ofstream& file){
        
        //base case
        if(root==nullptr){
            return;
        }
        printFreq(root->left, file);

        file << root->data << " - occurs: " << root->count << endl;

        printFreq(root->right, file);
    }

    // Displays the options to the uses
    void menu(){
        cout << endl;
        cout << "Type (1) to find frequency of a specific word.\n";
        cout << "Type (2) to print out all unique words in alphebetical order.\n";
        cout << "Type (3) to output frequency analysis to a text file.\n";
        cout << "Type any other integer to exit the program.\n";
}

int main(){
   
   // Creating a bst pointer that holds type string
   class bst<string>* myTree = new bst<string>();

    // creating declaring a read in file
    fstream myFile;
    string fileName;
    // prompting the user to enter the name of the file
    cout<<"Please enter the name of the file: \n";
    cin>>fileName;

    myFile.open(fileName, ios::in);
    
    // declaring variables that hold the total word count in the file and how many unique words are in the file
    int wordCount = 0;
    int uniqueCount = 0;

    // handles any incorrect inputs from the user
    if(myFile.fail()){
        cout << "There was an ERROR opening this file" << endl;
        return 1;
    }

    // if the file was successfully opened
    if(myFile.is_open()){
        string word;

        // while there are words in the file
        while(myFile >> word){
            //removes any non char elements in the word
            word = cleanString(word);
            //changes all chars in the word to lowercase
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            // if the word actually contains a char
            if(word != " " && word != ""){
                //increases the total word count then adds it to the tree.
                wordCount++;
                myTree->root = myTree->insert(myTree->root, word);
            }
            
        }
        //confirms to the user that the tree was filled
        cout << "The Binary Search Tree has been successfully filled." << endl;
        cout << "Total words: " << wordCount << "\n";
        cout << "Total UNIQUE words: " << uniqueCount << "\n" << endl;
        //finds the unique words count aka total nodes in the tree
        uniqueCount = myTree->size(myTree->root);
        
        //closes the file
        myFile.close();

    }

    //displays the menu and prompts the user for an input
    menu();
    int userInput;
    cin>>userInput;
    
    //handles any incorrect input from the user
    if(cin.fail()){
       cout << "Please enter a NUMBER corresponding to the given menu.\n";
       return 1;
    }

    // while the user has chosen option 1,2, or 3
    while(userInput > 0 && userInput < 4){
        
        //if user chose option one (frequency of any given word)
        if(userInput == 1){
            
            // prompts the user to enter a word they want to find
            string word;
            int freq;
            cout << "Enter the word you would like to find the frequency of: ";
            cin >> word;

            //finds the frequency of the word and displays it to the user
            freq = myTree->frequency(myTree->root, word);

            cout << "The word \"" << word << "\" appears " << freq << " times." << endl;

        }

        //if the user chose option 2 (print all words int alpebetical order)
        if(userInput == 2){
            
            //calls the print method from the bst class
            myTree->printInorder(myTree->root);
            cout<<endl;
        }

        //if the user chose option 3 (print frequency analysis to txt file)
        if(userInput == 3){
            
            //prompts the user for a name to an output file and opens it
            ofstream outputFile;
            string fileName;
            cout << "What is the name of the file you want to output to: \n";
            cin >> fileName;

            outputFile.open(fileName);

            //if there was an issue opening the txt file
            if(outputFile.fail()){
                cout << "There was an ERROR opening this file." << endl;
                return 1;
            }

            // prints total and unique words to the output file
            outputFile << "Total words: " << wordCount << "\n";
            outputFile << "Total UNIQUE words: " << uniqueCount << "\n" << endl;
            // prints each word with their frequency count next to them
            printFreq(myTree->root, outputFile);

            // tells the user to check the output file
            cout << "frequency analysis has been completed. Check file " << fileName << " for details." << endl;;
            outputFile.close(); // closes file

        }

        //prompts menu while still in loop
        menu();
        //takes then handles user input
        cin>>userInput;
        if(cin.fail()){
            cout << "Please enter a NUMBER corresponding to the given menu.\n";
            return 1;
        }
    }

    // once done with the tree, it is deleted to free up memory
    myTree->deleteTree(myTree->root);
    
    return 0;
}
