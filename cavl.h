#include <stdint.h>

#include "grammar/Parser.h"
#include "grammar/Printer.h"
#include "grammar/Absyn.h"

typedef struct Node {
    int16_t balance_factor; //reduce to smaller
    struct* Node left;
    struct* Node right;

} Node;
