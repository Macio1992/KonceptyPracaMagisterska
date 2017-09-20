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
    if(checkIfEdgeExistsInGraph(edgesF, Edge(0,1))) cout <<"jest"<<endl;
    else cout << "nie jest"<<endl;

    set<Edge> edgesS;
    set<int> verticesS;

    cout<<"Set:"<<endl;
    fill(edgesS, verticesS);
    print(edgesS);
    if(checkIfEdgeExistsInGraph(edgesS, Edge(0,1))) cout <<"jest"<<endl;
    else cout << "nie jest"<<endl;

    list<Edge> edgesL;
    list<int> verticesL;

    cout<<"List:"<<endl;
    fill(edgesL, verticesL);
    print(edgesL);
    if(checkIfEdgeExistsInGraph(edgesL, Edge(0,1))) cout <<"jest"<<endl;
    else cout << "nie jest"<<endl;

    multiset<Edge> edgesMulti;
    multiset<int> verticesMulti;

    cout<<"Multiset:"<<endl;
    fill(edgesMulti, verticesMulti);
    print(edgesMulti);
    if(checkIfEdgeExistsInGraph(edgesMulti, Edge(0,1))) cout <<"jest"<<endl;
    else cout << "nie jest"<<endl;

    return 0;
}