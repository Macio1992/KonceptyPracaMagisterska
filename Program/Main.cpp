#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <forward_list>

#include "Edge.h"
#include "Operations.cpp"

int main () {

    vector<Edge> edges;
    vector<int> vertices;

    fill(edges, vertices);
    determineEulerCycle(edges, vertices);

    set<Edge> edgesS;
    set<int> verticesS;

    fill(edgesS, verticesS);
    determineEulerCycle(edgesS, vertices);

    list<Edge> edgesL;
    list<int> verticesL;

    fill(edgesL, verticesL);
    determineEulerCycle(edgesL, verticesL);

    return 0;
}