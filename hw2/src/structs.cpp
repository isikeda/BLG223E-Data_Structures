//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Eda Işık
//---Student Number: 150200089
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

Token::Token(){
    symbol = "";
    val = 0;
    //The function initializes the tokens.
}

Node::Node(){
    next = NULL;
    left = NULL;
    right = NULL;
    //The function initializes the nodes.
}

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    //TODO
    this->head = NULL;
    //The function initializes the priority queue with NULL value.
};

Node* PriorityQueue::search(Node* n){
    Node *p = head;

    
    if(n->token.val < head->token.val)
        return NULL;
    else{
        while(p->next != NULL){
            if(p->next->token.val > n->token.val)
                return p;
            p=p->next;
        }
        return p;
    }

    //The function searches "n" through the nodes in the priority queue.
    //It returns NULL if the n's value of token is less than the value of the head, which means n's value of token is less than all values.
    //It returns the node after which it should be placed when enquing.
    //If n's value of token is grater than all nodes' values, the function returns the last node in the priority queue.
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    //TODO
    if(head == NULL){
        head = newnode;
        return;
    }
    Node* tmp = search(newnode); 
    if(tmp == NULL){
        newnode->next = head;
        this->head = newnode;
    }else{
        if(tmp->next == NULL){
            tmp->next = newnode;
        }else{
            newnode->next = tmp->next;
            tmp->next = newnode;
        }
    }
    //The function enques the newnode to the priority queue.
    //If the priority queue is empty, newnode becomes the of priority queue.
    //If it is not, search function is called and its return value assinged to the tmp node.
    //After then, newnode placed after the tmp node. 
};


//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    //TODO
    Node* tmp = this->head;
    if(tmp != NULL){
        this->head = tmp->next;
    }
    return tmp;
    //The function removes the head from the priority queue when it is called.
    //After removing, the new head is the next node of the removed head.
    //The function returns the removed head to be used.
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    //TODO
    this->root = NULL;
    //The function initializes the tree with NULL value.
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    //TODO
    if(this->root != NULL){
        deleteTree(this->root);
    }
    this->root = NULL;
    //The destructer function calls the deleteTree function with the root as a parameter for destruction.
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    if(node != NULL){
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = NULL;
    }
    //The function deletes the tree recursively.
    //The destruction is a postorder destruct.
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    //TODO
    Node* mergedNode = new Node;
    mergedNode->token.val = temp1->token.val + temp2->token.val;
    mergedNode->token.symbol = temp1->token.symbol + temp2->token.symbol; 

    mergedNode->left = temp1;
    mergedNode->right = temp2;

    return mergedNode;
    //The function merges the two parameter.
    //The mergedNode's value is the sum of the values of parameter nodes.
    //The mergedNode's symbol is the merged version of the symbols of parameter nodes.
    //The mergesNode's left child is temp1 node and its right child is temp2 node according to the huffman treee rules.
    //Let's assume temp1 is A3 and temp2 is C4, the mergedNode is AC7 and its left child is A3 and right child is C4.
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};