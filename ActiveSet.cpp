#include "ActiveSet.h"
#include "Gauss.h"
#include "Pruning.h"

#include <math.h>
#include <iostream>


ActiveSet::ActiveSet(){}

ActiveSet::ActiveSet(Pruning* pruning, double cste, int p, int t)
{
    m_label = t;
    m_cost = Gauss(cste, p);
    m_pruning = pruning;
}

int ActiveSet::getLabel(){return(m_label);}
Gauss& ActiveSet::getCost(){return(m_cost);}
Pruning* ActiveSet::getPruning(){return(m_pruning);}


///##### add_add_add #####/// ///##### add_add_add #####/// ///##### add_add_add #####///
///##### add_add_add #####/// ///##### add_add_add #####/// ///##### add_add_add #####///

void ActiveSet::addPoint(Point& pt){this->getCost().addPoint(pt);}
void ActiveSet::addIn(double& bound){m_pruning->addIn(this->getCost(), bound);}
void ActiveSet::addOut(ActiveSet* firstActiveSet, double& bound){m_pruning->addOut(firstActiveSet->getCost(), bound);}

///##### isElementPruned #####/// ///##### isElementPruned #####/// ///##### isElementPruned #####///
///##### isElementPruned #####/// ///##### isElementPruned #####/// ///##### isElementPruned #####///

bool ActiveSet::isElementPruned(){return(m_pruning->isPruned());}


///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///
///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///

void ActiveSet::show()
{
    std::cout<<"LABEL : "<<m_label<<" ";
    m_cost.show();
    m_pruning->show();
}

