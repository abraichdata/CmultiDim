#include "Point.h"

#include <iostream>

using namespace std; ///pour utiliser cout et endl de iostream

Point::Point(){}

Point::Point(int p){y = new double [p];}

Point::~Point(){
    //delete(y);
    }

double Point::get(int j){return(y[j]);}

void Point::add(double& data, int j){y[j] = data;}

void Point::show(int p){
    cout << "#Point#  ";
    for(unsigned int i = 0 ; i < p ; i++){cout<<i<<"# "<<y[i];}
    cout<<endl;
}
