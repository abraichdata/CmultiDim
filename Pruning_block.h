#ifndef PRUNING_BLOCK_H
#define PRUNING_BLOCK_H

#include "Pruning.h"
#include "Ball.h"
#include<vector>

class Pruning_block : public Pruning
{
    public:
        Pruning_block();
        Pruning_block(int p);
        Pruning_block* constructor();

        int getP();

        bool isPruned();
        void addIn(Gauss& cost, double& bound);
        void addOut(Gauss& cost, double& bound);

        bool cutIn();
        bool cutOut();

        void show();

    private:
        std::vector<double> bmin;
        std::vector<double> bmax;
        std::vector<Ball*> m_inB;
        std::vector<Ball*> m_outB;
};

#endif // PRUNING_BLOCK_H
