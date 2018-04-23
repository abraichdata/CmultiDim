#include "Pruning_balls.h"

Pruning_balls::Pruning_balls(){}

Pruning_balls* Pruning_balls::constructor(){return(new Pruning_balls());}



///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///
///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///


void Pruning_balls::addIn(Gauss& cost, double& bound)
{
    m_inB.add_Element(new Ball(cost.getC(),(bound-cost.minimum())/cost.getA()));
}

void Pruning_balls::addOut(Gauss& cost, double& bound)
{
    Ball* newball = new Ball(cost.getC(),(bound-cost.minimum())/cost.getA());
    Ball* ballIn = (Ball*) m_inB.getFirstElt()->getContent();

    if(ballIn->intersect(newball)){
        m_outB.add_Element(newball);
    }
}

///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///
///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///


bool Pruning_balls::isPruned()
{
    bool response = false;
    response = isIncludedInOut();
    if(response == false){response = isNonIntersectedIn();}
    return(response);
}




bool Pruning_balls::isNonIntersectedIn()
{
    bool resp = false;
    /// INTERSECTION OF BALLS IN m_inB
    m_inB.move_To_FirstElt();
    Ball *firstptrB = (Ball *) m_inB.getFirstElt()->getContent();
    Ball *ptr_inB;
    m_inB.move();
    while(!m_inB.isEnd() & resp == false)
    {
        ptr_inB = (Ball *) m_inB.getCurrentElt()->getContent();
        if(!firstptrB->intersect(ptr_inB)){resp = true;}
        m_inB.move();
    }
    return(resp);
}


bool Pruning_balls::isIncludedInOut()
{

    bool resp = false;
    /// pointers at the beginning of the lists
    m_inB.move_To_FirstElt();
    m_outB.move_To_FirstElt();

    ///first ball in m_inB and current ball in m_outB
    Ball *firstptrB = (Ball *) m_inB.getCurrentElt()->getContent();
    Ball *ptr_outB;

    bool intersect = true;

    while(!m_outB.isEnd() && resp == false)
    {
        ptr_outB = (Ball *) m_outB.getCurrentElt()->getContent();
        ///#### PRUNING
        resp = firstptrB->isIncluded(ptr_outB);
        m_outB.move();
    }


    return(resp);
}





void Pruning_balls::show(){
    std::cout << "size IN  "<<m_inB.size()<<" && ";
    m_inB.show();
    std::cout << "size OUT  "<<m_outB.size()<<" && ";
    m_outB.show();
}
