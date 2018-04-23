#ifndef ACTIVESET_H
#define ACTIVESET_H

#include "Gauss.h"
#include "Ball.h"
#include "Point.h"
#include "List_Ball.h"
#include "Pruning.h"

#include <cstdlib> //malloc

class ActiveSet
{
    public:
        ActiveSet();
        ActiveSet(Pruning* pruning, double cste, int p, int t);

        int getLabel();
        Gauss& getCost();
        Pruning* getPruning();

        void addPoint(Point& pt);

        void addIn(double& bound);
        void addOut(ActiveSet* firstActiveSet, double& bound);
        bool isElementPruned();

        void show();

    private:

        int m_label;
        Gauss m_cost;  /// pointer to the cost associated to the current piece
        Pruning* m_pruning;

};


#endif // ACTIVESET_H



