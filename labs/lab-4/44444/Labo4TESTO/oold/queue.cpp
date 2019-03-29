#include "queue.h"

using namespace queue;

/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/
/****************************************************************/
bool queue::isEmpty(const Queue& q){
    return q->next == q;
}
/****************************************************************/
// Enqueues elem in queue
/****************************************************************/
void queue::enqueue(Elem e, Queue& q){
    cell* temp = new cell;
    temp->elem = e;
    temp->prev= q->prev;
    q->prev->next = temp;
    temp->next = q;
    q->prev = temp;
}
/****************************************************************/
// Dequeues elem from queue
/****************************************************************/
Elem queue::dequeue(Queue& q){
	Elem e = queue::first(q);
	if(!queue::isEmpty(q)){
		Queue aux = q->next;
		aux->next->prev = q;
		q->next = aux->next;
		delete aux;
	}
	return e;
}
/****************************************************************/
Elem queue::first(const Queue& q){
	return q->next->elem;
}
/****************************************************************/
// Creates empty queue
/****************************************************************/
void queue::createEmpty(Queue& q)
{
    cell* aux = new cell;
    aux->elem = {"",SCONOSCIUTO};
    aux->next = aux;
    aux->prev = aux;
    q = aux;
}

/****************************************************************/
// Empties queue
/****************************************************************/
void queue::clear(const Queue& q){
    cell *aux = q;
    while(aux->next != q){
        aux =  aux->next;   
        delete aux->prev;
    }
    q->next = q;
    q->prev = q;
}
