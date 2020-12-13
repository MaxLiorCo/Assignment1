#ifndef SESSION_H_
#define SESSION_H_
#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"
#include "Agent.h"
#include <queue>

class Agent;
using namespace std;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);   //CONS
    ~Session();                         //DESTRACTOR
    Session(const Session& other);      //COPY CONS
    Session(Session&& other);     //Move CONS
    const Session& operator=(const Session& other);
    const Session& operator=(Session&& other);


    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int infected_index);  //there was only "int" given as parameter
    int dequeueInfected();
    TreeType getTreeType() const;
    //My addition
    Graph getCurrG() const;
    Graph * getCurrGPointer() ;
    int getCycleCounter() const ;
    bool isVirus(int index);
    bool isInfected(int index);
    bool continueSession();
    //void setActionHappened(bool happened);
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    //My addition
    queue<int> infected_queue;
    int cycleCounter = 0;
    unsigned int currAgentsSize = 0;
    //bool actionHappened = true; //if ture continue iteration
};

#endif


