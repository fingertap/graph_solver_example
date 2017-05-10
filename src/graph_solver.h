#ifndef GRAPH_SOLVER_H
#define GRAPH_SOLVER_H

#include "coin/ClpSimplex.hpp"
#include "coin/CoinBuild.hpp"
#include <string>
#include <vector>
using std::vector;
using std::string;

struct Node{
    int id;
    double dual;
    string category;
    Node() {}
    Node(int id, const char* category="Not Specified"):
        id(id), dual(0.), category(category){}
};

struct Edge{
    int id;
    int flow, lower, upper;
    int fromNode, toNode;
    double cost;
    string category;
    Edge(){}
    Edge(int id, 
         int from, int to,
         int lower, int upper,
         double cost, const char* category="Not Specified"):
        id(id), 
        flow(0), lower(lower), upper(upper),
        fromNode(from), toNode(to),
        cost(cost), category(category){}
};

class GraphSolver{
    private:
        int Status; // -1 for fail, 1 for success, 0 for not executed
        int nNode, nEdge;
        int source, sink;
        int maxFlow;
        double maxCost;
        vector<Node> nodes;
        vector<Edge> edges;
        vector<vector<int> > inArcs, outArcs;
    public:
        GraphSolver(): Status(0), nNode(0), nEdge(0), 
                       source(0), sink(0), 
                       maxFlow(0), maxCost(0.) {}
        int addNode(const char* description="Not Specified");
        int addEdge(int from, int to,
                int lower, int upper, double cost, 
                const char* description="Not Specified");
        const Node* getNode(int id){ return &nodes[id]; }
        const Edge* getEdge(int id){ return &edges[id]; }
        void solve();
        int getMaxFlow() const { return maxFlow; }
        double getMaxCost() const { return maxCost; }
        double status() const { return Status; }
        void setSourceSink(int source, int sink){
            this->source=source;
            this->sink = sink;
        }
        int getNEdge() const { return nEdge; }
        int getNNode() const { return nNode; }
};

#endif
