#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Session;

class Agent{
public:
    Agent(Session& session);
    virtual ~Agent();
    virtual void act()=0;
    //my functions
    virtual Agent* clone() const = 0;
protected:
    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    virtual void act();
    //my functions
    virtual Agent* clone() const;
};


class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    virtual void act();
    //my Addition
    virtual Agent* clone() const;
    int getNodeInd() const;
private:
    const int nodeInd;
    //my fields
    bool virusWasTouched = false;

};

#endif


