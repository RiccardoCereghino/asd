#include <iostream>
#include <stdexcept>

#include "token.h"
	
using namespace std;

// Implementa QUEUE 
namespace queue{
const int BLOCKDIM = 1000;

// Gli elementi della QUEUE sono token
typedef token Elem;       

typedef struct {
    Elem* queue;
    int size;
    int maxsize;
} Queue;

const Elem EMPTYELEM = {"", SCONOSCIUTO};


//typedef int Queue; // Definizione di Queue fasulla. MODIFICARE!

bool isEmpty(const Queue&);
void enqueue(Elem, Queue&);  /* inserisce l'elemento alla fine della lista */
Elem dequeue(Queue&);        /* cancella l'elemento in prima posizione (se esiste) e lo restituisce */
void add(int, Elem, Queue&);
Elem remove(int, Queue&);
}
