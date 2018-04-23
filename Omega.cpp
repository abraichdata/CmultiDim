#include "Omega.h"

#include<iostream>

using namespace std;

Omega::Omega(double b) : beta(b)
{
    pwQ = List_ActiveSet();
}

//####### segment #######// //####### segment #######// //####### segment #######//
//####### segment #######// //####### segment #######// //####### segment #######//


void Omega::segment(Data& data, const std::string& type)
{
    lastType = type;

    ///data downloading
    int p = data.getp();
    int n = data.getn();
    std::vector<Point> points = data.getvectPoints();

    ///PRUNING type ///pruning_type = "no_pruning", "pelt", "balls", "QP"
    Pruning* pruning_type;
    int known_type = 0;
    if(type == "pelt"){pruning_type = new Pruning_pelt(); known_type = 1;}
    if(type == "balls"){pruning_type = new Pruning_balls(); known_type = 1;}
    if(type == "ball2"){pruning_type = new Pruning_ball2(); known_type = 1;}
    if(type == "ballsV"){pruning_type = new Pruning_ballsV(); known_type = 1;}
    if(type == "block"){pruning_type = new Pruning_block(p); known_type = 1;}
    if(type == "QP"){pruning_type = new Pruning_QP(); known_type = 1;}
    if(known_type == 0){pruning_type = new Pruning_none();}


    ///Parameters
    double mb = 0; ///initial cost constant
    double mini = mb;
    int label = 0;

    for (int t = 0 ; t < n ; t++)
    {
        std::cout<<t<<" ";

        ///NEW activeSet
        ActiveSet *newAcSet = new ActiveSet(pruning_type->constructor(),mb,p,t);

        ///add element to pwQ +  add_point + dynamic programming
        pwQ.add_Element(newAcSet);
        pwQ.dyn_prog_algo(points[t],mini,label,t);
        mb = mini + beta;  ///new mb = global minimum step t + beta

        pwQ.topology(mb);   ///change geometry and pruning

        ///FILL the response vectors
        lastChangePoint.push_back(label); ///adding a label to changepoint
        nb_ActiveSet.push_back(pwQ.size());
        //pwQ.show();
    }
}




///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///
///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///

void Omega::show()
{
    std::cout << "----------------------------------------------------------------------------------"<< std::endl;
    std::cout << "---------------------------------    "<<lastType<<"     -----------------------------------"<< std::endl;
    std::cout << "----------------------------------------------------------------------------------"<< std::endl;
    std::cout << "lastChangePoint"<<" --- "<<"nb_ActiveSet"<< std::endl;

    for(unsigned int i = 0 ; i < lastChangePoint.size() ; i++)
    {
        std::cout<<i<<" -- "<<lastChangePoint[i]<<" -- "<<nb_ActiveSet[i]<<std::endl;
    }
    double nb_total_ActiveSet = 0;
    for (unsigned int i = 0 ; i < nb_ActiveSet.size() ; i++){nb_total_ActiveSet = nb_total_ActiveSet + nb_ActiveSet[i];}
    std::cout << "nb_total_ActiveSet : "<<nb_total_ActiveSet<< std::endl;

    std::cout << "--END--    "<<lastType<<"    --END--"<<std::endl;

}
