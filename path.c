#include "graph.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0; //a weight of 0 predefined
    p->vertices = stack_create(capacity); //calling the stack with its capacity
    return p;
}

void path_free(Path **pp) { //come back to later
    stack_free(&(*pp)->vertices);
    free(*pp);
    *pp = NULL;
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices); //grab only the stack size
}

uint32_t path_distance(const Path *p) {
    return p->total_weight; //distance is weight (the cost for how to return)
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t begin = 0;
    stack_peek(p->vertices, &begin);
    stack_push(p->vertices, val); //pushing the vertices
    p->total_weight += graph_get_weight(g, begin, val); //update the total weight from graph
}

uint32_t path_remove(Path *p, const Graph *g) { //come back to later
    uint32_t dummy = 0;
    stack_pop(p->vertices, &dummy);

    if (stack_empty(p->vertices)) { // if the stack is not empty
        p->total_weight -= graph_get_weight(g, 0, dummy); //removing the most recently aded vertex

    } else {
        uint32_t idiot = 0;
        stack_peek(p->vertices, &idiot);
        p->total_weight -= graph_get_weight(g, idiot, dummy);
    }
    return dummy;
}

void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *outfile, const Graph *g) {
    fprintf(outfile, "Alissa starts at:\n");

    stack_print(p->vertices, outfile, graph_get_names(g));
    uint32_t div = path_distance(p);
    fprintf(outfile, "Total Distance: %d\n", div);
}
