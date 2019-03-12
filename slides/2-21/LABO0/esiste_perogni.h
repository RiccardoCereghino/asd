#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>
#include <fstream> 
#include <stdlib.h>     /* srand, rand */

using namespace std;

enum Error {OK, FAIL, PRESENT, EMPTY, NOT_FOUND};

typedef int Elem;      // tipo base 
struct cell;           // definita nel file ausiliario
typedef cell *Seq;     // una sequenza e' univocamente identificata dal puntatore al suo primo elemento
const int FINEINPUT = -1000000; // serve per leggere sequenze da file: dobbiamo sapere quando terminare la lettura
const Seq EMPTY_SEQ = NULL; // costante che indica la sequenza vuota


void createEmpty(Seq&);                    /* crea la sequenza vuota */
Error insertElem(const Elem x, Seq& s);    /* inserisce l'elemento in prima posizione; restituisce FAIL in caso di errore e PRESENT se l'elemento era gia' presente; se tutto ok, restituisce OK */
int size(const Seq&);                      /* restituisce il numero degli elementi di una sequenza */
bool member(const Elem, const Seq&);       /* restituisce il valore dell'espressione booleana "l'elemento appartiene alla sequenza" */
bool isEmpty(const Seq&);                  /* restituisce il valore dell'espressione booleana "la sequenza e' vuota" */
// bool isThereLesserThan(const Elem, const Seq&); /* restituisce true se nella sequenza c'e' un valore minore dell'elemento passato come primo argomento */
bool areAllGreaterEqThan(const Elem, const Seq&); /* restituisce true se tutti gli elementi della sequenza sono maggiori o uguali all'elemento passato come primo argomento */
bool isThereLesserThanRec(const Elem, const Seq&); /* restituisce true se nella sequenza c'e' un valore minore dell'elemento passato come primo argomento, versione ricorsiva */
int sumRec(const Seq&); /* restituisce la somma degli elementi presenti nella lista, versione ricorsiva */
int prodRec(const Seq&); /* restituisce il prodotto degli elementi presenti nella lista, versione ricorsiva */


Seq seqReadFromFile(string);
Seq seqReadFromStdin();
void seqPrint(const Seq&);
