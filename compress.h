#ifndef __COMPRESS__H
#define __COMPRESS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int enc(int c, int key);
int dec(int c, int key);


#endif