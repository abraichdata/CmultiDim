#ifndef GAUSS_H
#define GAUSS_H

#include "Data.h"
#include "Point.h"
#include<vector>


class Gauss
{
    public:
        Gauss();
        Gauss(double cste, int p);

        int getA();
        std::vector<double> getC();
        double getAV();
        double getmb();

        double minimum();
        double point_eval(Point& pt);
        void addPoint(Point& pt);

        void show();

    private:
        /// COST = A*sum(i=1...p)[(C[i]-theta)^2] + AV + mb
        int A;
        std::vector<double> C;
        double AV;
        double mb;
};

#endif // GAUSS_H
