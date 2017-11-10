/******************* BST_main.cpp ************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "get_message.h"    // Header file includes Prototypes defined in get_message.cpp
#include "queues.h"         // Header file includes Prototypes defined in queues.cpp
#include "nodes.h"          // Header file includes Prototypes defined in nodes.cpp
#include "BST.h"            // Header file includes Prototypes defined in BST.cpp
#include "hash.h"            // Header file includes Prototypes defined in hash.cpp

void main(int argc, char *argv[])
{
    FILE *fp;
    char szBuf[BUFFER_LENGTH] = { NULL };   // array to store retrieved message content
    int iLen = BUFFER_LENGTH;               // number of characters in szBuf
    int mNumber = atoi(argv[1]);            // number of quotes to retrieve
    int q_count = 0;                        // number of quotes in file
    char next_char = '1';                   // manages while loop for file analysis
    int i = 0;                              // int for loop counting
    int M = HASH_TABLE_SIZE;                // size of hash table
    Node *pNode, *pHead;                    // Node pointers for node creation
    Message BST_node_Q = { NULL };          // Empty Message to hold quote text for BST
    BST_link BST_Q_ptr;                     // Pointer to BST node holding Fortune quote

    //seed random number generator
    time_t seed;
    seed = time(NULL);
    srand(time(NULL));

    // open quote file and print error if file not found
    if (fopen_s(&fp, "FortuneCookies.txt", "r") != 0) {
        printf("Error opening quote list. Check reference file.");
    }

    // set q_count to be number of quotes in file
    while (next_char != EOF) {
        next_char = fgetc(fp);
        if (next_char == '%') {
            if (fgetc(fp) == '%') {
                q_count++;
            }
        }
    }

    // create an array of q_count size to store start position of each quote
    long* q_start;
    q_start = (long *)calloc(q_count, sizeof(long));

    // move file pointer back to start of file and reset next_char and q_count
    fseek(fp, 0, SEEK_SET);
    next_char = '1';
    q_count = 0;

    // populate q_start with the starting position of each quote
    while (next_char != EOF) {
        next_char = fgetc(fp);
        if (next_char == '%') {
            if (fgetc(fp) == '%') {
                q_start[q_count] = ftell(fp);
                q_count++;
            }
        }
    }

    fclose(fp); // close the file pointer

    // calloc array of M integers to store hash key counts
    short* hashCount;
    hashCount = (short *)calloc(M, sizeof(short));

    // calloc array of M integers to store hash key collisions
    short* iHashTab;
    iHashTab = (short *)calloc(M, sizeof(short));

    // set all values of iHashTab to -1
    for (i = 0; i < M; i++) {
        iHashTab[i] = -1;
    }

    // calloc array of mNumber integers to store hash key collisions
    short* iMsgList;
    iMsgList = (short *)calloc(mNumber, sizeof(short));

    // set all values of iHashTab to -1
    for (i = 0; i < mNumber; i++) {
        iMsgList[i] = -1;
    }

    // create new empty binary search tree for Fortune quotes
    BSTInit();

    // for loop to 
    for (i = 0; i < mNumber; i++) {
        GetMessageFromFile(szBuf, iLen, q_start, q_count);      // populate szBuf
        memcpy(BST_node_Q.text, szBuf, strlen(szBuf) + 1);      // populate BST_node_Q.txt with szBuf
        BST_node_Q.hash = hashU(BST_node_Q.text, M);            // populate hash for Message
        hashCount[BST_node_Q.hash]++;                           // track totals of each hash using hashCounts
        trackCollisions(iMsgList, iHashTab, i, BST_node_Q.hash);// track collisions of hashes
        BST_Q_ptr = Insert(BST_node_Q);                         // insert Message into BST
    }

    // print counts of each hash (Part A of assignment)
    for (i = 0; i < M; i++) {
        printf("Hash key [%d] appears %d times\n", i, hashCount[i]);
    }

    printf("\n-------------------------------\n\n");

    // print message numbers of each hash key (Part B of assignment)
    for (i = 0; i < M; i++) {
        if (iHashTab[i] == -1) {
            printf("Hash key %d: EMPTY\n", i);
        }
        else {
            printf("Hash key %d: Message numbers %d ", i, iHashTab[i]);
            printCollisions(iMsgList, iHashTab[i], hashCount[i]);
            printf("\n");
        }
    }
    

    // print all BST message.text content in sorted (alphabetical) order
    //BSTPrint(BST_Q_ptr);

    free(q_start);
    free(hashCount);
    free(iHashTab);
    free(iMsgList);

    system("pause");
}


