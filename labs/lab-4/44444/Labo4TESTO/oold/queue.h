#include <iostream>

#include "token.h"

using namespace std;

namespace queue{
typedef token Elem;       

struct cell{
    Elem elem;
    cell *next;
    cell *prev;
};

typedef cell *Queue;

const Queue EMPTYQUEUE = NULL;

bool isEmpty(const Queue&);
void enqueue(Elem, Queue&);
Elem dequeue(Queue&);
Elem first(const Queue&);
void createEmpty(Queue&);
void clear(const Queue&);
}