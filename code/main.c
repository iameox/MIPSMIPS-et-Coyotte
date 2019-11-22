#include <stdio.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    char hex[SIZE];
    char ins[] = "ROTR $9,$9,29";

    MIPStoHex(ins, hex);

    return 1;
}