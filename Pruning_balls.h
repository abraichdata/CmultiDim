#ifndef PRUNING_BALLS_H
#define PRUNING_BALLS_H

#include "Pruning.h"
#include"List_Ball.h"

class Pruning_balls : public Pruning
{
    public:
        Pruning_balls();
        Pruning_balls* constructor();

        bool isPruned();
        bool isNonIntersectedIn();
        bool isIncludedInOut();

        void addIn(Gauss& cost, double& bound);
        void addOut(Gauss& cost, double& bound);

        void show();

    private:
        List_Ball m_inB;
        List_Ball m_outB;
};


#endif // PRUNING_BALLS_H
