#include "List_ActiveSet.h"

#include<iostream>

using namespace std;

List_ActiveSet::List_ActiveSet(){}

///##### dynamic_programming_algorithm #####/// ///##### dynamic_programming_algorithm #####///
///##### dynamic_programming_algorithm #####/// ///##### dynamic_programming_algorithm #####///

void List_ActiveSet::dyn_prog_algo(Point& pt, double& mini, int& label, int t)
{
    double temp_mini;
    move_To_FirstElt();

    //INITIALISATION
    ActiveSet *ptr = (ActiveSet *) getCurrentElt()->getContent();
    ptr->addPoint(pt);
    mini = ptr->getCost().minimum();
    label = ptr->getLabel();
    move();

    while(!isEnd())
    {
        ptr = (ActiveSet *) getCurrentElt()->getContent();

        ///### change COST
        ptr->addPoint(pt);
        ///### get MINIMUM
        temp_mini = ptr->getCost().minimum();

        if(temp_mini < mini){
                mini = temp_mini;
                label = ptr->getLabel();
        }
        move();
    }
}


///##### topology #####/// ///##### topology #####/// ///##### topology #####///
///##### topology #####/// ///##### topology #####/// ///##### topology #####///


void List_ActiveSet::topology(double bound)
{

    move_To_FirstElt();

    //INITIALISATION_ FIRST ELEMENT
    ActiveSet *firstPtr = (ActiveSet *) getFirstElt()->getContent();
    firstPtr->addIn(bound);
    ActiveSet *ptr;
    element *ptr_Elt_before = getCurrentElt();

    move();

    while(!isEnd())
    {
        ptr = (ActiveSet *) getCurrentElt()->getContent();
        ptr->addIn(bound); ///add a ball of intersection

        ///PRUNING
        if(ptr->isElementPruned()){deleteElt(ptr_Elt_before);}else{
           firstPtr->addOut(ptr,bound); ///add ball of exclusion in first ActiveSet
        }

        ptr_Elt_before = getCurrentElt();
        move();
    }

    ///First Element PRUNING
    if(firstPtr->isElementPruned()){deleteFirstElt();}

}


///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///
///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####/// ///##### show #####///

void List_ActiveSet::show()
{
    ActiveSet *ptr;
    element* temp = getFirstElt();

    while(temp != NULL)
    {
        ptr = (ActiveSet *) temp->getContent();
        ptr->show();
        temp = temp->nxt;
    }
}
