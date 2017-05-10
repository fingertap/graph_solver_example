SRC=$(PWD)/src
CLP_FLAG=-L $(SRC)/third_party/coin-Clp/lib -lClp -lClpSolver -lCoinUtils -lOsi -lOsiClp -I $(SRC)/third_party/coin-Clp/include/

example: $(SRC)/example.cpp $(SRC)/graph_solver.cpp
	g++ $^ $(CLP_FLAG) -o $@
