//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Eda Işık
//---Student Number: 150200089
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS

    //TODO
    int count = 1;
    
    for(unsigned i = 0; i < sortedKey.length(); i++){
        if(i == sortedKey.length()-1){
            Node* new_node = new Node;
            new_node->token.symbol = sortedKey[i];
            new_node->token.val = count;
            queue.enque(new_node);
            break;
        }
        if(sortedKey[i] == sortedKey[i+1]){
            count++;
        }else{
            Node* new_node = new Node;
            new_node->token.symbol = sortedKey[i];
            new_node->token.val = count;
            queue.enque(new_node);
            count = 1;
        }
    }   
    //The function finds the frequencies of the characters in the key, 
    //creates a node and assing its token's value and symbol according to found frequency.    
    //Then it enques the node to the priority queue.
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    //TODO
    this->findFrequency();
    while(queue.head->next != NULL){
        Node* node1 = queue.dequeue();
        Node* node2 = queue.dequeue();

        Node* new_node = huffmanTree.mergeNodes(node1, node2);
        
        queue.enque(new_node);
    }
    huffmanTree.root = queue.head;
    //The function creates the huffman tree from the priority queue.
    //It dequeues and takes the first two element of the priorty queue, then merges them with mergeNodes function.
    //It assigns the returned node to the new_node and enques it.
    //When there is just one element in the priority queue (the head of it), the function assign it to the root of the huffman tree.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//

bool Huffman::isSymbolExist(char tokenChar, Node* node){
    for(unsigned i = 0; i < node->token.symbol.size(); i++){
        if(tokenChar == node->token.symbol[i])
            return true;
    }
    return false;
    //The function controls whether the tokenChar is in the parameter node's token symbol.
    //It returns true if it is and returns false if it is not.
}

string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    //TODO
    
    if(traverse->token.symbol.length() == 1){
        if(traverse->token.symbol[0] == tokenChar) 
            return tokenBinary;
    }

    if(isSymbolExist(tokenChar, traverse->left)){
        return tokenBinary = "0" + getTokenBinary(tokenChar, traverse->left, tokenBinary);
    }else{
        return tokenBinary = "1" + getTokenBinary(tokenChar, traverse->right, tokenBinary);
    }
    //The function finds the parameter node's token binary recursively and returns it.
    //If the parameter node's left child has tokenChar, 
    //it adds "0" to the token binary and calls the getTokenBinary with parameter node's left child as parameter. 
    //Similarly, if the parameter node's right child has tokenChar, 
    //it adds "1" to the token binary and calls the getTokenBinary with parameter node's left child as parameter. 
    //When the parameter node's token symbol has one char, 
    //it is the tokenChar that we search, the function returns the tokenBinary at this point.
    
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    //TODO
    for(unsigned i = 0; i < password.length(); i++){
        string binary = getTokenBinary(password[i], huffmanTree.root, ""); 
        encodedBinaryPassword += binary;
        string value = to_string(binary.size());
        encodedValPassword += value;
    }
    //The function encodes the given password as parameter.
    //It calls the getTokenBinary function to find the encodedBinaryPassword and find its size to find the encodedValPassword.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //TODO

    int k = 0;
    for(unsigned i = 0; i < encodedValPassword.length(); i++){
        Node* tmp = huffmanTree.root;   

        for(int j = 0; j < (encodedValPassword[i] - '0'); j++){
            if(encodedBinaryPassword[k] == '0')
                tmp = tmp->left;
            else if(encodedBinaryPassword[k] == '1')
                tmp = tmp->right;  
            k++;
        }
        decodedPassword += tmp->token.symbol;
        
    }
    //The function decodes the password with given binary password and value password as parameters.
    //Starting from the root node, it traverses the tree according to 1's and 0's.
    //When the binary password character is 0, it goes to the left child,
    //and when the binary password character is 1, it goes to the right child.
    //The function adds the found by binary password and value password node's token symbol to the decodedPassword variable.
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    //TODO
    
    Node* tmp = huffmanTree.root;   

    for(unsigned i = 0; i < encodedToken.length(); i++){
        if(encodedToken[i] == '0')
            tmp = tmp->left;
        else if(encodedToken[i] == '1')
            tmp = tmp->right; 
    }
    //The function finds the token of given binary.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};