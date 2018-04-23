#include "Pruning_pelt.h"

Pruning_pelt::Pruning_pelt(){}
Pruning_pelt* Pruning_pelt::constructor(){return(new Pruning_pelt());}

void Pruning_pelt::addIn(Gauss& cost, double& bound){AxR2 = bound - cost.minimum();}
void Pruning_pelt::addOut(Gauss& cost, double& bound){}

///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///
///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///

bool Pruning_pelt::isPruned(){return(AxR2<0);}

void Pruning_pelt::show(){
    std::cout << "#Pruning_peltPruning_peltPruning_pelt#  "<<std::endl;

}


