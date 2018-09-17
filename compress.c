#include "compress.h"


/*
    XOR-encryption and decryption
*/
int enc(int c, int key)
{
    return (c ^ key);
}

int dec(int c, int key)
{
    return (c ^ key);
}