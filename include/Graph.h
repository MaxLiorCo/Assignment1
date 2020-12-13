#ifndef GRAPH_H_
#define GRAPH_H_

using namespace std;
#include <vector>


class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void setEdges(vector<vector<int>> matrix);
    //---- my additions
    Graph();
    vector<vector<int>> getEdges();
    vector<int> neighborsOf(int nodeInd);
    int matrixLength();
    vector<vector<int>>* getEdgesPointer();

private:
    std::vector<std::vector<int>> edges;
};

#endif
