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
	node* aux = l->next;
	node* auxbis;
	while(aux!=l){
		auxbis = aux->next;
		delete aux;
		aux = auxbis;
	}
	l->next = l;
	l->prev = l;
}


Elem list::get(int pos, const List& l)        /* restituisce l'elemento in posizione pos se presente; restituisce un elemento che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
{
	node* aux = l->next;
	int n = 0;
	while(aux!=l&&pos!=n){
		n++;
		aux = aux->next;
	}
	if(n==pos){
		return aux->info;
	}
	else return 0;
}


void list::set(int pos, Elem e, const List& l)        /* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
{
	node* aux = l->next;
	int n = 0;
	while(aux!=l&&pos!=n){
		n++;
		aux = aux->next;
	}
	if(n==pos){
		aux->info = e;
	}
}


void list::add(int pos, Elem e, const List& l)        /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
{
	node* aux = l->next;
	int n = 0;
	while(aux!=l&&pos!=n){
		n++;
		aux = aux->next;
	}
	node *aux2 = new node;
	aux2->info = e;
	(aux->prev)->next = aux2;
	aux2->prev = aux->prev;
	aux->prev = aux2;
	aux2->next = aux;
}


void list::addRear(Elem e,  const List& l)        /* inserisce l'elemento alla fine della lista */
{
    node* aux = new node;
    aux->info = e;
    aux->next = l;
    aux->prev = l->prev;
    (l->prev)->next = aux;
    l->prev = aux;
}


void list::addFront(Elem e, const List& l)        /* inserisce l'elemento all'inizio della lista */
{
	node *aux = new node;
	aux->info = e;
	aux->next = l->next;
	aux->prev = l;
	(l->next)->prev = aux;
	l->next = aux;
}


void list::removePos(int pos, const List& l)      /* cancella l'elemento in posizione pos dalla lista */
{
	int n = 0;
	node *aux = l->next;
	while(aux!=l&&n!=pos){
		n++;
		aux = aux->next;
	}
	if(n==pos){
		(aux->prev)->next = aux->next;
		(aux->next)->prev = aux->prev;
		delete aux;
		return;
	}
	cout << "posizione non valida\n";
}


void list::removeEl(Elem e, const List& l)        /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
{
	node* aux = l->next;
	node* aux2;
	while(aux!=l){
		if(aux->info==e){
			(aux->prev)->next = aux->next;
			(aux->next)->prev = aux->prev;
			aux2 = aux->next;
			delete aux;
			aux = aux2;
		}
		else aux = aux->next;
	}
}


bool list::isEmpty(const List& l)         /* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
{
	return(l==l->next);
}


int list::size(const List& l)           /* restituisce la dimensione della lista */
{
	int n = 0;
	node* aux = l->next;
	while(aux!=l){
		++n;
		aux = aux->next;
	}
	return n;
}


void list::createEmpty(List& l)           /* crea la lista vuota */
{
	l = new node;
	l->next = l;
	l->prev = l;
}
