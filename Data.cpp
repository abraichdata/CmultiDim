#include "Data.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Data::Data(std::string filename){

    myfilename = filename;
    string path("../"+filename);
    ifstream inputFile(path.c_str());
    string line, temp;
    getline(inputFile,line);

    ///nb of columns
    int nbCol(0);
    stringstream ss;
    ss.clear();
    ss << line;
    while (ss >> temp){nbCol = nbCol+1;}
    p = nbCol;

 ///nb of raws
    int nbRaw(1);
    while(getline(inputFile, line)){nbRaw = nbRaw+1;}
     n = nbRaw;
    inputFile.close();

///downloading in vectPoints
    ifstream inputFileAgain(path.c_str());
    for (int i = 0 ; i < n ; i++)
    {
        Point pt(p);
        double temp = 0;
        for (int j = 0 ; j < p ; j++){
                inputFileAgain >> temp;
                pt.add(temp,j);}
        //for (int j = 0 ; j < p ; j++){inputFileAgain >> pt.y[j];}
        vectPoints.push_back(pt);
    }
    inputFileAgain.close();
}



int Data::getp(){return(p);}
int Data::getn(){return(n);}
std::vector<Point> Data::getvectPoints(){return(vectPoints);}


///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///
///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///

void Data::show()
{
    cout<<"File : "<<myfilename<<endl;
    cout<<"number of Columns : "<<p<<endl;
    cout<<"number of Raws : "<<n<<endl;
    cout<<"Data : "<<endl;
      for (int i = 0 ; i < n ; i++)
    {
        cout<<i<<"  --- ";
        for (int j = 0 ; j < p ; j++){cout<<vectPoints[i].get(j)<<"  ";}
        cout<<endl;
    }
}
