#ifndef GAME_GRAPH_H
#define GAME_GRAPH_H

#include "common.h"

/* Functions of src/game/graph.c that other files call or reference (docs/naming.md, Prototypes) */
struct Screen;
struct DreamSys;
struct Screen *Graph_New(struct DreamSys *dreamSys);

#endif
