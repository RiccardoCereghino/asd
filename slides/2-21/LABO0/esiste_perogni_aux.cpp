#include "esiste_perogni.h" 

struct cell {
    Elem head;  // una sequenza e' costituita da una head che è un elemento
    Seq  tail;  // e da una tail che e' a sua volta una sequenza (e' intrinsecamente una definizione ***ricorsiva*** di sequenza)
};


/****************************************************************/
/****************************************************************/

void createEmpty(Seq& s)
{
   s = EMPTY_SEQ;   // assegno il valore EMPTY_SEQ a s
}

/****************************************************************/
bool isEmpty(const Seq& s)  
{
   return (s == EMPTY_SEQ);  
// ***NON*** SCRIVERE ASSOLUTAMENTE
// if (s == EMPTY_SEQ) return true; else return false;  
// E' UN PESSIMO MODO DI IMPLEMENTARE UNA FUNZIONE BOOLEANA CHE DEVE SOLO RESTITUIRE IL VALORE DI UN'ESPRESSIONE
}

/****************************************************************/
int size(const Seq& s)
{
   if (isEmpty(s))  // se la sequenza e' vuota la sua cardinalita' e' 0 
      return 0; 
   else 
      return size(s->tail)+1; // altrimenti e' la cardinalita' del resto della sequenza + 1
}


/****************************************************************/
bool member(const Elem e, const Seq& s)
// se si sa che la sequenza è implementata mediante una lista ordinata, e' possibile ottimizzare il codice; in questo caso non facciamo alcuna assunzione
{
   if (isEmpty(s))  // se la sequenza e' vuota l'elemento non c'e': restituisco false
      return false; 
   
   if (s->head == e)  // se la head e' l'elemento cercato restituisco true
      return true;
   else 
      return member(e, s->tail); // altrimenti chiamo ricorsivamente sulla coda, restituendo il risultato della chiamata ricorsiva
}


/****************************************************************/
Error insertElem(const Elem x, Seq& s) 
// insertElem aggiunge sempre in prima posizione; non rispetta quindi l'ordine "temporale" con cui gli elementi vengono inseriti, ma e' molto piu' efficiente rispetto a un inserimento in coda; se stiamo implementando un insieme, in cui la posizione degli elementi non conta, va benissimo inserire nel punto che rende l'operazione piu' efficiente
{
    if (member(x, s)) 
       return PRESENT; // l'elemento e' gia' presente, non lo aggiungo

    cell *aux;
    try  { aux = new cell; }
    catch(...) { return FAIL;} //heap esaurito
    aux->head=x;
    aux->tail=s;
    s = aux;
    return OK;
}

/****************************************************************/
bool isThereLesserThan(const Elem elem, const Seq& l){
   Seq cur=l;
   while (cur!=EMPTY_SEQ) 
   {
   if(cur->head < elem)
     return true;
   cur=cur->tail;
   }
   return false;
}


/****************************************************************/
bool areAllGreaterEqThan(const Elem elem, const Seq& l){
   return (!isThereLesserThan(elem, l)); // se l'insieme e' vuoto restituisce true
}


/****************************************************************/
bool isThereLesserThanRec(const Elem elem, const Seq& l){
   if (isEmpty(l)) return false;        // se l'insieme e' vuoto restituisce false
   if (l->head < elem) return true; 
   else return isThereLesserThanRec(elem, l->tail);
}


/****************************************************************/
int sumRecAux(const Seq& l){
   if (isEmpty(l)) return 0;
   else return l->head + sumRecAux(l->tail);
}


/****************************************************************/
int sumRec(const Seq& l){
   if (isEmpty(l)) return -1;
   else return sumRecAux(l);
}


/****************************************************************/
int prodRecAux(const Seq& l){
   if (isEmpty(l)) return 1;
   else return l->head * prodRecAux(l->tail);
}


/****************************************************************/
int prodRec(const Seq& l){
   if (isEmpty(l)) return -1;
   else return prodRecAux(l);
}


/****************************************************************/
Seq seqReadFromStream(istream& str)
{
    Seq s = EMPTY_SEQ;
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (e!= FINEINPUT)  // assumiamo che il segnale di fine input nel file sia il numero  FINEINPUT
       {
       insertElem(e, s);
       str>>e;
       if (!str) throw runtime_error("Errore inserimento dati\n");
       }
return s;
}

/****************************************************************/
Seq seqReadFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return seqReadFromStream(ifs);
}

/****************************************************************/
void seqPrint(const Seq& s)
{
   if (s != EMPTY_SEQ)
      {
      cout << s->head << " "; 
      seqPrint(s->tail);            
      }
}
