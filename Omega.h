#ifndef OMEGA_H
#define OMEGA_H

#include"Data.h"
#include"List_ActiveSet.h"

#include"Pruning_pelt.h"
#include"Pruning_balls.h"
#include"Pruning_ball2.h"
#include"Pruning_ballsV.h"
#include"Pruning_block.h"
#include"Pruning_QP.h"
#include"Pruning_none.h"

#include<vector>
#include<string>

class Omega
{
    public:
        Omega(double b);

        void segment(Data& data, const std::string& type = "pelt");
        void show();

    private:
        double beta;
        List_ActiveSet pwQ; ///linked list of objects ActiveSet. = a quadratic piecewise function (label + quadratics + geometry)

        std::vector<int> lastChangePoint; ///vector of lastChangePoint build by the algorithm
        std::vector<int> nb_ActiveSet; ///vector of lastChangePoint build by the algorithm

        std::string lastType;

};

#endif // OMEGA_H
