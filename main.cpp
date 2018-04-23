#include <iostream>
#include <fstream>

#include"Data.h" ///string+vector
#include"Omega.h" ///vector
#include <math.h>

#include <time.h>

//#include <iomanip> ///Set Precision scientific

//using namespace std;

int main()
{

   // cout << fixed << scientific <<setprecision(10); /// fixed scientific notation for numbers

///////////////////////////////////////////////////////////////
///Choice of a file and data downloading
    std::string file = "CmultiDim/dataG2.txt";
    Data data = Data(file);
    data.show();
    int n = data.getn();
    std::cout<<"PENALITY : "<<2*log(n)<<std::endl;

///////////////////////////////////////////////////////////////
double penalty = 2*log(n);


/// Create an OBJECT OMEGA
Omega omega(penalty);
clock_t tStart = clock();
/// Pruned Penalized Dynamic Programming ALGORITHM
omega.segment(data, "");
//double exec_time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
omega.show();
printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

/// Create an OBJECT OMEGA
Omega omega4(penalty);
clock_t tStart4 = clock();
/// Pruned Penalized Dynamic Programming ALGORITHM
omega4.segment(data, "balls");
omega4.show();
printf("Time taken: %.8fs\n", (double)(clock() - tStart4)/CLOCKS_PER_SEC);



/// Create an OBJECT OMEGA
Omega omega5(penalty);
clock_t tStart5 = clock();
/// Pruned Penalized Dynamic Programming ALGORITHM
omega5.segment(data, "ballsV");
omega5.show();
printf("Time taken: %.8fs\n", (double)(clock() - tStart5)/CLOCKS_PER_SEC);


/// Create an OBJECT OMEGA
Omega omega6(penalty);
clock_t tStart6 = clock();
/// Pruned Penalized Dynamic Programming ALGORITHM
omega6.segment(data, "ball2");
omega6.show();
printf("Time taken: %.8fs\n", (double)(clock() - tStart6)/CLOCKS_PER_SEC);


/// Create an OBJECT OMEGA
Omega omega7(penalty);
clock_t tStart7 = clock();
/// Pruned Penalized Dynamic Programming ALGORITHM
omega7.segment(data, "block");
omega7.show();
printf("Time taken: %.8fs\n", (double)(clock() - tStart7)/CLOCKS_PER_SEC);

/// Create an OBJECT OMEGA
Omega omega8(penalty);
clock_t tStart8 = clock();
/// Pruned Penalized Dynamic Programming ALGORITHM
omega8.segment(data, "QP");
omega8.show();
printf("Time taken: %.8fs\n", (double)(clock() - tStart8)/CLOCKS_PER_SEC);


/// Create an OBJECT OMEGA
Omega omega3(penalty);
clock_t tStart3 = clock();
/// Pruned Penalized Dynamic Programming ALGORITHM
omega3.segment(data, "pelt");
omega3.show();
printf("Time taken: %.8fs\n", (double)(clock() - tStart3)/CLOCKS_PER_SEC);




///////////////////////////////////////////////////////////////
/// Show the result
//omega.show();


int hold;
std::cin>>hold;

    return 0;
}
