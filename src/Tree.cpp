#include "../include/Tree.h"
using namespace std;
#include <vector>
#include "../include/Graph.h"
#include "../include/Session.h"

#include <queue>

//-----Constructor
Tree::Tree(int rootLabel): node(rootLabel), depth(0) ,children(){}
//-----Destructor
Tree::~Tree() {
    for(Tree *temp : children){
        if(temp)
            delete temp;
    }
}
//-----Copy Constructor
Tree::Tree(const Tree &other) : node(other.node), depth(other.depth), children() {
    for(unsigned int i=0; i<other.children.size() ; i++){
        Tree* temp = other.children[i]->clone();
        this->children.push_back(temp);
    }
}
//----- Move Constructor
Tree::Tree(Tree &&other) : node(other.node), depth(other.depth), children() {
    for(unsigned int i=0; i<other.children.size(); i++) {
        this->children.push_back(other.children[i]->clone());
        other.children[i] = nullptr;
    }
}
//----- Move Assignment Operator
const Tree& Tree::operator=(Tree &&other) {
    if(children[0])
        delete this;
    this->node=other.node;
    this->depth=other.depth;
    for(unsigned int i=0; i<other.children.size(); i++) {
        this->children.push_back(other.children[i]->clone());
        other.children[i]= nullptr;
    }
    return *this;
}
//------Copy Assignment Operator
const Tree& Tree::operator=(const Tree &other) {
    if(this!=&other){
        if(children[0])
            delete this;
        this->node=other.node;
        this->depth=other.depth;
        for(unsigned int i=0; i<other.children.size(); i++)
            this->children.push_back(other.children[i]->clone());
    }
    return *this;
}

//----Tree creator
Tree* Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Tree* root;
    Graph currG = session.getCurrG();
    switch(type){
        case Cycle:
            root = new CycleTree(rootLabel,session.getCycleCounter());
            break;
        case MaxRank:
            root = new MaxRankTree(rootLabel);
            break;
        case Root:
            root = new  RootTree(rootLabel);
            break;
    }
    vector<int> neighbors = currG.neighborsOf(rootLabel);
    if(neighbors.empty()) // if no neighbors for root(rootLabel)
        return root;
    queue<Tree*> nodeQ;
    bool inQ[currG.matrixLength()]; // we will never insert a visited node to the queue
    for (bool &elem : inQ)
        elem = false;
    nodeQ.push(root);
    inQ[rootLabel] = true;
    while(!nodeQ.empty()){
        Tree *temp = nodeQ.front();
        nodeQ.pop();
        neighbors=currG.neighborsOf(temp->node);
        for(int &i : neighbors){
            if(inQ[i]==false){
                Tree* neighbor;
                switch(type){
                    case Cycle:
                        neighbor = new CycleTree(i,session.getCycleCounter());
                        break;
                    case MaxRank:
                        neighbor = new MaxRankTree(i);
                        break;
                    case Root:
                        neighbor = new RootTree(i);
                        break;
                }
                neighbor->depth = temp->depth +1;
                nodeQ.push(neighbor);
                temp->addChild(neighbor);
                inQ[i]=true;
            }
        }
    }
    return root;
}

//-------------CycleTree Methods
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree() {
    int currDepth = 0;
    CycleTree* temp = this;
    while(!(temp->children.empty()) & (currDepth < currCycle - 1)){
        temp = (CycleTree*)temp->children[0];
        currDepth++;
    }
    return temp->getNode();
}
//-------------------------------
//--------------MaxRankTree Methods
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel){}

int MaxRankTree::traceTree() {
    MaxRankTree* nodeToRemove = removeInd(this,0,this);
    return nodeToRemove->getNode();
}
MaxRankTree* MaxRankTree::removeInd(MaxRankTree* maxNode, int depth, MaxRankTree* currNode) {
    if(maxNode!=currNode) {
        if (currNode->children.size() >= maxNode->children.size()) {
            if (currNode->children.size() > maxNode->children.size())
                maxNode = currNode;
            else if (currNode->getDepth() < maxNode->getDepth())
                maxNode = currNode;
            else if (currNode->getDepth() == maxNode->getDepth())
                if (currNode->getNode() < maxNode->getNode())
                    maxNode = currNode;
        }
    }
    for(unsigned int i=0; i<currNode->children.size() ; i++){
        MaxRankTree* temp = (MaxRankTree*)currNode->children[i]; /*currNode.children[i]*/;
        maxNode = removeInd(maxNode,temp->getDepth(),temp);
    }
    return maxNode;
}
//-----------RootTree Methods
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}
int RootTree::traceTree() {
    return this->getNode();
}

//-----Cloning
Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}
Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}
Tree* RootTree::clone() const {
    return new RootTree(*this);
}
//--------------------

//Different functions used during the assignment

void Tree::addChild(Tree* child) {
    this->children.push_back(child);
}

void Tree::addChild(const Tree &child) {
    addChild(child.clone());
}

void Tree::setNode(int rootLabel) {
    this->setNode(rootLabel);
}

int Tree::getNode() const {
    return node;
}

int Tree::getDepth() const {
    return this->depth;
}






