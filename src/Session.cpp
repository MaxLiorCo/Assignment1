#include "../include/Session.h"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using json = nlohmann::json;

//------------Constructor
Session::Session(const std::string &path) :g(), treeType(), agents(), infected_queue(){
    std::ifstream jsonFile(path);
    nlohmann::json parsed_json;
    parsed_json = nlohmann::json::parse(jsonFile);

    vector<vector<int>> matrix;
    for(unsigned int i=0; i<parsed_json["graph"].size(); i++)
        matrix.push_back(parsed_json["graph"][i]);
    g.setEdges(matrix);


    for(unsigned int i=0; i<parsed_json["agents"].size(); i++) {
        if (parsed_json["agents"][i][0] == "V") {
            int nodeInd = parsed_json["agents"][i][1];
            agents.push_back(new Virus(nodeInd, *this));
        }
        else
            agents.push_back(new ContactTracer(*this));
    }
    //define treeType=Cycle/MaxRank/Root
    string temp(parsed_json["tree"]);
    const char *tr = temp.c_str();
    switch(tr[0]){
        case 'C':
            treeType = Cycle;
            break;
        case 'M':
            treeType = MaxRank;
            break;
        case 'R':
            treeType = Root;
            break;
    }
    currAgentsSize = agents.size();

}

//Destructor
Session::~Session(){
    unsigned int size = agents.size();
    for(unsigned int i=0 ; i < size; i++){
        if(agents[i])
            delete(agents[i]);
    }
}

//Copy Constructor
Session::Session(const Session& other): g(other.getCurrG().getEdges()),treeType(other.treeType),agents(), infected_queue(other.infected_queue) {
    for(unsigned int i=0; i<other.agents.size();i++){
        Agent* newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
}

//Move Constructor
Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents) ,infected_queue(){
    for(auto& elem : other.agents)
        elem = nullptr;
}

//Copy Assignment
const Session & Session::operator=(const Session &other) {
    if(this != &other) {
        unsigned int size = agents.size();
        for(unsigned int i=0 ; i < size; i++){
            if(agents[i])
                delete(agents[i]);
        }
        g.setEdges(other.getCurrG().getEdges());
        treeType = other.treeType;
        infected_queue = other.infected_queue;
    }
    return *this;
}

//Move Assignment
const Session & Session::operator=(Session &&other) {
    unsigned int size = agents.size();
    for(unsigned int i=0 ; i < size; i++){
        if(agents[i])
            delete(agents[i]);
    }
    g = other.g;
    treeType = other.treeType;
    infected_queue = other.infected_queue;
    unsigned int size2 = other.agents.size();
    for(unsigned int i=0 ; i < size2; i++){
        other.agents[i] = nullptr;
    }
    return *this;
}

void Session::simulate() {
    while(continueSession()) {
        currAgentsSize = agents.size();
        cycleCounter++;
        for (unsigned int i = 0; i < currAgentsSize; i++) {
            agents[i]->act();
        }
    }
    json output;
    output["graph"]=getCurrG().getEdges();
    output["infected"];
    for(int i=0; i<getCurrG().matrixLength(); i++)
        if(isVirus(i))
            output["infected"].push_back(i);
    ofstream i("./output.json");
    i << output;
}

void Session::addAgent(const Agent& agent) {
    Agent * newAgent = agent.clone();
    agents.push_back(newAgent);
}

void Session::setGraph(const Graph& graph){
    g = graph;
}

void Session::enqueueInfected(int infected_index) {
    infected_queue.push(infected_index);
}
int Session::dequeueInfected(){
    if(infected_queue.empty())
        return -1;
    else {
        int Value = infected_queue.front();
        infected_queue.pop();
        return Value;
    }
}
TreeType Session::getTreeType() const{
    return this->treeType;
}
Graph Session::getCurrG() const{
    return this->g;
}

Graph* Session::getCurrGPointer()  {
    return &g;
}

int Session::getCycleCounter() const {
    return cycleCounter;
}

bool Session::isVirus(int index) {
    for(unsigned int i = 0; i<currAgentsSize ; i++) {
        //if it can dynamicly down cast to Virus enter the "if" statement
        if (dynamic_cast<Virus *>(agents[i]) != 0) {
            Virus* temp = (Virus*)agents[i];
            if(temp->getNodeInd() == index)
                return true;
        }
    }
    return false;
}

bool Session::isInfected(int index) {
    unsigned int size = agents.size();
    for(unsigned int i = 0; i<size ; i++) {
        //if it can dynamicly down cast to Virus enter the "if" statement
        if (dynamic_cast<Virus *>(agents[i]) != 0) {
            Virus* temp = (Virus*)agents[i];
            if(temp->getNodeInd() == index)
                return true;
        }
    }
    return false;
}

bool Session::continueSession() {
    vector<vector<int>> matrix = g.getEdges();
    for(unsigned int i=0 ; i<matrix.size() ; i++){
        if(isVirus(i)){
            for(unsigned int j=0 ; j<matrix[i].size() ; j++)
                if((matrix[i][j] == 1) & !isVirus(j))
                    return true; //virus is connected to healthy node, continue
        }
    }
    return false; // sick and healthy nodes are in different connected components
}




