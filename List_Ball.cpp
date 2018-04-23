#include "List_Ball.h"

#include<iostream>

using namespace std;

List_Ball::List_Ball(){}


void List_Ball::show()
{
    Ball *ptr ;
    element* temp = getFirstElt();

    while(temp != NULL)
    {
        ptr = (Ball *) temp->getContent();
        cout<<ptr->getR2()<<" - ";
        temp = temp->nxt;
    }
    cout<<endl;
}
