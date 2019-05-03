#ifndef NOC_H
#define NOC_H
#include "defs.h"

void *router(void *arg);
void *processor(void *arg);

unsigned int signal_x, signal_y;
#endif