#include "Pruning_none.h"

Pruning_none::Pruning_none(){}
Pruning_none* Pruning_none::constructor(){return(new Pruning_none());}

void Pruning_none::addIn(Gauss& cost, double& bound){}
void Pruning_none::addOut(Gauss& cost, double& bound){}

///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///
///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///

bool Pruning_none::isPruned(){return(false);}

void Pruning_none::show(){
    std::cout << "#Pruning_nonePruning_nonePruning_none#  "<<std::endl;
}

