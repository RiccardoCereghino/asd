/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
// Cereghino Riccardo
// Ouerghi Sarah
// Martins Tobi Gbekeleoluwa
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctype.h>

#include "token.h"
#include "queue.h"
#include "stack.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;
/////////////////////////////////////////////////////////////////////
// Funzioni principali: leggi() e calcola()
/////////////////////////////////////////////////////////////////////


// Estrae uno dopo l'altro i token dalla stringa "str", inserendoli via via nella coda "codaToken"
bool leggi(const string &str, queue::Queue &codaToken) {
	bool b;
	token t;
	string s = str;

	do{
		b = prossimoToken(s, t);
		queue::enqueue(t, codaToken);
	}while(b);

	return (t.k != SCONOSCIUTO && s.size()==0);
}

// Estrae uno dopo l'altro i token dalla coda, inserendoli via via sullo stack.
// Appena si incontra un token PARENTESI CHIUSA, quello segnala la fine
// di una sottoespressione; allora tiriamo giu' dallo stack gli ultimi cinque token inseriti.
// I token estratti dovrebbero essere esattamente, nell'ordine:
// un ")", un numero, un operatore aritmetico, un altro
// numero, e un "("; se non è così, allora si segnala
// errore sintattico e l'algoritmo termina.
// A questo punto la funzione deve convertire i token di tipo NUMERO in numeri interi, 
// eseguire l'operazione aritmetica opportuna, e trasformare il risultato da numero a
// token e inserire quest'ultimo sullo stack.
// Alla fine se non ci sono errori sintattici la funzione deve mettere nella variabile
// risultato il vaore dell'espressione
bool calcola(queue::Queue codaToken, int &risultato) {
  stack::Stack s = stack::EMPTYSTACK;
  bool flag = false, f = true;
  token r;
  r.k = NUMERO;
  do{
    token t = queue::dequeue(codaToken);
    if(f && queue::isEmpty(codaToken)){
      risultato = str2int(t.val);
      return true;
    }
    else{
      f = false;
    }
    stack::push(t,s);
    if(t.k == PARENTESI_CHIUSA){
      try{
        token t4 = stack::pop(s);
        if( stack::isEmpty(s))
          throw false;

        token t3 = stack::pop(s);
        if(t3.k != NUMERO|| stack::isEmpty(s))
          throw false;

        token t2 = stack::pop(s);
        if(!(t2.k == OP_SOMMA || t2.k == OP_SOTTRAZIONE || t2.k == OP_MOLTIPLICAZIONE) || stack::isEmpty(s))
          throw false;

        token t1 = stack::pop(s);
        if(t1.k != NUMERO || stack::isEmpty(s))
          throw false;

        token t0 = stack::pop(s);
        if(t0.k != PARENTESI_APERTA)
          throw false;

        // Everything is OK, converting and calculating
        flag = true;
        switch(t2.k){
          case OP_SOMMA:
            r.val = int2str(str2int(t1.val) + str2int(t3.val));
            break;
          case OP_SOTTRAZIONE:
            r.val = int2str(str2int(t1.val) - str2int(t3.val));
            break;
          case OP_MOLTIPLICAZIONE:
            r.val = int2str(str2int(t1.val) * str2int(t3.val));
            break;
          default:
            break;
        }
        stack::push(r,s);
      }
      catch(bool b){
        flag = b;
      }
    }
  }while(!queue::isEmpty(codaToken));

  if(flag){
    token result = stack::pop(s);
  
    risultato = str2int(result.val);
  }
  return flag;
}

/////////////////////////////////////////////////////////////////////
//                               MAIN
/////////////////////////////////////////////////////////////////////

int main() {

  string s;
  queue::Queue q;
  int r;

  queue::createEmpty(q);

  cout << "Inserisci l'espressione che vuoi valutare:" << endl;
  getline(cin,s);

  if (!leggi(s,q)) {
    cout << "errore lessicale\n";
    exit(1);

  }

  if (!calcola(q,r)) {
    cout << "errore sintattico\n";
    exit(1);
  }

  cout << "risultato: " << r << "\n";
  exit(0);
}
