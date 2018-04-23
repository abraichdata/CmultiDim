#ifndef PRUNING_PELT_H
#define PRUNING_PELT_H

#include "Pruning.h"

class Pruning_pelt : public Pruning
{
    public:
        Pruning_pelt();
        Pruning_pelt* constructor();

        bool isPruned();
        void addIn(Gauss& cost, double& bound);
        void addOut(Gauss& cost, double& bound);

        void show();

    private:

        double AxR2;

};

#endif // PRUNING_PELT_H
