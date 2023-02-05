/* @Author
Student Name: Eda Işık
Student ID : 150200089
Date: 26/10/2022
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    //the finished process FIFO initialized
    this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    delete mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    /*It execute the process by subtracting one from remainingTime. If process finishes, it add
    to mFinishedProcess.
    CpurRep::runCPU():  (int time) argument is used for defining the endTime of the process. 
    the CPURep objects keep the finished process. If a process is completed, 
    it will not return to the scheduler; the runCPU function saves the finished process into mFinishedProcess with endTime.*/
    
    //The function gets mpRunningProcess as parameter, decreases its remaining time by one and if the remaining time is zero, 
    //then adds it to the mFinishedProcess FIFO.
    p->remainingTime--;
    if(p->remainingTime == 0){
        p->endTime = time;
        this->mFinishedProcess->queue(p);
        return NULL;
    }else{
        return p;
    }
    
}

FIFORep* CPURep::getFinishedProcess()
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    this->mFinishedProcess = finishedProcess;
}