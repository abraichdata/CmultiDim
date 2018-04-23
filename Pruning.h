#ifndef PRUNING_H
#define PRUNING_H

#include"List_Ball.h"
#include"Gauss.h"

#include<iostream>

class Pruning
{
    public:
        Pruning();
        virtual Pruning* constructor() = 0;

        virtual bool isPruned() = 0;
        virtual void addIn(Gauss& cost, double& bound) = 0;
        virtual void addOut(Gauss& cost, double& bound) = 0;

        virtual void show() = 0;

    protected:

};

#endif // PRUNING_H
