#include "Pruning_ball2.h"

Pruning_ball2::Pruning_ball2()
{
    m_inB = new Ball();
    m_outB = new Ball();
}

Pruning_ball2* Pruning_ball2::constructor(){return(new Pruning_ball2());}



///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///
///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///

void Pruning_ball2::addIn(Gauss& cost, double& bound)
{
    m_inB->getC() = cost.getC();
    m_inB->getR2() = (bound-cost.minimum())/cost.getA();
}


void Pruning_ball2::addOut(Gauss& cost, double& bound)
{
    if((bound-cost.minimum())/cost.getA()>m_outB->getR2()){
        m_outB->getC() = cost.getC();
        m_outB->getR2() = (bound-cost.minimum())/cost.getA();
        }
}

///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///
///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///



bool Pruning_ball2::isPruned()
{
    bool response = false;
    if(m_outB->getR2() != 0){response = m_inB->isIncluded(m_outB);}
    return(response);
}




void Pruning_ball2::show(){

}
