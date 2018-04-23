#ifndef PRUNING_NONE_H
#define PRUNING_NONE_H

#include "Pruning.h"

class Pruning_none : public Pruning
{
    public:
        Pruning_none();
        Pruning_none* constructor();

        bool isPruned();
        void addIn(Gauss& cost, double& bound);
        void addOut(Gauss& cost, double& bound);

        void show();

    private:
};

#endif // PRUNING_NONE_H
