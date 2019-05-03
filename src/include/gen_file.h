#ifndef GEN_FILE_H
#define GEN_FILE_H
#include "defs.h"

void create_json();
void read_neighbor_json();
void exec_router_json();
void exec_proc_json();
void create_xml();
int neighbor_top(int x, int y);
int neighbor_bottom(int x, int y);
int neighbor_left(int x, int y);
int neighbor_right(int x, int y);

FILE *output;
int proc_id;
#endif