#include "Concepts.hpp"
#include "Edge.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <stack>
#include <set>
#include <map>

using namespace std;

struct findByAOrB {
    findByAOrB(int) : value(value){}
    bool operator()(Edge edge){
        return (edge.getA() == value || edge.getB() == value);
    }
    private:
        int value;
};

template<Sequence S, Random_access_iterator R>
void sortVertices(S &seq){
    sort(seq.begin(), seq.end());
}

template<typename S, typename R>
requires (Sequence<S>() && Bidirectional_iterator<R>()) || (SequenceForward<S>() && Forward_iterator<R>())
void sortVertices(S &seq){
    seq.sort();
}

template<Associative_container A, typename I>
void sortVertices(A &seq){}

template<Sequence S, typename Element>
void addElementToContainer(S &seq, Element e){
    seq.push_back(e);
}

template<SequenceForward S, typename Element>
void addElementToContainer(S &seq, Element e){
    seq.push_front(e);
}

template<Associative_container S, typename Element>
void addElementToContainer(S &seq, Element e){
    seq.insert(e);
}

template<typename S, typename Element>
requires Sequence<S>() || SequenceForward<S>()
typename S::iterator findElement(S &seq, Element e){
    return find(seq.begin(), seq.end(), e);
}

template<Associative_container S, typename Element>
typename S::iterator findElement(S &seq, Element e){
    return seq.find(e);
}

template<typename S, typename V>
void readData(ifstream &file, S &seq, V &vertices){

    int a,b;

    while(file >> a >> b){

        Edge e(a,b);

        addElementToContainer(seq, e);

        typename V::iterator it = findElement(vertices, a);
        if(it == vertices.end()) addElementToContainer(vertices, a);
        
        it = findElement(vertices, b);
        if(it == vertices.end()) addElementToContainer(vertices, b);

    }

}

template<typename E, typename V>
void fill(E &edges, V &vertices){

    ifstream file("data/file3.txt");
    
    if(!file){
        cout <<"Error input file";
        exit(0);
    }

    readData(file, edges, vertices);
    sortVertices<V, typename V::iterator>(vertices);
    file.close();

}

template<typename E>
void print(E &edges){
    cout<<endl;
    for(typename E::iterator it = edges.begin(); it != edges.end(); it++)
        cout << it->toString();
    cout<<endl;
}

template<typename S>
int getVerticesSize(typename S::iterator begin, typename S::iterator end){
    return distance(begin, end);
}

template<typename E, typename V>
bool checkIfGraphConnected(E &ed, V &vertices, int x, int startVertice) {

    int verticesSize = getVerticesSize<V>(vertices.begin(), vertices.end());
    bool *visited = new bool[verticesSize];
    for (int i = 0; i < verticesSize; i++) visited[i] = false;

    stack<int>stack;
    int vc = 0;
    
    stack.push(startVertice);
    visited[startVertice] = true;
    
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        vc++;

        for(typename E::iterator it = ed.begin(); it != ed.end(); it++){
            if(it->getA() == v && !visited[it->getB()]){
                visited[it->getB()] = true;
                stack.push(it->getB());
            } else if(it->getB() == v && !visited[it->getA()]){
                visited[it->getA()] = true;
                stack.push(it->getA());
            }
        }

    }

    delete [] visited;

    return (vc == verticesSize-x);

}

template<typename S> requires Sequence<S>() || SequenceForward<S>()
bool checkIfEdgeExistsInGraph(S &edges, Edge e){
    return (find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end());
}

template<Associative_container A>
bool checkIfEdgeExistsInGraph(A &edges, Edge e){
    return edges.find(Edge(e.getA(), e.getB())) != edges.end();
}

template<typename E>
int getEdgeIndex(E &edges, Edge e){
    return distance(edges.begin(), find_if(edges.begin(), edges.end(), Edge(e.getA(), e.getB())));
}

template<typename E, typename V>
bool checkIfAllEdgesEvenDegree(E &edges, V &vertices){
    int counter = 0, i = 0;
    for(auto v : vertices){
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) counter++;
        }
        if(counter % 2 == 0) i++;
    }
    return (i == getVerticesSize<V>(vertices.begin(), vertices.end()));
}

template<typename E>
int getNeighboursCount(E &edges, int v){
    int l = 0;
    for(auto e : edges)
        if(e.getA() == v || e.getB() == v)
            l++;
    return l;
}

template<typename S> requires Sequence<S>() || Associative_container<S>()
void deleteElementFromContainer(S &seq, typename S::iterator it){
    seq.erase(it);
}

template<SequenceForward S>
void deleteElementFromContainer(S &seq, typename S::iterator it){
    seq.remove(*it);
}

template<typename E, typename V>
bool checkIfStillConnected(E &edges, Edge e, int x, int startVertice, V &vertices){
    
    E tmp;

    for(auto e : edges)
        addElementToContainer(tmp, e);

    bool w = true;
    for(typename E::iterator it = tmp.begin(); it != tmp.end() && w; it++)
		if (it->getA() == e.getA() && it->getB() == e.getB()) {
            deleteElementFromContainer(tmp, it);
            w = false;
        }
        
    return checkIfGraphConnected(tmp, vertices, x, startVertice);
}

template<typename E, typename V>
int getZeroDegreeCount(E &edges, V &vertices){

    int l = 0, zeroDegreeVertex = 0;

    for(auto v : vertices){
        l = 0;
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) l++;
        }
        if(l == 0) zeroDegreeVertex++;
    }

    return zeroDegreeVertex;
}

template<typename S>
void removeEdgeWithOneNeighbour(S &edges, int &v){
    
    typename S::iterator it = findElement(edges, v);
    
    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    deleteElementFromContainer(edges, it);
}
/*
template<Associative_container A>
void removeEdgeWithOneNeighbour(A &edges, int &v){
    
    typename A::iterator it2;
    for(typename A::iterator it = edges.begin(); it != edges.end(); it++){
        if(it->getA() == v || it->getB() == v){
            it2 = it;
            if(it->getA() == v) v = it->getB();
            else v = it->getA();
            it = prev(edges.end());
        }
    }

    edges.erase(it2);
}

template<SequenceForward S>
void removeEdgeWithOneNeighbour(S &edges, int &v){
    
    typename S::iterator it = find(edges.begin(), edges.end(), v);
    
    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    edges.remove(*it);
}
*/
template<typename E, typename V> requires Sequence<E>()
void removeEdgeWithMoreNeighbour(E &edges, int &v, V &vertices){
    
    bool w = true;
    
    for(typename E::iterator i = edges.begin(); i != edges.end() && w; i++){
        if(i->getA() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getB();
            // edges.erase(i);
            deleteElementFromContainer(edges, i);
            // i = prev(edges.end());
            w = false;
        } else if(i->getB() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getA();
            deleteElementFromContainer(edges, i);
            // i = prev(edges.end());
            w = false;
        }
    }
}
/*
template<typename E, typename V> requires Associative_container<E>()
void removeEdgeWithMoreNeighbour(E &edges, int &v, V &vertices){
    for(typename E::iterator i = edges.begin(); i != edges.end(); i++){
        if(i->getA() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getB();
            edges.erase(i);
            i = prev(edges.end());
        } else if(i->getB() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getA();
            edges.erase(i);
            i = prev(edges.end());
        }
    }
}

template<SequenceForward E, typename V>
void removeEdgeWithMoreNeighbour(E &edges, int &v, V &vertices){
    bool w = true;
    for(typename E::iterator i = edges.begin(); i != edges.end() && w; i++){
        if(i->getA() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getB();
            edges.remove(*i);
            w = false;
            // i = prev(edges.end());
        } else if(i->getB() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getA();
            edges.remove(*i);
            w = false;
            // i = prev(edges.end());
        }
    }
}*/

template<typename E, typename V>
void determineEulerCycle(E &edges, V &vertices){

    int v = 0;

    bool condition = (checkIfGraphConnected(edges, vertices, 0, v) && checkIfAllEdgesEvenDegree(edges, vertices));
    
    if(condition){
        cout << "Euler cycle:" << endl << endl << v;
        while(!edges.empty()){
            switch(getNeighboursCount(edges, v)){
                case 1 : {
                    removeEdgeWithOneNeighbour(edges, v);
                    break;
                }
                default: {
                    removeEdgeWithMoreNeighbour(edges, v, vertices);
                    break;
                }
            }
            cout <<" -> "<<v;
        }
        cout << endl << endl;
    } else {
        cout<<"Invalid graph."<<endl;
        if(!checkIfGraphConnected(edges, vertices, 0, v))
            cout <<"Graph is not connected"<<endl;
        else if(!checkIfAllEdgesEvenDegree(edges, vertices))
            cout <<"Not all the edges are even"<<endl;
    }

}