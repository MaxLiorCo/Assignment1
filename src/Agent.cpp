#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"

using namespace std;


Agent::Agent(Session &session): session(session) {}
Agent::~Agent() {}

ContactTracer::ContactTracer(Session &session) : Agent(session) {}

Agent * ContactTracer::clone() const{
    return new ContactTracer(*this);
}

void ContactTracer::act() {
    vector<vector<int>> *edges = session.getCurrGPointer()->getEdgesPointer();
    int rootLabel = session.dequeueInfected();
    if(rootLabel!=-1) {
        Tree *tree = Tree::createTree(session, rootLabel);
        int indToRemove = tree->traceTree();
        for (int &elem : (*edges)[indToRemove]) // set the row to '0'
            elem = 0;
        for (unsigned int i = 0; i < edges->size(); i++) // set the column to '0'
            (*edges)[i][indToRemove] = 0;
        delete tree;
    }
}






Virus::Virus(int nodeInd, Session &session): Agent(session), nodeInd(nodeInd){
}

void Virus::act() {
    if(!virusWasTouched) {
        session.enqueueInfected(nodeInd);
        virusWasTouched = true;
        //next time we call act() this node will not be inserted into infected_queue
    }
    vector<vector<int>> edges = session.getCurrG().getEdges();
    bool foundNodeToInfect = false;
    for(unsigned int i=0 ; i<edges.size() && !foundNodeToInfect; i++ ){
        if(edges[nodeInd][i] == 1){
            if(!session.isInfected(i)) {
                Agent* temp = new Virus(i,session);
                session.addAgent(*temp);
                foundNodeToInfect = true;
                delete temp;
            }
        }

    }

}

Agent * Virus::clone() const {
    return new Virus(*this);
}

int Virus::getNodeInd() const {
    return nodeInd;
}




