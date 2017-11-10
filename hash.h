#pragma once
/* hash.h: Header file for hash functions and definitions */

#define HASH_TABLE_SIZE 29

#include "nodes.h"  // Header file includes Prototypes defined in nodes.cpp
#include "BST.h"    // Header file includes Prototypes defined in BST.h

/******************** function prototypes ***********************/

int hashU(char *v, int M);

void trackCollisions(short *iMsgList, short *iHashTab, int n, short k);

void printCollisions(short *iMsgList, short index, short count);