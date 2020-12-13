#ifndef TREE_H_
#define TREE_H_

using namespace std;
#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree &other);
    Tree(Tree&& other);
    const Tree& operator=(const Tree &other);
    const Tree& operator=(Tree&& other);

    virtual ~Tree();
    virtual Tree* clone() const=0;
    virtual int traceTree()=0;

    void addChild(const Tree& child);
    void addChild(Tree* child);
    void setNode(int rootLabel);
    int getNode() const;
    int getDepth() const;

    static Tree* createTree(const Session& session, int rootLabel);

private:
    int node;
    int depth;

protected:
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual Tree* clone() const;
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);

    virtual Tree* clone() const;
    virtual int traceTree();

private:
    MaxRankTree* removeInd(MaxRankTree* max, int depth, MaxRankTree* currNode);
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);

    virtual Tree* clone() const;
    virtual int traceTree();
};

#endif
