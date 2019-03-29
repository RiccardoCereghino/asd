#include "stack.h"

using namespace stack;

/****************************************************************/
bool stack::isEmpty(const Stack& s)
{
    return s==EMPTYSTACK;
}

/****************************************************************/
void stack::push(const Elem x, Stack& s) 
{
    Stack aux = new cell; 
    aux->elem=x;
    aux->next=s;
    s = aux;
}


/****************************************************************/
Elem stack::pop(Stack& s)
{
    if (isEmpty(s)) return EMPTYELEM;
    cell* cur=s;
    s=s->next;
    Elem e = cur->elem;
    delete cur;
    return e;
}

/****************************************************************/

