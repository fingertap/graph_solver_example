#include "graph_solver.h"

GraphSolver solver;

int main(){
    // The network is:
    //    A
    // S / \T
    //   \ /
    //    B
    // Add node
    int A, B, S, T;
    A = solver.addNode();
    B = solver.addNode();
    S = solver.addNode();
    T = solver.addNode();
    // Add Edge
    // addEdge(int from, int to, int capacity_lower_bound,
    //          int capacity_upper_bound, double cost )
    int SA=solver.addEdge(S, A, 0, 2, 10.0);
    int SB=solver.addEdge(S, B, 0, 2, 10.0);
    int AT=solver.addEdge(A, T, 0, 2, 10.0);
    int BT=solver.addEdge(B, T, 0, 2, 10.0);
    // Set source and sink
    solver.setSourceSink(S, T);
    // Start solving
    solver.solve();
    // Get the flow of an edge, note that here the flow and capapcity is assumed
    // to be integers.
    int flow = solver.getEdge(SA)->flow;
    return 0;
}
