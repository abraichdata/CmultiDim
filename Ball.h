#ifndef BALL_H
#define BALL_H

#include<vector>

#include <cstdlib> //malloc

class Ball
{
    public:
        Ball();
        Ball(std::vector<double> Center, double radius2, double nC = 0);

        double& getR2();
        std::vector<double>& getC();
        double& getNormC();

        bool intersect(Ball *ball);
        bool isIncluded(Ball *ball);

        void findNormC();

        Ball* clone();

        void show();

    protected:

    private:
        std::vector<double> C; ///array of size p (f double). Center of the ball
        double R2;   ///radius to the square
        double normC; /// L2 norm of the center point C
};


#endif // BALL_H
