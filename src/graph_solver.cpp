#include "graph_solver.h"

int GraphSolver::addNode(const char* description) {
    nodes.push_back(Node(nNode, description));
    inArcs.push_back(vector<int>());
    outArcs.push_back(vector<int>());
    return nNode++;
}

int GraphSolver::addEdge(int from, int to,
                    int lower, int upper, double cost,
                    const char* description){
    inArcs[to].push_back(nEdge);
    outArcs[from].push_back(nEdge);
    edges.push_back(Edge(nEdge, from, to, lower, upper, cost, description));
    return nEdge++;
}

void GraphSolver::solve(){
    ClpSimplex model;
    model.resize(0, edges.size());
    // Construct Object
    double *objective = model.objective();
    for(unsigned int i = 0; i < edges.size(); i ++){
        objective[i] = -edges[i].cost;
    }
    // Construct Rows
    CoinBuild rows;
    int lim, counter;
    for(int i = 0; i < int(nodes.size()); i ++){
        if(i == source || i == sink) continue;
        lim = inArcs[i].size() + outArcs[i].size();
        counter = 0;
        int *index = new int[lim];
        double *values = new double[lim];
        for(vector<int>::iterator iter = inArcs[i].begin();
                iter != inArcs[i].end(); iter ++){
            index[counter] = *iter;
            values[counter++] = 1.;
        }
        for(vector<int>::iterator iter = outArcs[i].begin();
                iter != outArcs[i].end(); iter ++){
            index[counter] = *iter;
            values[counter++] = -1.;
        }
        rows.addRow(lim, index, values, 0., 0.);
        delete []index;
        delete []values;
    }
    model.addRows(rows);
    // Construct Columns
    for(unsigned int i = 0; i < edges.size(); i ++){
        model.setColumnLower(i, edges[i].lower);
        model.setColumnUpper(i, edges[i].upper);
    }
    // Invoke solve to obtain the results
    model.primal();
    double *flow = model.primalColumnSolution();
    for(unsigned int i = 0; i < edges.size(); i ++){
        edges[i].flow = flow[i];
        maxFlow += flow[i];
        maxCost += flow[i]*edges[i].cost;
    }
    double *duals = model.dualRowSolution();
    for(unsigned int i = 0; i < nodes.size(); i ++){
        nodes[i].dual = duals[i];
    }
}
