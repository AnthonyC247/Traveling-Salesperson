#include "graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;

    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));

    g->weights = calloc(vertices, sizeof(g->weights[0]));

    for (uint32_t i = 0; i < vertices; i++) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}

void graph_free(Graph **gp) {
    if (gp != NULL && *gp != NULL) {
        if ((*gp)->names) {
            free((*gp)->names);
            (*gp)->names = NULL;
        }

        if ((*gp)->weights) {
            free((*gp)->weights);
            (*gp)->weights = NULL;
        }

        if ((*gp)->visited) {
            free((*gp)->visited);
            (*gp)->visited = NULL;
        }

        if (gp != NULL) {
            free((*gp)->names);
            free((*gp)->weights);
            free((*gp)->visited);
            *gp = NULL; //set the pointer to NULL to ensure we never double free
        }
    }
}

uint32_t graph_vertices(const Graph *g) {
    return (g)->vertices;
}

char **graph_get_names(const Graph *g) {
    return g->names; // names is defined as a double pointer in struct graph
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    if (g->directed) {
        g->weights[start][end] = weight;
    } else {
        g->weights[start][end] = weight;
        g->weights[end][start] = weight;
    }
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v])
        free(g->names[v]);
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    return g->weights[start][end];
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = true;
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = false;
}
bool graph_visited(const Graph *g, uint32_t v) {
    if (g->visited[v] == true) {
        return true;
    }
    return false;
}
