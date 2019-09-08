#ifndef DECISION_H
#define DECISION_H

//References//
//----------//
#include <stdbool.h>
#include <stdio.h>
#include "Memory.h"
#include "ANSNA.h"

//Parameters//
//----------//
//truth expectation needed for executions
#define DECISION_THRESHOLD 0.501
#define ANTICIPATION_THRESHOLD 0.54
//motor babbling chance
#define MOTOR_BABBLING_CHANCE_INITIAL 0.2
#define REFRACTORY_PERIOD 50
extern double MOTOR_BABBLING_CHANCE;

//Data structure//
//--------------//
typedef struct
{
    bool execute;
    int operationID;
    Operation op;
}Decision;

//Methods//
//-------//
//TODO move
void Relink_Implication(int layer, Implication *imp);
//ANSNA decision making rule applying when goal is an operation
bool Decision_Making(int layer, Event *goal, long currentTime);

#endif
