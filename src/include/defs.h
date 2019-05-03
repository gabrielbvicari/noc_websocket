#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define LENGTH      30
#define AMOUNT      250

struct dataline
{
    int source[AMOUNT];
    int target[AMOUNT];
    int end[AMOUNT];
    char **str;
};

struct processing_element
{
    int x[AMOUNT], y[AMOUNT], id[AMOUNT];
};

struct source
{
    int x[AMOUNT], y[AMOUNT];
};

struct target
{
    int x[AMOUNT], y[AMOUNT];
};

int num_lines, qt_nodes_x, qt_nodes_y, num_routers, aux_x, aux_y;
int right[AMOUNT], left[AMOUNT], top[AMOUNT], bottom[AMOUNT], local[AMOUNT], count_mes[AMOUNT];
struct dataline data;
struct processing_element pe;
struct source src;
struct target tgt;
#endif