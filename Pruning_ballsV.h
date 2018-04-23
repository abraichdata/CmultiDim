#ifndef PRUNING_BALLSV_H
#define PRUNING_BALLSV_H


#include "Pruning.h"
#include "Ball.h"
#include<vector>

class Pruning_ballsV : public Pruning
{
    public:
        Pruning_ballsV();
        Pruning_ballsV* constructor();

        bool isPruned();
        bool isNonIntersectedIn();
        bool isIncludedInOut();

        void addIn(Gauss& cost, double& bound);
        void addOut(Gauss& cost, double& bound);

        void show();

    private:
        std::vector<Ball*> m_inB;
        std::vector<Ball*> m_outB;
};

#endif // PRUNING_BALLSV_H
