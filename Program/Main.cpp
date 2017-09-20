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

    cout<<"Vector:"<<endl;
    fill(edges, vertices);
    print(edges);
    determineEulerCycle(edges, vertices);

    forward_list<Edge> edgesF;
    forward_list<int> verticesF;

    cout<<"Forward List:"<<endl;
    fill(edgesF, verticesF);
    print(edgesF);
    determineEulerCycle(edgesF, verticesF);

    set<Edge> edgesS;
    set<int> verticesS;

    cout<<"Set:"<<endl;
    fill(edgesS, verticesS);
    print(edgesS);
    determineEulerCycle(edgesS, verticesS);

    list<Edge> edgesL;
    list<int> verticesL;

    cout<<"List:"<<endl;
    fill(edgesL, verticesL);
    print(edgesL);
    determineEulerCycle(edgesL, verticesL);

    multiset<Edge> edgesMulti;
    multiset<int> verticesMulti;

    cout<<"Multiset:"<<endl;
    fill(edgesMulti, verticesMulti);
    print(edgesMulti);
    determineEulerCycle(edgesMulti, verticesMulti);

    return 0;
}