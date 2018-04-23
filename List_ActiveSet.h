#ifndef LIST_ACTIVESET_H
#define LIST_ACTIVESET_H

#include "List.h"
#include "ActiveSet.h"

class List_ActiveSet: public List, public ActiveSet
{
    public:
        List_ActiveSet();

        void dyn_prog_algo(Point& pt, double& mini, int& label, int t);
        void topology(double bound);

        void show();
};

#endif // LIST_ACTIVESET_H
