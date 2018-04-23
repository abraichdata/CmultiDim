#include "Ball.h"
#include <math.h>

#include <iostream>

Ball::Ball(){R2 = 0;}
Ball::Ball(std::vector<double> Center, double radius2, double nC): C(Center), R2(radius2), normC(nC){}

double& Ball::getR2(){return(R2);}
std::vector<double>& Ball::getC(){return(C);}
double& Ball::getNormC(){return(normC);}


bool Ball::intersect(Ball *ball){
    std::vector<double> C2 = ball->getC();
    double D = 0;
    for(unsigned int i = 0 ; i < C.size() ; i++){D = D + (C[i]-C2[i])*(C[i]-C2[i]);}
    return(sqrt(D) <= sqrt(this->getR2())+sqrt(ball->getR2()));
}

bool Ball::isIncluded(Ball *ball){
    std::vector<double> C2 = ball->getC();
    double D = 0;
    for(unsigned int i = 0 ; i < C.size() ; i++){D = D + (C[i]-C2[i])*(C[i]-C2[i]);}
    return(sqrt(D) <= sqrt(ball->getR2())-sqrt(this->getR2()));
}


Ball* Ball::clone(){return(new Ball(getC(),getR2()));}


void Ball::findNormC(){
    for(unsigned int i = 0 ; i < C.size() ; i++){normC = normC + C[i]*C[i];}
}


///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///
///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///


void Ball::show()
{
    std::cout<<"   BALL: "<<R2;
}

