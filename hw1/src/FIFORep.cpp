/* @Author
Student Name: Eda Işık
Student ID : 150200089
Date: 26/10/2022
*/

#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    //the head and the tail of the linked list "FIFO" initialized
    this->mpHead = NULL;
    this->mpTail = NULL;

}

FIFORep::FIFORep(ProcessRep* head)
{
    this->mpHead = head;
    this->mpTail = head;
}


FIFORep::~FIFORep()
{   
    ProcessRep* tmp = mpHead;
    while(tmp != NULL){
        ProcessRep* next = tmp->getNext();
        delete tmp;
        tmp = next;
    }
    mpHead = NULL;
    mpTail = NULL;

}

void FIFORep::setHead(ProcessRep* head)
{   
    if(head != NULL){
        this->mpHead = head;
    }
}

ProcessRep* FIFORep::getHead()
{
    return mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    this->mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    return mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    /*
        The function add a process to the tail of the queue.
    */
    
    p->setNext(NULL);
    
    if(this->mpHead == NULL){
        this->setHead(p);
        this->setTail(p);
    }else{
    this->mpTail->setNext(p);
    this->setTail(p);
    } 
    
}

ProcessRep* FIFORep::dequeue()
{   
    /*
        The function removes a process from the HEAD of the FIFO and returns it. If there is no item, it returns NULL.
    */   
    
    ProcessRep* temp = this->getHead(); 
    if(temp !=  NULL){
        this->mpHead = temp->getNext();
    }
    return temp;

}

ProcessRep* FIFORep::searchID(int id)
{   
    /*
        The function search a process by id and returns it if it exist otherwise returns NULL.
    */ 
    ProcessRep* temp = mpHead;
    while(temp->getNext() != NULL){
        if(temp->getProcessID() == id ){
            return temp;
        } 
        temp = temp->getNext();
    }
    return NULL;
}

void FIFORep::printFIFO()
{
    /*
        The function prints the proceses in the queue starting from Head to Tail.
    */
    ProcessRep* temp = mpHead;

    while(temp != NULL){
        cout << temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " ";  
        temp = temp->getNext();
    }

    delete temp;
}