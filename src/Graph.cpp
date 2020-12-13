
#include "../include/Graph.h"
#include <vector>

Graph::Graph(): edges() {}

Graph::Graph(std::vector<std::vector<int>> matrix): edges(matrix) {}

void Graph::setEdges(vector <vector<int>> matrix) {
    this->edges=matrix;
}

vector<vector<int>> Graph::getEdges() {
    return this->edges;
}

vector<int> Graph::neighborsOf(int nodeInd) {
    vector<int> neighbors;
    for(unsigned int i=0; i<getEdges()[nodeInd].size() ; i++){
        if(getEdges()[nodeInd][i]==1)
            neighbors.push_back(i);
    }
    return neighbors;
}

int Graph::matrixLength() {
    return edges.size();
}

vector<vector<int>>* Graph::getEdgesPointer() {
    return &(this->edges);
}


