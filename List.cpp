#include "List.h"

#include <iostream>

using namespace std; ///pour utiliser cout et endl de iostream

List::List()
{
    firstElt = NULL;
    currentElt = NULL;
}

List::~List()
{
    element *next;
    currentElt = firstElt;
    while(currentElt != NULL)
    {
        next = currentElt->nxt;
        delete currentElt;
        currentElt = next;
    }
}


element *List::getFirstElt(){return(firstElt);}
element *List::getCurrentElt(){return(currentElt);}


void List::add_Element(void* elt)
{
    element *address = new element;
    address->nxt = firstElt;
    address->content = elt;
    firstElt = address;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void List::move_To_FirstElt(){currentElt = firstElt;}

//void List::move(){if(currentElt != NULL){currentElt = currentElt->nxt;}}
void List::move(){currentElt = currentElt->nxt;}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void List::deleteFirstElt()
{
        element *next;
        next = firstElt->nxt;
        delete firstElt->content;
        firstElt = next;
        currentElt = firstElt;
}

void List::deleteElt(element *elt)
{
        elt->nxt = currentElt->nxt;
        delete currentElt->content;
        currentElt = elt;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool List::isEnd(){return(currentElt == NULL);}

int List::size()
{
    int nb = 0;
    element* temp = firstElt;
    while(temp != NULL)
    {
        nb = nb + 1;
        temp = temp->nxt;
    }
    return(nb);
}


