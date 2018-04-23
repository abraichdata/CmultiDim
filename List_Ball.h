#ifndef LIST_BALL_H
#define LIST_BALL_H


#include "List.h"
#include "Ball.h"

class List_Ball: public List, public Ball
{
    public:
        List_Ball();
        void show();
};

#endif // LIST_BALL_H
