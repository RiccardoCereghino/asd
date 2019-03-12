/*
Cereghino Riccardo
Ouerghi Sarah
Martins Tobi Gbekeleoluwa
*/

// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

#include "ASD-doubly-linked-list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
Elem info;
node *prev;
node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'  */
/*************************************************/

void readFromStream(istream& str, List& l)
{
    createEmpty(l);
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (e != FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {     
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
}

void readFromFile(string nome_file, List& l)  /* legge il contenuto di una lista da file */
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}



void readFromStdin(List& l)         /* legge il contenuto di una lista da standard input */
{
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}


void print(const List& l)           /* stampa la lista */
{
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l)     // avanza finche' non finisce la lista
     {
      cout << q->info << "; ";
      q = q->next; 
      }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

void list::clear(const List& l)                 /* "smantella" la lista svuotandola */
{
    node *aux = l;
    while(aux->next != l){
        aux =  aux->next;   
        delete aux->prev;
    }
    l->next = l;
    l->prev = l;
}


Elem list::get(int pos, const List& l)        /* restituisce l'elemento in posizione pos se presente; restituisce un elemento che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
{
    node *aux = l->next;
    int i=0;
    Elem r = 0;
    if(pos < size(l)){
        while(i < pos){
            aux=aux->next;
            ++i;
        }
        r = aux->info;
    }
    return r;
}


void list::set(int pos, Elem e, const List& l)        /* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
{
    List aux = l->next;
    int i=0;
    if(pos < size(l)){
        while(i<pos){
            aux = aux->next;
            i++;
        }
        aux->info = e;
    }
}


void list::add(int pos, Elem e, const List& l)        /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
{                                               
    List aux = l->next;
    int i=0;
    if(pos < size(l)){
        while(i<pos){
            aux = aux->next;
            i++;
        }

        node *cell = new node;
        cell->info = e;
        cell->next = aux;
        cell->prev = aux->prev;
        
        aux->prev->next = cell;
        aux->prev = cell;
    }
}


void list::addRear(Elem e,  const List& l)        /* inserisce l'elemento alla fine della lista */
{
    node* temp = new node;
    temp->info = e;
    temp->prev= l->prev;
    l->prev->next = temp;
    temp->next = l;
    l->prev = temp;
}


void list::addFront(Elem e, const List& l)        /* inserisce l'elemento all'inizio della lista */
{
    node* temp = new node;
    temp->info = e;
    
    temp->next= l->next;
    l->next->prev = temp;
    temp->prev = l;
    l->next = temp;

}


void list::removePos(int pos, const List& l)      /* cancella l'elemento in posizione pos dalla lista */
{
    if(size(l)>0){        
        List aux = l->next;
        int i=0;
        while(i<pos){
            aux = aux->next;
            ++i;
        }
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
        delete aux;
    }
}


void list::removeEl(Elem e, const List& l)        /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
{
    List aux = l->next;
    int i = 0;
    while(aux != l){
        if(aux->info == e){
            removePos(i, l);
            --i;
        }
        aux=aux->next;
        ++i;
    }
}

bool list::isEmpty(const List& l)         /* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
{
  return l->next == l;
}


int list::size(const List& l)           /* restituisce la dimensione della lista */
{
   int i=0;
   node* aux = l;
   while(aux->next != l){
        aux=aux->next;
        i++;
   }
   return i;
}


void list::createEmpty(List& l)           /* crea la lista vuota */
{
    node* aux = new node;
    aux->next = aux;
    aux->prev = aux;
    l = aux;
}
