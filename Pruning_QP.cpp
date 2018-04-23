#include "Pruning_QP.h"
#include <iostream>
#include <sstream>
#include <string>

#include <stdio.h>
#define MAXCOL 1000     /* maximum number of colums */


Pruning_QP::Pruning_QP(){}
Pruning_QP* Pruning_QP::constructor(){return(new Pruning_QP());}


///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///
///##### add #####/// ///##### add #####/// ///##### add #####/// ///##### add #####///

///##### addIn #####/// ///##### addIn #####/// ///##### addIn #####/// ///##### addIn #####///

void Pruning_QP::addIn(Gauss& cost, double& bound)
{
	Ball* newball = new Ball(cost.getC(),(bound-cost.minimum())/cost.getA());
	newball->findNormC();
	m_inB.push_back(newball);
	
	/// create pointInB as center of m_inB[0]
	if(m_inB.size()==1){
		int n = m_inB[0]->getC().size();
		for (int i = 0; i < n; i++){
			pointInB.push_back(m_inB[0]->getC()[i]);
		}
	}

}


///##### addOut #####/// ///##### addOut #####/// ///##### addOut #####/// ///##### addOut #####///

void Pruning_QP::addOut(Gauss& cost, double& bound)
{
	Ball* newball = new Ball(cost.getC(),(bound-cost.minimum())/cost.getA());
	newball->findNormC();
	
	/// add an out Ball (in m_outB) if intersection with m_inB[0] exists
	if(m_inB[0]->intersect(newball)){
		m_outB.push_back(newball);
		activeOut.push_back(m_outB.size()-1);
	}
}


///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///
///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####/// ///##### isPruned #####///


bool Pruning_QP::isPruned()
{

	bool response = false;  /// no pruning

	/// prune unused set in m_outB
	pruneActiveOut();

	bool intersection = false;
	bool isOnePointPruned = false;

	int k = 0;
	int length = activeOut.size();


/////////////////
    while (k < length && intersection == false)
     {
        intersection = convexQP(activeOut[k]);   ///intersection = true if min(convexQP) inside the out ball
        if(intersection == true){intersection = vertexEnum(activeOut[k]);}  ///if intersection = true => test vertexEnum
        k = k+1;
    }
/////////////////

    if(intersection == false){isOnePointPruned = getOnePoint();
	/// if no intersection, test a point, if no point => true, else...
	if(isOnePointPruned == true){response = true;}else{
		double test = 0;
		int n = pointInB.size();
		
		///test pointInB for all balls in m_out
		k = 0;
     		while (k < length && isOnePointPruned == false)
     		{
			test = 0;
			for (int i = 0; i < n; i++)
				test = test +  (pointInB[i]-m_outB[activeOut[k]]->getC()[i])*(pointInB[i]-m_outB[activeOut[k]]->getC()[i]);
			if(test - m_outB[activeOut[k]]->getR2() < 0){response = true;}
			k = k+1;
		}			
	}

	
    }

	//if(intersection == true){response = false;}
	//if(intersection == false){if(isOnePointPruned == true){response = true;}}


    return(response);
}


///##### convexQP #####/// ///##### convexQP #####/// ///##### convexQP #####/// ///##### convexQP #####///
///##### convexQP #####/// ///##### convexQP #####/// ///##### convexQP #####/// ///##### convexQP #####///

bool Pruning_QP::convexQP(int k)
{

    bool resp = false;
	//// library/QP //// library/QP //// library/QP //// library/QP //// library/QP //// library/QP
    quadprogpp::Matrix<double> G, CE, CI;
    quadprogpp::Vector<double> g0, ce0, ci0, x;
	int n, m, p;
	
    //dimension n
    n = m_inB[0]->getC().size();

    x.resize(n); //response vector
	//NO EQUALITY CONSTRAINT

    m = 0;
    CE.resize(n, m);
    ce0.resize(m);

    ///OBJECTIVE FUNCTION 0.5*xGx + g0.x
    G.resize(n, n);
    {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
                if(i==j){G[i][j]= 2;}else{G[i][j]= 0;};
	}
    g0.resize(n);
    {
		for (int i = 0; i < n; i++)
  			g0[i]=-2*m_outB[k]->getC()[i];
	}

    ///CONSTRAINTS : CI^T x + ci0 >= 0
    int p_in = m_inB.size();
	p = m_inB.size() + m_outB.size()-1;
    CI.resize(n, p);
    {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < p_in; j++)
				CI[i][j]=-2*(m_outB[k]->getC()[i]-m_inB[j]->getC()[i]);
        int l = 0;

        for (int i = 0; i < n; i++){
            l=0;
			for (int j = p_in; j < p; j++){
                if(l==k){l=l+1;}
				CI[i][j]=2*(m_outB[k]->getC()[i]-m_outB[l]->getC()[i]);
				l=l+1;
            }
        }
    }

    ci0.resize(p);
    {
		for (int j = 0; j < p_in; j++)
			ci0[j]= -m_outB[k]->getR2() + m_inB[j]->getR2() + m_outB[k]->getNormC() - m_inB[j]->getNormC();
        int l = 0;
        for (int j = p_in; j < p; j++){
            if(l==k){l=l+1;}
			ci0[j]= m_outB[k]->getR2() - m_outB[l]->getR2() - m_outB[k]->getNormC() + m_outB[l]->getNormC();
			l=l+1;
        }
	}

    solve_quadprog(G, g0, CE, ce0, CI, ci0, x);
    double res = 0;
    for (int i = 0; i < n; i++)
        res = res + (x[i]-m_outB[k]->getC()[i])*(x[i]-m_outB[k]->getC()[i]);

    res = res - m_outB[k]->getR2();
    resp = res<0;
	
    return(resp);
}


///##### createCONSTRAINT #####/// ///##### createCONSTRAINT #####/// ///##### createCONSTRAINT #####/// ///##### createCONSTRAINT #####///
///##### createCONSTRAINT #####/// ///##### createCONSTRAINT #####/// ///##### createCONSTRAINT #####/// ///##### createCONSTRAINT #####///



void Pruning_QP::createCONSTRAINT(lrs_dic *P, lrs_dat *Q, int k)
	{
	long num[MAXCOL];
	long den[MAXCOL];
	
	int n, p, l;
	//dimension n
	n = m_inB[0]->getC().size();

	///CONSTRAINTS : B + Ax >= 0
	int p_in = m_inB.size();
	p = m_inB.size() + m_outB.size()-1;  ///number of inequality constraints

	///###DEN
	for (int i = 0; i < n+1; i++){den[i] = 10000;}

	//std::cout<<"---------------- k "<<k<<std::endl;
	//std::cout<<"&&&m_inB.size&& "<<p_in<<std::endl;
	//std::cout<<"m_outB.size-1&& "<<p-p_in<<std::endl;

	///###NUM inB
	for (int j = 0; j < p_in; j++){
		for (int i = 1; i < n+1; i++){
			num[i] = (int)((-2*(m_outB[k]->getC()[i-1]-m_inB[j]->getC()[i-1]))*10000);
		}
		num[0] =  (int)((-m_outB[k]->getR2() + m_inB[j]->getR2() + m_outB[k]->getNormC() - m_inB[j]->getNormC())*10000);
		//std::cout<<"num0_inB "<<j<<" : "<<num[0]<<std::endl;
		lrs_set_row(P,Q,j+1,num,den,GE);
	}

	///###NUM outB
	l=0;

	for (int j = p_in; j < p; j++){
	if(l==k){l=l+1; 
		//std::cout<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<std::endl;
	}
		for (int i = 1; i < n+1; i++){
			num[i] = (int)((2*(m_outB[k]->getC()[i-1]-m_outB[l]->getC()[i-1]))*10000);
		}
		num[0] =  (int)((m_outB[k]->getR2() - m_outB[l]->getR2() - m_outB[k]->getNormC() + m_outB[l]->getNormC())*10000);
		//std::cout<<"num0_outB "<<l<<" : "<<num[0]<<std::endl;
		l=l+1;
		lrs_set_row(P,Q,j+1,num,den,GE);
	}
}


///##### vertexEnum #####/// ///##### vertexEnum #####/// ///##### vertexEnum #####/// ///##### vertexEnum #####///
///##### vertexEnum #####/// ///##### vertexEnum #####/// ///##### vertexEnum #####/// ///##### vertexEnum #####///


bool Pruning_QP::vertexEnum(int k)
{
    bool resp = false;

    std::vector<double> res;
	//std::cout<<"vertexEnum  ----   vertexEnum ----   vertexEnum ----   vertexEnum ----   vertexEnum "<<k<<std::endl;


    lrs_dic *P;	/* structure for holding current dictionary and indices  */
    lrs_dat *Q;	/* structure for holding static problem data             */
    lrs_mp_vector output;	/* one line of output:ray,vertex,facet,linearity */
    lrs_mp_matrix Lin;    /* holds input linearities if any are found      */

    lrs_init ("\n*vedemo:");
    Q = lrs_alloc_dat ("LRS globals");

    Q->n = m_inB[0]->getC().size()+1;           /* number of input columns         (dimension + 1 )  */
    Q->m = m_inB.size() + m_outB.size()-1;         /* number of input rows = number of inequalities     */

    output = lrs_alloc_mp_vector (Q->n);
    P = lrs_alloc_dic (Q);   /* allocate and initialize lrs_dic      */


if(Q->m < Q->n){
	resp = true;
	//std::cout<<"INFINITE___INFINITE___INFINITE"<<std::endl;
}else{

    createCONSTRAINT(P,Q,k);
    //lrs_getfirstbasis (&P, Q, &Lin, FALSE);
    if (!lrs_getfirstbasis (&P, Q, &Lin, FALSE)){
	//std::cout<<"  NO Feasible region ----  NO Feasible region  ----   NO Feasible region ----  NO Feasible region  ----    "<<std::endl;
	resp = false;
}else{
    
	double value = 0; 
	bool continu = true;
    do
    {
        for (int j = 0; j <= P->d; j++)
            if (lrs_getsolution(P, Q, output, j)){
             //   std::cout<<std::endl;
             //   std::cout<<" &&& ";

           //     lrs_printoutput(Q, output);

                if (Q->hull || zero (output[0])){ ////// INFINITE DIRECTION exist
                  //  std::cout<<std::endl;
                  //  std::cout<<"INFINITE DIRECTION  "<<std::endl;
			j = P->d +1;
			resp = true;
			continu = false;

                }else{  ////// Vertex case
                 //   std::cout<<std::endl;
                 //   std::cout<<"VERTEX"<<std::endl;
                    for (long h = 1; h < Q->n; h++){
			//std::cout<<double(output[h][1])/double(output[0][1])<<" ";
                        value = value + (double(output[h][1])/double(output[0][1]) - m_outB[k]->getC()[h-1])*(double(output[h][1])/double(output[0][1]) - m_outB[k]->getC()[h-1]);
                    }
			if(value>m_outB[k]->getR2()){
				resp = true;
				continu = false;
			}
              //  std::cout<<std::endl;
		//std::cout<<std::endl;
                }
            }
    }while(lrs_getnextbasis(&P, Q, FALSE)&(continu == true));
	}

	} //// test !lrs_getfirstbasis


   lrs_clear_mp_vector (output, Q->n);
   lrs_free_dic (P,Q);
   lrs_free_dat (Q);


 		if(resp == false){
//std::cout<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" <<std::endl;
}


    return(resp);
}


///##### getOnePoint #####/// ///##### getOnePoint #####/// ///##### getOnePoint #####/// ///##### getOnePoint #####///
///##### getOnePoint #####/// ///##### getOnePoint #####/// ///##### getOnePoint #####/// ///##### getOnePoint #####///

bool Pruning_QP::getOnePoint()
{
    bool resp = false;

    quadprogpp::Matrix<double> G, CE, CI;
    quadprogpp::Vector<double> g0, ce0, ci0, x;
	int n, m;
	
    //dimension n
    n = m_inB[0]->getC().size();

    //number of constraints
    int LAST = m_inB.size()-1;

    x.resize(n); //response vector
	//NO EQUALITY CONSTRAINT

    m = 0;
    CE.resize(n, m);
    ce0.resize(m);

    ///OBJECTIVE FUNCTION 0.5*xGx + g0.x
    G.resize(n, n);
    {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
                		if(i==j){G[i][j]= 2;}else{G[i][j]= 0;};
	}
    g0.resize(n);
    {
		for (int i = 0; i < n; i++)
  			g0[i]=-2*m_inB[LAST]->getC()[i];
	}

    ///CONSTRAINTS : CI^T x + ci0 >= 0
    CI.resize(n, LAST);
    {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < LAST; j++)
				CI[i][j]=-2*(m_inB[LAST]->getC()[i]-m_inB[j]->getC()[i]);
    }

    ci0.resize(LAST);
    {
		for (int j = 0; j < LAST; j++)
			ci0[j]= -m_inB[LAST]->getR2() + m_inB[j]->getR2() + m_inB[LAST]->getNormC() - m_inB[j]->getNormC();
    }

	/// SOLVE QP PROBLEM -> solution in x, size n
    solve_quadprog(G, g0, CE, ce0, CI, ci0, x);


    double res = 0;
    for (int i = 0; i < n; i++)
        res = res + (x[i]-m_inB[LAST]->getC()[i])*(x[i]-m_inB[LAST]->getC()[i]);

    if(res - m_inB[LAST]->getR2()<=0){ /// if result inside inB
    	for (int i = 0; i < n; i++){pointInB[i] = x[i];}
    }

    if(res - m_inB[LAST]->getR2()>0){ /// if result outside inB
	 double res2 = 0;
         for (int i = 0; i < n; i++)
        res2 = res2 +  (pointInB[i]-m_inB[LAST]->getC()[i])*(pointInB[i]-m_inB[LAST]->getC()[i]);
	if(res2 - m_inB[LAST]->getR2() > 0){resp = true;}

    }

return(resp);

}


///##### pruneActiveOut #####/// ///##### pruneActiveOut #####/// ///##### pruneActiveOut #####/// ///##### pruneActiveOut #####///
///##### pruneActiveOut #####/// ///##### pruneActiveOut #####/// ///##### pruneActiveOut #####/// ///##### pruneActiveOut #####///

void Pruning_QP::pruneActiveOut()
{
    int last = m_inB.size()-1;
    for (unsigned int i = 0; i < activeOut.size(); i++){
            if(!m_outB[activeOut[i]]->intersect(m_inB[last])){activeOut[i] = 0;}
    }
    unsigned int j = 0;
    while(j < activeOut.size()){
        if(activeOut[j]==0){
            activeOut.erase(activeOut.begin()+j);
        }else{j=j+1;}
    }

}


///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///
///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///



void Pruning_QP::show(){
    std::cout << "#Pruning_QPPruning_QPPruning_QP#  "<<std::endl;
}

