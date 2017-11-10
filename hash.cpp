/******************* hash.cpp ************************
*                                                    *
*  Functions adapted from ESE lecture slides         *
*  on creating BST functions                         *
*                                                    *
*****************************************************/

#include <stdio.h>
#include <stdlib.h>

int hashU(char *v, int M) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = (a*b) % (M - 1))
        h = (h*a + *v) % M;
    return(h);
}

void trackCollisions(short *iMsgList, short *iHashTab, int n, short k) {
    if (iHashTab[k] == -1) {
        iHashTab[k] = n;
    }
    else {
        iMsgList[n] = iHashTab[k];
        iHashTab[k] = n;
    }
}

void printCollisions(short *iMsgList, short index, short count) {
    if (count > 1) {
        printf("%d ", iMsgList[index]);
        count--;
        printCollisions(iMsgList, iMsgList[index], count);
    }
    else return;
}