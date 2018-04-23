#include "Pruning_ballsV.h"

Pruning_ballsV::Pruning_ballsV(){}

Pruning_ballsV* Pruning_ballsV::constructor(){return(new Pruning_ballsV());}


///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///
///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///

void Pruning_ballsV::addIn(Gauss& cost, double& bound)
{
    m_inB.push_back(new Ball(cost.getC(),(bound-cost.minimum())/cost.getA()));
    //std::cout<<m_inB.size()<<std::endl;
}

void Pruning_ballsV::addOut(Gauss& cost, double& bound)
{
    Ball* newball = new Ball(cost.getC(),(bound-cost.minimum())/cost.getA());

    if(m_inB[0]->intersect(newball)){
         m_outB.push_back(newball);
    }

    //m_outB.push_back(new Ball(cost.getC(),(bound-cost.minimum())/cost.getA()));

}

///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///
///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///


bool Pruning_ballsV::isPruned()
{
    bool response = false;
    response = isIncludedInOut();
    if(response == false){response = isNonIntersectedIn();}
    return(response);
}




bool Pruning_ballsV::isNonIntersectedIn()
{

    bool resp = false;
    /// INTERSECTION OF BALLS IN m_inB

    int length = m_inB.size();

    int i = 0;
    while(i<(length-1) && resp == false)
    {
        if(!m_inB[length-1]->intersect(m_inB[i])){resp = true;}
        i = i+1;
    }
    //if(resp == true){std::cout<<"AZAZAZAZAZAZ"<<std::endl;}

    return(resp);
}


bool Pruning_ballsV::isIncludedInOut()
{

    bool resp = false;
    int length = m_inB.size();
    int lengthOUT = m_outB.size();

    int i = 0;
    while(i<lengthOUT && resp == false)
    {
        resp = m_inB[length-1]->isIncluded(m_outB[i]);
        i = i+1;
    }

    return(resp);
}



void Pruning_ballsV::show(){
    std::cout << "size IN  "<<m_inB.size()<<" && ";
    std::cout << "size OUT  "<<m_outB.size()<<" && ";
}
