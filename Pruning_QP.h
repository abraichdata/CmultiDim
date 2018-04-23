#ifndef PRUNING_QP_H
#define PRUNING_QP_H

#include "Pruning.h"
#include<vector>

#include "library/QP/QuadProg.hh"
#include "library/QP/Array.hh"

#include "library/lrslib/lrslib.h"
#include "library/lrslib/lrsmp.h"

class Pruning_QP : public Pruning
{
    public:
        Pruning_QP();
        Pruning_QP* constructor();

        bool isPruned();
        void addIn(Gauss& cost, double& bound);
        void addOut(Gauss& cost, double& bound);

        bool convexQP(int k);

	void createCONSTRAINT(lrs_dic *P, lrs_dat *Q, int k);
        bool vertexEnum(int k);

        bool getOnePoint();

        void pruneActiveOut();

        void show();

    private:
        std::vector<Ball*> m_inB;
        std::vector<Ball*> m_outB;
        std::vector<int> activeOut;
	std::vector<double> pointInB;


};

#endif // PRUNING_QP_H
