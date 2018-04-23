#ifndef DATA_H
#define DATA_H

#include "Point.h"

#include <string>
#include<vector>

class Data
{
    public:
        Data(std::string filename);

        int getp();
        int getn();
        std::vector<Point> getvectPoints();

        void show();

    private:
        std::string myfilename;
        int p; ///number of dimensions
        int n; ///number of observations
        std::vector<Point> vectPoints;
};

#endif // DATA_H
