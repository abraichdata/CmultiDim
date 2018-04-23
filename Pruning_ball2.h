#ifndef PRUNING_BALL2_H
#define PRUNING_BALL2_H

#include "Pruning.h"
#include"Ball.h"

class Pruning_ball2 : public Pruning
{
    public:
        Pruning_ball2();
        Pruning_ball2* constructor();

        bool isPruned();

        void addIn(Gauss& cost, double& bound);
        void addOut(Gauss& cost, double& bound);

        void show();

    private:
        Ball* m_inB;
        Ball* m_outB;
};


#endif // PRUNING_BALL2_H
