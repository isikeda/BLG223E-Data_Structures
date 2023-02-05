/* @Author
Student Name: Eda Işık
Student ID : 150200089
Date: 26/10/2022 
*/

#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    //private and public attributes initialized
    this->mpRunningProcess = NULL;
    for(int i = 0; i < 3; i++){ 
        this->mpProcessFIFO[i] = new FIFORep();
    }

    pCpuObj = new CPURep();
    timeSliceCount = 0;
    totalTime = 0;

}
SchedulerRep::~SchedulerRep()
{
    delete mpRunningProcess;
    mpRunningProcess = NULL;

    for(int i = 0; i < 3; i++){ 
        delete this->mpProcessFIFO[i]; 
        //this->mpProcessFIFO[i]->setHead(NULL);
        //this->mpProcessFIFO[i]->setTail(NULL);
    }

    delete pCpuObj;
    pCpuObj = NULL;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    return mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    //if the parameter is NULL, the function set the mpRunningProcess as NULL, if it is not NULL and it cames for the first time
    //the function initializes its starttime
    if(p == NULL){
        mpRunningProcess = NULL;
        return;
    }

    this->mpRunningProcess = p;
    if(this->mpRunningProcess->startTime == -1){
        this->mpRunningProcess->startTime = totalTime-1;
    }
    
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    return mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
/*
    It adds the new process to the end of the appropriate FIFO.
    queue()
*/  
    if(p->getProcessType() == "A"){
        mpProcessFIFO[0]->queue(p);
    }else if(p->getProcessType() == "B"){
        mpProcessFIFO[1]->queue(p);
    }else if(p->getProcessType() == "C"){
        mpProcessFIFO[2]->queue(p);
    }

}

ProcessRep* SchedulerRep::popProcess()
{
/*
    It removes a process from the beginning of the FIFOs according to the scheduler rule and returns it.
    dequeue()   
*/

    ProcessRep* p = NULL;

    if(this->mpProcessFIFO[0]->getHead() != NULL){
        p = this->mpProcessFIFO[0]->dequeue();
    }else if(this->mpProcessFIFO[1]->getHead() != NULL){
        p = this->mpProcessFIFO[1]->dequeue();
    }else if(this->mpProcessFIFO[2]->getHead() != NULL){
        p = this->mpProcessFIFO[2]->dequeue();
    }

    return p;
}

bool SchedulerRep::checkTimeSlice()
{
    //the function controls the quantum, whether it is finished
    if(this->mpRunningProcess->getProcessType() == "A"){
        if(timeSliceCount < 2){
            timeSliceCount++;
            return false;
        }
        timeSliceCount = 1;
        return true;
    }else if(this->mpRunningProcess->getProcessType() == "B"){
        if(timeSliceCount < 4){
            timeSliceCount++;
            return false;
        }
        timeSliceCount = 1;
        return true;
    }else if(this->mpRunningProcess->getProcessType() == "C"){
        if(timeSliceCount < 8){
            timeSliceCount++;
            return false;
        }
        timeSliceCount = 1;
        return true;
    }
    return false;
}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p)
{
    //the function send process to CPU and runs it 
    return pCpuObj->runCPU(p, totalTime); 
}
void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.
         The function that takes process info as arguments is used for ordering the arriving job and taking 
         the simulation forward one step according to schedule rules.
*/
    //Firstly, the function makes the new process 
    //Then it controls whether there is a running process or not, it places the new process according to the rules
    //After then it sends the running process to CPU
    //Finally, it sets the the new running process with the popProcess() and setRunningProcess() function if the remaining time 
    //is zero or the quantum is finished


    ProcessRep* new_p = new ProcessRep(type, id, arrivalTime, processTime);
    
    totalTime++;

    if(mpRunningProcess == NULL){
        setRunningProcess(new_p); 
    }else{
        if(mpRunningProcess->getProcessType() == "B" && new_p->getProcessType() == "A"){
            pushProcess(mpRunningProcess);
            setRunningProcess(new_p);
        }else if(mpRunningProcess->getProcessType() == "C" && new_p->getProcessType() == "B"){
            pushProcess(mpRunningProcess);
            setRunningProcess(new_p);
        }else if(mpRunningProcess->getProcessType() == "C" && new_p->getProcessType() == "A"){
            pushProcess(mpRunningProcess);
            setRunningProcess(new_p);
        }else{
            pushProcess(new_p);
        }
    }

    ProcessRep* temp = sendProcessToCPU(mpRunningProcess);

    if(mpRunningProcess != NULL && checkTimeSlice()){
        pushProcess(mpRunningProcess);
        setRunningProcess(popProcess());
    }
    if(temp == NULL){
        setRunningProcess(popProcess());
    }

    
   
    
}

void SchedulerRep::schedule(ProcessRep* p)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.
        The function takes only NULL as input to take the simulation one step forward according to schedule rules.


    */

    //The function firstly controls if there is a running process or not, if not it sets running process
    //Then it sends the running process to CPU
    //Finally, it sets the the new running process with the popProcess() and setRunningProcess() function if the remaining time 
    //is zero or the quantum is finished

    totalTime++;

    if(mpRunningProcess == NULL){
        setRunningProcess(popProcess());
        if(mpRunningProcess == NULL){
            timeSliceCount++;
            return;
        }
    }

    ProcessRep* temp = sendProcessToCPU(mpRunningProcess);
    if(temp == NULL){
        setRunningProcess(popProcess());
    }

    if(mpRunningProcess != NULL && checkTimeSlice()){
        pushProcess(mpRunningProcess);
        setRunningProcess(popProcess());
    }
    
}
