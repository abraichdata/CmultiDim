#include "Pruning_block.h"
#include<vector>
#include<math.h>

Pruning_block::Pruning_block(){}

Pruning_block::Pruning_block(int p)
{
    double inf=1.0/0.0;
    bmin = std::vector<double>(p,-1.0*inf);
    bmax = std::vector<double>(p,inf);
}

Pruning_block* Pruning_block::constructor(){return(new Pruning_block(this->getP()));}

int Pruning_block::getP(){return(bmin.size());}


///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///
///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///


void Pruning_block::addIn(Gauss& cost, double& bound)
{
    m_inB.push_back(new Ball(cost.getC(),(bound-cost.minimum())/cost.getA()));
}

void Pruning_block::addOut(Gauss& cost, double& bound)
{
    Ball* newball = new Ball(cost.getC(),(bound-cost.minimum())/cost.getA());

    if(m_inB[0]->intersect(newball)){
         m_outB.push_back(newball);
    }
}

///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///
///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///


bool Pruning_block::isPruned()
{
    bool response = false;
    response = cutIn();
    //  int freq = (m_inB.size()-1) % 10;
    //  if(freq == 0){response = cutOut();}
    if(response==false){response = cutOut();}
    return(response);
}

bool Pruning_block::cutIn()
{
    bool resp = false;

    ///last ball in m_inB
    int length = m_inB.size();
    std::vector<double> center = m_inB[length-1]->getC();
    double R2 = m_inB[length-1]->getR2();

    ///vector minimum Pmin
    std::vector<double> Pmin;

    for (unsigned int i = 0 ; i < center.size() ; i++)
    {
        if(center[i]<bmin[i]){
            Pmin.push_back(bmin[i]);
        }else if(center[i]>bmax[i]){
            Pmin.push_back(bmax[i]);
        }else{Pmin.push_back(center[i]);}
    }

    double D = 0;
    for (unsigned int i = 0 ; i < center.size() ; i++)
    {
        D = D + (Pmin[i]-center[i])*(Pmin[i]-center[i]);
    }

    ///new bounds
    double newbmin;
    double newbmax;
    double R2bis;
    for (unsigned  int i = 0 ; i < center.size() ; i++)
    {
        R2bis = R2-D+(Pmin[i]-center[i])*(Pmin[i]-center[i]);
        if(R2bis<=0){resp = true;}else{
            newbmin = center[i]-sqrt(R2bis);
            newbmax = center[i]+sqrt(R2bis);

            if(newbmax<=bmin[i]){resp = true;}
                else if(newbmin>=bmax[i]){resp = true;}else{
                    bmin[i] = std::max(bmin[i],newbmin);
                    bmax[i] = std::min(bmax[i],newbmax);
                }
        }
    }
    return(resp);
}

bool Pruning_block::cutOut()
{
    bool resp = false;

    ///a ball in m_outB
    int length = m_outB.size();

    if(length > 0){ //// if m_outB no empty. Compare with the last element in m_outB
        std::vector<double> center = m_outB[length-1]->getC();
        double R2 = m_outB[length-1]->getR2();

        ///vector minimum Pmax
        std::vector<double> Pmax;

        for (unsigned int i = 0 ; i < center.size() ; i++)
        {
            if(bmax[i]-center[i]<center[i]-bmin[i]){
                Pmax.push_back(bmin[i]);
            }else{Pmax.push_back(bmax[i]);}
        }

        double D = 0;
        for (unsigned int i = 0 ; i < center.size() ; i++)
        {
            D = D + (Pmax[i]-center[i])*(Pmax[i]-center[i]);
        }

        ///new bounds
        double newbmin;
        double newbmax;
        double R2bis;

        for (unsigned int i = 0 ; i < center.size() ; i++)
        {
            R2bis = R2-D+(Pmax[i]-center[i])*(Pmax[i]-center[i]);
            if(R2bis>0){
                newbmin = center[i]-sqrt(R2bis);
                newbmax = center[i]+sqrt(R2bis);

                if(newbmax<=bmax[i]){bmin[i] = std::max(bmin[i],newbmax);}
                    else if(newbmin>=bmin[i]){bmax[i] = std::min(bmax[i],newbmin);}
                if((newbmax>=bmax[i]) & (newbmin<=bmin[i])){resp = true;}
                }
        }
    }

    return(resp);
}



void Pruning_block::show(){
    std::cout << "#Pruning_blockPruning_blockPruning_block#  "<<std::endl;
}
