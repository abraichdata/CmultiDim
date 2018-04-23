#ifndef LIST_H
#define LIST_H

#include <cstdlib>

struct element
{
    void *content;
    element *nxt;

    void* getContent(){return(content);}
};


class List
{
    public:
        List();
        virtual ~List();

        element* getFirstElt();
        element* getCurrentElt();

        void add_Element(void*);

        void move_To_FirstElt();
        void move();

        void deleteFirstElt();
        void deleteElt(element *elt);

        bool isEnd();
        int size();

    private:
        element* firstElt;
        element* currentElt;
};

#endif // LIST_H
